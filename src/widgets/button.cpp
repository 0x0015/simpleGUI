#include "../internal.hpp"
#include <QPushButton>

bool internal::button(const std::string_view label){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::button, false});
		QPushButton* newWidget = new QPushButton(QString::fromStdString(std::string(label)));
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string_view>{}(label);

		widgetCounter++;
		return false;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::button){
		QPushButton* newWidget = new QPushButton(QString::fromStdString(std::string(label)));
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::button;

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
		if(widgets[widgetCounter].value.pressedLastFrame){
			widgetCounter++;
			return false;
		}else{
			widgets[widgetCounter].value.pressedLastFrame = true;
			widgetCounter++;
			return true;
		}
	}else{
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgetCounter++;
		return false;
	}	
}

