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
		ratio
	};
	widgetTypeEnum widgetType;
	union widgetValueUnion{
		bool pressedLastFrame;
		bool checked;
	};
	widgetValueUnion value{};
	QWidget* widget;
	std::size_t valueHash;
};
