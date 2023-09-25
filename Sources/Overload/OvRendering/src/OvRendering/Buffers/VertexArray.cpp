/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvRendering/Buffers/VertexArray.h"

OvRendering::Buffers::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_bufferID);
	glBindVertexArray(m_bufferID);
}

OvRendering::Buffers::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_bufferID);
}

// 绑定VAO
void OvRendering::Buffers::VertexArray::Bind()
{
	glBindVertexArray(m_bufferID);
}

// 解绑VAO
void OvRendering::Buffers::VertexArray::Unbind()
{
	glBindVertexArray(0);
}

// 获取VAO的id
GLint OvRendering::Buffers::VertexArray::GetID()
{
	return m_bufferID;
}
