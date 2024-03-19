#include "../internal.hpp"
#include <QRadioButton>

bool internal::radioButton(const std::string_view label, int* v, int button_v){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::radioButton, 0});
		QRadioButton* newWidget = new QRadioButton(QString::fromStdString(std::string(label)));
		if(v)
			newWidget->setChecked(*v == button_v);
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string_view>{}(label);

		widgetCounter++;
		return false;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::radioButton){
		QRadioButton* newWidget = new QRadioButton(QString::fromStdString(std::string(label)));
		if(v)
			newWidget->setChecked(*v == button_v);
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::checkbox;

		widgetCounter++;
		return false;
	}
	auto labelHash = std::hash<std::string_view>{}(label);
	QRadioButton* button = static_cast<QRadioButton*>(widgets[widgetCounter].widget);
	
	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		button->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	/*
	if(check){
		if(widgets[widgetCounter].value.checked != button->isChecked()){
			*check = button->isChecked();
			widgets[widgetCounter].value.checked = button->isChecked();

			widgetCounter++;
			return true;
		}else{
			if(*check != button->isChecked())
				button->setChecked(*check);
		}
	}

	widgetCounter++;
	if(check)
		return *check;
	else
		return false;
	*/

	widgetCounter++;
	return false;
}
