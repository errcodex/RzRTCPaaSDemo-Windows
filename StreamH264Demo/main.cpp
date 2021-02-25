
#include <QtWidgets/QApplication>
#include "StreamH264Demo.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	StreamH264Demo::instance()->initialize();
	StreamH264Demo::instance()->createWindow(H264_WINDOW::WELCOME)->show();

    return a.exec();
}
