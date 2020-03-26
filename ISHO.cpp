#include <iostream>
#include<conio.h>
#include<string>
#include <ctime>
#include ".\mingw-std-threads\mingw.thread.h"
using namespace std;

int *runtime_code = new int(1); //����N�X
double max_x = 40.0;//�ŧi�̤j�d��
double max_y = 40.0;//�ŧi�̤j�d��
double full_x = max_x;
double full_y = max_y;


// �ŧi���O���a
class player {
// �ŧi public ����
public:
    int x; //��l�y��x
    int y; //��l�y��y
    double re_set_coordinate(double,double);
    void console();
private:


};
double player::re_set_coordinate(double new_x = 0,double new_y = 0){
//���s�]�w�y�СA�P�ɥi�H�Ω��l�ơA���M�]�i�H�Ω�ץο��~
x = new_x;
y = new_y;
}

class chatting_box_and_console{
//�ŧipublic����
public:
    void console(player &input);
    double safe_check(double, double);
};
//�����٥Ϊ��w���ˬd
double chatting_box_and_console::safe_check(double checking_x, double checking_y){
    int i = 1;
    if ((checking_x <= full_x)&&(checking_y <= full_y)){
        i = 0;
    }
    //�ˬd����
    if (i == 0){
        return 13395;
    }
    //�^�����T
    else{
        cout << "���~[1]�y�п��~\n";
        return 41392;
    }
    //�^�����~
}
//�ŧi���O����x
void chatting_box_and_console::console(player &input){
    string command;
    while (*runtime_code == 1){
        cin >> command;
        if(command == string("exit")){
            *runtime_code = 0;
        }
        else if(command == string("SetCoordinate")){
            double i,j;
            cout << "��J�s��x�y��:";
            cin >> i;
            cout << "��J�s��y�y��:";
            cin >> j;
            cout << "��襤\n";
            int k = safe_check(i,j);
            if (k == 13395){
                input.re_set_coordinate(i,j);
                cout << "�w�ͮ�\n";
            }
            else{
                cout << "��異��\n";
            };
        }
    }
}
//�ŧi������
void Delay(int time)//time*1000������
{
clock_t now = clock();
while(clock() - now < time);
}
void layout(player &input){
    while (*runtime_code == 1){
        Delay(16);
        /*�@�����u����60��
        ����꧹����CPU����t��(kHz)*/
        cout << input.x << "," << input.y << endl;
    }
}

int main() {
    cout << "Hello! World!\n";
    cout << "�a�ϳ̤jX�b:" << full_x << endl;
    cout << "�a�ϳ̤jY�b:" << full_y << endl;
    cout << "";
    player My_Self;//�غc���a
    My_Self.re_set_coordinate(0,0);//��l�ƪ��a
    chatting_box_and_console box;//�غc�½c�@�~
    thread a(&chatting_box_and_console::console,&box,(My_Self));
    a.join();
    thread b(layout,(My_Self));
    b.join();


    return 0;
}

