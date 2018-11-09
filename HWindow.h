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
	H_MemberFunction_def(hshow, HWindow);
	H_MemberFunction_def(hhide, HWindow);
	H_MemberFunction_def(hadd, HWindow);
	H_MemberFunction_def(hsetTitle, HWindow);
private:
	Ui::HWindow ui;
};
