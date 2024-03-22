#include "../internal.hpp"
#include "combo.hpp"

constexpr uint32_t combo_type = COMPILE_TIME_CRC32_STR("combo");

comboWidget::comboWidget(QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel();
	combo = new QComboBox();
	layout->addWidget(label);
	layout->addWidget(combo);
}

comboWidget::comboWidget(const std::string_view s_label, const std::string_view s_text, const std::span<const std::string_view> items, QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel(QString::fromStdString(std::string(s_label)));
	combo = new QComboBox();
	for(unsigned int i=0;i<items.size();i++){
		combo->addItem(QString::fromStdString(std::string(items[i])));
	}
	combo->setCurrentText(QString::fromStdString(std::string(s_text)));
	layout->addWidget(label);
	layout->addWidget(combo);
}

comboWidget::comboWidget(const std::string_view s_label, const std::string_view s_text, const std::span<const char*> items, QWidget* parent) : QWidget(parent){
	layout = new QHBoxLayout();
	setLayout(layout);
	label = new QLabel(QString::fromStdString(std::string(s_label)));
	combo = new QComboBox();
	for(unsigned int i=0;i<items.size();i++){
		combo->addItem(QString::fromStdString(std::string(items[i])));
	}
	combo->setCurrentText(QString::fromStdString(std::string(s_text)));
	layout->addWidget(label);
	layout->addWidget(combo);
}

size_t hashViewSpan(const std::span<const std::string_view> items){
	size_t itemsHash = 0;
	for(unsigned int i=0;i<items.size();i++){
		std::hash_combine(itemsHash, items[i]);
	}
	return itemsHash;
}

struct comboState{
	size_t itemsHash;
	int selectionNum;
};

bool internal::combo(const std::string_view label, int* current_item, const std::span<const std::string_view> items){
	std::string_view defaultSelected;
	if(current_item)
		defaultSelected = items[*current_item];
	else
		defaultSelected = std::string_view("");

	if(emplaceCorrectQWidget<comboWidget, combo_type>(label, defaultSelected, items)){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = comboState{hashViewSpan(items), current_item ? *current_item : 0};
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	size_t itemsHash = hashViewSpan(items);
	comboState& state = std::any_cast<comboState&>(widgets[widgetCounter].state);

	comboWidget* input = static_cast<comboWidget*>(widgets[widgetCounter].widget);

	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		input->label->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	if(state.itemsHash != itemsHash){
		input->combo->clear();
		for(unsigned int i=0;i<items.size();i++){
			input->combo->addItem(QString::fromStdString(std::string(items[i])));
		}
		state.itemsHash = itemsHash;
	}

	if(current_item){
		if(state.selectionNum != *current_item){
			input->combo->setCurrentIndex(*current_item);
			state.selectionNum = *current_item;
		}else if(state.selectionNum != input->combo->currentIndex()){
			state.selectionNum = input->combo->currentIndex();
			*current_item = state.selectionNum;

			widgetCounter++;
			return true;
		}
	}

	widgetCounter++;
	return false;
}

size_t hashCharptrSpan(const std::span<const char*> items){
	size_t itemsHash = 0;
	for(unsigned int i=0;i<items.size();i++){
		std::hash_combine(itemsHash, std::string_view(items[i]));
	}
	return itemsHash;
}

bool internal::combo(const std::string_view label, int* current_item, const std::span<const char*> items){
	std::string_view defaultSelected;
	if(current_item)
		defaultSelected = std::string_view(items[*current_item]);
	else
		defaultSelected = std::string_view("");

	if(emplaceCorrectQWidget<comboWidget, combo_type>(label, defaultSelected, items)){
		widgets[widgetCounter].valueHash = std::hash<std::string_view>{}(label);
		widgets[widgetCounter].state = comboState{hashCharptrSpan(items), current_item ? *current_item : 0};
		widgetCounter++;
		return false;
	}

	auto labelHash = std::hash<std::string_view>{}(label);
	size_t itemsHash = hashCharptrSpan(items);
	comboState& state = std::any_cast<comboState&>(widgets[widgetCounter].state);

	comboWidget* input = static_cast<comboWidget*>(widgets[widgetCounter].widget);

	//widget exists, type is text
	if(widgets[widgetCounter].valueHash != labelHash){
		input->label->setText(QString::fromStdString(std::string(label)));
		widgets[widgetCounter].valueHash = labelHash;
	}

	if(state.itemsHash != itemsHash){
		input->combo->clear();
		for(unsigned int i=0;i<items.size();i++){
			input->combo->addItem(QString::fromStdString(std::string(items[i])));
		}
		state.itemsHash = itemsHash;
	}

	if(current_item){
		if(state.selectionNum != *current_item){
			input->combo->setCurrentIndex(*current_item);
			state.selectionNum = *current_item;
		}else if(state.selectionNum != input->combo->currentIndex()){
			state.selectionNum = input->combo->currentIndex();
			*current_item = state.selectionNum;

			widgetCounter++;
			return true;
		}
	}

	widgetCounter++;
	return false;
}

bool internal::combo(const std::string_view label, int* current_item, const char** items, unsigned int num_items){
	return combo(label, current_item, std::span<const char*>(items, num_items));
}

