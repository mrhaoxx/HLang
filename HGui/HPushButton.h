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
	HPointer hconnect(HArgs args);
	HPointer hdisconnect(HArgs args);
	HPointer hsetText(HArgs args);
private:
	QSharedPointer<HFunction> whenClicked = nullptr;
};
