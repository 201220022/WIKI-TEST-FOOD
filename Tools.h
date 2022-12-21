#ifndef _TOOLS_H_
#define _TOOLS_H_
DWORD Getpid(int mode);
HWND GetWindowHandleByPID(DWORD dwProcessID);
string GBK_2_UTF8(string gbkStr);
string UTF8_2_GBK(string utf8Str);

int Int(float a);
string FloatTran(float src);
bool Equal(float a, float b);

void FigureOut(HDC hdc, int x, int y, int figure);
void StringOut(HDC hdc, int x, int y, string str);
void FloatOut(HDC hdc, int x, int y, float figure);
void Picture(HDC hdc, string src, int x = 0, int y = 0, bool transparent = 0);
void Picture(HDC hdc, string src, int x, int y, int a, int b);

bool InBox(int mouse_x, int mouse_y, int l, int u, int r, int d);
void Order();
bool Rand(float p);
string Time(float t);
int End();

void GetInput();
void PutInput();
void GetBase();
void PutBase();
void GetTrain();
void GetData();
void DelData();
void PutData();
int Recognize(int i, int j);
void ReadRecast(HDC hdc, int m);
#endif
