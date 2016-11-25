#include <map>
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk.lib")

#define UTINY_API __declspec(dllexport)

#include "../include/GameObject.h"
#include "../include/Renderer.h"
#include "../include/Scene.h"

class FbxModelLoader
{
public:

	FbxManager* pManager;
	FbxIOSettings* pIOSettings;
	FbxImporter* pImporter;
	FbxScene* pScene;

	int ImportFbxFile(const char* filename);

	void Init();
	void Print();
};

void FbxModelLoader::Init()
{
	pManager = FbxManager::Create();
	pIOSettings = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(pIOSettings);
	pImporter = FbxImporter::Create(pManager, "");
}

int FbxModelLoader::ImportFbxFile(const char * filename)
{
	if (!pImporter->Initialize(filename, -1, pManager->GetIOSettings())) {
		printf("Error on FbxImporter::Initialize: %s\n\n", pImporter->GetStatus().GetErrorString());
		return -1;
	}

	pScene = FbxScene::Create(pManager, "Scene");
	pImporter->Import(pScene);
	pImporter->Destroy();

	return 0;
}

void PrintNode(FbxNode* pNode);
void FbxModelLoader::Print()
{
	FbxNode* pRootNode = pScene->GetRootNode();
	for (int i = 0;i < pRootNode->GetChildCount();i++)
	{
		PrintNode(pRootNode->GetChild(i));
	}

}
//--------------------------------------------------------------------------------------
//                                    Depended Functions
//--------------------------------------------------------------------------------------
#pragma region Depended Functions

/* Tab character ("\t") counter */
int numTabs = 0;

/**
* Print the required number of tabs.
*/
void PrintTabs() {
	for (int i = 0; i < numTabs; i++)
		printf("\t");
}

/**
* Return a string-based representation based on the attribute type.
*/

FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) {
	switch (type) {
	case FbxNodeAttribute::eUnknown: return "unidentified";
	case FbxNodeAttribute::eNull: return "null";
	case FbxNodeAttribute::eMarker: return "marker";
	case FbxNodeAttribute::eSkeleton: return "skeleton";
	case FbxNodeAttribute::eMesh: return "mesh";
	case FbxNodeAttribute::eNurbs: return "nurbs";
	case FbxNodeAttribute::ePatch: return "patch";
	case FbxNodeAttribute::eCamera: return "camera";
	case FbxNodeAttribute::eCameraStereo: return "stereo";
	case FbxNodeAttribute::eCameraSwitcher: return "camera switcher";
	case FbxNodeAttribute::eLight: return "light";
	case FbxNodeAttribute::eOpticalReference: return "optical reference";
	case FbxNodeAttribute::eOpticalMarker: return "marker";
	case FbxNodeAttribute::eNurbsCurve: return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary: return "boundary";
	case FbxNodeAttribute::eNurbsSurface: return "nurbs surface";
	case FbxNodeAttribute::eShape: return "shape";
	case FbxNodeAttribute::eLODGroup: return "lodgroup";
	case FbxNodeAttribute::eSubDiv: return "subdiv";
	default: return "unknown";
	}
}

/**
* Print an attribute.
*/
void PrintAttribute(FbxNodeAttribute* pAttribute) {
	if (!pAttribute) return;

	FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
	FbxString attrName = pAttribute->GetName();
	PrintTabs();
	// Note: to retrieve the character array of a FbxString, use its Buffer() method.
	printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}

/**
* Print a node, its attributes, and all its children recursively.
*/

void PrintNode(FbxNode* pNode) {
	PrintTabs();
	const char* nodeName = pNode->GetName();
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	// Print the contents of the node.
	printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
		nodeName,
		translation[0], translation[1], translation[2],
		rotation[0], rotation[1], rotation[2],
		scaling[0], scaling[1], scaling[2]
	);
	numTabs++;

	// Print the node's attributes.
	for (int i = 0; i < pNode->GetNodeAttributeCount(); i++)
		PrintAttribute(pNode->GetNodeAttributeByIndex(i));

	// Recursively print the children.
	for (int j = 0; j < pNode->GetChildCount(); j++)
		PrintNode(pNode->GetChild(j));

	numTabs--;
	PrintTabs();
	printf("</node>\n");

}



