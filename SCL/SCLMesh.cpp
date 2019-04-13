#include "SCLPrerequisites.h"
#include "SCLMesh.h"
#include "SCLResource.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace SCL
{
	void _processMaterial(const aiMaterial* material,const aiScene* scene,const aiTextureType textureType)
	{
		int textureCount = material->GetTextureCount(textureType);
		if (textureCount <= 0)
		{
			return;
		}

		//获取纹理图片
		for (int i = 0; i < textureCount; ++i)
		{
			
			aiString texturePath;
			if (material->GetTexture(textureType, i, &texturePath) == AI_SUCCESS)
			{
				OutputDebugString(texturePath.C_Str());
			}
			
		}
	}

	void _processMesh(const aiMesh* mesh, const aiScene* scene)
	{
		//顶点
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			//位置
			if (mesh->HasPositions())
			{
				Vector3f pos;
				pos.x = mesh->mVertices[i].x;
				pos.y = mesh->mVertices[i].y;
				pos.y = mesh->mVertices[i].z;
			}

			//法线
			if (mesh->HasNormals())
			{
				Vector3f normal;
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;
			}
			//纹理
			for (int j = 0; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++j)
			{
				if (mesh->HasTextureCoords(j))
				{
					Vector2f texturecoord;
					texturecoord.x = mesh->mTextureCoords[j][i].x;
					texturecoord.y = mesh->mTextureCoords[j][i].y;
				}
				else
					break;
			}
			//颜色
			for (int j = 0; j < AI_MAX_NUMBER_OF_COLOR_SETS; ++j)
			{
				if (mesh->HasVertexColors(j))
				{
					Vector4f color;
					color.x = mesh->mColors[j][i].r;
					color.y = mesh->mColors[j][i].g;
					color.z = mesh->mColors[j][i].b;
				}
				else
					break;
			}
		}
		//索引
		for (int i = 0; i < mesh->mNumFaces; ++i)
		{
			const aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; ++j)
			{
				auto index = face.mIndices[j];
			}
		}

		//材质
		if (scene->HasMaterials())
		{
			if (mesh->mMaterialIndex >= 0)
			{
				const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				_processMaterial(material, scene, aiTextureType_DIFFUSE);
				_processMaterial(material, scene, aiTextureType_SPECULAR);
			}
		}
	}

	void _processNode(const aiNode* node, const aiScene* scene)
	{
		//处理当前节点的数据
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_processMesh(mesh, scene);
		}

		for (int i = 0; i < node->mNumChildren; ++i)
		{
			_processNode(node->mChildren[i], scene);
		}
	}

	Mesh::Mesh(const String& name, const String& group)
		: Resource(name, group)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			return;
		}
		_processNode(scene->mRootNode, scene);
	}


	Mesh::~Mesh()
	{
	}
}
