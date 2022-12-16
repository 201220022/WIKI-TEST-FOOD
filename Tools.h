#ifndef _TOOLS_H_
#define _TOOLS_H_
//获取雷电模拟器。与计算器无关
DWORD Getpid(int mode);
HWND GetWindowHandleByPID(DWORD dwProcessID);
//GBK，UTF8互转
string GBK_2_UTF8(string gbkStr);
string UTF8_2_GBK(string utf8Str);

//浮点数转int,不用担心精度问题
int Int(float a);
//不用担心精度地把浮点数转string
string FloatTran(float src);
//不用担心精度比较浮点数相等
bool Equal(float a, float b);
/*
将整数，字符串，浮点数显示到（x,y）处。
FigureOut功能被FloatOut覆盖，StringOut(hdc, x, y, FloatTran(1.01))，也能显示Float
原装的函数是TextOut.一些特殊字符如果StringOut有问题就用原装的TextOut
*/
void FigureOut(HDC hdc, int x, int y, int figure);
void StringOut(HDC hdc, int x, int y, string str);
void FloatOut(HDC hdc, int x, int y, float figure);
/*
	Picture是我封装好了的图片显示函数
	Picture(hdc, "1.jpg");将图片显示到（0,0）位置
	Picture(hdc, "1.jpg"，x, y);将图片显示到（x, y）位置
	Picture(hdc, "1.jpg"，x, y, 1);将图片透明地显示到（x, y）位置，图片中像素为(1,1,1)的像素点不显示。
	Picture(hdc, "1.jpg"，x1, y1, x2, y2);将图片伸缩到(x2,y2)大小，并显示到(x1.y1)
*/
void Picture(HDC hdc, string src, int x = 0, int y = 0, bool transparent = 0);
void Picture(HDC hdc, string src, int x, int y, int a, int b);

//鼠标点击在区域内
bool InBox(int mouse_x, int mouse_y, int l, int u, int r, int d);
//0至6随机排序，保存到order[7],用来解决随意攻击等
void Order();
//以p的概率随机决定事件是否发生
bool Rand(float p);


void GetInput();//获取保存的队伍输入信息
void PutInput();//保存当亲的队伍输入信息
void GetBase();//和计算器无关
void PutBase();//和计算器无关
void GetTrain();//和计算器无关
void GetData();//和计算器无关
void DelData();//和计算器无关
void PutData();//和计算器无关
int Recognize(int i, int j);//和计算器无关
void ReadRecast(HDC hdc, int m);//和计算器无关
#endif
