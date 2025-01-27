/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <windows.h>

#include "OvWindowing/Dialogs/MessageBox.h"

#undef MessageBox

OvWindowing::Dialogs::MessageBox::MessageBox(std::string p_title, std::string p_message, EMessageType p_messageType, EButtonLayout p_buttonLayout, bool p_autoSpawn) :
	m_title(p_title),    // title
	m_message(p_message), // message
	m_buttonLayout(p_buttonLayout), // 按钮布局
	m_messageType(p_messageType) // message类型
{
	if (p_autoSpawn)
		Spawn();
}

const OvWindowing::Dialogs::MessageBox::EUserAction& OvWindowing::Dialogs::MessageBox::GetUserAction() const
{
	return m_userResult;
}

void OvWindowing::Dialogs::MessageBox::Spawn()
{
	// 最终调用Widows API实现
	int msgboxID = MessageBoxA
	(
		nullptr,
		static_cast<LPCSTR>(m_message.c_str()),
		static_cast<LPCSTR>(m_title.c_str()),
		static_cast<UINT>(m_messageType) | static_cast<UINT>(m_buttonLayout) | MB_DEFBUTTON2
	);

	m_userResult = static_cast<EUserAction>(msgboxID);
}
