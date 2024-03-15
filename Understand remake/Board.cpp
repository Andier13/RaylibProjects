#include "Board.h"
#include "Cell.h"
#include "auxiliary.h"
#include <fstream>
#include "ResourceClass.h"


typename Board::Index Board::GetCellIndex()
{
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			if (CheckCollisionPointRec(GetMousePosition(), cells[i][j].box))
				return { i, j };
	return {};
}

void Board::DisplayCell(Cell cell)
{
	Color background = (*resource)->currentColors.bright;
	Color outline = (*resource)->currentColors.darkest;
	Color fill = (*resource)->currentColors.darker;
	Rectangle box = cell.box;
	Vector2 center = ::center(box);
	float length = std::min(box.width, box.height);
	float radius = 0.50f * length / 2;
	float thickness = 0.05f * length;
	Rectangle outerBoundary = rectFromCenter(center, { box.width + thickness, box.height + thickness });
	Rectangle innerBoundary = rectFromCenter(center, { box.width - thickness, box.height - thickness });
	
	if (cell.active)
	{
		background = fill;
		fill = outline;
	}
	
	DrawRectangleRec(outerBoundary, outline);
	DrawRectangleRec(innerBoundary, background);
	//DrawRectangleLinesEx(box, thickness, outline);
	switch (cell.type)
	{
	case CellType::Empty:
		break;
	case CellType::Circle:
		DrawCircleV(center, radius + thickness, outline);
		DrawCircleV(center, radius, fill);
		break;
	case CellType::Square:
		radius = radius / sin(PI / 4);
		thickness = thickness / sinf(PI / 2 - PI / 4);
		DrawPoly(center, 4, radius + thickness, 45, outline);
		DrawPoly(center, 4, radius, 45, fill);
		break;
	case CellType::Triangle:
		radius = radius / sin(PI / 3);
		center.y += 1.f / 3 * radius;
		thickness = thickness / sinf(PI / 2 - PI / 3);
		DrawPoly(center, 3, radius + thickness, 180, outline);
		DrawPoly(center, 3, radius, 180, fill);
		break;
	case CellType::Upside_down_triangle:
		radius = radius / sin(PI / 3);
		center.y -= 1.f / 3 * radius;
		thickness = thickness / sinf(PI / 2 - PI / 3);
		DrawPoly(center, 3, radius + thickness, 0, outline);
		DrawPoly(center, 3, radius, 0, fill);
		break;
	case CellType::Right_triangle:
		radius = radius / sin(PI / 3);
		center.x -= 1.f / 3 * radius;
		thickness = thickness / sinf(PI / 2 - PI / 3);
		DrawPoly(center, 3, radius + thickness, 90, outline);
		DrawPoly(center, 3, radius, 90, fill);
		break;
	case CellType::Left_triangle:
		radius = radius / sin(PI / 3);
		center.x += 1.f / 3 * radius;
		thickness = thickness / sinf(PI / 2 - PI / 3);
		DrawPoly(center, 3, radius + thickness, -90, outline);
		DrawPoly(center, 3, radius, -90, fill);
		break;
	case CellType::Hexagon:
		radius = radius / sin(PI / 2 - PI / 6);
		thickness = thickness / sinf(PI / 2 - PI / 6);
		DrawPoly(center, 6, radius + thickness, 30, outline);
		DrawPoly(center, 6, radius, 30, fill);
		break;
	case CellType::Pentagon:
		radius = radius / sin(PI / 2 - PI / 5);
		center.y += 0.1f * radius;
		thickness = thickness / sin(PI / 2 - PI / 5);;
		DrawPoly(center, 5, radius + thickness, 180, outline);
		DrawPoly(center, 5, radius, 180, fill);
		break;
	case CellType::Octogon:
		radius = radius / sin(PI / 2 - PI / 8);
		thickness = thickness / sinf(PI / 2 - PI / 8);
		DrawPoly(center, 8, radius + thickness, 180.f/8, outline);
		DrawPoly(center, 8, radius, 180.f / 8, fill);
		break;
	default:
		break;
	}

}

Board::Board() : rows(0), cols(0), cells(nullptr), path{}, box{}, checks{}
{
}

Board::Board(std::string filename) : rows(0), cols(0), cells(nullptr), path{}, box{}, checks{}
{
	//LoadBoard(filename);
}

Board::~Board()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete[] cells[i];
	}
	delete cells;
}

