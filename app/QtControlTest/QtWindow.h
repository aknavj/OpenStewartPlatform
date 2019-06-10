#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <QWidget>
#include <QObject>

#include "QtSerialConnection.h"

/*
 */
class CServoWindow : public QWidget {
		
		Q_OBJECT

	public:
        CServoWindow(CSerialConnection *conn,QWidget * parent = 0);
	
	public slots:
		void changeValue(int, int);
		void timeEvent();

	private:
		CSerialConnection *connection;
		int timeCount;
};

#endif /* __WINDOW_H__ */
