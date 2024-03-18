#include "internal.hpp"
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

void internal::text(const std::string& label){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::text});
		QLabel* newWidget = new QLabel(QString::fromStdString(label));
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string>{}(label);

		widgetCounter++;
		return;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::text){
		QLabel* newWidget = new QLabel(QString::fromStdString(label));
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].valueHash = std::hash<std::string>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::text;

		widgetCounter++;
		return;
	}
	//widget exists, type is text
	auto labelHash = std::hash<std::string>{}(label);
	if(widgets[widgetCounter].valueHash != labelHash){
		static_cast<QLabel*>(widgets[widgetCounter].widget)->setText(QString::fromStdString(label));
		widgets[widgetCounter].valueHash = labelHash;
	}
	widgetCounter++;
}

bool internal::button(const std::string& label){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::button, false});
		QPushButton* newWidget = new QPushButton(QString::fromStdString(label));
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string>{}(label);

		widgetCounter++;
		return false;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::button){
		QPushButton* newWidget = new QPushButton(QString::fromStdString(label));
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgets[widgetCounter].valueHash = std::hash<std::string>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::button;

		widgetCounter++;
		return false;
	}
	auto labelHash = std::hash<std::string>{}(label);
	QPushButton* button = static_cast<QPushButton*>(widgets[widgetCounter].widget);
	
	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		button->setText(QString::fromStdString(label));
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

void internal::checkbox(const std::string& label, bool* check){
	if(widgetCounter >= (int)widgets.size()){
		widgets.push_back({widget::widgetTypeEnum::checkbox, check ? *check : false});
		QCheckBox* newWidget = new QCheckBox(QString::fromStdString(label));
		if(check)
			newWidget->setChecked(*check);
		gui->layout->addWidget(newWidget);
		widgets.back().widget = newWidget;
		widgets.back().valueHash = std::hash<std::string>{}(label);

		widgetCounter++;
		return;
	}
	if(widgets[widgetCounter].widgetType != widget::widgetTypeEnum::checkbox){
		QCheckBox* newWidget = new QCheckBox(QString::fromStdString(label));
		if(check)
			newWidget->setChecked(*check);
		gui->layout->replaceWidget(widgets[widgetCounter].widget, newWidget);
		widgets[widgetCounter].widget = newWidget;
		widgets[widgetCounter].value.pressedLastFrame = false;
		widgets[widgetCounter].valueHash = std::hash<std::string>{}(label);
		widgets[widgetCounter].widgetType = widget::widgetTypeEnum::checkbox;

		widgetCounter++;
		return;
	}
	auto labelHash = std::hash<std::string>{}(label);
	QCheckBox* checkbox = static_cast<QCheckBox*>(widgets[widgetCounter].widget);
	
	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		checkbox->setText(QString::fromStdString(label));
		widgets[widgetCounter].valueHash = labelHash;
	}

	if(check){
		if(widgets[widgetCounter].value.checked != checkbox->isChecked()){
			*check = checkbox->isChecked();
			widgets[widgetCounter].value.checked = checkbox->isChecked();
		}else{
			if(*check != checkbox->isChecked())
				checkbox->setChecked(*check);
		}
	}

	widgetCounter++;
}