void Board::Update()
{
	Vector2 mouseV = GetMousePosition();
	bool potential_game_zone = CheckCollisionPointRec(mouseV, rectFromCenter({ WIDTH / 2, HEIGHT / 2 }, { WIDTH - 400, HEIGHT }));
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		
		if (potential_game_zone)
		{
			path.clear();
			if (CheckCollisionPointRec(mouseV, box))
			{
				path.push_back(GetCellIndex());
				selected = true;
			}
			for (size_t i = 0; i < checks.size(); i++)
				check_results[i] = false;
		}
		
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && path.size()>0 && potential_game_zone)
	{
		Index current = GetCellIndex();
		Index last = path.back();
		if (std::abs((int64_t)current.i - (int64_t)last.i) + std::abs((int64_t)current.j - (int64_t)last.j) == 1)
			if (cells[current.i][current.j].active)
			{
				Index lastPrev = path.at(path.size() - 2);
				if (current.i == lastPrev.i && current.j == lastPrev.j)
					path.pop_back();
			}
			else
				path.push_back(current);
	}

	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			cells[i][j].active = false;
	for (const auto& index : path)
		cells[index.i][index.j].active = true;

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && path.size() > 0 && selected)
	{
		selected = false;
		for (size_t i = 0; i < checks.size(); i++)
			check_results[i] = checks[i](*this);
		bool completed = true;
		for (const auto& value : check_results)
			completed = completed && value;
		if (completed)
		{
			if (last)
				PlaySound((*resource)->finalSolution);
			else
				PlaySound((*resource)->correctSolution);
		}
		else
			PlaySound((*resource)->partialSolution);
	}
}

void Board::Display()
{
	Color background = (*resource)->currentColors.bright;
	Color outline = (*resource)->currentColors.darkest;
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			DisplayCell(cells[i][j]);
	float length = cells[0][0].box.width;
	float thickness = 0.08f * length;
	float start_length = length * 0.80f;
	float start_thickness = length * 0.07f;

	if (example != nullptr)
	{
		Color outline = { 128, 128, 128 , 255 };

		for (size_t i = 0; i < example->size() - 1; i++)
		{
			Index current = example->at(i);
			Index next = example->at(i + 1);

			Vector2 currentV = center(cells[current.i][current.j].box);
			Vector2 nextV = center(cells[next.i][next.j].box);

			if (i == 0)
			{
				Vector2 shift = { (float)next.j - (int)current.j, (float)next.i - (int)current.i };
				shift = shift * 0.5 * (start_length + start_thickness);
				currentV = currentV + shift;
			}

			DrawLineEx(currentV, nextV, thickness, outline);
			//DrawCircleV(currentV, thickness / 2, outline);
			//DrawCircleV(nextV, thickness / 2, outline);
			DrawRectangleRec(rectFromCenter(currentV, { thickness, thickness }), outline);
			DrawRectangleRec(rectFromCenter(nextV, { thickness, thickness }), outline);
		}

		Index first = example->at(0);
		Vector2 center = ::center(cells[first.i][first.j].box);
		DrawRectangleLinesEx(rectFromCenter(center, { start_length + start_thickness, start_length + start_thickness }), start_thickness, outline);
	}

	if (path.size()>=2)
		for (size_t i = 0; i < path.size()-1; i++)
		{
			Index current = path.at(i);
			Index next = path.at(i+1);

			Vector2 currentV = center(cells[current.i][current.j].box);
			Vector2 nextV = center(cells[next.i][next.j].box);

			if (i == 0)
			{
				Vector2 shift = { (float)next.j - (int)current.j, (float)next.i - (int)current.i };
				shift = shift * 0.5 * (start_length + start_thickness);
				currentV = currentV + shift;
			}

			DrawLineEx(currentV, nextV, thickness, outline);
			//DrawCircleV(currentV, thickness / 2, outline);
			//DrawCircleV(nextV, thickness / 2, outline);
			DrawRectangleRec(rectFromCenter(currentV, { thickness, thickness }), outline);
			DrawRectangleRec(rectFromCenter(nextV, { thickness, thickness }), outline);
		}
	if (path.size() >= 1)
	{
		Index first = path.at(0);
		Vector2 center = ::center(cells[first.i][first.j].box);
		DrawRectangleLinesEx(rectFromCenter(center, { start_length + start_thickness, start_length + start_thickness }), start_thickness, outline);
	}

	if (check_results.size() > 0)
	{
		float distX = 30;
		float distY = 50;
		float radius = 30;
		thickness = 5;

		size_t n = check_results.size();
		float width = 2 * n * radius + (n - 1) * distX;

		if (last)
		{
			int i = 0;
			Vector2 pos1 = { WIDTH / 2 - width / 2 + (2 * i + 1) * radius + i * distX, HEIGHT - distY };
			i = (int)check_results.size() - 1;
			Vector2 pos2 = { WIDTH / 2 - width / 2 + (2 * i + 1) * radius + i * distX, HEIGHT - distY };
			bool completed = true;
			for (const auto& value : check_results)
				completed = completed && value;
			DrawLineExRound(pos1, pos2, 2*radius, outline);
			DrawLineExRound(pos1, pos2, 2*(radius - thickness), (completed ? outline : background));
		}
		else
		{
			for (size_t i = 0; i < check_results.size(); i++)
			{
				Vector2 pos = { WIDTH / 2 - width / 2 + (2 * i + 1) * radius + i * distX, HEIGHT - distY };
				DrawCircleV(pos, radius, outline);
				DrawCircleV(pos, radius - thickness, (check_results[i] ? outline : background));
			}
		}
	}
}

