#include "../internal.hpp"
#include <QWidget>
#include <QHBoxLayout>

void internal::sameLine(){
	widgetPosInfo.sameLine = true;
}

void internal::applySameline(){
	//okay, this is actually going to need some architectural changes
	if(widgetPosInfo.sameLine){
		if(widgetPosInfo.wasLastSameLine){
			//layout should already be good, do nothing
		}else{
			//new layout needs to be made, and the last widget needs to be moved into it
			QWidget* layoutWidget = new QWidget();
			QLayout* hlayout = new QHBoxLayout();
			layoutWidget->setLayout(hlayout);
			hlayout->addWidget(widgets.back().widget);
			widgetPosInfo.layout->replaceWidget(widgets.back().widget, layoutWidget);
			widgetPosInfo.layout = hlayout;
			widgetPosInfo.wasLastSameLine = true;
		}
	}else if(widgetPosInfo.wasLastSameLine){
		widgetPosInfo.layout = widgetPosInfo.layout->parentWidget()->layout();
	}
}

