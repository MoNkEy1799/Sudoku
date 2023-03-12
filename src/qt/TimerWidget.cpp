#include "TimerWidget.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QGridLayout>
#include <QFont>

#include <string>

TimerWidget::TimerWidget(QWidget* parent)
    : QWidget(parent), m_totalSeconds(0), m_timer(nullptr)
{
    QFont font = QFont("Sans-Serif", 15);
    font.setBold(true);

    m_timer = new QTimer(this);
    m_timeLabel = new QLabel(this);
    m_timeLabel->setFont(font);
    m_timeLabel->setAlignment(Qt::AlignCenter);

    setMinimumHeight(100);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_timeLabel);

    connect(m_timer, &QTimer::timeout, this, &TimerWidget::updateLabel);
}

void TimerWidget::startMyTimer()
{
    m_timer->start(1000);
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
        text += std::to_string(currentTime.hours) + "H ";
    }

    if (currentTime.minutes != 0)
    {
        text += std::to_string(currentTime.minutes) + "M ";
    }

    text += std::to_string(currentTime.seconds) + "S ";
    m_timeLabel->setText(text.c_str());

    m_totalSeconds++;
}
