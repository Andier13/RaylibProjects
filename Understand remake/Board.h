#pragma once
#include "Cell.h"
#include "auxiliary.h"

class ResourceClass;
class Board;
typedef const Board& Condition_input;
typedef bool (*Condition)(const Board&);

class Board
{
public:
	struct Index {
		size_t i, j;
	};

	int rows, cols;
	Cell** cells;
	std::vector<Index> path;
	std::vector<Index>* example = nullptr;

	ResourceClass** resource = nullptr;

	bool selected = false;
	bool last = false;

protected:
	std::vector<Condition> checks;
	std::vector<bool> check_results;
	Rectangle box;

	Index GetCellIndex();
	void DisplayCell(Cell cell);

public:
	Board();
	Board(std::string filename);
	~Board();
	void Update();
	void Display();
	void AddCheck(Condition check);
	const Cell& CellAt(Index index) const;
	//void LoadBoard(std::string filename);
	void LoadBoard(std::ifstream& f);
	bool IsSolved();
};

