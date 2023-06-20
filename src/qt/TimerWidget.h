#pragma once

#include <QWidget>
#include <QTimer>
#include <QLabel>

class Highscores;

struct Time
{
public:
	uint32_t seconds, minutes, hours;
};

class TimerWidget : public QWidget
{
	Q_OBJECT

public:
	TimerWidget(int width, Highscores* highscore, QWidget* parent = nullptr);

	void startTimer();
	int stopTimer();
	void resetTimer();
	void updateLabel(bool advanceTime = true);
	std::string getTime();

private:
	QTimer* m_timer;
	QLabel* m_timeLabel;
	uint32_t m_totalSeconds;
	Highscores* m_highscore;
};