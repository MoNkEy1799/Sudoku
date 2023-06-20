import numpy as np
import os

class SudokuBoard:
	def __init__(self, board: np.ndarray, openTiles: int) -> None:
		self.board = board
		self.openTiles = openTiles

def reformatBoard(data: list[str]) -> SudokuBoard:
	board = np.zeros((9, 9))
	for index in [12, 8, 4, 0]:
		data.pop(index)
	for row, line in enumerate(data):
		for col, number in enumerate(line.replace(" ", "").replace("|", "").replace("\n", "")):
			if number.isdigit():
				board[row, col] = int(number)
	
	return SudokuBoard(board, np.count_nonzero(board))		

def getSudokusFromFile(filepath: str) -> list[SudokuBoard]:
	result = list()
	with open(f"runs/{filepath}", "r") as file:
		data = file.readlines()
		i = 0
		while i < len(data):
			line = data[i]
			if "- - -" in line:
				result.append(reformatBoard(data[i:i+13]))
				i += 13
			else:
				i += 1
	
	return result

def getBoardDistribution(boardList: list[SudokuBoard]) -> dict[int, int]:
	dist = dict()
	for board in boardList:
		if board.openTiles not in dist:
			dist[board.openTiles] = 0
		dist[board.openTiles] += 1

	return dict(sorted(dist.items()))

def dumpToNewFile(boardList: list[SudokuBoard], outpath: str, openTileCap: int = 25) -> None:
	with open(outpath, "w") as file:
		for board in boardList:
			if board.openTiles > openTileCap:
				continue
			file.write(f"{board.openTiles}\n")
			for row in board.board:
				for num in row:
					file.write(str(int(num)))
				file.write("\n")
			file.write("\n")
			
def main() -> None:
	allBoards = list()
	files = [path for path in os.listdir("runs/") if path.endswith(".txt")]
	for path in files:
		[allBoards.append(board) for board in getSudokusFromFile(path)]

	dumpToNewFile(allBoards, "output.txt")
	print(f"Distribution of open tiles in the runs (we only care about ot <= 25):\n{getBoardDistribution(allBoards)}")

if __name__ == "__main__":
	main()
