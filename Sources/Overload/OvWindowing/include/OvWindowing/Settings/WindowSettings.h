/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "OvWindowing/Cursor/ECursorShape.h"
#include "OvWindowing/Cursor/ECursorMode.h"

namespace OvWindowing::Settings
{
	/**
	* Contains window settings
	*/
	struct WindowSettings 
	{
		/**
		* A simple constant used to ignore a value setting (Let the program decide for you)
		* @note You can you WindowSettings::DontCare only where it is indicated
		*/
		static const int32_t DontCare = -1;

		/**
		* Title of the window (Displayed in the title bar)
		*/
		std::string title; // 窗口标题

		/**
		* Width in pixels of the window
		*/
		uint16_t width;  // 窗口的宽度

		/**
		* Height in pixels of the window
		*/
		uint16_t height; // 窗口的长度

		/**
		* Minimum width of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t minimumWidth = DontCare; // 窗口宽度的最小值

		/**
		* Minimum height of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t minimumHeight = DontCare; // 窗口高度的最小值

		/**
		* Maximum width of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t maximumWidth = DontCare;

		/**
		* Maximum height of the window.
		* Use WindowSettings::DontCare to disable limit
		*/
		int16_t maximumHeight = DontCare;

		/**
		* Specifies if the window is by default in fullscreen or windowed mode
		*/
		bool fullscreen = false;

		/**
		* Specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc.
		* An undecorated window may still allow the user to generate close events on some platforms. This hint is ignored
		* for full screen windows.
		*/
		bool decorated = true;

		/**
		* specifies whether the windowed mode window will be resizable by the user. The window will still be resizable using
		* the "SetSize(uint16_t, uint16_t)" method of the "Window" class. This hint is ignored for full screen windows
		*/
		bool resizable = true; // 是否可改变大小

		/**
		* Specifies whether the windowed mode window will be given input focus when created. This hint is ignored for
		* full screen and initially hidden windows.
		*/
		bool focused = true;

		/**
		* Specifies whether the windowed mode window will be maximized when created. This hint is ignored for full screen windows.
		*/
		bool maximized = false;

		/**
		* Specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top.
		* This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This hint is
		* ignored for full screen windows.
		*/
		bool floating = false; // 是否悬浮

		/**
		* Specifies whether the windowed mode window will be initially visible. This hint is ignored for full screen windows.
		*/
		bool visible = true; // 是否可见

		/**
		* Specifies whether the full screen window will automatically iconify and restore
		* the previous video mode on input focus loss. This hint is ignored for windowed mode windows
		*/
		bool autoIconify = true;

		/**
		* Specifies the desired refresh rate for full screen windows. If set to WindowSettings::DontCare, the highest
		* available refresh rate will be used. This hint is ignored for windowed mode windows.
		*/
		int32_t refreshRate = WindowSettings::DontCare; // 窗口刷新频率

		/**
		* Specifies the default cursor mode of the window
		*/
		Cursor::ECursorMode cursorMode = Cursor::ECursorMode::NORMAL; // 

		/**
		* Specifies the default cursor shape of the window
		*/
		Cursor::ECursorShape cursorShape = Cursor::ECursorShape::ARROW; // 光标的形状

		/**
		* Defines the number of samples to use (For anti-aliasing)
		*/
		uint32_t samples = 4;
	};
}