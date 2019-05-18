// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#ifdef _WIN32

#ifdef SCL_EXPORTS
#define SCL_DLL __declspec( dllexport )
#else
#define SCL_DLL __declspec( dllimport )
#endif

#pragma warning(disable:4251)

#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>

// 在此处引用程序需要的其他标头
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include <algorithm>

#include <cassert>

#include "SCLVector.h"
#include "SCLMatrix.h"
#include "SCLQuaternion.h"

//多线程部分
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#define SCL_AUTO_LOCK_MUTEX_NAME mMutex
#define SCL_AUTO_MUTEX std::recursive_mutex SCL_AUTO_LOCK_MUTEX_NAME
#define SCL_AUTO_LOCK_MUTEX std::unique_lock<std::recursive_mutex> sclAutoLockMutex(SCL_AUTO_LOCK_MUTEX_NAME)
#define SCL_THREAD_SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

namespace SCL
{
	class Root;
	class Renderer;
	class RenderTarget;
	class Window;
	class Viewport;
	class Camera;
	class Image;
	class Texture2D;

	class ShaderProgram;
	class RendererStateCache;

	class Scene;

	class ColorValue;
	class ResourceManager;
	class Resource;
	class Mesh;
	class SubMesh;
	class MeshManager;
	class Entity;

	class SceneNode;
	class MovableObject;

	struct Vertex;
	class Quaternion;

	typedef std::string String;
	typedef unsigned int uint;
	typedef unsigned char uchar;

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Vector4<float> Vector4f;

	typedef Matrix<4, float> Matrix4f;

	typedef std::shared_ptr<Mesh> MeshPtr;
	typedef std::shared_ptr<Resource> ResourcePtr;

	typedef std::list<SceneNode*> SceneNodeList;

	class NetworkManager;
}

struct GLFWwindow;
