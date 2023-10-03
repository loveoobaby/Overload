/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <functional>

#include "OvRendering/Core/Renderer.h"

OvRendering::Core::Renderer::Renderer(Context::Driver& p_driver) : m_driver(p_driver), m_state(0)
{
}

// 设置清屏颜色
void OvRendering::Core::Renderer::SetClearColor(float p_red, float p_green, float p_blue, float p_alpha)
{
	glClearColor(p_red, p_green, p_blue, p_alpha);
}

// 清屏缓冲器
void OvRendering::Core::Renderer::Clear(bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer)
{
	glClear
	(
		(p_colorBuffer ? GL_COLOR_BUFFER_BIT : 0) |
		(p_depthBuffer ? GL_DEPTH_BUFFER_BIT : 0) |
		(p_stencilBuffer ? GL_STENCIL_BUFFER_BIT : 0)
	);
}

void OvRendering::Core::Renderer::Clear(OvRendering::LowRenderer::Camera & p_camera, bool p_colorBuffer, bool p_depthBuffer, bool p_stencilBuffer)
{
	/* Backup the previous OpenGL clear color */
	GLfloat previousClearColor[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, previousClearColor);

	/* Clear the screen using the camera clear color */
	const OvMaths::FVector3& cameraClearColor = p_camera.GetClearColor();
	SetClearColor(cameraClearColor.x, cameraClearColor.y, cameraClearColor.z, 1.0f);
	Clear(p_colorBuffer, p_depthBuffer, p_stencilBuffer);

	/* Reset the OpenGL clear color to the previous clear color (Backuped one) */
	SetClearColor(previousClearColor[0], previousClearColor[1], previousClearColor[2], previousClearColor[3]);
}

// 设置线光栅化宽度，默认是1
void OvRendering::Core::Renderer::SetRasterizationLinesWidth(float p_width)
{
	glLineWidth(p_width);
}

// 指定是画点、线、面
void OvRendering::Core::Renderer::SetRasterizationMode(Settings::ERasterizationMode p_rasterizationMode)
{
	glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(p_rasterizationMode));
}

// 设置OpenGL启用或关闭一些功能
void OvRendering::Core::Renderer::SetCapability(Settings::ERenderingCapability p_capability, bool p_value)
{
	(p_value ? glEnable : glDisable)(static_cast<GLenum>(p_capability));
}

bool OvRendering::Core::Renderer::GetCapability(Settings::ERenderingCapability p_capability) const
{
	return glIsEnabled(static_cast<GLenum>(p_capability));
}

void OvRendering::Core::Renderer::SetStencilAlgorithm(Settings::EComparaisonAlgorithm p_algorithm, int32_t p_reference, uint32_t p_mask)
{
	glStencilFunc(static_cast<GLenum>(p_algorithm), p_reference, p_mask);
}

void OvRendering::Core::Renderer::SetDepthAlgorithm(Settings::EComparaisonAlgorithm p_algorithm)
{
	glDepthFunc(static_cast<GLenum>(p_algorithm));
}

void OvRendering::Core::Renderer::SetStencilMask(uint32_t p_mask)
{
	glStencilMask(p_mask);
}

void OvRendering::Core::Renderer::SetStencilOperations(Settings::EOperation p_stencilFail, Settings::EOperation p_depthFail, Settings::EOperation p_bothPass)
{
	glStencilOp(static_cast<GLenum>(p_stencilFail), static_cast<GLenum>(p_depthFail), static_cast<GLenum>(p_bothPass));
}

void OvRendering::Core::Renderer::SetCullFace(Settings::ECullFace p_cullFace)
{
	glCullFace(static_cast<GLenum>(p_cullFace));
}

void OvRendering::Core::Renderer::SetDepthWriting(bool p_enable)
{
	glDepthMask(p_enable);
}

void OvRendering::Core::Renderer::SetColorWriting(bool p_enableRed, bool p_enableGreen, bool p_enableBlue, bool p_enableAlpha)
{
	glColorMask(p_enableRed, p_enableGreen, p_enableBlue, p_enableAlpha);
}

void OvRendering::Core::Renderer::SetColorWriting(bool p_enable)
{
	glColorMask(p_enable, p_enable, p_enable, p_enable);
}

// 设置视口大小
void OvRendering::Core::Renderer::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

