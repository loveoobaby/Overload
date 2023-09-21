/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "OvTools/Eventing/Event.h"

namespace OvTools::Eventing
{
	template<class... ArgTypes>
	ListenerID Event<ArgTypes...>::AddListener(Callback p_callback)
	{
		// 分配id
		ListenerID listenerID = m_availableListenerID++;
		// 插入回调map容器中
		m_callbacks.emplace(listenerID, p_callback);
		return listenerID;
	}

	template<class... ArgTypes>
	ListenerID Event<ArgTypes...>::operator+=(Callback p_callback)
	{
		return AddListener(p_callback);
	}

	// 删除事件处理callback
	template<class... ArgTypes>
	bool Event<ArgTypes...>::RemoveListener(ListenerID p_listenerID)
	{
		return m_callbacks.erase(p_listenerID) != 0;
	}

	template<class... ArgTypes>
	bool Event<ArgTypes...>::operator-=(ListenerID p_listenerID)
	{
		return RemoveListener(p_listenerID);
	}

	// 清空所有callback
	template<class... ArgTypes>
	void Event<ArgTypes...>::RemoveAllListeners()
	{
		m_callbacks.clear();
	}

	template<class... ArgTypes>
	uint64_t Event<ArgTypes...>::GetListenerCount()
	{
		return m_callbacks.size();
	}

	// 启动事件处理
	template<class... ArgTypes>
	void Event<ArgTypes...>::Invoke(ArgTypes... p_args)
	{
		for (auto const& [key, value] : m_callbacks)
			value(p_args...);
	}
}