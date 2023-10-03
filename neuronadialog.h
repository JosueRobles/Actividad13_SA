#ifndef NEURONADIALOG_H
#define NEURONADIALOG_H

#include <QDialog>

namespace Ui {
class NeuronaDialog;
}

class NeuronaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NeuronaDialog(QWidget *parent = nullptr);
    ~NeuronaDialog();

    int id() const;
    float voltaje() const;
    int pos_x() const;
    int pos_y() const;
    int red() const;
    int green() const;
    int blue() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NeuronaDialog *ui;
};

#endif // NEURONADIALOG_H
