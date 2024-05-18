// finished
#ifndef _USER_CONTROL_H_
#define _USER_CONTROL_H_

#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdlib.h>

extern int getch();
extern void alarm_us(int n);
extern int dynamic_x;
extern int dynamic_y;
extern struct termios tm_old;
extern int score_x;
extern int score_y;
extern int level_x;
extern int level_y;
extern int user_score;
extern int user_level;
extern int tm;


extern int dynamic_num;
extern int dynamic_mode;
extern int dynamic_color;
extern void key_control();
extern int change_shape();

extern int move_down(int num,int mode);
extern int move_right(int n,int m);
extern int move_left(int n,int m);
extern void fall_down();
extern void game_over();
extern void recover_attribute();
#endif 