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
			whenClicked->run(HArgs()).clear();
	});
	MDebug("Constructed");
}

HPushButton::~HPushButton()
{
	MDebug("Destructed");
}

HPointer HPushButton::hconnect(HArgs args)
{
	CheckArgs(2);
	CheckArgsType(0, HString);
	CheckArgsType(1, HFunction);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "clicked") {
		this->whenClicked = HObjectHelper(args[1]).to<HFunction>();
		return HPointer(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}

HPointer HPushButton::hdisconnect(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	if (HObjectHelper(args[0]).to<HString>()->toQString() == "clicked") {
		this->whenClicked = nullptr;
		return HPointer(new HVoid);
	}
	throw HError(HError::RT_ERROR, WhyConnectSlotError);
}
HPointer HPushButton::hsetText(HArgs args)
{
	CheckArgs(1);
	CheckArgsType(0, HString);
	this->setText(HObjectHelper(args[0]).to<HString>()->toQString());
	return HPointer(new HVoid);
}