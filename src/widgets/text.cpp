#include "../internal.hpp"
#include <QLabel>

void internal::text(const std::string_view label){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::text});
		QLabel* newWidget = new QLabel(QString::fromStdString(std::string(label)));
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string_view>{}(label);

		widgetCounter++;
		return;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::text){
		QLabel* newWidget = new QLabel(QString::fromStdString(std::string(label)));
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::text;

		widgetCounter++;
		return;
	}
	//widget exists, type is text
	auto labelHash = std::hash<std::string_view>{}(label);
	if(widgets[widgetCounter].valueHash != labelHash){
		static_cast<QLabel*>(widgets[widgetCounter].widget)->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}
	widgetCounter++;
}

