#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include "HLang.h"
#include <QMainWindow>
namespace Ui {
	class commandline;
}

class commandline : public QMainWindow
{
	Q_OBJECT

public:
	explicit commandline(QWidget *parent = nullptr);
	~commandline();
	void add(QString str);
private slots:

	void on_lineEdit_returnPressed();

private:
	Ui::commandline *ui;
};
#endif // COMMANDLINE_H
