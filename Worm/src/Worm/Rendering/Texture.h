#pragma once

#include <inttypes.h>
#include <filesystem>

namespace Worm {
	struct TextureSpecification {
		// texture filtering mag and min

		// texture wrapping x axis ( s )
		// texture wrapping y axis ( t )
		// texture wrapping z axis ( r )

		// border color -> used if clamped to border
	};

	class Texture{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind() const = 0;
	
		// Returns the ID of the texture 
		virtual uint32_t GetID() const = 0;
		// Loads to image binary data to RAM 
		virtual void LoadData(std::filesystem::path path) = 0;
		virtual TextureSpecification GetSpecification() = 0;
	public:
		static Shared<Texture> Create(std::filesystem::path path);
	};
}