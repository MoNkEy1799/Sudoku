#include "Highscores.h"
#include "MainWindow.h"

#include <fstream>
#include <string>
#include <unordered_map>
#include <array>

Highscores::Highscores(MainWindow* main)
{
    loadData();
}

void Highscores::addScore(Difficulty diff, uint16_t seconds)
{
	if (diff == Difficulty::NONE)
	{
		return;
	}
	for (int i = 0; i < 10; i++)
	{
		if (seconds < m_scoreData[diff][i].time)
		{
			shiftData(diff, i);
			Score s = newScore();
			s.time = seconds;
			m_scoreData[diff][i] = s;
			saveData();
			scoreChanged = true;
			break;
		}
	}
}

void Highscores::addStat(Stats stat, uint32_t addCount, bool save)
{
	m_stats[stat] += addCount;
	if (save)
	{
		saveData();
	}
	statChanged = true;
}

std::string Highscores::formattedScore(Difficulty diff, int placing, bool save)
{
	Score& score = m_scoreData[diff][placing];
	if (score.year == 0)
	{
		if (save)
		{
			return std::string("- \n");
		}
		return std::string("-");
	}

	std::string format;
	std::string dateSep = ".";
	std::string timeSep = ":";
	std::string sep = " - ";
	if (save)
	{
		dateSep = "";
		timeSep = "";
		sep = "--";
	}

	std::ostringstream osd;
	osd << std::setw(2) << std::setfill('0') << std::to_string(score.day);
	format += osd.str();
	format += dateSep;

	std::ostringstream osm;
	osm << std::setw(2) << std::setfill('0') << std::to_string(score.month);
	format += osm.str();
	format += dateSep;

	std::ostringstream osy;
	osy << std::setw(4) << std::setfill('0') << std::to_string(score.year);
	format += osy.str();

	format += sep;

	std::ostringstream osh;
	osh << std::setw(2) << std::setfill('0') << std::to_string(score.hour);
	format += osh.str();
	format += timeSep;

	std::ostringstream osn;
	osn << std::setw(2) << std::setfill('0') << std::to_string(score.minute);
	format += osn.str();
	format += timeSep;

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << std::to_string(score.second);
	format += oss.str();

	format += sep;

	if (save)
	{
		std::ostringstream ost;
		ost << std::setw(4) << std::setfill('0') << std::to_string(score.time) + " \n";
		format += ost.str();
	}
	else
	{
		format += std::to_string(score.time) + " s";
	}

	return format;
}

std::string Highscores::getStat(Stats stat)
{
	return std::to_string(m_stats[(int)stat]);
}

void Highscores::shiftData(Difficulty diff, int index)
{
	for (int i = 9; i > index; i--)
	{
		m_scoreData[diff][i] = m_scoreData[diff][i - 1];
	}
}

void Highscores::loadData()
{
	std::array<std::stringstream, 5> filedata = {};
	std::ifstream file;
	file.open("saves/highscores.txt");

	Difficulty diff = Difficulty::NONE;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("#EASY") != std::string::npos)
		{
			diff = Difficulty::EASY;
			continue;
		}
		else if (line.find("#MEDIUM") != std::string::npos)
		{
			diff = Difficulty::MEDIUM;
			continue;
		}
		else if (line.find("#HARD") != std::string::npos)
		{
			diff = Difficulty::HARD;
			continue;
		}
		else if (line.find("#EXTREME") != std::string::npos)
		{
			diff = Difficulty::EXTREME;
			continue;
		}
		else if (line.find("#STATS") != std::string::npos)
		{
			diff = Difficulty::NONE;
			continue;
		}
		filedata[(int)diff] << line;
	}

	for (int diff = 1; diff < 5; diff++)
	{
		for (int place = 0; place < 10; place++)
		{
			Score score;
			std::string temp;
			filedata[diff] >> temp;

			if (temp != "-")
			{
				score.day = std::stoi(temp.substr(0, 2));
				score.month = std::stoi(temp.substr(2, 2));
				score.year = std::stoi(temp.substr(4, 4));
				score.hour = std::stoi(temp.substr(10, 2));
				score.minute = std::stoi(temp.substr(12, 2));
				score.second = std::stoi(temp.substr(14, 2));
				score.time = (uint16_t)std::stoi(temp.substr(18, 4));
			}
			m_scoreData[(Difficulty)diff][place] = score;
		}
	}
	for (int stat = 0; stat < 5; stat++)
	{
		std::string temp;
		filedata[0] >> temp;
		m_stats[stat] = std::stoi(temp);
	}
	file.close();
}

void Highscores::saveData()
{
	std::ofstream file;
	file.open("saves/highscores.txt");
	for (int diff = 1; diff < 5; diff++)
	{
		if (diff == 1)
		{
			file << "#EASY\n";
		}
		else if (diff == 2)
		{
			file << "#MEDIUM\n";
		}
		else if (diff == 3)
		{
			file << "#HARD\n";
		}
		else if (diff == 4)
		{
			file << "#EXTREME\n";
		}
		for (int place = 0; place < 10; place++)
		{
			Score& score = m_scoreData[(Difficulty)diff][place];
			file << formattedScore((Difficulty)diff, place, true);
		}
		file << "\n";
	}
	file << "#STATS\n";
	for (int stat = 0; stat < 5; stat++)
	{
		file << std::to_string(m_stats[stat]) + " \n";
	}
	file.close();
}

Score Highscores::newScore()
{
	std::stringstream now;
	now << std::chrono::system_clock::now();
	std::string ymd, hms;
	now >> ymd;
	now >> hms;
	Score retScore;
	retScore.year = std::stoi(ymd.substr(0, 4));
	retScore.month = std::stoi(ymd.substr(5, 2));
	retScore.day = std::stoi(ymd.substr(8, 2));
	retScore.hour = (std::stoi(hms.substr(0, 2)) + 1) % 24;
	retScore.minute = std::stoi(hms.substr(3, 2));
	retScore.second = (int)std::round(std::stof(hms.substr(6, 4)));
	return retScore;
}
