#ifndef _USER_PRINT_H_
#define _USER_PRINT_H_
extern int next_num; //7个图案中的4个方向中某个方向。选择某个图案
extern int next_mode; //4个方向中某个方向。
extern int next_color; //颜色

// 右侧图形的坐标位置
extern int next_x;
extern int next_y;

// 初始化图形坐标
extern int init_x;
extern int init_y;

// 实时动态变化的坐标位置
extern int dynamic_x;
extern int dynamic_y;

// 实时动态变化的具体形状，颜色，模式
extern int dynamic_num;
extern int dynamic_mode;
extern int dynamic_color;

// 三维数组存储俄罗斯方块
extern int shape[7][4][18];
extern int matrix[24][28];

extern void store_current_shape();

extern void print_mode_shape(int n,int m,int x,int y,int c);
extern void print_next_shape();
extern void erase_last_shape(int n,int m,int a,int b); 

extern int judge_shape(int num,int mode,int x,int y);
extern void init_new_shape();
#endif