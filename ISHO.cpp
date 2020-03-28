#include <iostream>
#include<string>
#include <ctime>
#include <thread>
#include <tchar.h>
using namespace std;

int *runtime_code = new int(1); //執行代碼

//檢查完畢

double max_x = 40.0;//宣告最大範圍
double max_y = 40.0;//宣告最大範圍
double full_x = max_x;
double full_y = max_y;

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

/*
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
}*/
#ifndef LINUX
#define UNICODE
#include <windows.h>
//主窗口類名稱
static char *szWindowClass[] = {"DesktopApp"};
//出現在應用程序標題欄中的字串
static char *szTitle[] = {"Windows Desktop Guided Tour Application"};
HINSTANCE hInst;
//轉發此代碼模塊中包含的函數的聲明：
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = "DesktopApp";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    hInst = hInstance;//將實例句柄存儲在全局變量中
    HWND hWnd = CreateWindow(// CreateWindow的參數說明：
        szWindowClass,// szWindowClass：應用程序的名稱
        szTitle,// szTitle：出現在標題欄中的文本
        WS_OVERLAPPEDWINDOW,// WS_OVERLAPPEDWINDOW：要創建的窗口的類型
        CW_USEDEFAULT, CW_USEDEFAULT,// CW_USEDEFAULT，CW_USEDEFAULT：初始位置（x，y）
        500, 100,// 500、100：初始大小（寬度，長度）
        NULL,// NULL：此窗口的父級
        NULL,// NULL：此應用程序沒有菜單欄
        hInstance,// hInstance：WinMain中的第一個參數
        NULL// NULL：在此應用程序中不使用
    );

   ShowWindow(hWnd,// ShowWindow的參數說明：
      nCmdShow);// hWnd：從CreateWindow返回的值
   UpdateWindow(hWnd);// nCmdShow：WinMain中的第四個參數
}


#endif // LINUX


