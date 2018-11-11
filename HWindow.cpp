#include "HWindow.h"
#include <QPushbutton>
#include "HLang.h"
#include "HBool.h"
#include "HString.h"
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

H_MemberFunction_def(hsetTitle, HWindow)
{
	CheckArgs(1);
	SetupArgs;
	this->setWindowTitle(HObjTo(HMain->accessclass(GetArg(0)), HString*)->toQString());
	return new HBool(true);
}

H_MemberFunction_def(hadd, HWindow)
{
	CheckArgs(1);
	SetupArgs;
	if (HMain->accessclass(GetArg(0))->QGuiClassHandle == nullptr)
		return new HBool(false);
	ui.main->addWidget(HMain->accessclass(GetArg(0))->QGuiClassHandle);
	return new HBool(true);
}

H_MemberFunction_def(hshow, HWindow)
{
	CheckArgs(0);
	this->show();
	return new HBool(true);
}
H_MemberFunction_def(hhide, HWindow)
{
	CheckArgs(0);
	this->hide();
	return new HBool(true);
}