#pragma once

#include <QPushButton>
#include "HObject.h"
#include "HBaseInterface.h"
#include "HLogic/HFunction.h"
class HPushButton : private QPushButton, public HObject
{
	Q_OBJECT;
	H_OBJECT(HPushButton);
public:
	HPushButton(QWidget *parent);
	~HPushButton();
	HObject* hconnect(HArgs args);
	HObject* hdisconnect(HArgs args);
	HObject* hsetText(HArgs args);
private:
	HFunction *whenClicked = nullptr;
};
