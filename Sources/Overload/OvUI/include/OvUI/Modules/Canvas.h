/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <algorithm>

#include <OvTools/Eventing/Event.h>

#include "OvUI/API/IDrawable.h"
#include "OvUI/Panels/APanel.h"
#include "OvUI/ImGui/imgui.h"
#include "OvUI/ImGui/imgui_impl_glfw.h"
#include "OvUI/ImGui/imgui_impl_opengl3.h"

namespace OvUI::Modules
{
	/**
	* A Canvas represents the whole frame available for UI drawing
	*/
	class Canvas : public API::IDrawable
	{
	public:
		/**
		* Adds a panel to the canvas
		* @param p_panel
		*/
		// 向Canvas中增加面板
		void AddPanel(Panels::APanel& p_panel);

		/**
		* Removes a panel from the canvas
		* @param p_panel
		*/
		// 删除面板
		void RemovePanel(Panels::APanel& p_panel);

		/**
		* Removes every panels from the canvas
		*/
		void RemoveAllPanels();

		/**
		* Makes the canvas a dockspace (Dockable panels will be able to attach themselves to the canvas)
		*/
		// docker面板
		void MakeDockspace(bool p_state);

		/**
		* Returns true if the canvas is a dockspace
		*/
		bool IsDockspace() const;

		/**
		* Draw the canvas (Draw every panels)
		*/
		void Draw() override;

	private:
		std::vector<std::reference_wrapper<Panels::APanel>> m_panels;
		bool m_isDockspace = false;
	};
}
