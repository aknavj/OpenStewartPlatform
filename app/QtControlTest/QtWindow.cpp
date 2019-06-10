#include <QGridLayout>
#include <QTimer>
#include <math.h>

#include "QtWindow.h"
#include "QtAdjRangeSlider.h"

/*
 */
CServoWindow::CServoWindow(CSerialConnection *conn, QWidget * parent) : QWidget(parent) {
	connection = conn;

	QGridLayout *layout = new QGridLayout;
	
	CAdjRangeSlider *slider1 = new CAdjRangeSlider(0,250,QString("Servo1"));
	slider1->setId(0);
	connect(slider1, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider2 = new CAdjRangeSlider(0,250,QString("Servo2"));
	slider2->setId(1);
	connect(slider2, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider3 = new CAdjRangeSlider(0,250,QString("Servo3"));
	slider3->setId(2);
	connect(slider3, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider4 = new CAdjRangeSlider(0,250,QString("Servo4"));
	slider4->setId(3);
	connect(slider4, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider5 = new CAdjRangeSlider(0,250,QString("Servo5"));
	slider5->setId(4);
	connect(slider5, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider6 = new CAdjRangeSlider(0,250,QString("Servo6"));
	slider6->setId(5);
	connect(slider6, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	layout->addWidget(slider1,0,0);
	layout->addWidget(slider2,1,0);
	layout->addWidget(slider3,2,0);
	layout->addWidget(slider4,0,1);
	layout->addWidget(slider5,1,1);
	layout->addWidget(slider6,2,1);
	setLayout(layout);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeEvent()));
	timer->setInterval(30);
	timer->setSingleShot(false);
	timeCount = 0;
}

/*
 */
void CServoWindow::changeValue(int servo, int value) {
	unsigned char data[2] = {(unsigned char)servo, (unsigned char)(value+5)};
	connection->send(data, 2);
}

/*
 */
void CServoWindow::timeEvent() {

	if(timeCount > 124) timeCount = 0;

	unsigned char data[6][2]={
		{0,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)},
		{1,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)},
		{2,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)},
		{3,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)},
		{4,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)},
		{5,(unsigned char)(((cos((double)timeCount/20)*125)+125)+5)}
	};

	connection->send(data[0], 2);
	connection->send(data[1], 2);
	connection->send(data[2], 2);
	connection->send(data[3], 2);
	connection->send(data[4], 2);
	connection->send(data[5], 2);

	timeCount++;
}
