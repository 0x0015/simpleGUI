#include "../internal.hpp"
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include "textInput.hpp"

constexpr uint32_t textInput_type = COMPILE_TIME_CRC32_STR("textInput");

textInputWidget::textInputWidget(QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel();
	textEdit = new QLineEdit();
	layout->addWidget(label);
	layout->addWidget(textEdit);
}

textInputWidget::textInputWidget(const std::string_view s_label, const std::string_view s_text, QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel(QString::fromStdString(std::string(s_label)));
	textEdit = new QLineEdit(QString::fromStdString(std::string(s_text)));
	layout->addWidget(label);
	layout->addWidget(textEdit);
}

bool internal::textInput(const std::string_view label, std::span<char> buf){
	if(emplaceCorrectQWidget<textInputWidget, textInput_type>(label, std::string_view(buf.data()))){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = std::hash<std::string_view>{}(std::string_view(buf.data()));
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	auto bufHash = std::hash<std::string_view>{}(std::string_view(buf.data()));

	textInputWidget* input = static_cast<textInputWidget*>(widgets[widgetCounter].widget);

	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		input->label->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	auto currentTextHash = std::hash<std::string>{}(input->textEdit->text().toStdString());
	if(std::any_cast<size_t>(widgets[widgetCounter].state) != currentTextHash){
		//std::cout<<"Found text box to have changed to "<<input->textEdit->text().toStdString()<<", size: "<<input->textEdit->text().size()<<std::endl;
		widgets[widgetCounter].state = currentTextHash;
		memcpy(buf.data(), input->textEdit->text().toLocal8Bit().data(), std::min<int>(buf.size()-1, input->textEdit->text().size()));
		for(unsigned int i=std::min<unsigned int>(buf.size()-1, input->textEdit->text().size());i<buf.size();i++){
			buf[i] = 0;
		}
		widgetCounter++;
		return true;
	}else if(std::any_cast<size_t>(widgets[widgetCounter].state) != bufHash){
		//std::cout<<"Found buf to have changed"<<std::endl;
		widgets[widgetCounter].state = bufHash;
		input->textEdit->setText(QString::fromStdString(std::string(std::string_view(buf.data()))));
	}

	widgetCounter++;
	return false;
}

bool internal::textInput(const std::string_view label, std::string& buf){
	if(emplaceCorrectQWidget<textInputWidget, textInput_type>(label, buf)){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = std::hash<std::string>{}(buf);
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	auto bufHash = std::hash<std::string>{}(buf);

	textInputWidget* input = static_cast<textInputWidget*>(widgets[widgetCounter].widget);

	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		input->label->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	auto currentTextHash = std::hash<std::string>{}(input->textEdit->text().toStdString());
	if(std::any_cast<size_t>(widgets[widgetCounter].state) != currentTextHash){
		//std::cout<<"Found text box to have changed to "<<input->textEdit->text().toStdString()<<", size: "<<input->textEdit->text().size()<<std::endl;
		widgets[widgetCounter].state = currentTextHash;
		buf = input->textEdit->text().toStdString();
		widgetCounter++;
		return true;
	}else if(std::any_cast<size_t>(widgets[widgetCounter].state) != bufHash){
		//std::cout<<"Found buf to have changed"<<std::endl;
		widgets[widgetCounter].state = bufHash;
		input->textEdit->setText(QString::fromStdString(buf));
	}

	widgetCounter++;
	return false;
}
