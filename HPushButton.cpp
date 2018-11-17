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
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>() != nullptr)
	{
		whenClicked = HLangHelper(HMain->accessclass(GetArg(0))).to<HFunction>();
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
	if (HLangHelper(HMain->accessclass(GetArg(0))).to<HString>() != nullptr)
	{
		this->setText(HLangHelper(HMain->accessclass(GetArg(0))).to<HString>()->toQString());
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}