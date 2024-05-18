#include <stdio.h> 
#include <termios.h>
#include <signal.h> 
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include "user_print.h"
#include "user_control.h"

extern int tm;//0.8s

extern int score_x; //分数的横坐标
extern int score_y; //分数的纵坐标
extern int level_x; //等级的横坐标
extern int level_y; //等级的纵坐标

void print_start_ui()
{
    // user清屏
 printf("\33[2J");
 int i;
 //输出黄色最顶行、最低行
 for(i = 0;i < 47;i++){
 printf("\33[%d;%dH\33[43m \33[0m",5,i+10);
 printf("\33[%d;%dH\33[43m \33[0m",30,i+10);
 }
 
//  输出黄色三列
 for(i = 0;i < 26;i++){
 printf("\33[%d;%dH\33[43m \33[0m",i+5,10);
 printf("\33[%d;%dH\33[43m \33[0m",i+5,40);
 printf("\33[%d;%dH\33[43m \33[0m",
 i+5,56);
 }
 
 //输出用户下一图形分割行
 for(i=0;i < 17;i++){
 printf("\33[%d;%dH\33[43m \33[0m",12,40+i);
 }
 
//  输出分数和等级
 printf("\33[%d;%dH分数:\33[0m",score_y,score_x);
 
 printf("\33[%d;%dH等级:\33[0m",level_y,level_x);
 fflush(NULL);
}
void init_game_ui()
{
 
 //输出窗体界面
 print_start_ui();
 
//  等待用户输入，然后程序开始执行
 getch();
 
 
//  获取随机数
// 设置随机数终极
 srand(time(NULL));
//  random()%(max-min+1)+min;
 dynamic_num = random()%7;
 dynamic_mode = random()%4;
 dynamic_color = random()%7+40;
 
 dynamic_x = init_x; 
 dynamic_y = init_y;
 
 //生成图形
 print_mode_shape(dynamic_num,dynamic_mode,dynamic_x,dynamic_y,dynamic_color);
 print_next_shape();
 printf("\33[?25l");
}

// 如果get_matrix_result函数是在同一个.c文件中定义的，
//确保它的定义在judge_end_game函数调用它之前。
int get_matrix_result(int n_line)
{
 int i = 0;
 if(n_line < 0)
 {
 return 1;
 }
 for(i = 0;i<28;i++)
 {
 if(matrix[n_line][i] != 0)
 {
 return 1;
 }
 }
 return 0;
}

int judge_end_game()
{
 int n_line = 23;
 int n_count = 0;
 int i = 0; 
 for(i = 0;i<24;i++)//0~23
 {
 int no_zero = get_matrix_result(i);
 if(no_zero != 0)
 {
 n_line--;
 }
 else
 {
 return 0;
 }
 }
 return 1;
}



void sig_handler(int signum)
{
//  图形向下移动
 move_down(dynamic_num,dynamic_mode);

//  判断游戏是否结束
 if(judge_end_game() == 1)
 {
 game_over();
//  恢复正常输入属性
 recover_attribute();
 exit(0); //结束当前进程
 }
 return;
}

int main()
{
 init_game_ui();

 signal(SIGALRM,sig_handler);

 //tm =0.8s
 alarm_us(tm);

 key_control();
 while(1);
 return 0;
}