#include <iostream>
#include<conio.h>
#include<string>
#include <ctime>
#include ".\mingw-std-threads\mingw.thread.h"
using namespace std;

int *runtime_code = new int(1); //執行代碼
double max_x = 40.0;//宣告最大範圍
double max_y = 40.0;//宣告最大範圍
double full_x = max_x;
double full_y = max_y;


// 宣告類別玩家
class player {
// 宣告 public 成員
public:
    int x; //初始座標x
    int y; //初始座標y
    double re_set_coordinate(double,double);
    void console();
private:


};
double player::re_set_coordinate(double new_x = 0,double new_y = 0){
//重新設定座標，同時可以用於初始化，當然也可以用於修用錯誤
x = new_x;
y = new_y;
}

class chatting_box_and_console{
//宣告public成員
public:
    void console(player &input);
    double safe_check(double, double);
};
//給智障用的安全檢查
double chatting_box_and_console::safe_check(double checking_x, double checking_y){
    int i = 1;
    if ((checking_x <= full_x)&&(checking_y <= full_y)){
        i = 0;
    }
    //檢查完成
    if (i == 0){
        return 13395;
    }
    //回報正確
    else{
        cout << "錯誤[1]座標錯誤\n";
        return 41392;
    }
    //回報錯誤
}
//宣告類別控制台
void chatting_box_and_console::console(player &input){
    string command;
    while (*runtime_code == 1){
        cin >> command;
        if(command == string("exit")){
            *runtime_code = 0;
        }
        else if(command == string("SetCoordinate")){
            double i,j;
            cout << "輸入新的x座標:";
            cin >> i;
            cout << "輸入新的y座標:";
            cin >> j;
            cout << "更改中\n";
            int k = safe_check(i,j);
            if (k == 13395){
                input.re_set_coordinate(i,j);
                cout << "已生效\n";
            }
            else{
                cout << "更改失敗\n";
            };
        }
    }
}
//宣告延遲函數
void Delay(int time)//time*1000為秒數
{
clock_t now = clock();
while(clock() - now < time);
}
void layout(player &input){
    while (*runtime_code == 1){
        Delay(16);
        /*一分鐘只執行60次
        但其實完全看CPU執行速度(kHz)*/
        cout << input.x << "," << input.y << endl;
    }
}

int main() {
    cout << "Hello! World!\n";
    cout << "地圖最大X軸:" << full_x << endl;
    cout << "地圖最大Y軸:" << full_y << endl;
    cout << "";
    player My_Self;//建構玩家
    My_Self.re_set_coordinate(0,0);//初始化玩家
    chatting_box_and_console box;//建構黑箱作業
    thread a(box.console(My_Self));
    a.join();
    thread b(layout(My_Self));
    b.join();


    return 0;
}