void ReadVertex(FbxMesh* pMesh, int ctrlPointIndex, float* pVertex)
{
	FbxVector4* pCtrlPoint = pMesh->GetControlPoints();
	pVertex[0] = (float)pCtrlPoint[ctrlPointIndex][0];
	pVertex[1] = (float)pCtrlPoint[ctrlPointIndex][1];
	pVertex[2] = (float)pCtrlPoint[ctrlPointIndex][2];
}

void ReadUV(FbxMesh* pMesh, int ctrlPointIndex, int textureUVIndex, int uvLayer, float* pUV)
{
	if (uvLayer >= 2 || pMesh->GetElementUVCount() <= uvLayer)
	{
		//return false;
		return;
	}

	FbxGeometryElementUV* pVertexUV = pMesh->GetElementUV(uvLayer);

	switch (pVertexUV->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
	{
		switch (pVertexUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			pUV[0] = (float)pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[0];
			pUV[1] = (float)pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[1];
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int id = pVertexUV->GetIndexArray().GetAt(ctrlPointIndex);
			pUV[0] = (float)pVertexUV->GetDirectArray().GetAt(id)[0];
			pUV[1] = (float)pVertexUV->GetDirectArray().GetAt(id)[1];
		}
		break;

		default:
			break;
		}
	}
	break;

	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (pVertexUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		case FbxGeometryElement::eIndexToDirect:
		{
			pUV[0] = (float)pVertexUV->GetDirectArray().GetAt(textureUVIndex)[0];
			pUV[1] = (float)pVertexUV->GetDirectArray().GetAt(textureUVIndex)[1];
		}
		break;

		default:
			break;
		}
	}
	break;
	}
}

void ReadNormal(FbxMesh* pMesh, int ctrlPointIndex, int vertexCounter, float* pNormal)
{
	if (pMesh->GetElementNormalCount() < 1)
	{
		return;
	}

	FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(0);
	switch (leNormal->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
	{
		switch (leNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			pNormal[0] = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[0];
			pNormal[1] = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[1];
			pNormal[2] = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[2];
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int id = leNormal->GetIndexArray().GetAt(ctrlPointIndex);
			pNormal[0] = (float)leNormal->GetDirectArray().GetAt(id)[0];
			pNormal[1] = (float)leNormal->GetDirectArray().GetAt(id)[1];
			pNormal[2] = (float)leNormal->GetDirectArray().GetAt(id)[2];
		}
		break;

		default:
			break;
		}
	}
	break;

	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (leNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			pNormal[0] = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[0];
			pNormal[1] = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[1];
			pNormal[2] = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[2];
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int id = leNormal->GetIndexArray().GetAt(vertexCounter);
			pNormal[0] = (float)leNormal->GetDirectArray().GetAt(id)[0];
			pNormal[1] = (float)leNormal->GetDirectArray().GetAt(id)[1];
			pNormal[2] = (float)leNormal->GetDirectArray().GetAt(id)[2];
		}
		break;

		default:
			break;
		}
	}
	break;
	}
}

#pragma endregion


Transform GetNodeTransform(FbxNode* pNode) {
	FbxDouble3 translation = pNode->LclTranslation.Get();
	FbxDouble3 rotation = pNode->LclRotation.Get();
	FbxDouble3 scaling = pNode->LclScaling.Get();

	Transform t;
	
	t.translation.x = translation[0];
	t.translation.y = translation[1];
	t.translation.z = translation[2];

	t.rotation.x = rotation[0];
	t.rotation.y = rotation[1];
	t.rotation.z = rotation[2];

	t.scale.x = scaling[0];
	t.scale.y = scaling[1];
	t.scale.z = scaling[2];

	return t;
}

