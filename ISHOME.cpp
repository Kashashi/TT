#include <iostream>
#include<string>
#include <ctime>
#include <thread>
#include <fstream>
using namespace std;

char set_file_need_name[] = ("1.txt");//該字串為設定檔案
//int *runtime_code = new int(1); //執行代碼
int runtime_code [1] = {0};

double max_x = 40.0;//宣告最大範圍
double max_y = 40.0;//宣告最大範圍
double full_x = max_x;
double full_y = max_y;

//宣告延遲函數
void Delay(int time){//time*1000為秒數
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

//檢查完畢

bool Find_set(string a="a",string c="c",string b="="){
    ifstream in(set_file_need_name);
    string line;//行數
    string need_str = a+b+c;//字串合併
    if((a=="a")&&(c=="c")){//懶人警告
        cout << "你是不是忘記了什麼?\n";
    }
    if(in){// 有該檔案
        while (getline(in,line)) // line中不包括每行的換行符
        {
            cout << line << endl;
            if(line == need_str){
                cout <<"OK" << endl;
                return true;
            }
            else{
                cout << "該筆資料不存在或是遺失";
                *runtime_code = 3;
                return false;
            }
        }
    }
    else // 沒有該檔案
    {
        cout <<"沒有該檔案" << endl;
        return false;
    }
}

//void GUARD(int **runtime_code){
void GUARD(int runtime_code[1]){
    if(Find_set("GUARD","ON")){
    }
}

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
    HWND hwnd;//這是視窗的控制權
    MSG messages;//此處保存到應用程序的消息
    WNDCLASSEX wincl;//視窗類別的數據結構

    /* 視窗結構 */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;//視窗標題
    wincl.lpfnWndProc = WindowProcedure;//Windows調用此功能
    wincl.style = CS_DBLCLKS;//捕捉雙擊
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* 使用默認圖標和鼠標指針 */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;//視窗選單狀態:無
    wincl.cbClsExtra = 0;//視窗類別後沒有多餘的字節
    wincl.cbWndExtra = 0;//結構或視窗詳情
    /* 使用Windows的默認顏色作為窗口的背景 */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* 註冊視窗類別，如果失敗，則退出程序 */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* 該類別已完成註冊，就創建程序 */
    hwnd = CreateWindowEx (
           0,//視窗擴充變數
           szClassName,//類別名稱
           _T("Code::Blocks Template Windows App"),//標題文字
           WS_OVERLAPPEDWINDOW,//預設視窗
           CW_USEDEFAULT,//視窗出現的位置:由系統決定
           CW_USEDEFAULT,//顯示位置
           544,//應用程式的寬度
           375,//應用程式的高度 使用的是像素為單位
           HWND_DESKTOP,//指定為某東西的子視窗 這裡指定為桌面的子視窗
           NULL,//應用程式的選單:無
           hThisInstance,//程序實例處理程序
           NULL//視窗創建數據:無
           );

    /* 使視窗在螢幕上可見 */
    ShowWindow (hwnd, nCmdShow);
    /************************
    *   這裡可以加點什麼   *
    ************************/
    /* 運行消息循環。 它將一直運行到GetMessage()返回0為止 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* 將虛擬按鍵消息轉換為字符消息 */
        TranslateMessage(&messages);
        /* 發送消息到視窗過程 */
        DispatchMessage(&messages);
    }

    /* 程序的返回值為0 - PostQuitMessage()給出的數值 */
    return messages.wParam;
}


/* Windows函數DispatchMessage()調用此函數 */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)//處裡消息
    {
        case WM_DESTROY:
            PostQuitMessage (0);//將WM_QUIT發送到消息序列
            break;
        default://用於我們不處理的消息
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

#else
int main(){
    cout << "Hello! World!\n";
    cout << "地圖最大X軸:" << full_x << endl;
    cout << "地圖最大Y軸:" << full_y << endl;
    cout << "";
    player My_Self;//建構玩家
    My_Self.re_set_coordinate(0,0);//初始化玩家
    //thread RunTime_Code_Reseter(&GUARD,&runtime_code);
    thread RunTime_Code_Reseter(&GUARD,&runtime_code[1]);
	thread command_line(&player::console,&My_Self);
    thread player_control(&player::layout,&My_Self);
    RunTime_Code_Reseter.join();
    command_line.join();
    player_control.join();


    return 0;
}

#endif // LINUX
