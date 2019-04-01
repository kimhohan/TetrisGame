#include "Tetromino.h"
#include <iostream>
#include <windows.h>
using namespace std;

Point g_tetromino_pattern[7][4][4] =
{
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(0, -2) }, { Point(-2, 0), Point(-1, 0), Point(0, 0), Point(1, 0) } },  // I
    { { Point(0, 1), Point(0, 0), Point(0, -1), Point(-1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, 1) },
      { Point(0, 1), Point(0, 0), Point(1, 1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(1, -1) } },  // J
    { { Point(-1, 1), Point(0, 1), Point(0, 0), Point(0, -1) }, { Point(1, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(0, -1), Point(1, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(-1, -1) } }, // L
    { { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) },
      { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(-1, -1), Point(0, -1) } },  // O
    { { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(1, -1) }, { Point(0, 0), Point(1, 0), Point(-1, -1), Point(0, -1) } },  // S
    { { Point(0, 1), Point(-1, 0), Point(0, 0), Point(0, -1) }, { Point(0, 1), Point(-1, 0), Point(0, 0), Point(1, 0) },
      { Point(0, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(1, 0), Point(0, -1) } },  // T
    { { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) },
      { Point(1, 1), Point(0, 0), Point(1, 0), Point(0, -1) }, { Point(-1, 0), Point(0, 0), Point(0, -1), Point(1, -1) } }  // Z
};

Tetromino::Tetromino(Board *board, TETROMINO_TYPE type) : board_(board), type_(type)
{
    rotate_ = 0;
}

void Tetromino::textcolor(int color_number)         //색깔함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
};

void Tetromino::tetriscolor(void)
{
	switch (type_)                  //테트로미노 타입에 따른 색깔지정
	{
	case 0:
		textcolor(1);
		break;
	case 1:
		textcolor(2);
		break;
	case 2:
		textcolor(3);
		break;
	case 3:
		textcolor(4);
		break;
	case 4:
		textcolor(5);
		break;
	case 5:
		textcolor(6);
		break;
	case 6:
		textcolor(7);
		break;
	}
}

void Tetromino::Draw(Point reference_pos)
{
	tetriscolor();

	Tetromino::tetrominoghost(reference_pos, center_pos_);
	for (int i = 0; i<4; i++)
	{
		Point cur_pos(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		Point::GotoXY(cur_pos);
		if (center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY()<20)
			cout << "■";
	}

}

void Tetromino::Erase(Point reference_pos)
{
	for (int i = 0; i<4; i++)
	{
		Point cur_pos(reference_pos + Point::GetScrPosFromCurPos(ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		Point::GotoXY(cur_pos);
		if (cur_pos.GetY()>0)
			cout << "  ";
	}
	for (int i = 0; i<4; i++)
	{
		Point cur_pos(reference_pos + Point::GetScrPosFromCurPos(center_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		Point::GotoXY(cur_pos);
		if (cur_pos.GetY()>0)
			cout << "  ";
	}
	
}

void Tetromino::SetCenterPos(Point pos)
{
    center_pos_ = pos;
}

bool Tetromino::MoveDown(Point reference_pos)
{
	
	center_pos_.SetY(center_pos_.GetY() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		Erase(reference_pos);
		center_pos_.SetY(center_pos_.GetY() - 1);
		Draw(reference_pos);
		return true;
	}
	else
	{
		center_pos_.SetY(center_pos_.GetY() + 1);
		return false;
	}

    return true;
}

void Tetromino::MoveRight(Point reference_pos)
{
    center_pos_.SetX(center_pos_.GetX() + 1);

    if (CheckValidPos())
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
        Erase(reference_pos);
        center_pos_.SetX(center_pos_.GetX() + 1);
        Draw(reference_pos);
    }
    else
    {
        center_pos_.SetX(center_pos_.GetX() - 1);
    }
}

void Tetromino::MoveLeft(Point reference_pos)
{
	center_pos_.SetX(center_pos_.GetX() - 1);

	if (CheckValidPos())
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
		Erase(reference_pos);
		center_pos_.SetX(center_pos_.GetX() - 1);
		Draw(reference_pos);
	}
	else
	{
		center_pos_.SetX(center_pos_.GetX() + 1);
	}
}

void Tetromino::Rotate(Point reference_pos)
{
	Erase(reference_pos);
	rotate_++;
	if (rotate_ == 4)
	{
		if (CheckValidPos())
		{
			rotate_ = 0;
			Draw(reference_pos);
		}
		else
		{
			rotate_--;
			Draw(reference_pos);
		}
	}
	else
	{
		if (CheckValidPos())
		{
			Draw(reference_pos);
		}
		else
		{
			rotate_--;
			Draw(reference_pos);
		}
	}
}

void Tetromino::GoBottom(Point reference_pos)
{
    while (MoveDown(reference_pos))
    {
        Sleep(10); //Sleep(100);
    }
}

bool Tetromino::CheckValidPos(void)
{

    for (int i = 0; i < 4; i++)
    {
        Point cur_pos(center_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

        if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
            return false;
        if (cur_pos.GetY() < 0)
            return false;
        if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
            return false;
    }

    return true;
}

void Tetromino::MarkCurTetrominoPos(Point reference_pos)
{
	int i;
	for (i = 0; i < 4; i++)// board_ 2차원 배열에서 테트로미노의 4개의 각 점 위치를 mark하기
	{
		board_->SetState(center_pos_ + g_tetromino_pattern[type_][rotate_][i], type_);
	}
}

bool Tetromino::CheckEndCondition(void)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (center_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY() >= 20)
			return true;
	}
	return false;
}

bool Tetromino::CheckValidghost_Pos(Point ghost_pos)
{
	for (int i = 0; i < 4; i++)
	{
		Point cur_pos(ghost_pos.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX(), ghost_pos.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY());

		if (cur_pos.GetX() < 0 || cur_pos.GetX() > 9)
			return false;
		if (cur_pos.GetY() < 0)
			return false;
		if (cur_pos.GetY() <= 19 && board_->GetState(cur_pos) != EMPTY)
			return false;
	}

	return true;
}
void Tetromino::tetrominoghost(Point reference_pos ,Point center_pos)
{
	int i, n =0;
	ghost_pos_=center_pos;

	while (CheckValidghost_Pos(ghost_pos_))
	{
		ghost_pos_.SetY(ghost_pos_.GetY() - 1);
	}

	ghost_pos_.SetY(ghost_pos_.GetY() + 1);

	for (int i = 0; i<4; i++)
	{
		Point cur_pos(reference_pos + Point::GetScrPosFromCurPos(ghost_pos_ + g_tetromino_pattern[type_][rotate_][i]));
		Point::GotoXY(cur_pos);
		if (ghost_pos_.GetY() + g_tetromino_pattern[type_][rotate_][i].GetY()<20 )
			if (ghost_pos_.GetX() + g_tetromino_pattern[type_][rotate_][i].GetX()<10)
			cout << "□";
	}
}