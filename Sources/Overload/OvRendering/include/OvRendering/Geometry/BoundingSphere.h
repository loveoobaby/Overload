/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <OvMaths/FVector3.h>

namespace OvRendering::Geometry
{
	/**
	* Data structure that defines a bounding sphere (Position + radius)
	* 
	* ��Χ��
	*/
	struct BoundingSphere
	{
		OvMaths::FVector3 position; // ����
		float radius;  // �뾶
	};
}