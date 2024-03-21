#include "../internal.hpp"
#include "combo.hpp"

constexpr uint32_t combo_type = COMPILE_TIME_CRC32_STR("combo");

textInputWidget::textInputWidget(QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel();
	combo = new QComboBox();
	layout->addWidget(label);
	layout->addWidget(combo);
}

textInputWidget::textInputWidget(const std::string_view s_label, const std::string_view s_text, const std::span<const std::span<char>> items, QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel(QString::fromStdString(std::string(s_label)));
	combo = new QComboBox(QString::fromStdString(std::string(s_text)));
	for(unsigned int i=0;i<items.size();i++){
		combo.addItem(QString::fromStdString(std::string(std::string_view(items[i].data()))));
	}
	layout->addWidget(label);
	layout->addWidget(combo);
}

size_t hashSpanSpan(const std::span<const std::span<char>> items){
	size_t itemsHash = 0;
	for(unsigned int i=0;i<items.size();i++){
		std::hash_combine(itemsHash, std::string_view(items[i].data()));
	}
	return itemsHash;
}

bool internal::combo(const std::string_view label, int* current_item, const std::span<const std::span<char>> items){
	std::string_view defaultSelected;
	if(current_item)
		defaultSelected = std::string_view(items[*current_item].data());
	else
		defaultSelected = std::string_view("");

	if(emplaceCorrectQWidget<comboWidget, combo_type>(label, defaultSelected)){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = hashSpanSpan(items);
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	size_t itemsHash = hashSpanSpan(items);

	comboWidget* input = static_cast<comboWidget*>(widgets[widgetCounter].widget);

	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		input->label->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	auto currentItemsHash = 0;
	for(int i=0;i<input->combo->count();i++){
		std::hash_combine(currentItemsHash, input->combo->itemText(i));
	}

	if(std::any_cast<size_t>(widgets[widgetCounter].state) != currentItemsHash){
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
	
}
