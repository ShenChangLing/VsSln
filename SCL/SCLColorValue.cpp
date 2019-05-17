#include "SCLPrerequisites.h"
#include "SCLColorValue.h"

namespace SCL
{
	ColorValue::ColorValue(float red, float green, float blue, float alpha)
		: r(red), g(green), b(blue), a(alpha)
	{
	}

	ColorValue::~ColorValue()
	{
	}
}