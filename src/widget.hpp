#pragma once
#include <QWidget>
#include "util.hpp"
#include <any>

class widget{
public:
	uint32_t widgetType;
	std::any state;
	QWidget* widget;
	std::size_t valueHash;
};


