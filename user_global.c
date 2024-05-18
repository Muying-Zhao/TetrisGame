#include "user_print.h"
#include <termios.h>

struct termios tm_old;

int user_score = 0;//用户的分数
int user_level = 0;//用户的层次

int next_num = 0; //7个图案中的选择某个图案
int next_mode = 0;//4个方向中某个方向
int next_color = 0; //颜色

// 初始化图形坐标
int init_x = 24;
int init_y = 6;

// 右侧图形的坐标位置
int next_x = 46;
int next_y = 8;

// 实时动态变化的坐标位置
int dynamic_x = 0;
int dynamic_y = 0;

// 实时动态变化的具体形状，颜色，模式
int dynamic_num = 0;
int dynamic_mode = 0;
int dynamic_color = 0;

// 设置定时器时间
int tm=800000;//0.8s
// int tm=200000;//0.2s

int score_x = 45; //分数的横坐标
int score_y = 18; //分数的纵坐标
int level_x = 45; //等级的横坐标
int level_y = 22; //等级的纵坐标

int matrix[24][28]={0};


int shape[7][4][18] = 
{
 {
 {1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 2,2}, 
 {1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 2,2}, 
 {1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 2,2}, 
 {1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 2,2}, 
 },
 {
 {1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 3,0}, 
 {1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,3}, 
 {1,0,0,0, 1,0,0,0, 1,0,0,0, 1,0,0,0, 3,0}, 
 {1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,3}, 
 },
 {
 {0,1,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,0,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0, 2,1}, 
 {1,1,1,0, 0,1,0,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {0,1,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0, 2,1} 
 },
 {
 {1,1,0,0, 0,1,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {0,1,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0, 2,1}, 
 {1,1,0,0, 0,1,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {0,1,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0, 2,1}, 
 },
 {
 {0,1,1,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,0,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0, 2,1}, 
 {0,1,1,0, 1,1,0,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,0,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0, 2,1}, 
 },
 {
 {0,0,1,0, 1,1,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,0,0,0, 1,0,0,0, 1,1,0,0, 0,0,0,0, 2,1}, 
 {1,1,1,0, 1,0,0,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,1,0,0, 0,1,0,0, 0,1,0,0, 0,0,0,0, 2,1} 
 },
 {
 {1,0,0,0, 1,1,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {1,1,0,0, 1,0,0,0, 1,0,0,0, 0,0,0,0, 2,1}, 
 {1,1,1,0, 0,0,1,0, 0,0,0,0, 0,0,0,0, 1,2}, 
 {0,1,0,0, 0,1,0,0, 1,1,0,0, 0,0,0,0, 2,1}}, 
};