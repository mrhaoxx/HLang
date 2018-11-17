#pragma once
#include "HObject.h"
#include <QWidget>
#include "ui_HWindow.h"

class HWindow : public QWidget, public HObject
{
	Q_OBJECT;
	H_OBJECT(HWindow)
public:
	HWindow(QWidget *parent = Q_NULLPTR);
	~HWindow();
	HObject* hshow(std::vector<HObject*> args);
	HObject* hhide(std::vector<HObject*> args);
	HObject* hadd(std::vector<HObject*> args);
	HObject* hsetTitle(std::vector<HObject*> args);
private:
	Ui::HWindow ui;
};
