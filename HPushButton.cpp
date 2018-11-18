#include "HPushButton.h"
#include "HBaseInterface.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	IsGuiClass;
	DefineMemberFunction("setText", &HPushButton::hsetText);
	DefineMemberFunction("setClicked", &HPushButton::setClicked);
	DefineMemberFunction("setClickedArgs", &HPushButton::setClickedArgs);
	connect(this, &HPushButton::clicked, this, [&] {
		if (whenClicked != nullptr)
			whenClicked->hexec((whenClickedArgs == nullptr) ? HArgs() : *whenClickedArgs);
	});
}

HPushButton::~HPushButton()
{
}

HObject* HPushButton::setClicked(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HFunction);
	whenClicked = HObjectHelper(args[0]).to<HFunction>();
	return new HRet(true);
}

HObject* HPushButton::hsetText(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->setText(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HRet(true);
}
HObject* HPushButton::setClickedArgs(HArgs args)
{
	this->whenClickedArgs = new HArgs(args);
	return new HRet(true);
}