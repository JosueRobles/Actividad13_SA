#include "widget.h"

#include <QApplication>
#include <map>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Widget w;
    w.show();
    return a.exec();
}
