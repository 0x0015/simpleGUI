#include "../internal.hpp"
#include <QCheckBox>

constexpr uint32_t checkbox_type = COMPILE_TIME_CRC32_STR("checkbox");

bool internal::checkbox(const std::string_view label, bool* check){
	if(emplaceCorrectQWidget<QCheckBox, checkbox_type>(QString::fromStdString(std::string(label)))){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = check ? *check : false;
		if(check) static_cast<QCheckBox*>(widgets[widgetCounter].widget)->setChecked(*check);
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
		if(std::any_cast<bool>(widgets[widgetCounter].state) != checkbox->isChecked()){
			*check = checkbox->isChecked();
			widgets[widgetCounter].state = checkbox->isChecked();

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
