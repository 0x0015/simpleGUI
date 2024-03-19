#include "../internal.hpp"
#include <QRadioButton>

constexpr uint32_t radioButton_type = COMPILE_TIME_CRC32_STR("radioButton");

bool internal::radioButton(const std::string_view label, int* v, int button_v){
	if(emplaceCorrectQWidget<QRadioButton, radioButton_type>(QString::fromStdString(std::string(label)))){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = v ? *v == button_v : false;
		if(v) static_cast<QRadioButton*>(widgets[widgetCounter].widget)->setChecked(*v == button_v);
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


	if(v){
		if(std::any_cast<bool>(widgets[widgetCounter].state) != button->isChecked()){
			if(button->isChecked())
				*v = button_v;
			widgets[widgetCounter].state = button->isChecked();

			widgetCounter++;
			return true;
		}else{
			button->setChecked(*v == button_v);
		}
	}

	widgetCounter++;
	if(v)
		return *v == button_v;
	else
		return false;
}
