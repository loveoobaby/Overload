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
	* °üÎ§Çò
	*/
	struct BoundingSphere
	{
		OvMaths::FVector3 position; // ÇòÐÄ
		float radius;  // °ë¾¶
	};
}