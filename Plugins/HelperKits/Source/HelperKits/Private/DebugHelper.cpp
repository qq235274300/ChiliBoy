// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHelper.h"
//#include "DynamicMesh3.h"
//#include "DynamicMeshAttributeSet.h"
//#include "RuntimeGeometryUtils/Private/tinyobj/tiny_obj_loader.h"
//#include <fstream>
//#include <Misc/Paths.h>
//#include <algorithm>
//#include <cctype>

//
//bool OBJLOAD::LoadMeshFromFile(const FString& fileName,FDynamicMesh3& MeshOut)
//{
//	if (!FPaths::FileExists(fileName))
//	{
//		DebugHelper::Count() << fileName << "-->file do not exists" << DebugHelper::Endl();
//		return false;
//	}
//	std::string filename = std::string(TCHAR_TO_UTF8(*fileName));
//	std::ifstream file(filename);
//	std::string firstLine;
//	std::getline(file,firstLine);
//	std::transform(firstLine.begin(), firstLine.end(), firstLine.begin(),std::tolower);
//	bool CCW = false;
//	if (firstLine.find("ccw") != std::string::npos)
//	{
//		CCW = true;
//	}
//
//	using namespace tinyobj;
//	bool loadstate = false;
//	attrib_t attribs;
//	std::vector<shape_t> shapes;
//	std::vector<material_t> materials;
//	std::string warn;
//	std::string error;
//	//tinyobj::LoadObj(&attribs, &shapes,&materials, &warn, &error,filename.c_str());
//	/*if (!warn.empty())
//	{
//		DebugHelper::Count() << fileName << "warns -- > "<< warn.c_str() << DebugHelper::Endl();
//	}
//	if (!error.empty())
//	{
//		DebugHelper::Count() << fileName << "error -- > " << error.c_str() << DebugHelper::Endl();
//	}
//	if (!loadstate)
//	{
//		DebugHelper::Count() << fileName << "-->file load faied" << DebugHelper::Endl();
//		return false;
//	}*/
//	
//
//
//	const auto vertices = attribs.vertices;
//	//for (size_t i = 0; i < vertices.size(); i++3u)
//	//{
//	//	/*MeshOut.AppendVertex(
//	//		FVector3d
//	//		(
//	//			vertices[i + 0u],
//	//			vertices[i + 1u],
//	//			vertices[i + 2u]
//	//		)
//	//	);*/
//	//	
//	//};
//
//
//
//
//	return false;
//};
