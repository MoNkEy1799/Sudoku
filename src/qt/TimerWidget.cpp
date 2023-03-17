#include "TimerWidget.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QGridLayout>
#include <QFont>

#include <string>

TimerWidget::TimerWidget(int width, QWidget* parent)
    : QWidget(parent), m_totalSeconds(0), m_timer(nullptr)
{
    QFont font = QFont("Sans-Serif", 20);
    font.setBold(true);

    m_timer = new QTimer(this);
    m_timeLabel = new QLabel(this);
    m_timeLabel->setFont(font);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setText("0s ");

    setMinimumHeight(100);
    setMaximumWidth(width);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_timeLabel);

    connect(m_timer, &QTimer::timeout, this, &TimerWidget::updateLabel);
}

void TimerWidget::startTimer()
{
    updateLabel();
    m_timer->start(1000);
}

void TimerWidget::stopTimer()
{
    m_timer->stop();
}

void TimerWidget::resetTimer()
{
    m_totalSeconds = 0;
    m_timeLabel->setText("0s ");
}

Time TimerWidget::getTime()
{
    return Time({ m_totalSeconds % 60, m_totalSeconds / 60 % 60, m_totalSeconds / 3600 });
}

void TimerWidget::updateLabel()
{
    Time currentTime = getTime();
    std::string text = "";

    if (currentTime.hours != 0)
    {
        text += std::to_string(currentTime.hours) + "h ";
    }

    if (currentTime.minutes != 0)
    {
        text += std::to_string(currentTime.minutes) + "m ";
    }

    text += std::to_string(currentTime.seconds) + "s ";
    m_timeLabel->setText(text.c_str());

    m_totalSeconds++;
}
