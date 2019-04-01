#include <iostream>
#include <windows.h>
#include "Board.h"
using namespace std;

Board::Board()
{
	int i, j;

	for (i = 0; i < 10; i++) 
    {
		for (j = 0; j < 20; j++)
			board_[i][j] = EMPTY;
	}
}

int Board::GetState(Point pos)
{ 
	return board_[pos.GetX()][pos.GetY()]; 
}

void Board::SetState(Point pos, int state) 
{ 
	board_[pos.GetX()][pos.GetY()] = state;	
}
void Board::angel_card(Point reference_pos)
{
	int i, j, s;
	for (j = 0; j < 19; j++)
	{
		Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(0, j)));
		for (int i = 0; i < 10; i++)
		{
			board_[i][j] = board_[i][j+1];
			tetriscolor(GetState(Point(i, j)));

			if (board_[i][j] != EMPTY)
				cout << "■";
			else
				cout << "  ";
		}
	}
}

int Board::CheckLineFull(Point reference_pos)
{

	int count = 0;
	int i, j, s;

	for ( i = 0; i < 20; i++)
	{
		s = 1;
			for (j = 0; j < 10; j++)
			{
				if (board_[j][i] == EMPTY)
					s = 0;
			}
			if (s == 1)
			{
				count++;
				for (j = i; j < 19; j++)
				{
					Point::GotoXY(reference_pos + Point::GetScrPosFromCurPos(Point(0, j)));
					for (int i = 0; i < 10; i++)
					{
						board_[i][j] = board_[i][j + 1];
						tetriscolor(GetState(Point(i, j)));

						if (board_[i][j] != EMPTY)
							cout << "■";
						else
							cout << "  ";
				    }
			    }
				i--;
			}
	}

	return count;
}

void Board::textcolor(int color_number)         //색깔함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
};

void Board::tetriscolor(int type)
{
	switch (type)                  //테트로미노 타입에 따른 색깔지정
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
