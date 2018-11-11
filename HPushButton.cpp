#include "HPushButton.h"
#include "HLang.h"
#include "HBool.h"
#include "HString.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	IsGuiClass;
	DefineMemberFunction("setText", &HPushButton::hsetText);
	DefineMemberFunction("setClicked", &HPushButton::setClick);
	connect(this, &HPushButton::clicked, this, [&] {
		if (whenClicked != nullptr)
			whenClicked->hexec(HOBJECTS(), HOBJECTS());
	});
}

HPushButton::~HPushButton()
{
}

H_MemberFunction_def(setClick, HPushButton)
{
	CheckArgs(1);
	SetupArgs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HFunction*) != nullptr)
	{
		whenClicked = HObjTo(HMain->accessclass(GetArg(0)), HFunction*);
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}

H_MemberFunction_def(hsetText, HPushButton)
{
	CheckArgs(1);
	SetupArgs;
	if (HObjTo(HMain->accessclass(GetArg(0)), HString*) != nullptr)
	{
		this->setText(HObjTo(HMain->accessclass(GetArg(0)), HString*)->toQString());
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}