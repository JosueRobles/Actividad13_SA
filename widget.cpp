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
#include <math.h>

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

    escenas();
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
    ui->listWidget->clear();
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->listWidget->insertItem(0,"ID: "+qry.value(0).toString());
            ui->listWidget->insertItem(1,"Voltaje: "+qry.value(1).toString());
            ui->listWidget->insertItem(2,"Pos. en x: "+qry.value(2).toString());
            ui->listWidget->insertItem(3,"Pos. en y: "+qry.value(3).toString());
            ui->listWidget->insertItem(4,"Red: "+qry.value(4).toString());
            ui->listWidget->insertItem(5,"Green: "+qry.value(5).toString());
            ui->listWidget->insertItem(6,"Blue: "+qry.value(6).toString());
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}


void Widget::escenas()
{
    connOpen();
    esce = new QGraphicsScene(this);
    ui->graphicsView->setScene(esce);

    QSqlQuery qry;
    qry.prepare("SELECT * FROM neurona");
    if(qry.exec())
    {
        while(qry.next())
        {
            QBrush rgbBrush;
            QPen rgbPen;
            float vtj=qry.value(1).toFloat();
            int px=qry.value(2).toInt();
            int py=qry.value(3).toInt();
            int r=qry.value(4).toInt();
            int g=qry.value(5).toInt();
            int b=qry.value(6).toInt();
            QColor color(r,g,b);
            rgbBrush.setColor(color);
            rgbPen.setColor(color);
            rgbPen.setWidth(1);
            elip = esce->addEllipse(px,py,vtj,vtj,rgbPen,rgbBrush);
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}

void Widget::on_sortId_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * FROM neurona ORDER BY id ASC");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
}


void Widget::on_sortVoltaje_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("SELECT * FROM neurona ORDER BY voltaje DESC");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
}


void Widget::on_mostrarPuntos_clicked()
{
    connOpen();
    esce = new QGraphicsScene(this);
    ui->graphicsView->setScene(esce);

    QSqlQuery qry;
    qry.prepare("SELECT * FROM neurona");
    if(qry.exec())
    {
        while(qry.next())
        {
            QBrush rgbBrush;
            QPen rgbPen;
            QString id=qry.value(0).toString();
            int px=qry.value(2).toInt();
            int py=qry.value(3).toInt();
            int r=qry.value(4).toInt();
            int g=qry.value(5).toInt();
            int b=qry.value(6).toInt();
            QColor color(r,g,b);
            rgbBrush.setColor(color);
            rgbPen.setColor(color);
            rgbPen.setWidth(1);
            text=esce->addText(id);
            text->setPos(px-6,py-6);
            elip = esce->addEllipse(px,py,1,1,rgbPen,rgbBrush);
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}


void Widget::on_mostrarLineas_clicked()
{
    connOpen();
    esce = new QGraphicsScene(this);
    ui->graphicsView->setScene(esce);
    QSqlQuery qry;

    qry.prepare("SELECT * FROM neurona ORDER BY pos_x|pos_y ASC");
    if(qry.exec())
    {
        QPen rgbPen;
        rgbPen.setWidth(1);
        int px1,px2,py1,py2, r,g,b;
        QString id;
        float peso;
        id=qry.value(0).toString();
        px1=qry.value(2).toInt();
        py1=qry.value(3).toInt();
        text=esce->addText(id);
        text->setPos(px1-6,py1-6);
        while(qry.next()){
            id=qry.value(0).toString();
            px2=qry.value(2).toInt();
            py2=qry.value(3).toInt();
            r=qry.value(4).toInt();
            g=qry.value(5).toInt();
            b=qry.value(6).toInt();
            QColor color(r,g,b);
            rgbPen.setColor(color);
            text=esce->addText(id);
            text->setPos(px2-6,py2-6);
            line = esce->addLine(px1,py1,px2,py2,rgbPen);
            peso=sqrt(((px2-px1)*(px2-px1))+((py2-py1)*(py2-py1)));
            text=esce->addText(QString::number(peso));
            text->setPos(px2-px1,py2-py1);
            text->setDefaultTextColor(color);
            px1=px2;
            py1=py2;
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}

void Widget::on_busquedaAmplitud_clicked()
{
    connOpen();
    esce = new QGraphicsScene(this);
    ui->graphicsView->setScene(esce);
    QSqlQuery qry;

    qry.prepare("SELECT * FROM neurona ORDER BY pos_x|pos_y ASC");
    if(qry.exec())
    {
        QPen rgbPen;
        rgbPen.setWidth(4);
        int px1,px2,py1,py2;
        QString id1,id2;
        float peso;
        ui->plainTextEdit->insertPlainText("Lista Visitados");
        id1=qry.value(0).toString();
        px1=qry.value(2).toInt();
        py1=qry.value(3).toInt();
        text=esce->addText(id1);
        text->setPos(px1-6,py1-6);
        ui->plainTextEdit->appendPlainText(id1);
        while(qry.next()){
            id2=qry.value(0).toString();
            px2=qry.value(2).toInt();
            py2=qry.value(3).toInt();
            QColor color(1,250,1);
            rgbPen.setColor(color);
            ui->plainTextEdit->appendPlainText(id2);
            text=esce->addText(id2);
            text->setPos(px2-6,py2-6);
            line = esce->addLine(px1,py1,px2,py2,rgbPen);
            peso=sqrt(((px2-px1)*(px2-px1))+((py2-py1)*(py2-py1)));
            text=esce->addText(QString::number(peso));
            text->setPos(px2-px1,py2-py1);
            text->setDefaultTextColor(color);
            id1=id2;
            px1=px2;
            py1=py2;
        }
        connClose();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }
}
