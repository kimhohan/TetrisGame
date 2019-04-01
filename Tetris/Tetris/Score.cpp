#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
#include "Score.h"

Score::Score()
{
    score_ = 0;
    score_pos_ = Point(28, 9);
}

void Score::Print(Point reference_pos)
{
    Point::GotoXY(reference_pos + score_pos_);
    cout << "    ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Point::GotoXY(reference_pos + score_pos_);
    cout << setw(5) << score_;
}

void Score::UpdateScore(Point reference_pos, int increment)
{
	if (increment == 1)
		score_ = score_+ 1;
	else if (increment == 2)
		score_ = score_+increment * 2;
	else if (increment == 3)
		score_ = score_+increment * 3;
	else
		score_ = score_+increment * 4;

    Print(reference_pos);
}

int Score::score()
{

	return score_;
}