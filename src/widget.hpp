#pragma once
#include <QWidget>
#include <functional>

class widget{
public:
	enum widgetTypeEnum{
		none,
		text,
		button,
		checkbox,
		radioButton
	};
	widgetTypeEnum widgetType;
	union widgetValueUnion{
		bool pressedLastFrame;
		bool checked;
		int radioValue;
	};
	widgetValueUnion value{};
	QWidget* widget;
	std::size_t valueHash;
};
