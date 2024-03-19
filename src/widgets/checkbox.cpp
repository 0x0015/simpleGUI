#include "../internal.hpp"
#include <QCheckBox>

bool internal::checkbox(const std::string_view label, bool* check){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::checkbox, check ? *check : false});
		QCheckBox* newWidget = new QCheckBox(QString::fromStdString(std::string(label)));
		if(check)
			newWidget->setChecked(*check);
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string_view>{}(label);

		widgetCounter++;
		return false;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::checkbox){
		QCheckBox* newWidget = new QCheckBox(QString::fromStdString(std::string(label)));
		if(check)
			newWidget->setChecked(*check);
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::checkbox;

		widgetCounter++;
		return false;
	}
	auto labelHash = std::hash<std::string_view>{}(label);
	QCheckBox* checkbox = static_cast<QCheckBox*>(widgets[widgetCounter].widget);
	
	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		checkbox->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	if(check){
		if(widgets[widgetCounter].value.checked != checkbox->isChecked()){
			*check = checkbox->isChecked();
			widgets[widgetCounter].value.checked = checkbox->isChecked();

			widgetCounter++;
			return true;
		}else{
			if(*check != checkbox->isChecked())
				checkbox->setChecked(*check);
		}
	}

	widgetCounter++;
	if(check)
		return *check;
	else
		return false;
}
