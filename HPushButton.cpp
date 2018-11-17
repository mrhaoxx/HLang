#include "HPushButton.h"
#include "HBaseInterface.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	IsGuiClass;
	DefineMemberFunction("setText", &HPushButton::hsetText);
	DefineMemberFunction("setClicked", &HPushButton::setClick);
	connect(this, &HPushButton::clicked, this, [&] {
		if (whenClicked != nullptr)
			whenClicked->hexec(std::vector<HObject*>());
	});
}

HPushButton::~HPushButton()
{
}

HObject* HPushButton::setClick(std::vector<HObject*> args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HFunction>() != nullptr)
	{
		whenClicked = HObjectHelper(args[0]).to<HFunction>();
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}

HObject* HPushButton::hsetText(std::vector<HObject*> args)
{
	CheckArgs(1);
	if (HObjectHelper(args[0]).to<HString>() != nullptr)
	{
		this->setText(HObjectHelper(args[0]).to<HString>()->toQString());
		return new HBool(true);
	}
	else
	{
		return new HBool(false);
	}
}