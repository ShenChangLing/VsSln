#pragma once
#include "SCLPrerequisites.h"
#include "SCLResource.h"

namespace SCL
{
	class SCL_DLL Mesh : public Resource
	{
	public:
		Mesh(const String& name, const String& group);
		~Mesh();

		SubMesh* createSubMesh();
		void destroySubMesh(SubMesh* sub_mesh);
		void destroyAllSubMesh();

	protected:
		typedef std::vector<SubMesh*> SubMeshList;
	private:
		SubMeshList mSubMeshs;
	};
}
