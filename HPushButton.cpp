#include "HPushButton.h"
#include "HLang.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	DefineMemberFunction("setText", &HPushButton::hsetText);
}

HPushButton::~HPushButton()
{
}

H_MemberFunction_def(hsetText, HPushButton)
{
	CheckArgs(1);
	this->setText(IsVarrsToStr(__arglist.toStringList().at(0)));
	return HOBJECTS(true);
}