#include "Tetris.h"
#include "Controller.h"
#include "Tetromino.h"
//#include "GhostTetromino.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

Tetris::Tetris(Point reference_pos, int key_esc, int key_right, int key_left, int key_rotate, int key_down,int key_space, int key_m, int key_t) : reference_pos_(reference_pos) 
{ 
	C = 5;
    running_ = true; 
    cur_tetromino_ = NULL;
    next_tetromino_ = NULL;
    start_time_ = clock();
    falling_speed_ = 0.8;

    SetCursorInvisible();

    controller_.SetController(key_esc, key_right, key_left, key_rotate, key_down, key_space, key_m, key_t);
    DrawBoard();
    GenerateNextTetromino();
    GetCurTetrominoFromNext();
    GenerateNextTetromino();
    cur_tetromino_->Draw(reference_pos_);
    next_tetromino_->Draw(reference_pos_);		
    score_.Print(reference_pos_);
}

void Tetris::DrawBoard(void)
{
    int i;
	
    Point::GotoXY(reference_pos_);
    cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";
for (i = 0; i < 21; i++) {
    Point::GotoXY(reference_pos_ + Point(0, i + 1));
    cout << "��                    ��            ��";
}
	Point::GotoXY(reference_pos_+Point(0,21));
	cout << "�ˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢˢ�";
	Point::GotoXY(reference_pos_ + Point(24, 7));
	cout << "�ˢˢˢˢˢ�";
	Point::GotoXY(reference_pos_ + Point(24, 11));
	cout << "�ˢˢˢˢˢ�";

	Point::GotoXY(reference_pos_ + Point(25, 13));
	if (controller_.Getkey_right() == KEY_RIGHT)
		cout << "�� ������";
	else
		cout << (char)controller_.Getkey_right() << " ������";

	Point::GotoXY(reference_pos_ + Point(25, 15));
	if (controller_.Getkey_left() == KEY_LEFT)
		cout << "�� ����";
	else
		cout << (char)controller_.Getkey_left() << " ����";

	Point::GotoXY(reference_pos_ + Point(25, 17));
	if (controller_.Getkey_rotate() == KEY_UP)
		cout << "�� ����";
	else
		cout << (char)controller_.Getkey_rotate() << " ����";

	Point::GotoXY(reference_pos_ + Point(25, 19));
	if (controller_.Getkey_down() == KEY_DOWN)
		cout << "�� �Ʒ�";
	else
		cout << (char)controller_.Getkey_down() << " �Ʒ�";

	Point::GotoXY(reference_pos_ + Point(25, 23));
	if (controller_.Getkey_m() == 'm')
		cout << "m õ��ī�� " << C ;
	else
		cout << (char)controller_.Getkey_m() << " õ��ī��" << C;

	Point::GotoXY(reference_pos_ + Point(10, 23));
	if (controller_.Getkey_t() == 't')
		cout << "t �޽� ";
	else
		cout << (char)controller_.Getkey_t() << " �޽�";
}

void Tetris::Run(void)
{
    while (running_) 
    {
        RunStep();
    }
}

void Tetris::RunStep(void)
{
    if (_kbhit()) 
    {
        int key = Controller::GetKey();
        KeyHandler(key);
    }
    else 
    {
        NormalStep();		
    }
}

bool Tetris::KeyHandler(int key)
{
    if (key == controller_.Getkey_esc()) 
    {
        running_ = false;
        return true;
    }
    else if (key == controller_.Getkey_right()) 
    {
        cur_tetromino_->MoveRight(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_left()) 
    {
        cur_tetromino_->MoveLeft(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_rotate()) 
    {
        cur_tetromino_->Rotate(reference_pos_);
        return true;
    }
    else if (key == controller_.Getkey_down()) 
    {
        cur_tetromino_->MoveDown(reference_pos_);
        return true;
    }
	else if (key == controller_.Getkey_space())
	{
		cur_tetromino_->GoBottom(reference_pos_);
		PrepareNextStep();
	}
	else if (key == controller_.Getkey_m())
	{
		if (C > 0)
		{
			board_.angel_card(reference_pos_);
			C--;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			Point::GotoXY(reference_pos_ + Point(25, 23));
			if (controller_.Getkey_m() == 'm')
				cout << "m õ��ī�� " << C;
			else
				cout << (char)controller_.Getkey_m() << " õ��ī��" << C;
		}
	}
	else if (key == controller_.Getkey_t())
	{
		_getch();
	}
    return false;
}

void Tetris::NormalStep(void)
{
    if (GetDiffTime() >= falling_speed_) 
    {
        if (cur_tetromino_->MoveDown(reference_pos_)) 
        {
            start_time_ = clock();
        }
        else 
        {	// ������ ��������. ��ó��
            PrepareNextStep();
        }
    }
}

void Tetris::PrepareNextStep(void)
{
	if (score_.score() > 40)
		falling_speed_ = 0.2;
	else if (score_.score() > 20)
		falling_speed_ = 0.4;

		cur_tetromino_->MarkCurTetrominoPos(reference_pos_);

		int EraseLineCount = board_.CheckLineFull(reference_pos_);
		if (EraseLineCount > 0)
			score_.UpdateScore(reference_pos_, EraseLineCount);
		if (cur_tetromino_->CheckEndCondition())
		{
			running_ = false;
			Point::GotoXY(reference_pos_ + Point(10, 10));
			cout << "The game is over !!!";
			_getch();
		}
		else
		{
			next_tetromino_->Tetromino::Erase(reference_pos_);
			GetCurTetrominoFromNext();
			cur_tetromino_->Draw(reference_pos_);
			GenerateNextTetromino();
			next_tetromino_->Draw(reference_pos_);
		}
		start_time_ = clock();
	
}

void Tetris::GenerateNextTetromino(void)
{
    TETROMINO_TYPE tetromino_type = (TETROMINO_TYPE) (rand() % TETROMINO_TYPE_COUNT);
    //if (rand() % 10 == 0)           // GhostTetromino
    //    next_tetromino_ = new GhostTetromino(&board_, tetromino_type);
    //else
    next_tetromino_ = new Tetromino(&board_, tetromino_type);
	next_tetromino_->SetCenterPos(g_next_tetromino_init_pos);
}

void Tetris::GetCurTetrominoFromNext(void)
{

	if (cur_tetromino_ != NULL)
	{
		delete cur_tetromino_;
	}// cur_tetromino_�� ���� NULL�� �ƴ϶�� delete

	cur_tetromino_ = next_tetromino_;// next_tetromino_�� ��Ʈ�ι̳븦 cur_tetromino_�� ������

	cur_tetromino_->SetCenterPos(g_cur_tetromino_init_pos);// cur_tetromino_�� ���� ��ġ setting    
}

double Tetris::GetDiffTime(void)
{
    clock_t CurTime;
    CurTime = clock();	//time(&CurTime);
    return ((double) (CurTime - start_time_) / CLOCKS_PER_SEC);
}

// Utility
void Tetris::SetCursorInvisible(void)	// ȭ�� Ŀ���� �� ���̰� ��
{
    CONSOLE_CURSOR_INFO ci = { 10, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}