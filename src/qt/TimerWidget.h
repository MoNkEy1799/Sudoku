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
	TimerWidget(int width, QWidget* parent = nullptr);

	void startTimer();
	void stopTimer();
	void resetTimer();

private:
	QTimer* m_timer;
	QLabel* m_timeLabel;
	uint32_t m_totalSeconds;

	void updateLabel();
	Time getTime();
};