/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GL/glew.h>

#include "OvRendering/Buffers/IndexBuffer.h"

OvRendering::Buffers::IndexBuffer::IndexBuffer(unsigned int* p_data, size_t p_elements)
{
	glGenBuffers(1, &m_bufferID); // 生成EBO对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID); // 绑定当前对象
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_elements * sizeof(unsigned int), p_data, GL_STATIC_DRAW); // 分配数据
}

// 代理构造
OvRendering::Buffers::IndexBuffer::IndexBuffer(std::vector<uint32_t>& p_data) : IndexBuffer(p_data.data(), p_data.size())
{
}

OvRendering::Buffers::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_bufferID); // 删除EBO对象
}

void OvRendering::Buffers::IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
}

void OvRendering::Buffers::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OvRendering::Buffers::IndexBuffer::GetID()
{
	return m_bufferID;
}