// 从FrameBuffer中读取数据
void OvRendering::Core::Renderer::ReadPixels(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Settings::EPixelDataFormat format, Settings::EPixelDataType type, void* data)
{
	glReadPixels(x, y, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
}

bool OvRendering::Core::Renderer::GetBool(GLenum p_parameter)
{
	GLboolean result;
	glGetBooleanv(p_parameter, &result);
	return static_cast<bool>(result);
}

bool OvRendering::Core::Renderer::GetBool(GLenum p_parameter, uint32_t p_index)
{
	GLboolean result;
	glGetBooleani_v(p_parameter, p_index, &result);
	return static_cast<bool>(result);
}

int OvRendering::Core::Renderer::GetInt(GLenum p_parameter)
{
	GLint result;
	glGetIntegerv(p_parameter, &result);
	return static_cast<int>(result);
}

int OvRendering::Core::Renderer::GetInt(GLenum p_parameter, uint32_t p_index)
{
	GLint result;
	glGetIntegeri_v(p_parameter, p_index, &result);
	return static_cast<int>(result);
}

float OvRendering::Core::Renderer::GetFloat(GLenum p_parameter)
{
	GLfloat result;
	glGetFloatv(p_parameter, &result);
	return static_cast<float>(result);
}

float OvRendering::Core::Renderer::GetFloat(GLenum p_parameter, uint32_t p_index)
{
	GLfloat result;
	glGetFloati_v(p_parameter, p_index, &result);
	return static_cast<float>(result);
}

double OvRendering::Core::Renderer::GetDouble(GLenum p_parameter)
{
	GLdouble result;
	glGetDoublev(p_parameter, &result);
	return static_cast<double>(result);
}

double OvRendering::Core::Renderer::GetDouble(GLenum p_parameter, uint32_t p_index)
{
	GLdouble result;
	glGetDoublei_v(p_parameter, p_index, &result);
	return static_cast<double>(result);
}

int64_t OvRendering::Core::Renderer::GetInt64(GLenum p_parameter)
{
	GLint64 result;
	glGetInteger64v(p_parameter, &result);
	return static_cast<int64_t>(result);
}

int64_t OvRendering::Core::Renderer::GetInt64(GLenum p_parameter, uint32_t p_index)
{
	GLint64 result;
	glGetInteger64i_v(p_parameter, p_index, &result);
	return static_cast<int64_t>(result);
}

std::string OvRendering::Core::Renderer::GetString(GLenum p_parameter)
{
	const GLubyte* result = glGetString(p_parameter);
	return result ? reinterpret_cast<const char*>(result) : std::string();
}

std::string OvRendering::Core::Renderer::GetString(GLenum p_parameter, uint32_t p_index)
{
	const GLubyte* result = glGetStringi(p_parameter, p_index);
	return result ? reinterpret_cast<const char*>(result) : std::string();
}

void OvRendering::Core::Renderer::ClearFrameInfo()
{
	m_frameInfo.batchCount		= 0;
	m_frameInfo.instanceCount	= 0;
	m_frameInfo.polyCount		= 0;
}

/**
* 绘制网格
* p_mesh（网格信息）
* p_primitiveMode（绘制网格的模式）
* p_instances（绘制实例的数量）
*/
void OvRendering::Core::Renderer::Draw(Resources::IMesh& p_mesh, Settings::EPrimitiveMode p_primitiveMode, uint32_t p_instances)
{
	if (p_instances > 0)
	{
		// 更新frameInfo，记录渲染的数量信息
		++m_frameInfo.batchCount;
		m_frameInfo.instanceCount += p_instances;
		m_frameInfo.polyCount += (p_mesh.GetIndexCount() / 3) * p_instances;

		p_mesh.Bind();
		
		if (p_mesh.GetIndexCount() > 0) // 使用EBO进行渲染
		{
			/* With EBO */
			if (p_instances == 1)
				glDrawElements(static_cast<GLenum>(p_primitiveMode), p_mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr);
			else
				glDrawElementsInstanced(static_cast<GLenum>(p_primitiveMode), p_mesh.GetIndexCount(), GL_UNSIGNED_INT, nullptr, p_instances);
		}
		else
		{
			/* Without EBO */  //使用VBO进行渲染
			if (p_instances == 1)
				glDrawArrays(static_cast<GLenum>(p_primitiveMode), 0, p_mesh.GetVertexCount());
			else
				glDrawArraysInstanced(static_cast<GLenum>(p_primitiveMode), 0, p_mesh.GetVertexCount(), p_instances);
		}

		p_mesh.Unbind();
	}
}

/*
* 获取视锥体内部的网格
*/
std::vector<std::reference_wrapper<OvRendering::Resources::Mesh>> OvRendering::Core::Renderer::GetMeshesInFrustum
(
	const OvRendering::Resources::Model& p_model,
	const OvRendering::Geometry::BoundingSphere& p_modelBoundingSphere,
	const OvMaths::FTransform& p_modelTransform,
	const OvRendering::Data::Frustum& p_frustum,
	OvRendering::Settings::ECullingOptions p_cullingOptions
)
{
	// 是否开启视锥体裁剪
	const bool frustumPerModel = OvRendering::Settings::IsFlagSet(Settings::ECullingOptions::FRUSTUM_PER_MODEL, p_cullingOptions);

	if (!frustumPerModel || p_frustum.BoundingSphereInFrustum(p_modelBoundingSphere, p_modelTransform))
	{
		std::vector<std::reference_wrapper<OvRendering::Resources::Mesh>> result;

		// 是否开启网格视锥体裁剪
		const bool frustumPerMesh = OvRendering::Settings::IsFlagSet(Settings::ECullingOptions::FRUSTUM_PER_MESH, p_cullingOptions);

		const auto& meshes = p_model.GetMeshes();

		for (auto mesh : meshes)
		{
			// Do not check if the mesh is in frustum if the model has only one mesh, because model and mesh bounding sphere are equals
			if (meshes.size() == 1 || !frustumPerMesh || p_frustum.BoundingSphereInFrustum(mesh->GetBoundingSphere(), p_modelTransform))
			{
				result.emplace_back(*mesh); // 在视锥体中的网格
			}
		}

		return result;
	}

	return {};
}

/**
* 获取渲染管线的状态
*/
uint8_t OvRendering::Core::Renderer::FetchGLState()
{
	using namespace OvRendering::Settings;

	uint8_t result = 0;

	GLboolean cMask[4];
	glGetBooleanv(GL_COLOR_WRITEMASK, cMask);

	if (GetBool(GL_DEPTH_WRITEMASK))						result |= 0b0000'0001; // 是否深度缓冲可写
	if (cMask[0])											result |= 0b0000'0010; // 是否颜色缓冲可写
	if (GetCapability(ERenderingCapability::BLEND))			result |= 0b0000'0100; // 是否开启混合
	if (GetCapability(ERenderingCapability::CULL_FACE))		result |= 0b0000'1000; // 是否开启面剔除
	if (GetCapability(ERenderingCapability::DEPTH_TEST))	result |= 0b0001'0000; // 是否开启深度测试

	switch (static_cast<ECullFace>(GetInt(GL_CULL_FACE)))
	{
	case OvRendering::Settings::ECullFace::BACK:			result |= 0b0010'0000; break;
	case OvRendering::Settings::ECullFace::FRONT:			result |= 0b0100'0000; break;
	case OvRendering::Settings::ECullFace::FRONT_AND_BACK:  result |= 0b0110'0000; break;
	}

	return result;
}

/**
* 设置渲染管线的状态
* 
*/
void OvRendering::Core::Renderer::ApplyStateMask(uint8_t p_mask)
{
	if (p_mask != m_state)
	{
		using namespace OvRendering::Settings;

		if ((p_mask & 0x01) != (m_state & 0x01))	SetDepthWriting(p_mask & 0x01);  // 设置深度缓冲可写
		if ((p_mask & 0x02) != (m_state & 0x02))	SetColorWriting(p_mask & 0x02);  // 设置颜色缓冲可写
		if ((p_mask & 0x04) != (m_state & 0x04))	SetCapability(ERenderingCapability::BLEND, p_mask & 0x04); // 设置是否可混合
		if ((p_mask & 0x08) != (m_state & 0x08))	SetCapability(ERenderingCapability::CULL_FACE, p_mask & 0x8); // 设置面剔除
		if ((p_mask & 0x10) != (m_state & 0x10))	SetCapability(ERenderingCapability::DEPTH_TEST, p_mask & 0x10); // 设置深度测试

		if ((p_mask & 0x08) && ((p_mask & 0x20) != (m_state & 0x20) || (p_mask & 0x40) != (m_state & 0x40)))
		{
			int backBit = p_mask & 0x20;
			int frontBit = p_mask & 0x40;
			SetCullFace(backBit && frontBit ? ECullFace::FRONT_AND_BACK : (backBit ? ECullFace::BACK : ECullFace::FRONT)); // 设置面剔除的方向
		}

		m_state = p_mask;
	}
}

void OvRendering::Core::Renderer::SetState(uint8_t p_state)
{
	m_state = p_state;
}

const OvRendering::Core::Renderer::FrameInfo& OvRendering::Core::Renderer::GetFrameInfo() const
{
	return m_frameInfo;
}
