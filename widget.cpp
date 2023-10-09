#include "widget.h"
#include "ui_widget.h"
#include "neuronadialog.h"
#include <iostream>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>

void Widget::connClose()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Widget::connOpen()
{
    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/anama.DESKTOP-NLSIKUB/Desktop/6anamos/SeminarioAlgoritmia/QTableWidget/database.db");
    if(!mydb.open()){
        return false;
    }else{
        return true;
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Neuronas");
    connOpen();

    QStringList titulos;
    ui->tableWidget->setColumnCount(7);
    titulos << "ID" << "Voltaje" << "Posición en X" << "Posición en Y" << "Red" << "Green" << "Blue";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_agregarInicio_clicked()
{
    int res, fila, id, pos_x, pos_y, red, green, blue;
    float voltaje;
    NeuronaDialog nd(this);
    nd.setWindowTitle("Captura de neurona");
    res = nd.exec();
    if(res==QDialog::Rejected)
        return;
    id=nd.id();
    voltaje=nd.voltaje();
    pos_x=nd.pos_x();
    pos_y=nd.pos_y();
    red=nd.red();
    green=nd.green();
    blue=nd.blue();
    ui->tableWidget->insertRow(0);
    fila=0;
    ui->tableWidget->setItem(fila, ID, new QTableWidgetItem(QString::number(id)));
    ui->tableWidget->setItem(fila, VOLTAJE, new QTableWidgetItem(QString::number(voltaje)));
    ui->tableWidget->setItem(fila, POS_X, new QTableWidgetItem(QString::number(pos_x)));
    ui->tableWidget->setItem(fila, POS_Y, new QTableWidgetItem(QString::number(pos_y)));
    ui->tableWidget->setItem(fila, RED, new QTableWidgetItem(QString::number(red)));
    ui->tableWidget->setItem(fila, GREEN, new QTableWidgetItem(QString::number(green)));
    ui->tableWidget->setItem(fila, BLUE, new QTableWidgetItem(QString::number(blue)));
}


void Widget::on_agregarFinal_clicked()
{
    int res, fila, id, pos_x, pos_y, red, green, blue;
    float voltaje;
    NeuronaDialog nd(this);
    nd.setWindowTitle("Captura de neurona");
    res = nd.exec();
    if(res==QDialog::Rejected)
        return;
    id=nd.id();
    voltaje=nd.voltaje();
    pos_x=nd.pos_x();
    pos_y=nd.pos_y();
    red=nd.red();
    green=nd.green();
    blue=nd.blue();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    fila=ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(fila, ID, new QTableWidgetItem(QString::number(id)));
    ui->tableWidget->setItem(fila, VOLTAJE, new QTableWidgetItem(QString::number(voltaje)));
    ui->tableWidget->setItem(fila, POS_X, new QTableWidgetItem(QString::number(pos_x)));
    ui->tableWidget->setItem(fila, POS_Y, new QTableWidgetItem(QString::number(pos_y)));
    ui->tableWidget->setItem(fila, RED, new QTableWidgetItem(QString::number(red)));
    ui->tableWidget->setItem(fila, GREEN, new QTableWidgetItem(QString::number(green)));
    ui->tableWidget->setItem(fila, BLUE, new QTableWidgetItem(QString::number(blue)));
}



void Widget::on_guardar_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * FROM neurona");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() <<(modal->rowCount());
}


void Widget::on_recuperar_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * FROM neurona");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() <<(modal->rowCount());
}


void Widget::on_buscarId_textChanged(const QString &arg1)
{
    QString id=arg1;
    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM neurona WHERE id='"+id+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->listWidget->clear();
            ui->listWidget->insertItem(0,qry.value(0).toString());
            ui->listWidget->insertItem(1,qry.value(1).toString());
            ui->listWidget->insertItem(2,qry.value(2).toString());
            ui->listWidget->insertItem(3,qry.value(3).toString());
            ui->listWidget->insertItem(4,qry.value(4).toString());
            ui->listWidget->insertItem(5,qry.value(5).toString());
            ui->listWidget->insertItem(6,qry.value(6).toString());
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}

