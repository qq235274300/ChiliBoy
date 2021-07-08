#include "DynamicMeshOBJReader.h"
#include "DynamicMeshAttributeSet.h"
#include "tinyobj/tiny_obj_loader.h"
#include <fstream>
#include <Misc/Paths.h>
#include <algorithm>
#include <cctype>
#include <DebugHelper.h>

#pragma region tiny_objStruct
// Vertex attributes

//struct attrib_t {
//	std::vector<real_t> vertices;  // 'v'(xyz)
//
//	// For backward compatibility, we store vertex weight in separate array.
//	std::vector<real_t> vertex_weights;  // 'v'(w)
//	std::vector<real_t> normals;         // 'vn'
//	std::vector<real_t> texcoords;       // 'vt'(uv)
//
//	// For backward compatibility, we store texture coordinate 'w' in separate
//	// array.
//	std::vector<real_t> texcoord_ws;  // 'vt'(w)
//	std::vector<real_t> colors;       // extension: vertex colors
//
//	//
//	// TinyObj extension.
//	//
//
//	// NOTE(syoyo): array index is based on the appearance order.
//	// To get a corresponding skin weight for a specific vertex id `vid`,
//	// Need to reconstruct a look up table: `skin_weight_t::vertex_id` == `vid`
//	// (e.g. using std::map, std::unordered_map)
//	std::vector<skin_weight_t> skin_weights;
//
//	attrib_t() {}
//
//	//
//	// For pybind11
//	//
//	const std::vector<real_t> &GetVertices() const { return vertices; }
//
//	const std::vector<real_t> &GetVertexWeights() const { return vertex_weights; }
//};
//
//struct shape_t {
//	std::string name;
//	mesh_t mesh;
//	lines_t lines;
//	points_t points;
//};


#pragma endregion




bool RTGUtils::ReadOBJMesh(
	const FString& Path,
	FDynamicMesh3& MeshOut,
	bool bNormals,
	bool bTexCoords,
	bool bVertexColors,
	bool bReverseOrientation)
{
	std::string inputfile(TCHAR_TO_UTF8(*Path));
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!warn.empty()) {
		UE_LOG(LogTemp, Display, TEXT("%s"), warn.c_str());
	}

	if (!err.empty()) {
		UE_LOG(LogTemp, Display, TEXT("%s"), err.c_str());
	}

	if (!ret) {
		return false;
	}

	// append vertices
	for (size_t vi = 0; vi < attrib.vertices.size() / 3; ++vi)
	{
		tinyobj::real_t vx = attrib.vertices[3 * vi + 0];
		tinyobj::real_t vy = attrib.vertices[3 * vi + 1];
		tinyobj::real_t vz = attrib.vertices[3 * vi + 2];

		MeshOut.AppendVertex(FVector3d(vx, vy, vz));
	}


	if (bVertexColors)
	{
		MeshOut.EnableVertexColors(FVector3f::Zero());
		for (size_t vi = 0; vi < attrib.vertices.size() / 3; ++vi)
		{
			tinyobj::real_t r = attrib.colors[3 * vi + 0];
			tinyobj::real_t g = attrib.colors[3 * vi + 1];
			tinyobj::real_t b = attrib.colors[3 * vi + 2];

			MeshOut.SetVertexColor(vi, FVector3f((float)r, (float)g, (float)b));
		}
	}

	if (bNormals || bTexCoords)
	{
		MeshOut.EnableAttributes();
	}
	FDynamicMeshNormalOverlay* Normals = (bNormals) ? MeshOut.Attributes()->PrimaryNormals() : nullptr;
	FDynamicMeshUVOverlay* UVs = (bTexCoords) ? MeshOut.Attributes()->PrimaryUV() : nullptr;
	if (Normals)
	{
		for (size_t ni = 0; ni < attrib.normals.size() / 3; ++ni)
		{
			tinyobj::real_t nx = attrib.normals[3 * ni + 0];
			tinyobj::real_t ny = attrib.normals[3 * ni + 1];
			tinyobj::real_t nz = attrib.normals[3 * ni + 2];

			Normals->AppendElement(FVector3f((float)nx, (float)ny, (float)nz));
		}
	}
	if (UVs)
	{
		for (size_t ti = 0; ti < attrib.texcoords.size() / 2; ++ti)
		{
			tinyobj::real_t tx = attrib.texcoords[2 * ti + 0];
			tinyobj::real_t ty = attrib.texcoords[2 * ti + 1];

			UVs->AppendElement(FVector2f((float)tx, (float)ty));
		}
	}

	// append faces as triangles
	for (size_t s = 0; s < shapes.size(); s++) {	// Loop over shapes

		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {	// Loop over faces(polygon)
			int fv = shapes[s].mesh.num_face_vertices[f];

			TArray<FIndex3i> Triangles;
			for (size_t v = 1; v < fv - 1; v++)
			{
				Triangles.Add(FIndex3i(0, v, v + 1));
			}

			int32 NumTris = Triangles.Num();
			for (int32 ti = 0; ti < NumTris; ++ti)
			{
				FIndex3i TriVerts = Triangles[ti];
				tinyobj::index_t idx0 = shapes[s].mesh.indices[index_offset + TriVerts.A];
				tinyobj::index_t idx1 = shapes[s].mesh.indices[index_offset + TriVerts.B];
				tinyobj::index_t idx2 = shapes[s].mesh.indices[index_offset + TriVerts.C];

				int32 tid = MeshOut.AppendTriangle(idx0.vertex_index, idx1.vertex_index, idx2.vertex_index);

				if (Normals && Normals->IsElement(idx0.normal_index) && Normals->IsElement(idx1.normal_index) && Normals->IsElement(idx2.normal_index))
				{
					Normals->SetTriangle(tid, FIndex3i(idx0.normal_index, idx1.normal_index, idx2.normal_index));
				}
				if (UVs && UVs->IsElement(idx0.texcoord_index) && UVs->IsElement(idx1.texcoord_index) && UVs->IsElement(idx2.texcoord_index))
				{
					UVs->SetTriangle(tid, FIndex3i(idx0.texcoord_index, idx1.texcoord_index, idx2.texcoord_index));
				}
			}

			index_offset += fv;

			// per-face material
			//shapes[s].mesh.material_ids[f];
		}
	}

	if (bReverseOrientation)
	{
		MeshOut.ReverseOrientation();
	}

	return true;
}

