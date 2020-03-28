#include <iostream>
#include<string>
#include <ctime>
#include <thread>
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
#include <tchar.h>
#include <windows.h>

//宣告Windows程序
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

//使類名成為全局變量
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

#endif // LINUX

