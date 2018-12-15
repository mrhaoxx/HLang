#include "HWindow.h"
#include <QPushButton>
#include "HBaseInterface.h"
HWindow::HWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	DefineMemberFunction(HWindow, "show", &HWindow::hshow);
	DefineMemberFunction(HWindow, "hide", &HWindow::hhide);
	DefineMemberFunction(HWindow, "add", &HWindow::hadd);
	DefineMemberFunction(HWindow, "setTitle", &HWindow::hsetTitle);
	MDebug("Constructed");
}

HWindow::~HWindow()
{
	MDebug("Destructed");
}

QSharedPointer<HObject> HWindow::hsetTitle(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->setWindowTitle(HObjectHelper(args[0]).to<HString>()->toQString());
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HWindow::hadd(HArgs args)
{
	CheckArgs(1);
	if (args[0]->QGuiClassHandle == nullptr)
		throw HError(HError::RT_ERROR, WhyHWindowAddWeightFailed);
	ui.main->addWidget(args[0]->QGuiClassHandle);
	return QSharedPointer<HObject>(new HVoid);
}

QSharedPointer<HObject> HWindow::hshow(HArgs args)
{
	CheckArgs(0);
	this->show();
	return QSharedPointer<HObject>(new HVoid);
}
QSharedPointer<HObject> HWindow::hhide(HArgs args)
{
	CheckArgs(0);
	this->hide();
	return QSharedPointer<HObject>(new HVoid);
}