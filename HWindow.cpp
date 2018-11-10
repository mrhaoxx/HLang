#include "HWindow.h"
#include <QPushbutton>
#include "HLang.h"
#include "HBool.h"
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
	this->setWindowTitle(*(QString*)HObjTo(HMain->accessclass(GetArg(0)), HLang*));
	return new HBool(true);
}

H_MemberFunction_def(hadd, HWindow)
{
	CheckArgs(1);
	SetupArgs;
	if (HMain->accessQGuiclass(GetArg(0)) == nullptr)
		return new HBool(false);
	ui.main->addWidget(HMain->accessQGuiclass(GetArg(0)));
	return new HBool(true);
}

H_MemberFunction_def(hshow, HWindow)
{
	this->show();
	return new HBool(true);
}
H_MemberFunction_def(hhide, HWindow)
{
	this->hide();
	return new HBool(true);
}