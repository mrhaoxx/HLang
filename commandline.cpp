#include "commandline.h"
#include "ui_commandline.h"

commandline::commandline(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::commandline)
{
    ui->setupUi(this);
}

commandline::~commandline()
{
    delete ui;
}

void commandline::on_lineEdit_returnPressed()
{
    ui->textBrowser->setText(ui->textBrowser->document()->toPlainText()+ui->lineEdit->text());
    if (ui->lineEdit->text().split(Separator).length()>1)
    {
        if (map[ui->lineEdit->text().split(Separator)[0]])
        {
            if (map[ui->lineEdit->text().split(Separator)[0]]->map.contains(ui->lineEdit->text().split(Separator)[1])){
                map[ui->lineEdit->text().split(Separator)[0]]->map[ui->lineEdit->text().split(Separator)[1]](HArgs(ui->lineEdit->text()));
                ui->textBrowser->append(Separator);
                ui->textBrowser->append(">>");
            }
            else
            {
                ui->textBrowser->append("Command Not Find");
                ui->textBrowser->append(">>");
            }
        }
        else
        {
            ui->textBrowser->append("Namespace Not Find");
            ui->textBrowser->append(">>");
        }
    }
    else
    {
        ui->textBrowser->append("Command len not right");
        ui->textBrowser->append(">>");
    }
    ui->lineEdit->clear();
}
