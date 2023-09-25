/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <GL/glew.h>

#include "OvRendering/Buffers/VertexBuffer.h"

namespace OvRendering::Buffers
{
	// 分配VBO，并赋予数据
	template <class T>
	inline VertexBuffer<T>::VertexBuffer(T* p_data, size_t p_elements)
	{
		glGenBuffers(1, &m_bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		glBufferData(GL_ARRAY_BUFFER, p_elements * sizeof(T), p_data, GL_STATIC_DRAW);
	}

	// 代理构造函数？
	template<class T>
	inline VertexBuffer<T>::VertexBuffer(std::vector<T>& p_data) : VertexBuffer(p_data.data(), p_data.size())
	{
	}

	// 销毁VBO
	template<class T>
	inline VertexBuffer<T>::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_bufferID);
	}

	// 绑定VBO
	template <class T>
	inline void VertexBuffer<T>::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
	}

	// unbind VBO
	template <class T>
	inline void VertexBuffer<T>::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// 获取VBO的id
	template <class T>
	inline uint32_t VertexBuffer<T>::GetID()
	{
		return m_bufferID;
	}
}