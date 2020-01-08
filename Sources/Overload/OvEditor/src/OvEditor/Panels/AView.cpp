/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <GL/glew.h>

#include "OvEditor/Panels/AView.h"
#include "OvEditor/Core/EditorActions.h"

OvEditor::Panels::AView::AView
(
	const std::string& p_title,
	bool p_opened,
	const OvUI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings), m_editorRenderer(EDITOR_RENDERER())
{
	m_cameraPosition = { -10.0f, 4.0f, 10.0f };
	m_camera.SetPitch(-10.0f);
	m_camera.SetYaw(-45.f);

	m_image = &CreateWidget<OvUI::Widgets::Visual::Image>(m_fbo.GetTextureID(), OvMaths::FVector2{ 0.f, 0.f });
}

void OvEditor::Panels::AView::Update(float p_deltaTime)
{
	auto[winWidth, winHeight] = GetSafeSize();

	m_image->size = OvMaths::FVector2(static_cast<float>(winWidth), static_cast<float>(winHeight));

	m_fbo.Resize(winWidth, winHeight);
}

void OvEditor::Panels::AView::_Draw_Impl()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

	OvUI::Panels::PanelWindow::_Draw_Impl();

	ImGui::PopStyleVar();
}

void OvEditor::Panels::AView::Render()
{
	FillEngineUBO();

	auto [winWidth, winHeight] = GetSafeSize();

	EDITOR_CONTEXT(shapeDrawer)->SetViewProjection(m_camera.GetProjectionMatrix() * m_camera.GetViewMatrix());

	glViewport(0, 0, winWidth, winHeight); // TODO: Move this OpenGL call to OvRendering

	_Render_Impl();
}

void OvEditor::Panels::AView::SetCameraPosition(const OvMaths::FVector3 & p_position)
{
	m_cameraPosition = p_position;
}

const OvMaths::FVector3 & OvEditor::Panels::AView::GetCameraPosition() const
{
	return m_cameraPosition;
}

OvRendering::LowRenderer::Camera & OvEditor::Panels::AView::GetCamera()
{
	return m_camera;
}

std::pair<uint16_t, uint16_t> OvEditor::Panels::AView::GetSafeSize() const
{
	auto result = GetSize() - OvMaths::FVector2{ 0.f, 25.f }; // 25 == title bar height
	return { static_cast<uint16_t>(result.x), static_cast<uint16_t>(result.y) };
}

const OvMaths::FVector3& OvEditor::Panels::AView::GetGridColor() const
{
	return m_gridColor;
}

void OvEditor::Panels::AView::SetGridColor(const OvMaths::FVector3& p_color)
{
	m_gridColor = p_color;
}

void OvEditor::Panels::AView::FillEngineUBO()
{
	auto& engineUBO = *EDITOR_CONTEXT(engineUBO);

	auto[winWidth, winHeight] = GetSafeSize();

	size_t offset = sizeof(OvMaths::FMatrix4); // We skip the model matrix (Which is a special case, modified every draw calls)
	engineUBO.SetSubData(OvMaths::FMatrix4::Transpose(m_camera.GetViewMatrix()), std::ref(offset));
	engineUBO.SetSubData(OvMaths::FMatrix4::Transpose(m_camera.GetProjectionMatrix()), std::ref(offset));
	engineUBO.SetSubData(m_cameraPosition, std::ref(offset));
}

void OvEditor::Panels::AView::PrepareCamera()
{
	auto [winWidth, winHeight] = GetSafeSize();
	m_camera.CacheMatrices(winWidth, winHeight, m_cameraPosition);
}

