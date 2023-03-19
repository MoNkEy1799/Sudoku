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
	void removeGuess(int guess);
	void removeAllGuesses();
	void addNumber(int number);
	void updateInvolvedGuesses(int number);
	void fixNumber(int number);
	void highlightTile(int number);
	void removeHighlight();

	int getId() { return m_id; };
	TileState getState() { return m_state; };
	QPushButton* getButton() { return m_innerCircle; };
	QPushButton* getButtonHighlight() { return m_innerCircleHighlight; };
	
	const static std::unordered_map<int, std::array<int, 9>> idLookUp;

private:
	template<class C, typename T>
	static bool contains(C&& c, T e) { return std::find(std::begin(c), std::end(c), e) != std::end(c); };

	int m_id;
	std::array<bool, 9> m_guess;
	TileState m_state;

	QPushButton* m_innerCircle;
	QPushButton* m_innerCircleHighlight;
	SudokuBoard* m_board;

	void displayGuess();

	bool inGuess(int number) { return m_guess[number]; };
};
