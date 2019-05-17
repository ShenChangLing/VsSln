#include "SCLPrerequisites.h"
#include "SCLMesh.h"
#include "SCLSubMesh.h"
#include "SCLResource.h"

#include "SCLImage.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace SCL
{
	void _processMaterial(const aiMaterial* material, const aiScene* scene, const aiTextureType textureType)
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

	void _processMesh(const aiMesh* mesh, const aiScene* scene, SubMesh* sub_mesh)
	{
		//判断是否有法向量信息
		bool is_normal = mesh->HasNormals();
		bool is_vertexcolor = mesh->HasVertexColors(0);

		//顶点
		for (int i = 0; i < mesh->mNumVertices; ++i)
		{
			static Vector3f pos = Vector3f::ZERO;

			//位置
			pos.x = mesh->mVertices[i].x;
			pos.y = mesh->mVertices[i].y;
			pos.y = mesh->mVertices[i].z;

			//法线
			if (is_normal)
			{
				Vector3f normal(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
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
					Vector4f color(mesh->mColors[j][i].r, mesh->mColors[j][i].g, mesh->mColors[j][i].b, 1.0f);
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

	void _processNode(const aiNode* node, const aiScene* scene, Mesh* myMesh)
	{
		//处理当前节点的数据
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_processMesh(mesh, scene, myMesh->createSubMesh());
		}

		for (int i = 0; i < node->mNumChildren; ++i)
		{
			_processNode(node->mChildren[i], scene, myMesh);
		}
	}

	Mesh::Mesh(const String& name, const String& group)
		: Resource(name, group)
	{
		mSubMeshs.clear();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(name, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			return;
		}
		_processNode(scene->mRootNode, scene, this);

		importer.FreeScene();
	}

	Mesh::~Mesh()
	{
		destroyAllSubMesh();
	}

	SubMesh* Mesh::createSubMesh()
	{
		SubMesh* sm = new SubMesh(this);

		mSubMeshs.push_back(sm);

		return sm;
	}

	void Mesh::destroySubMesh(SubMesh* sub_mesh)
	{
		auto iter = mSubMeshs.begin();
		auto iterEnd = mSubMeshs.end();

		bool isFind = false;
		while (iter != iterEnd)
		{
			if (*iter == sub_mesh)
			{
				std::swap(*iter, mSubMeshs.back());
				isFind = true;
				break;
			}
			++iter;
		}
		if (isFind)
		{
			mSubMeshs.pop_back();
			delete sub_mesh;
			isFind = false;
		}
	}

	void Mesh::destroyAllSubMesh()
	{
		for (auto sub_mesh : mSubMeshs)
		{
			delete sub_mesh;
		}
		mSubMeshs.clear();
	}
}