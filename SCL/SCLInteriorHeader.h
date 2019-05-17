#pragma once
#pragma warning(push)
#pragma warning(disable:4819)

#include <glad/glad.h>
#include <glfw3.h>

#include <FreeImage.h>

#include <ft2build.h>
#include FT_FREETYPE_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

#include <al.h>
#include <alc.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma warning(pop)
