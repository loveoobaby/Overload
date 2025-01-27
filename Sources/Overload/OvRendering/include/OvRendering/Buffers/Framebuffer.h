﻿/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>

#include "OvRendering/Context/Driver.h"

namespace OvRendering::Buffers
{
	/**
	* Wraps OpenGL Framebuffer
	* 封装OpenGL帧缓存对象
	*/
	class Framebuffer
	{
	public:
		/**
		* Create the framebuffer
		* @param p_width 帧缓冲的宽
		* @param p_height 帧缓存的高
		*/
		Framebuffer(uint16_t p_width = 0, uint16_t p_height = 0);

		/**
		* Destructor
		*/
		~Framebuffer();

		/**
		* Bind the framebuffer
		*/
		void Bind();

		/**
		* Unbind the framebuffer
		*/
		void Unbind();

		/**
		* Defines a new size for the framebuffer
		* @param p_width
		* @param p_height
		*/
		void Resize(uint16_t p_width, uint16_t p_height);

		/**
		* Returns the ID of the OpenGL framebuffer
		*/
		uint32_t GetID();

		/**
		* Returns the ID of the OpenGL render texture
		*/
		uint32_t GetTextureID();

		/**
		* Returns the ID of the OpenGL render buffer
		*/
		uint32_t GetRenderBufferID();

	private:
		uint32_t m_bufferID = 0; // 帧缓冲的id
		uint32_t m_renderTexture = 0;
		uint32_t m_depthStencilBuffer = 0;
	};
}