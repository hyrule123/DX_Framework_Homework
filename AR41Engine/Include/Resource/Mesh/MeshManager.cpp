
#include "MeshManager.h"
#include "SpriteMesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	// 기본 메쉬 생성 센터 중심, 좌하단 중심
	VertexColor	CenterColorMesh[4] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	unsigned int	RectIndex[6] = { 0, 1, 3, 0, 3, 2 };

	CreateMesh(nullptr, MeshType::Sprite, "CenterColorRect",
		CenterColorMesh, sizeof(VertexColor), 4, D3D11_USAGE_IMMUTABLE,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex,
		4, 6, D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);

	VertexColor	LBColorMesh[4] =
	{
		VertexColor(Vector3(0.f, 1.f, 0.f), Vector4::Red),
		VertexColor(Vector3(1.f, 1.f, 0.f), Vector4::Green),
		VertexColor(Vector3(0.f, 0.f, 0.f), Vector4::Blue),
		VertexColor(Vector3(1.f, 0.f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f))
	};

	CreateMesh(nullptr, MeshType::Sprite, "LBColorRect",
		LBColorMesh, sizeof(VertexColor), 4, D3D11_USAGE_IMMUTABLE,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIndex,
		4, 6, D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);


	//집 모양의 메쉬 생성
	VertexColor	ArrowMesh[5] =
	{
		VertexColor(Vector3(-0.5f, 0.5f, 0.f), Vector4::Red),
		VertexColor(Vector3(0.5f, 0.5f, 0.f), Vector4::Green),
		VertexColor(Vector3(-0.5f, -0.5f, 0.f), Vector4::Blue),
		VertexColor(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 1.f, 1.f)),
		VertexColor(Vector3(0.f, 1.f, 0.f), Vector4(0.f, 1.f, 1.f, 1.f))
	};

	unsigned int	ArrowMeshIndex[9] = { 0, 1, 3, 0, 3, 2, 0, 4, 1 };

	CreateMesh(nullptr, MeshType::Sprite, "ArrowShape",
		ArrowMesh, sizeof(VertexColor), 5, D3D11_USAGE_IMMUTABLE,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, ArrowMeshIndex, 4, 9, D3D11_USAGE_IMMUTABLE, DXGI_FORMAT_R32_UINT);


	return true;
}

bool CMeshManager::CreateMesh(CScene* Scene, MeshType Type, const std::string& Name,
	void* VtxData, int Size, int Count, D3D11_USAGE VtxUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IdxData, int IdxSize, 
	int IdxCount, D3D11_USAGE IdxUsage, DXGI_FORMAT Fmt)
{
	if (FindMesh(Name))
		return true;

	CMesh* Mesh = nullptr;

	switch (Type)
	{
	case MeshType::Sprite:
		Mesh = new CSpriteMesh;
		break;
	case MeshType::UI:
		break;
	case MeshType::Static:
		break;
	case MeshType::Animation:
		break;
	}

	Mesh->SetScene(Scene);
	Mesh->SetName(Name);

	if (!Mesh->CreateMesh(VtxData, Size, Count, VtxUsage, Primitive,
		IdxData, IdxSize, IdxCount, IdxUsage, Fmt))
	{
		SAFE_RELEASE(Mesh);
		return false;
	}

	m_mapMesh.insert(std::make_pair(Name, Mesh));

	return true;
}

CMesh* CMeshManager::FindMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter == m_mapMesh.end())
		return nullptr;

	return iter->second;
}

void CMeshManager::ReleaseMesh(const std::string& Name)
{
	auto	iter = m_mapMesh.find(Name);

	if (iter != m_mapMesh.end())
	{
		if (iter->second->GetRefCount() == 1)
			m_mapMesh.erase(iter);
	}
}
