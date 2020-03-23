#include "player.h"
#include <iostream>

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
