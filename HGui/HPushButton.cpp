#include "HPushButton.h"
#include "HBaseInterface.h"
HPushButton::HPushButton(QWidget *parent)
	: QPushButton(parent)
{
	IsGuiClass;
	DefineMemberFunction(HPushButton, "setText", &HPushButton::hsetText);
	DefineMemberFunction(HPushButton, "connect", &HPushButton::hconnect);
	DefineMemberFunction(HPushButton, "disconnect", &HPushButton::hdisconnect);
	this->connect(this, &HPushButton::clicked, this, [&] {
		if (whenClicked != nullptr)
			delete whenClicked->run(HArgs());
	});
	MDebug("Constructed");
}

HPushButton::~HPushButton()
{
	MDebug("Destructed");
}

HObject* HPushButton::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "clicked") {
		this->whenClicked = HObjectHelper(args[1]).to<HFunction>();
		return new HVoid;
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

HObject* HPushButton::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "clicked") {
		this->whenClicked = nullptr;
		return new HVoid;
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}
HObject* HPushButton::hsetText(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->setText(HObjectHelper(args[0]).to<HString>()->toQString());
	return new HVoid;
}