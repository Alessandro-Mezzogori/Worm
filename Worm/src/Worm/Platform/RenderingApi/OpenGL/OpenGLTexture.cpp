#include "wormpch.h"
#include "OpenGLTexture.h"

#include "Worm/Core/Log.h"

#include <glad/glad.h>

#include <stb_image.h>

namespace Worm{

    OpenGLTexture::OpenGLTexture(std::filesystem::path path) {
        // Generate the OpenGL Texture Object and bind it
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        
        // TODO do something with the TextureSpecifications
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        LoadData(path);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_ID);
    }

    void OpenGLTexture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    void OpenGLTexture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t OpenGLTexture::GetID() const
    {
        return m_ID;
    }

    void OpenGLTexture::LoadData(std::filesystem::path path)
    {
        int width, height, numChannels;
        // Load the texture data
        uint8_t* data = stbi_load(path.string().c_str(), &width, &height, &numChannels, 0);

        if (data == nullptr) {
            WORM_LOG_CORE_ERROR("TEXTURE LOADING ERROR | path: {0}", path.string());
        }

        GLenum format = GL_RGB;
        switch (numChannels) {
            case 1: format = GL_RED;    break;
            case 2: format = GL_RG;     break;
            case 3: format = GL_RGB;    break;
            case 4: format = GL_RGBA;   break;
        }

        // Load the texture data to the OpenGL Texture Object
        glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
     
        stbi_image_free(data);
    }

    TextureSpecification OpenGLTexture::GetSpecification()
    {
        return TextureSpecification();
    }

}