#include <QApplication>
#include <stdio.h>

#include "QtWindow.h"
#include "QtMovesWindow.h"
#include "QtSerialConnection.h"

/*
 */
int main(int argc ,char **args) {

	char *device = "/dev/ttyUSB1";

	CSerialConnection *serial = new CSerialConnection(device);

	if(serial->erroNo != EOK) {
		printf("%d\n", serial->erroNo);
	}
	  
    serial->setBaud(9600);
    if(serial->erroNo != EOK) {
		printf("%d\n", serial->erroNo);
    }
	  
    serial->setCharSize(8);
    if(serial->erroNo != EOK) {
		printf("%d\n", serial->erroNo);
    }
	
    serial->setParity(0,0);
    if(serial->erroNo != EOK) {
		printf("%d\n", serial->erroNo);
    }
  
    serial->setStopBits(0);
    if(serial->erroNo != EOK) {
		printf("%d\n", serial->erroNo);
	}

    QApplication *app = new QApplication(argc, args);
	
    CServoWindow *window = new CServoWindow(serial);
    CMovesWindow *window2 = new CMovesWindow(serial);

    window2->show();
    window->show();
	
    int result = app->exec();

    delete window;
    delete app;
	
    serial->disconnect();
    delete serial;

    return result;
}
