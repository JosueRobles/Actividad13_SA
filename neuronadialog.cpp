#include "neuronadialog.h"
#include "ui_neuronadialog.h"

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
