#include <iostream>
#include<conio.h>
#include<string>
#include <ctime>
#include <thread>
using namespace std;

int *runtime_code = new int(1); //執行代碼

//檢查完畢

float max_x = 40.0;//宣告最大範圍
float max_y = 40.0;//宣告最大範圍
float full_x = max_x;
float full_y = max_y;

//宣告延遲函數
void Delay(int time)//time*1000為秒數
{
clock_t now = clock();
while(clock() - now < time);
}

class player {// 宣告 public 成員
public:
    int x; //初始座標x
    int y; //初始座標y
    double re_set_coordinate(double new_x = 0,double new_y = 0){//重新設定座標，同時可以用於初始化，當然也可以用於修用錯誤
        x = new_x;
        y = new_y;
    }
    void console(){
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
                    re_set_coordinate(i,j);
                    cout << "已生效\n";
                }
                else{
                    cout << "更改失敗\n";
                };
            }
        }
    }
    bool safe_check(double checking_x, double checking_y){
        int check_code = 1;
        if ((checking_x <= full_x)&&(checking_y <= full_y)){
            check_code = 0;
        }
        if (check_code == 0){return true;}
        else {cout << "錯誤[1]座標錯誤\n";return false;}
    }
    void layout(){
        while (*runtime_code == 1){
            Delay(16);
            /*一分鐘只執行60次
            但其實完全看CPU執行速度(kHz)*/
            cout << x << "," << y << endl;
        }
    }
};


int main(){
    cout << "Hello! World!\n";
    cout << "地圖最大X軸:" << full_x << endl;
    cout << "地圖最大Y軸:" << full_y << endl;
    cout << "";
    player My_Self;//建構玩家
    My_Self.re_set_coordinate(0,0);//初始化玩家
	thread a(&player::console,&My_Self);
    thread b(&player::layout,&My_Self);
    a.join();
    b.join();

    return 0;
}


