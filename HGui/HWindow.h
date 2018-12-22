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
	HPointer hshow(HArgs args);
	HPointer hhide(HArgs args);
	HPointer hadd(HArgs args);
	HPointer hsetTitle(HArgs args);
private:
	Ui::HWindow ui;
};
