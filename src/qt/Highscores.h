#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <array>

class MainWindow;
enum class Difficulty;

struct Score
{
	uint16_t time = ~0;
	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
};

enum Stats { GAMES, WON, LOST, TIME, LEFT, RIGHT };

class Highscores
{
public:
	Highscores(MainWindow* main = nullptr);
	void addScore(Difficulty diff, uint16_t seconds);
	void addStat(Stats stat, uint32_t addCount, bool save = false);
	std::string formattedScore(Difficulty diff, int placing, bool save);
	std::string getStat(Stats stat);

	bool scoreChanged, statChanged;

private:
	std::unordered_map<Difficulty, std::array<Score, 10>> m_scoreData;
	std::array<uint32_t, 6> m_stats;
	MainWindow* m_mainWindow;

	void shiftData(Difficulty diff, int index);
	void loadData();
	void saveData();
	Score newScore();
};