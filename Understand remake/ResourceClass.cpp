#include "ResourceClass.h"

void ResourceClass::AddConditions(Board* board)
{
	if (levelName == "1")
	{
		board->AddCheck([](Condition_input board)->bool {
			Cell first = board.CellAt(board.path[0]);
			return first.type == CellType::Square;
			});
		board->AddCheck([](Condition_input board)->bool {
			Cell last = board.CellAt(board.path.back());
			return last.type == CellType::Circle;
			});
	}
	else if (levelName == "2")
	{
		board->AddCheck([](Condition_input board)->bool {
			Cell first = board.CellAt(board.path[0]);
			return first.type == CellType::Square;
			});
		board->AddCheck([](Condition_input board)->bool {
			Cell last = board.CellAt(board.path.back());
			return last.type == CellType::Circle;
			});
		board->AddCheck([](Condition_input board)->bool {
			for (const auto& index : board.path)
				if (board.CellAt(index).type == CellType::Upside_down_triangle)
					return false;
			return true;
			});
	}
	else if (levelName == "3")
	{
		board->AddCheck([](Condition_input board)->bool {
			Cell first = board.CellAt(board.path[0]);
			return first.type == CellType::Square;
			});
		board->AddCheck([](Condition_input board)->bool {
			Cell last = board.CellAt(board.path.back());
			return last.type == CellType::Circle;
			});
		board->AddCheck([](Condition_input board)->bool {
			int count = 0;
			for (const auto& index : board.path)
				if (board.CellAt(index).type != CellType::Empty)
					count++;
			return count == 3;
			});
	}
	else if (levelName == "4")
	{
		board->AddCheck([](Condition_input board)->bool {
			Cell first = board.CellAt(board.path[0]);
			return first.type == CellType::Square;
			});
		board->AddCheck([](Condition_input board)->bool {
			Cell last = board.CellAt(board.path.back());
			return last.type == CellType::Circle;
			});
		board->AddCheck([](Condition_input board)->bool {
			int count = 0;
			for (const auto& index : board.path)
				if (board.CellAt(index).type == CellType::Triangle)
					count++;
			return count == 1;
			});
	}
}
