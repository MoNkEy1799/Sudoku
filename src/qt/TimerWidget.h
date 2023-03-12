#pragma once

#include <QWidget>
#include <QTimer>
#include <QLabel>

struct Time
{
public:
	uint32_t seconds, minutes, hours;
};

class TimerWidget : public QWidget
{

	Q_OBJECT

public:
	TimerWidget(QWidget* parent = nullptr);

	void startMyTimer();

public slots:
	void updateLabel();

private:
	QTimer* m_timer;
	QLabel* m_timeLabel;
	uint32_t m_totalSeconds;

	Time getTime();
};