#ifndef __SLIDER_H__
#define __SLIDER_H__

#include <QWidget>
#include <QSlider>

/*
 */
class QString;
class QKeyEvent;
class QLineEdit;

/*
 */
class CAdjRangeSlider : public QWidget {
	
		Q_OBJECT
		
	public:
	
		CAdjRangeSlider(int minValue, int maxValue, QString label, QWidget *parent = 0);

		void setId(int id);
	
	signals:
		void maximumChanged(QString value);
		void minimumChanged(QString value);
		void valueChangedSl(int, int);

	private slots:
		void emitValueChange(int);

	protected:
		void keyPressEvent(QKeyEvent *event);

	private:
		QSlider *slider;
		QLineEdit *minInput;
		QLineEdit *maxInput;
		int id;

		void setMin(QString min);
		void setMax(QString max);
};

#endif /* __SLIDER_H__ */
