#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_agregarInicio_clicked();

    void on_agregarFinal_clicked();

    void on_guardar_clicked();

    void on_recuperar_clicked();

private:
    Ui::Widget *ui;

    enum Columna
    {
        ID, VOLTAJE, POS_X, POS_Y, RED, GREEN, BLUE
    };
};
#endif // WIDGET_H
