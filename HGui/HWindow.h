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
	HObject* hshow(HArgs args);
	HObject* hhide(HArgs args);
	HObject* hadd(HArgs args);
	HObject* hsetTitle(HArgs args);
private:
	Ui::HWindow ui;
};