VertexFormat* GetNodeMeshData(FbxNode* pNode, int& datasize) {
	auto attr = pNode->GetNodeAttribute();
	if (!attr) return NULL;

	auto type = attr->GetAttributeType();

	if (type == FbxNodeAttribute::eMesh) {
		FbxMesh* pMesh = pNode->GetMesh();
		int triangleCount = pMesh->GetPolygonCount();


		int n = 0;
		VertexFormat* buffer = (VertexFormat*)malloc(sizeof(VertexFormat)*triangleCount * 3);
		for (int i = 0;i < triangleCount;i++) {
			for (int j = 0;j < 3;j++) {
				int ctrlPointIndex = pMesh->GetPolygonVertex(i, j);
				ReadVertex(pMesh, ctrlPointIndex, buffer[n].Position);
				ReadUV(pMesh, ctrlPointIndex, pMesh->GetTextureUVIndex(i, j), 0, buffer[n].UV);
				ReadNormal(pMesh, ctrlPointIndex, n, buffer[n].Normal);
				n++;
			}
		}
		datasize = n * sizeof(VertexFormat);
		return buffer;
	}
	datasize = 0;
	return NULL;
}

void AssignNode(GameObject& outnode, FbxNode* pNode) {
	outnode.name = pNode->GetName();
	
	*outnode.GetComponent<Transform>() = GetNodeTransform(pNode);

	void* pData = NULL;
	int dataSize = 0;

	Mesh* mesh = NULL;
	
	if (!pNode->GetNodeAttribute()) 
		return;
	auto type = pNode->GetNodeAttribute()->GetAttributeType();

	switch (type)
	{
	case fbxsdk::FbxNodeAttribute::eUnknown:
	
		break;
	case fbxsdk::FbxNodeAttribute::eNull:
		break;
	case fbxsdk::FbxNodeAttribute::eMarker:
		break;
	case fbxsdk::FbxNodeAttribute::eSkeleton:
		break;
	case fbxsdk::FbxNodeAttribute::eMesh:
		///Get node mesh data
		///return:
		///	datasize		data byte-length, reference in parameter
		///	vertex buffer	data start address
		
		pData = GetNodeMeshData(pNode, dataSize);
		mesh = new Mesh;
		mesh->SetMeshData(pData, dataSize / (sizeof(VertexFormat) * 3));
		outnode.AddComponent(mesh);
		outnode.AddComponent(new Renderer);


		break;
	case fbxsdk::FbxNodeAttribute::eNurbs:
		break;
	case fbxsdk::FbxNodeAttribute::ePatch:
		break;
	case fbxsdk::FbxNodeAttribute::eCamera:
		break;
	case fbxsdk::FbxNodeAttribute::eCameraStereo:
		break;
	case fbxsdk::FbxNodeAttribute::eCameraSwitcher:
		break;
	case fbxsdk::FbxNodeAttribute::eLight:
		break;
	case fbxsdk::FbxNodeAttribute::eOpticalReference:
		break;
	case fbxsdk::FbxNodeAttribute::eOpticalMarker:
		break;
	case fbxsdk::FbxNodeAttribute::eNurbsCurve:
		break;
	case fbxsdk::FbxNodeAttribute::eTrimNurbsSurface:
		break;
	case fbxsdk::FbxNodeAttribute::eBoundary:
		break;
	case fbxsdk::FbxNodeAttribute::eNurbsSurface:
		break;
	case fbxsdk::FbxNodeAttribute::eShape:
		break;
	case fbxsdk::FbxNodeAttribute::eLODGroup:
		break;
	case fbxsdk::FbxNodeAttribute::eSubDiv:
		break;
	case fbxsdk::FbxNodeAttribute::eCachedEffect:
		break;
	case fbxsdk::FbxNodeAttribute::eLine:
		break;
	default:
		break;
	}

}

void ProcessFbxNode(FbxNode* pNode,GameObject* root)
{
	for (int i = 0;i < pNode->GetChildCount();i++) {
		
		GameObject* obj = new GameObject();
		AssignNode(*obj, pNode->GetChild(i));
		root->AddChild(obj);

		ProcessFbxNode(pNode->GetChild(i), obj);
	}
}

int Scene::LoadModel(const char* filename, GameObject* parent) {
	FbxModelLoader loader;
	loader.Init();
	if (loader.ImportFbxFile(filename) != 0) { return -1; }
	FbxNode* pNode = loader.pScene->GetRootNode();
	//PrintNode(pNode);

	if (parent == NULL)
		parent = this;
	ProcessFbxNode(pNode,parent);
	return 0;
}