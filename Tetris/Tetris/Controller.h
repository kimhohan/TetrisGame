#ifndef JHHWANG_CONTROLLER_H
#define JHHWANG_CONTROLLER_H

#define KEY_ESC 27
#define KEY_UP (256 + 72)
#define KEY_DOWN (256 + 80)
#define KEY_LEFT (256 + 75)
#define KEY_RIGHT (256 + 77)
#define KEY_SPACE ' '

class Controller 
{
public :
    void SetController(int key_esc, int key_right, int key_left, int key_rotate, int key_down, int key_space, int key_m, int key_t);	   
    int Getkey_esc() { return key_esc_; }
    int Getkey_right() { return key_right_; }
    int Getkey_left() { return key_left_; }
    int Getkey_rotate() { return key_rotate_; }
    int Getkey_down() { return key_down_; }
	int Getkey_space() { return key_space_; }
	int Getkey_m() { return key_m_; }
	int Getkey_t() { return key_t_; }

    static int GetKey();    // 현재 입력된 키 알아오기

private :
    int key_esc_;           // 테트리스 종료
    int key_right_;         // 오른쪽으로 이동
    int key_left_;          // 왼쪽으로 이동
    int key_rotate_;        // 회전
    int key_down_;     
	int key_space_;// 한 번에 내려오기
	int key_m_;
	int key_t_;
};

#endif