void Board::AddCheck(Condition check)
{
	checks.push_back(check);
	check_results.push_back(false);
}

const Cell& Board::CellAt(Index index) const
{
	return cells[index.i][index.j];
}
/*
void Board::LoadBoard(std::string filename)
{
	std::ifstream f(filename);
	std::string input;

	f >> rows >> cols;
	cells = new Cell * [rows];
	for (size_t i = 0; i < rows; i++)
		cells[i] = new Cell[cols];

	
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
		{
			f >> input;
			if (input == "em")
				cells[i][j].type = CellType::Empty;
			else if (input == "ci")
				cells[i][j].type = CellType::Circle;
			else if (input == "sq")
				cells[i][j].type = CellType::Square;
			else if (input == "tr")
				cells[i][j].type = CellType::Triangle;
			else if (input == "ut")
				cells[i][j].type = CellType::Upside_down_triangle;
			else if (input == "lt")
				cells[i][j].type = CellType::Left_triangle;
			else if (input == "rt")
				cells[i][j].type = CellType::Right_triangle;
			else if (input == "pe")
				cells[i][j].type = CellType::Pentagon;
			else if (input == "he")
				cells[i][j].type = CellType::Hexagon;
			else if (input == "oc")
				cells[i][j].type = CellType::Octogon;
			std::cout << input << ' ';
		}
	f.close();

	float unit = HEIGHT / 8;
	float w = cols * unit;
	float h = rows * unit;
	Rectangle outline = rectFromCenter({ WIDTH / 2, HEIGHT / 2 }, { w, h });
	box = outline;
	//DrawRectangleLinesEx(outline, 10, GREEN);
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			cells[i][j].box = { outline.x + j * unit, outline.y + i * unit, unit, unit };
}*/

void Board::LoadBoard(std::ifstream& f)
{
	std::string input;

	f >> rows >> cols;
	cells = new Cell * [rows];
	for (size_t i = 0; i < rows; i++)
		cells[i] = new Cell[cols];


	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
		{
			f >> input;
			if (input == "em")
				cells[i][j].type = CellType::Empty;
			else if (input == "ci")
				cells[i][j].type = CellType::Circle;
			else if (input == "sq")
				cells[i][j].type = CellType::Square;
			else if (input == "tr")
				cells[i][j].type = CellType::Triangle;
			else if (input == "ut")
				cells[i][j].type = CellType::Upside_down_triangle;
			else if (input == "lt")
				cells[i][j].type = CellType::Left_triangle;
			else if (input == "rt")
				cells[i][j].type = CellType::Right_triangle;
			else if (input == "pe")
				cells[i][j].type = CellType::Pentagon;
			else if (input == "he")
				cells[i][j].type = CellType::Hexagon;
			else if (input == "oc")
				cells[i][j].type = CellType::Octogon;

		}
	//f.close();

	float unit = HEIGHT / 8;
	float w = cols * unit;
	float h = rows * unit;
	Rectangle outline = rectFromCenter({ WIDTH / 2, HEIGHT / 2 }, { w, h });
	box = outline;
	//DrawRectangleLinesEx(outline, 10, GREEN);
	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			cells[i][j].box = { outline.x + j * unit, outline.y + i * unit, unit, unit };
}

bool Board::IsSolved()
{
	if (check_results.size() == 0)
		return false;
	for (size_t i = 0; i < check_results.size(); i++)
		if (!check_results[i])
			return false;
	return true;
}
