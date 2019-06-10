#include <QGridLayout>
#include <QTimer>
#include <math.h>
#include <stdio.h>

#include "QtMovesWindow.h"
#include "QtAdjRangeSlider.h"

/*
 */
CMovesWindow::CMovesWindow(CSerialConnection *conn, QWidget * parent) : QWidget(parent) {
	
	connection = conn;

	servoValues[0][0] = 0;
	servoValues[0][1] = 125;
	servoValues[1][0] = 1;
	servoValues[1][1] = 125;
	servoValues[2][0] = 2;
	servoValues[2][1] = 125;
	servoValues[3][0] = 3;
	servoValues[3][1] = 125;
	servoValues[4][0] = 4;
	servoValues[4][1] = 125;
	servoValues[5][0] = 5;
	servoValues[5][1] = 125;

	oldSliderVals[0][0] = 0;
	oldSliderVals[0][1] = 125;
	oldSliderVals[1][0] = 1;
	oldSliderVals[1][1] = 125;
	oldSliderVals[2][0] = 2;
	oldSliderVals[2][1] = 125;
	oldSliderVals[3][0] = 3;
	oldSliderVals[3][1] = 125;
	oldSliderVals[4][0] = 4;
	oldSliderVals[4][1] = 125;
	oldSliderVals[5][0] = 5;
	oldSliderVals[5][1] = 125;

	QGridLayout *layout = new QGridLayout;

	CAdjRangeSlider *slider1 = new CAdjRangeSlider(0,250,QString("Pitch"));
	slider1->setId(0);
	connect(slider1, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider2 = new CAdjRangeSlider(0,250,QString("Roll"));
	slider2->setId(1);
	connect(slider2, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider3 = new CAdjRangeSlider(0,250,QString("Yaw"));
	slider3->setId(2);
	connect(slider3, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider4 = new CAdjRangeSlider(0,250,QString("Sway"));
	slider4->setId(3);
	connect(slider4, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider5 = new CAdjRangeSlider(0,250,QString("Surge"));
	slider5->setId(4);
	connect(slider5, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	CAdjRangeSlider *slider6 = new CAdjRangeSlider(0,250,QString("Heave"));
	slider6->setId(5);
	connect(slider6, SIGNAL(valueChangedSl(int, int)), this, SLOT(changeValue(int, int)));

	layout->addWidget(slider1,0,0);
	layout->addWidget(slider2,1,0);
	layout->addWidget(slider3,2,0);
	layout->addWidget(slider4,0,1);
	layout->addWidget(slider5,1,1);
	layout->addWidget(slider6,2,1);
		
	setLayout(layout);
}

/*
 */
void CMovesWindow::changeValue(int move, int value) {
	
	switch(move) {
		case 0 :
			break;
		case 1 :
			break;
		case 2 :
			for(int i = 0; i < 6; i++) {
				if(servoValues[i][1] + (value - oldSliderVals[2][1]) > 150) {
				   servoValues[i][1] = 150;
				} else if(servoValues[i][1] + (value - oldSliderVals[2][1]) < 70) {
					servoValues[i][1] = 70;
				} else {
					servoValues[i][1] += value - oldSliderVals[2][1];
				}
		
				connection->send(servoValues[i], 2);
		
			}
			
			oldSliderVals[2][1] = value;
			
			break;
		case 3 :
			break;
		case 4 :
			break;
		case 5 :
			for(int i = 0; i < 6; i++) {
				if(i%2 == 0) {
					if(servoValues[i][1] + (value - oldSliderVals[5][1]) > 250) {
						servoValues[i][1] = 250;
					} else {
						servoValues[i][1] += value - oldSliderVals[5][1];
					}
				} else {
					if(servoValues[i][1] - (value - oldSliderVals[5][1]) < 0) {
						servoValues[i][1] = 0;
					}else {
						servoValues[i][1] -= value - oldSliderVals[5][1];
					}
				}
				
				connection->send(servoValues[i], 2);
			}
    
			oldSliderVals[5][1] = value;
			
			break;
    }

    printf("Sliders:\n");
    
	for(int i = 0; i < 6; i++) {
		printf("%d:%d\n", oldSliderVals[i][0], oldSliderVals[i][1]);
    }
	
    printf("Servos:\n");
	for(int i = 0; i < 6; i++) {
		printf("%d:%d\n", servoValues[i][0], servoValues[i][1]);
    }
	
    printf("Value: %d\n", value);
}

/*
 */
void CMovesWindow::timeEvent() {

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
