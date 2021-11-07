#pragma once

#include "Worm/Rendering/Texture.h"

#include <filesystem>

namespace Worm {
	class OpenGLTexture : public Texture {
	public:
		OpenGLTexture(std::filesystem::path path);
		virtual ~OpenGLTexture() override;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind() const override;

		virtual uint32_t GetID() const override;
		virtual void LoadData(std::filesystem::path path) override;
		virtual TextureSpecification GetSpecification() override;
	private:
		uint32_t m_ID;
	};
}