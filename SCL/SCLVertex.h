#pragma once
#include "SCLPrerequisites.h"

namespace SCL
{
	//顶点
	struct SCL_DLL Vertex
	{
		//
	};

	//顶点
	struct SCL_DLL Vertex_Position3f_Color4f_TextureCoord : public Vertex
	{
		Vector3f position;
		Vector4f color;
		Vector2f textureCoord;

		Vertex_Position3f_Color4f_TextureCoord()
			: position(0, 0, 0),
			color(0, 0, 0, 0),
			textureCoord(0, 0)
		{
			//
		}
	};

	struct SCL_DLL Vertex_Position3f_TextureCoord : public Vertex
	{
		Vector3f position;
		Vector2f textureCoord;

		Vertex_Position3f_TextureCoord() :
			position(0, 0, 0),
			textureCoord(0, 0)
		{
			//
		}
	};
}
