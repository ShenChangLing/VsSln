#pragma once

namespace SCL
{
	typedef uint RGBA;

	class SCL_DLL ColorValue
	{
	public:
		ColorValue(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f);
		~ColorValue();

		RGBA toRGBA();

		float r, g, b, a;
	};
}
