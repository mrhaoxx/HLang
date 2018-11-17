#include "HPushButton.h"
#include "HBaseInterface.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	IsGuiClass;
	DefineMemberFunction("setText", &HPushButton::hsetText);
	DefineMemberFunction("setClicked", &HPushButton::setClicked);
	connect(this, &HPushButton::clicked, this, [&] {
		if (whenClicked != nullptr)
			whenClicked->hexec(HArgs());
	});
}

HPushButton::~HPushButton()
{
}

HObject* HPushButton::setClicked(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HFunction>() != nullptr)
	{
		whenClicked = HObjectHelper(args[0]).to<HFunction>();
		return new HRet(true);
	}
	else
	{
		return new HRet(nullptr, false, WhyHPushButtonSetClickedFailed);
	}
}

HObject* HPushButton::hsetText(HArgs args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		this->setText(HObjectHelper(args[0]).to<HString>()->toQString());
		return new HRet(true);
	}
	else
	{
		return new HRet(nullptr, false, WhyHPushButtonSetTextFailed);
	}
}