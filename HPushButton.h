#pragma once

#include <QPushButton>
#include "HObject.h"
#include "HBaseInterface.h"
class HPushButton : private QPushButton, public HObject
{
	Q_OBJECT;
	H_OBJECT(HPushButton);
public:
	HPushButton(QWidget *parent);
	~HPushButton();
	H_MemberFunction_def(hsetText, HPushButton);
	H_MemberFunction_def(setClick, HPushButton);
private:
	HFunction *whenClicked = nullptr;
};
