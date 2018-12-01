#include "HWindow.h"
#include <QPushButton>
#include "HBaseInterface.h"
HWindow::HWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	DefineMemberFunction("show", &HWindow::hshow);
	DefineMemberFunction("hide", &HWindow::hhide);
	DefineMemberFunction("add", &HWindow::hadd);
	DefineMemberFunction("setTitle", &HWindow::hsetTitle);
}

HWindow::~HWindow()
{
}

HObject* HWindow::hsetTitle(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->setWindowTitle(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HVoid;
}

HObject* HWindow::hadd(HArgs args)
{
	CheckArgs(1);
	if (args[0]->QGuiClassHandle == nullptr)
		throw HError(HError::RT_ERROR, WhyHWindowAddWeightFailed);
	ui.main->addWidget(args[0]->QGuiClassHandle);
	return new HVoid;
}

HObject* HWindow::hshow(HArgs args)
{
	CheckArgs(0);
	this->show();
	return new HVoid;
}
HObject* HWindow::hhide(HArgs args)
{
	CheckArgs(0);
	this->hide();
	return new HVoid;
}