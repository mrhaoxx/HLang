#pragma once

#include <QPushButton>
#include "HObject.h"
#include "HBaseInterface.h"
#include "HFunction.h"
class HPushButton : private QPushButton, public HObject
{
	Q_OBJECT;
	H_OBJECT(HPushButton);
public:
	HPushButton(QWidget *parent);
	~HPushButton();
	HObject* hsetText(HArgs args);
	HObject* setClickedArgs(HArgs args);
	HObject* setClicked(HArgs args);
private:
	HFunction *whenClicked = nullptr;
	HArgs *whenClickedArgs = nullptr;
};
