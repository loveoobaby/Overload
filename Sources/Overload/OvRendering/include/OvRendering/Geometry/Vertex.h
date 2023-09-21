/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

namespace OvRendering::Geometry
{
	/**
	* Data structure that defines the geometry of a vertex
	* 
	* 顶点信息
	*/
	struct Vertex
	{
		float position[3]; // 顶点坐标
		float texCoords[2]; // 纹理坐标
		float normals[3];   // 法线
		float tangent[3];   // 切线
		float bitangent[3]; // 法线X切线，三者组成局部坐标系
	};
}