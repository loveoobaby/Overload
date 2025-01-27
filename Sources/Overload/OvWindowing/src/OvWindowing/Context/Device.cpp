/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvWindowing/Context/Device.h"

#include <stdexcept>

OvTools::Eventing::Event<OvWindowing::Context::EDeviceError, std::string> OvWindowing::Context::Device::ErrorEvent;

OvWindowing::Context::Device::Device(const Settings::DeviceSettings& p_deviceSettings)
{
	BindErrorCallback();

	int initializationCode = glfwInit(); // 初始化GLFW

	if (initializationCode == GLFW_FALSE)
	{
		throw std::runtime_error("Failed to Init GLFW");
		glfwTerminate();
	}
	else
	{
		// 初始化Cursor
		CreateCursors();

		if (p_deviceSettings.debugProfile)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// 设置OpenGL的版本
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_deviceSettings.contextMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_deviceSettings.contextMinorVersion);
		// 设置使用OpenGL核心模式
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// 设置多重采样
		glfwWindowHint(GLFW_SAMPLES, p_deviceSettings.samples);

		m_isAlive = true;
	}
}

OvWindowing::Context::Device::~Device()
{
	if (m_isAlive)
	{
		DestroyCursors();
		glfwTerminate();
	}
}

// 获取窗口的长宽
std::pair<int16_t, int16_t> OvWindowing::Context::Device::GetMonitorSize() const
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	return std::pair<int16_t, int16_t>(static_cast<int16_t>(mode->width), static_cast<int16_t>(mode->height));
}

// 获取cursor实例
GLFWcursor * OvWindowing::Context::Device::GetCursorInstance(Cursor::ECursorShape p_cursorShape) const
{
	return m_cursors.at(p_cursorShape);
}

bool OvWindowing::Context::Device::HasVsync() const
{
	return m_vsync;
}

void OvWindowing::Context::Device::SetVsync(bool p_value)
{
	glfwSwapInterval(p_value ? 1 : 0);
	m_vsync = p_value;
}

void OvWindowing::Context::Device::PollEvents() const
{
	glfwPollEvents();
}

float OvWindowing::Context::Device::GetElapsedTime() const
{
	return static_cast<float>(glfwGetTime());
}

// 绑定Error的回调
void OvWindowing::Context::Device::BindErrorCallback()
{
	auto errorCallback = [](int p_code, const char* p_description)
	{
		ErrorEvent.Invoke(static_cast<EDeviceError>(p_code), p_description);
	};

	glfwSetErrorCallback(errorCallback);
}

// 初始化m_cursors
void OvWindowing::Context::Device::CreateCursors()
{
	m_cursors[Cursor::ECursorShape::ARROW] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::ARROW));
	m_cursors[Cursor::ECursorShape::IBEAM] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::IBEAM));
	m_cursors[Cursor::ECursorShape::CROSSHAIR] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::CROSSHAIR));
	m_cursors[Cursor::ECursorShape::HAND] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::HAND));
	m_cursors[Cursor::ECursorShape::HRESIZE] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::HRESIZE));
	m_cursors[Cursor::ECursorShape::VRESIZE] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::VRESIZE));
}

// 销毁Cursor
void OvWindowing::Context::Device::DestroyCursors()
{
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::ARROW]);
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::IBEAM]);
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::CROSSHAIR]);
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::HAND]);
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::HRESIZE]);
	glfwDestroyCursor(m_cursors[Cursor::ECursorShape::VRESIZE]);
}
