#pragma once
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>

class comboWidget : public QWidget{
	Q_OBJECT
public:
	comboWidget(QWidget* parent = nullptr);
	comboWidget(const std::string_view s_label, const std::string_view s_text, const std::span<const std::span<char>> items, QWidget* parent = nullptr);
	~comboWidget() = default;
	QHBoxLayout* layout;
	QLabel* label;
	QComboBox* combo;
};
