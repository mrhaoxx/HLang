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
	QSharedPointer<HObject> hconnect(HArgs args);
	QSharedPointer<HObject> hdisconnect(HArgs args);
	QSharedPointer<HObject> hsetText(HArgs args);
private:
	QSharedPointer<HFunction> whenClicked = nullptr;
};