RUNTIMEGEOMETRYUTILS_API bool RTGUtils::LoadSimpleObj(const FString& fileName, FDynamicMesh3& MeshOut, bool flip /*= false*/,bool bVcolor/*= false*/, bool bNormal /*= false*/, bool bUV /*= false*/ )
{
	if (!FPaths::FileExists(fileName))
	{
		DebugHelper::Count() << fileName << "-->file do not exists" << DebugHelper::Endl();
		return false;
	}
	//判断DrawOrder  ccw  counter-ccw
	std::string filename = std::string(TCHAR_TO_UTF8(*fileName));
	std::ifstream file(filename);
	std::string firstLine;
	std::getline(file, firstLine);
	std::transform(firstLine.begin(), firstLine.end(), firstLine.begin(), std::tolower);
	bool CCW = false;
	if (firstLine.find("ccw") != std::string::npos)
	{
		CCW = true;
	}

	using namespace tinyobj;
	bool loadstate = false;
	attrib_t attribs;
	std::vector<shape_t> shapes;
	std::vector<material_t> materials;
	std::string warn;
	std::string error;

	loadstate = LoadObj(&attribs, &shapes, nullptr, &warn, &error, filename.c_str());
	if (!warn.empty())
	{
		DebugHelper::Count() << fileName << "warns -- > " << warn.c_str() << DebugHelper::Endl();
	}
	if (!error.empty())
	{
		DebugHelper::Count() << fileName << "error -- > " << error.c_str() << DebugHelper::Endl();
	}
	if (!loadstate)
	{
		DebugHelper::Count() << fileName << "-->file load faied" << DebugHelper::Endl();
		return false;
	}
	//读取Vertices  
	const auto vertices = attribs.vertices;
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		MeshOut.AppendVertex(FVector3d(
			vertices[i + 0],
			vertices[i + 1],
			vertices[i + 2]
		));

	};
	//Color
	if (bVcolor)
	{
		MeshOut.EnableVertexColors(FVector3f::Zero());
	}
	const auto colors = attribs.colors;
	for (size_t i = 0; i < vertices.size(); i += 3)
	{
		const int vId = i / 3;
		MeshOut.SetVertexColor(vId, FVector3f(
			(float)colors[i + 0],
			(float)colors[i + 1],
			(float)colors[i + 2]
		));		
	};
	//Normal & UV
	FDynamicMeshNormalOverlay* NormalAttrib = nullptr;
	FDynamicMeshUVOverlay* UVAttrib = nullptr;
	if (bNormal || bUV)
	{
		MeshOut.EnableAttributes();
	}
	if (bNormal)
	{
		 NormalAttrib =  MeshOut.Attributes()->PrimaryNormals();
		const auto normals = attribs.normals;
		for (size_t i = 0; i < normals.size(); i += 3)
		{
			NormalAttrib->AppendElement(
				FVector3f(
					(float)normals[i + 0],
					(float)normals[i + 1],
					(float)normals[i + 2]
				)
			);
		}

		
	}
	if (bUV)
	{
		  UVAttrib = MeshOut.Attributes()->PrimaryUV();
		const auto uvs = attribs.texcoords;
		for (size_t i = 0; i < uvs.size(); i += 2)
		{
			UVAttrib->AppendElement(
				FVector2f(
					(float)uvs[i + 0],
					(float)uvs[i + 1]
				)
			);
		}
	}


	
	//读取shape 一个Obj文件有多个 我们只读一个
	//mesh_t mesh = shapes[0].mesh;
	//Ok we do more
	for (size_t i = 0; i < shapes.size(); ++i)
	{
		const mesh_t mesh = shapes[i].mesh;
		auto faces = mesh.num_face_vertices;
		for (size_t f = 0; f < faces.size(); ++f)
		{
			if (faces[f] != 3u)
			{
				DebugHelper::Count() << fileName << "obj face is not a Triangle" << DebugHelper::Endl();
				return false;
			}

			index_t Index0 = mesh.indices[f * 3u + 0];
			index_t Index1 = mesh.indices[f * 3u + 1];
			index_t Index2 = mesh.indices[f * 3u + 2];


			int32 tid = MeshOut.AppendTriangle(Index0.vertex_index, Index1.vertex_index, Index2.vertex_index);

			if (NormalAttrib && NormalAttrib->IsElement(Index0.normal_index) && NormalAttrib->IsElement(Index1.normal_index) && NormalAttrib->IsElement(Index2.normal_index))
			{
				NormalAttrib->SetTriangle(tid, FIndex3i(Index0.normal_index, Index1.normal_index, Index2.normal_index));
			}
			if (UVAttrib && UVAttrib->IsElement(Index0.texcoord_index) && UVAttrib->IsElement(Index1.texcoord_index) && UVAttrib->IsElement(Index2.texcoord_index))
			{
				UVAttrib->SetTriangle(tid, FIndex3i(Index0.texcoord_index, Index1.texcoord_index, Index2.texcoord_index));
			}
		}
	}

	if (flip)
	{
		MeshOut.ReverseOrientation();
	}

	return true;
}

