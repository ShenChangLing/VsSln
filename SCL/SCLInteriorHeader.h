#pragma once
#pragma warning(push)
#pragma warning(disable:4819)

//OPENGL库文件
#include <glad/glad.h>
#include <glfw3.h>

//图片库头文件
#include <FreeImage.h>

//字体库头文件
#include <ft2build.h>
#include FT_FREETYPE_H

//多媒体编码解码库头文件
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavutil/avutil.h>
#include <libswresample/swresample.h>
#include <libswscale/swscale.h>
}

//声音库头文件
#include <al.h>
#include <alc.h>

//数学库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//网络库头文件
#include <curl/curl.h>

//日志库头文件
#ifndef GOOGLE_GLOG_DLL_DECL
#define GOOGLE_GLOG_DLL_DECL
#endif

#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif

#include <glog/logging.h>

#ifndef SCL_LOGINFO
#define SCL_LOGINFO LOG(INFO)
#endif

#ifndef SCL_DLOGINFO
#define SCL_DLOGINFO DLOG(INFO)
#endif

#pragma warning(pop)
