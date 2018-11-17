#include "HWindow.h"
#include <QPushbutton>
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

HObject* HWindow::hsetTitle(std::vector<HObject*> args)
{
	CheckArgs(1);
	this->setWindowTitle(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HBool(true);
}

HObject* HWindow::hadd(std::vector<HObject*> args)
{
	CheckArgs(1);
	if (args[0]->QGuiClassHandle == nullptr)
		return new HBool(false);
	ui.main->addWidget(args[0]->QGuiClassHandle);
	return new HBool(true);
}

HObject* HWindow::hshow(std::vector<HObject*> args)
{
	CheckArgs(0);
	this->show();
	return new HBool(true);
}
HObject* HWindow::hhide(std::vector<HObject*> args)
{
	CheckArgs(0);
	this->hide();
	return new HBool(true);
}