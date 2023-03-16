#pragma once

#include <QWidget>
#include <QPushButton>

#include <string>
#include <array>
#include <unordered_map>
#include <algorithm>

class SudokuBoard;

enum class TileState { GUESS, SET, FIXED };

class Tile : public QWidget
{
	Q_OBJECT

public:
	Tile(int id, SudokuBoard* board = nullptr, QWidget* parent = nullptr);

	void addGuess(int guess);
	void removeGuesses();
	void addNumber(int number);
	void updateInvolvedGuesses();
	void fixNumber(int number);

	int getId() { return m_id; };
	TileState getState() { return m_state; };
	QPushButton* getButton() { return m_inner; };

private:
	const static std::unordered_map<int, std::array<int, 9>> m_idLookUp;
	template<class C, typename T>
	static bool contains(C&& c, T e) { return std::find(std::begin(c), std::end(c), e) != std::end(c); };

	int m_id;
	std::array<bool, 9> m_guess;
	TileState m_state;

	QPushButton* m_inner;
	SudokuBoard* m_board;
	QFont m_fontGuess, m_fontSet;

	void displayGuess();

	bool inGuess(int number) { return m_guess[number]; };
};
