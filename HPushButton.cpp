#include "HPushButton.h"
#include "HLang.h"
#include "HBool.h"
#include "HString.h"
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
	SetupArgs;
	this->setText(*(QString*)HObjTo(HMain->accessclass(GetArg(0)), HLang*));
	return new HBool(true);
}