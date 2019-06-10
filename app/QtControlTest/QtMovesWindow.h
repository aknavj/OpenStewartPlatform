#ifndef __MOVES_WINDOW_H__
#define __MOVES_WINDOW_H__

#include <QWidget>
#include <QObject>

#include "QtSerialConnection.h"

/*
 */
class CMovesWindow : public QWidget {

		Q_OBJECT
			
	public:
        CMovesWindow(CSerialConnection *conn,QWidget * parent = 0);

	public slots:
		void changeValue(int, int);
		void timeEvent();

	private:
	
		CSerialConnection *connection;
		int timeCount;
		unsigned char servoValues[6][2];
		unsigned char oldSliderVals[6][2];
};

#endif /* __MOVES_WINDOW_H__ */
