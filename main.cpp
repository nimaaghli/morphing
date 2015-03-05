
#include <QtWidgets/QApplication>
#include "morphing.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    morphing w;
    w.show();
    
    return a.exec();
}
