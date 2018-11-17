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
	HObject* hsetText(std::vector<HObject*> args);
	HObject* setClick(std::vector<HObject*> args);
private:
	HFunction *whenClicked = nullptr;
};
