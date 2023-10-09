#include "neuronadialog.h"
#include "ui_neuronadialog.h"
#include <QMessageBox>

NeuronaDialog::NeuronaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NeuronaDialog)
{
    ui->setupUi(this);
}

NeuronaDialog::~NeuronaDialog()
{
    delete ui;
}

void NeuronaDialog::on_buttonBox_accepted()
{
    Widget conn;
    QString id, voltaje, pos_x, pos_y, red, green, blue;
    id=ui->id->text();
    voltaje=ui->voltaje->text();
    pos_x=QString::number(ui->pos_x->value());
    pos_y=QString::number(ui->pos_y->value());
    red=ui->red->text();
    green=ui->green->text();
    blue=ui->blue->text();

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("INSERT INTO neurona (id,voltaje,pos_x,pos_y,red,green,blue) VALUES ('"+id+"','"+voltaje+"','"+pos_x+"','"+pos_y+"','"+red+"','"+green+"','"+blue+"')");
    if(qry.exec())
    {
        QMessageBox::critical(this,tr("SAVE"),tr("Saved"));
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
    accept();
}

void NeuronaDialog::on_buttonBox_rejected()
{
    reject();
}

int NeuronaDialog::id() const
{
    return ui->id->text().toInt();
}
float NeuronaDialog::voltaje() const
{
    return ui->voltaje->text().toFloat();
}
int NeuronaDialog::pos_x() const
{
    return ui->pos_x->value();
}
int NeuronaDialog::pos_y() const
{
    return ui->pos_y->value();
}
int NeuronaDialog::red() const
{
    return ui->red->text().toInt();
}
int NeuronaDialog::green() const
{
    return ui->green->text().toInt();
}
int NeuronaDialog::blue() const
{
    return ui->blue->text().toInt();
}
