#include "HWindow.h"
#include <QPushbutton>
#include "HLang.h"
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
	this->setWindowTitle(IsVarrsToStr(__arglist.toStringList().at(0)));
	return HOBJECTS(true);
}

H_MemberFunction_def(hadd, HWindow)
{
	CheckArgs(1);
	if (HMain->accessQGuiclass(__arglist.toStringList().at(0)) == nullptr)
		return HOBJECTS(false);
	ui.main->addWidget(HMain->accessQGuiclass(__arglist.toStringList().at(0)));
	return HOBJECTS(true);
}

H_MemberFunction_def(hshow, HWindow)
{
	this->show();
	return HOBJECTS(true);
}
H_MemberFunction_def(hhide, HWindow)
{
	this->hide();
	return HOBJECTS(true);
}