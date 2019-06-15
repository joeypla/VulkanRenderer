#include "Mesh.h"
#include "fbxsdk.h"
Mesh::Mesh()
{

}

bool Mesh::load(const std::string& path)
{
	// Just a quick testing load to make sure things are working
	/*MeshVertex m1;
	m1.pos.x = 0.0f;
	m1.pos.y = 100.0f;
	m1.pos.z = 100.0f;

	MeshVertex m2;
	m2.pos.x = -50.0f;
	m2.pos.y = 0.0f;
	m2.pos.z = 100.0f;

	MeshVertex m3;
	m3.pos.x = 50.0f;
	m3.pos.y = 0.0f;
	m3.pos.z = 100.0f;

	vertices.push_back(m1);
	vertices.push_back(m2);
	vertices.push_back(m3);

	setup();

	return true;*/
	// Create the FBX manager
	FbxManager* manager = FbxManager::Create();

	// Get the settings for loading our model
	FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	// Create the import manager and attempt to initialise with the file we want to load
	FbxImporter* importer = FbxImporter::Create(manager, "");
	bool initialised = importer->Initialize(path.c_str(), -1, manager->GetIOSettings());
	if (!initialised)
	{
			printf("Failed importer");
		return false; // failed
	}

	// Create an empty scene
	FbxScene* mScene = FbxScene::Create(manager, "tempScene");

	// Begin importing the data into the scene
	importer->Import(mScene);

	importer->Destroy();

	FbxNode* pFbxRootNode = mScene->GetRootNode();

	if (pFbxRootNode)
	{
		for (int i = 0; i < pFbxRootNode->GetChildCount(); i++)
		{
			FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);

			if (pFbxChildNode->GetNodeAttribute() == NULL)
				continue;

			FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

			if (AttributeType != FbxNodeAttribute::eMesh)
				continue;

			FbxMesh* pMesh = (FbxMesh*)pFbxChildNode->GetNodeAttribute();

			FbxVector4* pVertices = pMesh->GetControlPoints();

			for (int j = 0; j < pMesh->GetPolygonCount(); j++)
			{
				int iNumVertices = pMesh->GetPolygonSize(j);
				assert(iNumVertices == 3);

				for (int k = 0; k < iNumVertices; k++) {
					int iControlPointIndex = pMesh->GetPolygonVertex(j, k);

					MeshVertex vertex;
					vertex.pos.x = (float)pVertices[iControlPointIndex].mData[0];
					vertex.pos.y = (float)pVertices[iControlPointIndex].mData[2];
					vertex.pos.z = (float)pVertices[iControlPointIndex].mData[1];

					fbxsdk::FbxVector4 normal;
					pMesh->GetPolygonVertexNormal(j, k, normal);

					vertex.normal.x = (float)normal.mData[0];
					vertex.normal.y = (float)normal.mData[1];
					vertex.normal.z = (float)normal.mData[2];

					vertices.push_back(vertex);


				}
				
				

				
			}
		}
	}
	
	
	setup();
	return true;
}	

void Mesh::setup()
{
	// 1st attribute buffer : vertices
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), vertices.data(), GL_STATIC_DRAW);

	/* Vertex positions */
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(MeshVertex),                  // stride
		(void*)0            // array buffer offset
	);

	/* Vertex normals */
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		sizeof(MeshVertex),                  // stride
		(void*)offsetof(MeshVertex, normal)            // array buffer offset
	);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}