#pragma once
#include "internal.hpp"

template<class T, uint32_t widget_type, class... Args> bool internal::emplaceCorrectQWidget(const Args&... args){
	internal::applySameline();

	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget_type});
		T* newWidget = new T(args...);
		widgetPosInfo.layout->addWidget(newWidget);
		widgets.back().widget = newWidget;

		return true;
	}
	if(widgets[widgetCounter].widgetType != widget_type){
		T* newWidget = new T(args...);
		widgetPosInfo.layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].widgetType = widget_type;

		return true;
	}

	return false;
}
