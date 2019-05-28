#include "SCLPrerequisites.h"
#include "SCLInteriorHeader.h"

#include "glad.c"

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"freeimage.lib")

#pragma comment(lib,"freetype.lib")

#pragma comment(lib,"avformat.lib")

#pragma comment(lib,"OpenAL32.lib")

#pragma comment(lib,"assimp-vc140-mt.lib")

#pragma comment(lib,"libcurl.lib")

#ifdef _DEBUG
#pragma comment(lib,"glogd.lib")
#else
#pragma comment(lib,"glog.lib")
#endif

#ifdef WIN32
#pragma comment(lib,"WS2_32.LIB")
#endif
