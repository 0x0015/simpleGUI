#pragma once
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

class textInputWidget : public QWidget{
	Q_OBJECT
public:
	textInputWidget(QWidget* parent = nullptr);
	textInputWidget(const std::string_view s_label, const std::string_view s_text, QWidget* parent = nullptr);
	~textInputWidget() = default;
	QHBoxLayout* layout;
	QLabel* label;
	QLineEdit* textEdit;
};
