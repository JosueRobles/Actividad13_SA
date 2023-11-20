#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QDebug>
#include <QtGui>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
//#include "grafo.h"
//#include "algoritmos.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QSqlDatabase mydb;
    void connClose();
    bool connOpen();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_agregarInicio_clicked();

    void on_agregarFinal_clicked();

    void on_guardar_clicked();

    void on_recuperar_clicked();

    void on_buscarId_textChanged(const QString &arg1);

    void escenas();

    void on_sortId_clicked();

    void on_sortVoltaje_clicked();

    void on_mostrarPuntos_clicked();

    void on_mostrarLineas_clicked();

    void on_busquedaAmplitud_clicked();

private:
    Ui::Widget *ui;

    enum Columna
    {
        ID, VOLTAJE, POS_X, POS_Y, RED, GREEN, BLUE
    };

    QGraphicsScene *esce;
    QGraphicsEllipseItem *elip;
    QGraphicsLineItem *line;
    QGraphicsTextItem *text;
};
#endif // WIDGET_H
