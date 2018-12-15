#pragma once
#include "HObject.h"
#include <QWidget>
#include "ui_HWindow.h"

class HWindow : public QWidget, public HObject
{
	Q_OBJECT;
	H_OBJECT(HWindow)
public:
	HWindow(QWidget *parent = Q_NULLPTR);
	~HWindow();
	QSharedPointer<HObject> hshow(HArgs args);
	QSharedPointer<HObject> hhide(HArgs args);
	QSharedPointer<HObject> hadd(HArgs args);
	QSharedPointer<HObject> hsetTitle(HArgs args);
private:
	Ui::HWindow ui;
};
