#include "../internal.hpp"
#include <QLabel>

constexpr uint32_t text_type = COMPILE_TIME_CRC32_STR("text");

void internal::text(const std::string_view label){
	if(emplaceCorrectQWidget<QLabel, text_type>(QString::fromStdString(std::string(label)))){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
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

