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

private:
    Ui::Widget *ui;

    enum Columna
    {
        ID, VOLTAJE, POS_X, POS_Y, RED, GREEN, BLUE
    };
};
#endif // WIDGET_H
