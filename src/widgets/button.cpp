#include "../internal.hpp"
#include <QPushButton>

constexpr uint32_t button_type = COMPILE_TIME_CRC32_STR("button");

bool internal::button(const std::string_view label){
	if(emplaceCorrectQWidget<QPushButton, button_type>(QString::fromStdString(std::string(label)))){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = false;
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	QPushButton* button = static_cast<QPushButton*>(widgets[widgetCounter].widget);
	
	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		button->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;

	}
	if(button->isDown()){
		if(std::any_cast<bool>(widgets[widgetCounter].state)){
			widgetCounter++;
			return false;
		}else{
			widgets[widgetCounter].state = true;
			widgetCounter++;
			return true;
		}
	}else{
		widgets[widgetCounter].state = false;
		widgetCounter++;
		return false;
	}	
}

