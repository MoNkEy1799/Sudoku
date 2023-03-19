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
    m_timer = new QTimer(this);
    m_timeLabel = new QLabel(this);
    m_timeLabel->setFont(QFont("Sans-Serif", 20, QFont::Bold));
    m_timeLabel->setFixedSize(160, 50);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel->setText("0s ");
    m_timeLabel->setObjectName("Time");

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

std::string TimerWidget::getTime()
{
    std::string time;

    if (m_totalSeconds / 3600 != 0)
    {
        time += std::to_string(m_totalSeconds / 3600) + "h ";
    }

    if (m_totalSeconds / 60 % 60 != 0)
    {
        time += std::to_string(m_totalSeconds / 60 % 60) + "m ";
    }

    time += std::to_string(m_totalSeconds % 60) + "s ";
    return time;
}

void TimerWidget::updateLabel()
{
    m_timeLabel->setText(getTime().c_str());
    m_totalSeconds++;
}
