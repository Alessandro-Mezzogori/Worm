#include "wormpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Worm {
	OpenGLShader::OpenGLShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			WORM_LOG_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED {0}", infoLog);
		}

		// fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			WORM_LOG_CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED {0}", infoLog);
		}

		// link shaders
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);
		glLinkProgram(m_ID);

		// check for linking errors
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			WORM_LOG_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED {0}", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Activate() const
	{
		glUseProgram(m_ID);
	}

	int32_t OpenGLShader::GetUniformBlockBinding(std::string_view name) const
	{
		GLint result;
		GLuint block_index = glGetUniformBlockIndex(m_ID, name.data());
		glGetActiveUniformBlockiv(m_ID, block_index, GL_UNIFORM_BLOCK_BINDING, &result);

		return static_cast<int32_t>(result);
	}

	void OpenGLShader::LoadInt(std::string_view name, int value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniform1iv(location, 1, &value);
	}

	void OpenGLShader::LoadFloat(std::string_view name, float value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniform1fv(location, 1, &value);
	}

	void OpenGLShader::LoadFloat3(std::string_view name, glm::vec3 value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::LoadFloat4(std::string_view name, glm::vec4 value) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::LoadMat3(std::string_view name, glm::mat3 value, bool transpose) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniformMatrix3fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::LoadMat4(std::string_view name, glm::mat4 value, bool transpose) const
	{
		GLint location = glGetUniformLocation(m_ID, name.data());
		glUniformMatrix4fv(location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
	}

}