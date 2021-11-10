#pragma once

#include "Worm/Core/Log.h"

namespace Worm {
	enum class ShaderType {
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		INT,
		INT2,
		INT3,
		INT4,
		MAT3,
		MAT4,
		BOOL
	};

	static unsigned int ShaderTypeSizeOf(ShaderType type) {
		switch (type)
		{
		case Worm::ShaderType::FLOAT:	return 4 * 1;
		case Worm::ShaderType::FLOAT2:	return 4 * 2;
		case Worm::ShaderType::FLOAT3:	return 4 * 3;
		case Worm::ShaderType::FLOAT4:	return 4 * 4;
		case Worm::ShaderType::INT:		return 4 * 1;
		case Worm::ShaderType::INT2:	return 4 * 2;
		case Worm::ShaderType::INT3:	return 4 * 3;
		case Worm::ShaderType::INT4:	return 4 * 4;
		case Worm::ShaderType::MAT3:	return 4 * 3 * 3;
		case Worm::ShaderType::MAT4:	return 4 * 4 * 4;
		case Worm::ShaderType::BOOL:	return 1 * 1;
		default:
			WORM_CORE_ASSERT(false, "Unknown ShaderType");
		}
	}
}