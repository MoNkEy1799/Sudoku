#include "Highscores.h"
#include "MainWindow.h"


Highscores::Highscores(MainWindow* main)
{
    loadData();
}

void Highscores::addScore(Difficulty diff, uint16_t seconds)
{
}

void Highscores::addStat(Stats stat, uint32_t addCount, bool save)
{
}

std::string Highscores::formattedScore(Difficulty diff, int placing, bool save)
{
    return std::string();
}

std::string Highscores::getStat(Stats stat)
{
    return std::string();
}

void Highscores::shiftData(Difficulty diff, int index)
{
}

void Highscores::loadData()
{
}

void Highscores::saveData()
{
}

Score Highscores::newScore()
{
    return Score();
}
