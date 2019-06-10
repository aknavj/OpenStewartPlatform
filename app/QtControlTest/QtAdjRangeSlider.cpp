#include <QGridLayout>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QPushButton>
#include <QKeyEvent>

#include "QtAdjRangeSlider.h"

/*
 */
CAdjRangeSlider::CAdjRangeSlider(int minValue, int maxValue, QString label, QWidget *parent) : QWidget(parent) {
	
	QLabel *name = new QLabel(label);
	name->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        
	QFont font(name->font());
	font.setBold(true);
	font.setPixelSize(20);
	name->setFont(font);

	QLabel *minLabel = new QLabel("Min");
	minLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	minInput = new QLineEdit(QString::number(minValue));

	QLCDNumber *value = new QLCDNumber(3);
	value->setSegmentStyle(QLCDNumber::Flat);

	QLabel *maxLabel = new QLabel("Max");
	maxLabel->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

	maxInput = new QLineEdit(QString::number(maxValue));

	slider = new QSlider(Qt::Horizontal);
	slider->setRange(minValue,maxValue);

	connect(slider, SIGNAL(valueChanged(int)), value, SLOT(display(int)));
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(emitValueChange(int)));
	connect(this, SIGNAL(minimumChanged(QString)), minInput, SLOT(setText(QString)));
	connect(this, SIGNAL(maximumChanged(QString)), maxInput, SLOT(setText(QString)));
	slider->setValue(125);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(name,0,0,1,3);
	layout->addWidget(minLabel,1,0);
	layout->addWidget(minInput,2,0);
	layout->addWidget(value,1,1,2,1);
	layout->addWidget(maxLabel,1,2);
	layout->addWidget(maxInput,2,2);
	layout->addWidget(slider,4,0,1,3);
	layout->setColumnStretch(1,1);
	layout->setRowStretch(1,1);
	
	setLayout(layout);
}

/*
 */
void CAdjRangeSlider::setMin(QString min) {

	int value = min.toInt();

	if(value >= slider->maximum()) {
		slider->setMinimum(slider->maximum()-1);
		emit minimumChanged(QString::number(slider->maximum()-1,10));
	} else {
		slider->setMinimum(min.toInt());
	}

	if(value > slider->value()) {
		slider->setValue(value);
		return;
    }
}

/*
 */
void CAdjRangeSlider::setMax(QString max) {

    int value = max.toInt();

    if(value <= slider->minimum()) {
        slider->setMaximum(slider->minimum()+1);
        emit maximumChanged(QString::number(slider->minimum()+1,10));
    } else {
        slider->setMaximum(max.toInt());
    }

    if(value < slider->value()) {
        slider->setValue(value);
        return;
    }
}

/*
 */
void CAdjRangeSlider::keyPressEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_Enter) {
        if(minInput->hasFocus()) {
            setMin(minInput->text());
        }
        if(maxInput->hasFocus()) {
            setMax(maxInput->text());
        }
    }
}

/*
 */
void CAdjRangeSlider::setId(int id) {
    this->id = id;
}

/*
 */
void CAdjRangeSlider::emitValueChange(int value) {
    emit valueChangedSl(id, value);
}
