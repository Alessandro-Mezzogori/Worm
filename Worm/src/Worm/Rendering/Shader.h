#pragma once

namespace Worm {
	class Shader {
	public:
		virtual ~Shader() = default;
		
		virtual void Activate() const = 0;
	};
}