#include "Definition.h"
#include "Core.h"
#include "Tools.h"
using namespace std;
extern HDC hdc;
extern InputInfo inputs[5][4];
extern RelicInfo 遗迹;

BOOL FindProcessPid(LPCSTR ProcessName, DWORD& dwPid)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	BOOL    bRet = FALSE;
	do
	{
		if (!strcmp(ProcessName, _bstr_t(pe32.szExeFile)))
		{
			dwPid = pe32.th32ProcessID;
			bRet = TRUE;
			break;
		}

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return bRet;
}
DWORD Getpid(int mode) {
	LPCSTR ListApps[]{ mode == 1 ? "dnplayer.exe" : "Wormhole.exe" };
	DWORD dwPid = 0;
	for (int i = 0; i < (sizeof(ListApps) / sizeof(ListApps[0])); i++)
	{
		if (FindProcessPid(ListApps[i], dwPid))
		{
			return  dwPid;
		}
	}
	return 0;
}
HWND GetWindowHandleByPID(DWORD dwProcessID)
{
	HWND h = GetTopWindow(0);
	while (h)
	{
		DWORD pid = 0;
		DWORD dwTheardId = GetWindowThreadProcessId(h, &pid);
		if (dwTheardId != 0)
		{
			if (pid == dwProcessID/*your process id*/)
			{
				// here h is the handle to the window

				if (GetTopWindow(h))
				{
					return h;
				}
				// return h;	
			}
		}
		h = ::GetNextWindow(h, GW_HWNDNEXT);
	}
	return NULL;
}
string GBK_2_UTF8(string gbkStr) {
	string outUtf8 = "";
	int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	outUtf8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return outUtf8;
}
string UTF8_2_GBK(string utf8Str) {
	string outGBK = "";
	int n = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
	WCHAR* str1 = new WCHAR[n];
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
	char* str2 = new char[n];
	WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, n, NULL, NULL);
	outGBK = str2;
	delete[] str1;
	str1 = NULL;
	delete[] str2;
	str2 = NULL;
	return outGBK;
}
int Str2Attribute(string src) {
	if (src == "力量")return 力量编号;
	if (src == "魔力")return 魔力编号;
	if (src == "技巧")return 技巧编号;
	if (src == "速度")return 速度编号;
	if (src == "体质")return 体质编号;
	if (src == "护甲")return 护甲编号;
	if (src == "抗性")return 抗性编号;
	if (src == "武威")return 武威编号;
	if (src == "物伤")return 物伤编号;
	if (src == "魔伤")return 魔伤编号;
	if (src == "持续")return 持续编号;
	if (src == "物理单吸")return 物理单吸编号;
	if (src == "物理群吸")return 物理群吸编号;
	if (src == "魔法单吸")return 魔法单吸编号;
	if (src == "魔法群吸")return 魔法群吸编号;
	if (src == "命中率")return 命中率编号;
	if (src == "闪避率")return 闪避率编号;
	if (src == "暴击率")return 暴击率编号;
	if (src == "异常附加率")return 异常附加率编号;
	if (src == "卸负")return 卸负编号;
	if (src == "无视护甲")return 无视护甲编号;
	if (src == "无视抗性")return 无视抗性编号;
	if (src == "物伤格挡")return 物伤格挡编号;
	if (src == "魔伤格挡")return 魔伤格挡编号;
	if (src == "回复效果")return 回复效果编号;
	if (src == "吸血效果")return 吸血效果编号;
	if (src == "治疗效果")return 治疗效果编号;
	return -1;
}

wchar_t wstr[50]; 
void StringTran(string src) {
	const char* pCStrKey = src.c_str();
	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, wstr, pSize);
}
string FloatTran(float src) {
	src += 0.0001;
	string str = to_string(src);
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.' && str[i + 1] == '0' && str[i + 2] == '0' && str[i + 3] == '0')str = str.substr(0, i);
		else if (str[i] == '.' && str[i + 1] != '0' && str[i + 2] == '0' && str[i + 3] == '0')str = str.substr(0, i + 2);
		else if (str[i] == '.' && str[i + 2] != '0' && str[i + 3] == '0')str = str.substr(0, i + 3);
	}
	return str;
}
void FigureOut(HDC hdc, int x, int y, int figure) {
	_itow_s(figure, wstr, 10);
	TextOut(hdc, x, y, wstr, wcslen(wstr));
}
void StringOut(HDC hdc, int x, int y, string str) {
	StringTran(str);
	TextOut(hdc, x, y, wstr, wcslen(wstr));
}
void FloatOut(HDC hdc, int x, int y, float figure) {
	StringTran(FloatTran(figure));
	TextOut(hdc, x, y, wstr, wcslen(wstr));
}
void Picture(HDC hdc, string src, int x, int y, bool transparent) {
	BITMAP mbm; HBITMAP mhbm; HDC mhdcbits; CImage mimage;
	StringTran(src);
	mimage.Load(wstr); mhbm = mimage.Detach();
	mhdcbits = CreateCompatibleDC(hdc);
	GetObject(mhbm, sizeof(BITMAP), &mbm);
	SelectObject(mhdcbits, mhbm);
	if (transparent) TransparentBlt(hdc, x, y, mbm.bmWidth, mbm.bmHeight, mhdcbits, 0, 0, mbm.bmWidth, mbm.bmHeight, RGB(1, 1, 1));
	else BitBlt(hdc, x, y, mbm.bmWidth, mbm.bmHeight, mhdcbits, 0, 0, SRCCOPY);
	DeleteDC(mhdcbits); DeleteObject(mhbm);
}
void Picture(HDC hdc, string src, int x, int y, int a, int b) {
	BITMAP mbm; HBITMAP mhbm; HDC mhdcbits; CImage mimage;
	StringTran(src);
	mimage.Load(wstr); mhbm = mimage.Detach();
	mhdcbits = CreateCompatibleDC(hdc);
	GetObject(mhbm, sizeof(BITMAP), &mbm);
	SelectObject(mhdcbits, mhbm);
	SetStretchBltMode(hdc, HALFTONE);
	StretchBlt(hdc, x, y, a, b, mhdcbits, 0, 0, mbm.bmWidth, mbm.bmHeight, SRCCOPY);
	DeleteDC(mhdcbits); DeleteObject(mhbm);
}

bool InBox(int mouse_x, int mouse_y, int l, int u, int r, int d) {
	if (mouse_x > l && mouse_x < r && mouse_y>u && mouse_y < d)return true;
	return false;
}
/*
int order[7];
void Order() {
	int box[7] = { 0,0,0,0,0,0,0 };
	int c = 0;
	while (c < 7) {
		int t = rand() % 7;
		if (box[t] == 0) {
			box[t] = 1;
			order[c] = t;
			c++;
		}
	}
}
*/
vector<int> order;
void Order(int num) {
	order.clear();
	int box[7] = { 0,0,0,0,0,0,0 };
	int c = 0;
	while (c < num) {
		int t = rand() % num;
		if (box[t] == 0) {
			box[t] = 1;
			order.push_back(t);
			c++;
		}
	}
}
int Int(float a) {
	if (a < 0)return a - 0.5;
	return a + 0.5;
}
bool Rand(float p) {
	if (p >= 1)return true;
	if (p <= 0)return false;
	float g = (rand() % 8192) / 8192.0;
	return (p >= g);
}
string Time(float t) {
	int f = int(t * 10 + 0.001) % 10;
	int s = int(t + 0.001) % 60;
	int m = int(t + 0.001) / 60;
	string ret = "";
	if (m < 10)ret += "0";
	ret += FloatTran(m);
	ret += ":";
	if (s < 10)ret += "0";
	ret += FloatTran(s);
	ret += ".";
	ret += FloatTran(f);
	return ret;
}
int End() {
	extern vector<Entity> entity[2];
	bool alive;
	alive = 0;
	for (int i = 0; i < entity[1].size(); i++)if (entity[1][i].存活 == 1)alive = 1;
	if (alive == 0) {
		return 2;
	}
	alive = 0;
	for (int i = 0; i < entity[0].size(); i++)if (entity[0][i].存活 == 1)alive = 1;
	if (alive == 0) {
		return 1;
	}
	return 0;
}

int basex, basey, clickInterval;
struct train {
	bool data[11][6];
	int number;
	train* next;
}*trains = NULL;
int out, maxsimilar;
bool charac[12][11][13];
bool figure[12][4][11][6];
int recastdata[12][2000];
int attribute[12];
extern int cursuit;
void Free(train* t) {
	if (t == NULL)return;
	if (t->next == NULL) {
		free(t);
		return;
	}
	else {
		Free(t->next);
		free(t);
		return;
	}
}
void GetInput() {
	fstream file("Texts/输入记录.txt");
	file >> cursuit;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			file >> inputs[i][j].职业; inputs[i][j].职业 = UTF8_2_GBK(inputs[i][j].职业);
			file >> inputs[i][j].武器; inputs[i][j].武器 = UTF8_2_GBK(inputs[i][j].武器);
			file >> inputs[i][j].铠甲; inputs[i][j].铠甲 = UTF8_2_GBK(inputs[i][j].铠甲);
			file >> inputs[i][j].饰品1; inputs[i][j].饰品1 = UTF8_2_GBK(inputs[i][j].饰品1);
			file >> inputs[i][j].饰品2; inputs[i][j].饰品2 = UTF8_2_GBK(inputs[i][j].饰品2);
			file >> inputs[i][j].环;
			file >> inputs[i][j].环特效级别;
			file >> inputs[i][j].魔石;
			file >> inputs[i][j].魔石参数a;
			file >> inputs[i][j].魔石参数b;
			for(int k=0;k<8;k++)file >> inputs[i][j].面板[k];
			for (int k = 0; k < 10; k++)file >> inputs[i][j].战利品[k];
			file >> inputs[i][j].先发;
			file >> inputs[i][j].技能设置[0];
			file >> inputs[i][j].技能设置[1];
			file >> inputs[i][j].技能设置[2];
			file >> inputs[i][j].技能设置[3];
			file >> inputs[i][j].攻击偏好;
		}
	}
	file >> 遗迹.遗迹战斗;
	file >> 遗迹.遗迹状态效果;
	file >> 遗迹.遗迹生命;
	file >> 遗迹.遗迹护甲;
	file >> 遗迹.遗迹抗性;
	file >> 遗迹.遗迹物伤;
	file >> 遗迹.遗迹魔伤;
	file >> 遗迹.遗迹回复效果;
	file >> 遗迹.遗迹吸血效果;
	file >> 遗迹.遗迹治疗效果;
	file >> 遗迹.遗迹命中率;
	file >> 遗迹.遗迹暴击率;
	extern string monster;
	file >> monster;
}
void PutInput() {
	fstream file;
	file.open("Texts/输入记录.txt", ofstream::out | ofstream::ate);
	file << cursuit << endl << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			file << GBK_2_UTF8(inputs[i][j].职业) << endl;
			file << GBK_2_UTF8(inputs[i][j].武器) << endl;
			file << GBK_2_UTF8(inputs[i][j].铠甲) << endl;
			file << GBK_2_UTF8(inputs[i][j].饰品1) << endl;
			file << GBK_2_UTF8(inputs[i][j].饰品2) << endl;
			file << inputs[i][j].环 << endl;
			file << inputs[i][j].环特效级别 << endl;
			file << inputs[i][j].魔石 << endl;
			file << inputs[i][j].魔石参数a << endl;
			file << inputs[i][j].魔石参数b << endl;
			for (int k = 0; k < 8; k++)file << inputs[i][j].面板[k] << endl;
			for (int k = 0; k < 10; k++)file << inputs[i][j].战利品[k] << endl;
			file << inputs[i][j].先发 << endl;
			file << inputs[i][j].技能设置[0] << endl;
			file << inputs[i][j].技能设置[1] << endl;
			file << inputs[i][j].技能设置[2] << endl;
			file << inputs[i][j].技能设置[3] << endl;
			file << inputs[i][j].攻击偏好 << endl << endl;
		}
	}
	file << 遗迹.遗迹战斗 << endl;
	file << 遗迹.遗迹状态效果 << endl;
	file << 遗迹.遗迹生命 << endl;
	file << 遗迹.遗迹护甲 << endl;
	file << 遗迹.遗迹抗性 << endl;
	file << 遗迹.遗迹物伤 << endl;
	file << 遗迹.遗迹魔伤 << endl;
	file << 遗迹.遗迹回复效果 << endl;
	file << 遗迹.遗迹吸血效果 << endl;
	file << 遗迹.遗迹治疗效果 << endl;
	file << 遗迹.遗迹命中率 << endl;
	file << 遗迹.遗迹暴击率 << endl;
	extern string monster;
	file << monster << endl;
}
void GetBase() {
	fstream infile("Texts/设备适配.txt");
	infile >> basex;
	infile >> basey;
	infile >> clickInterval;
	infile.close();
}
void PutBase() {
	fstream file;
	file.open("Texts/设备适配.txt", ofstream::out | ofstream::ate);
	file << basex << endl << basey << endl << clickInterval << endl;
}
void GetTrain() {
	Free(trains);
	trains = NULL;
	fstream infile("Texts/训练集.txt");
	char ch = '0'; infile >> ch;
	while (!infile.eof()) {
		train* p = new train;
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 6; j++) {
				if (ch == 'O')p->data[i][j] = 1;
				else p->data[i][j] = 0;
				infile >> ch;
			}
		}
		p->number = ch - 48;
		p->next = trains;
		trains = p;
		infile >> ch;
	}
	infile.close();
}
void GetData() {
	fstream infile("Texts/统计结果.txt");
	char ch = '0'; infile >> ch;
	int r = -1;
	while (!infile.eof()) {
		while (!(ch >= 48 && ch < 58 || ch == '_') && !infile.eof()) {
			if (ch == 'r')r++;
			infile >> ch;
		}
		while (ch != '=' && !infile.eof()) {
			int n1 = 0, n2 = 0;
			for (int i = 3; i >= 0; i--) {
				if (ch != '_')n1 += pow(10, i) * (ch - 48);
				infile >> ch;
			}
			infile >> ch;
			for (int i = 5; i >= 0; i--) {
				if (ch != '_')n2 += pow(10, i) * (ch - 48);
				infile >> ch;
			}
			recastdata[r][n1] = n2;
		}
	}
	infile.close();
}
void DelData() {
	fstream file;
	file.open("Texts/统计结果.txt", ofstream::out | ofstream::ate);
	for (int i = 0; i < 12; i++) {
		char str = i + 65;
		file << "==============Attri " << str << "==============" << endl;
	}
	file.close();
	for (int i = 0; i < 12; i++)for (int k = 0; k < 2000; k++)recastdata[i][k] = 0;
}
void PutData() {
	fstream file;
	file.open("Texts/统计结果.txt", ofstream::out | ofstream::ate);
	for (int i = 0; i < 12; i++) {
		char str = i + 65;
		file << "==============Attri " << str << "==============" << endl;
		for (int j = 0; j < 2000; j++) {
			if (recastdata[i][j] != 0) {
				if (j < 1000)file << "_";
				if (j < 100)file << "_";
				if (j < 10)file << "_";
				file << j << ":";
				if (recastdata[i][j] < 100000)file << "_";
				if (recastdata[i][j] < 10000)file << "_";
				if (recastdata[i][j] < 1000)file << "_";
				if (recastdata[i][j] < 100)file << "_";
				if (recastdata[i][j] < 10)file << "_";
				file << recastdata[i][j] << endl;
			}
		}
	}
	file.close();
}
int Recognize(int i, int j) {
	GetTrain();
	int count = 0;
	for (int k = 0; k < 11; k++) {
		for (int l = 0; l < 6; l++) {
			if (figure[i][j][k][l] == 1)count++;
		}
	}
	if (count < 10) {
		out = -1; maxsimilar = 66;
		return -1;
	}
	train* t = trains;
	out = -1; maxsimilar = -1;
	while (t != NULL) {
		int cursimilar = 0;
		for (int k = 0; k < 11; k++) {
			for (int l = 0; l < 6; l++) {
				if (figure[i][j][k][l] == t->data[k][l])cursimilar++;
			}
		}
		if (cursimilar > maxsimilar) {
			out = t->number;
			maxsimilar = cursimilar;
		}
		t = t->next;
	}
	if (maxsimilar < 66) {
		if (maxsimilar > 56) {
			ofstream file("Texts/训练集.txt", ofstream::app);
			for (int k = 0; k < 11; k++) {
				for (int l = 0; l < 6; l++) {
					if (figure[i][j][k][l] == 1)file << "O";
					else file << "_";
				}
				file << endl;
			}
			file << out << endl;
			file.close();
			GetData();
		}
		else if (maxsimilar > 50) {
			cout << "               WARNING：AI has never seen similar figure before." << endl;
			for (int k = 0; k < 11; k++) {
				for (int l = 0; l < 6; l++) {
					if (figure[i][j][k][l] == 1)cout << "O";
					else cout << "_";
				}
				cout << endl;
			}cout << out << "?(" << maxsimilar << ")" << endl;
			cout << "               AI can not confidently deside, please add it to 训练集.txt" << endl;
		}
		else {
			out = -2;
			return -2;
		}
	}
	return out;
}
int GetAttribute(int i) {
	int a[4]; int ret;
	Recognize(i, 0); a[0] = out;
	if (out != -2) { Recognize(i, 1); a[1] = out; }
	if (out != -2) { Recognize(i, 2); a[2] = out; }
	if (out != -2) { Recognize(i, 3); a[3] = out; }
	if (out == -2)ret = -1;
	else if (a[3] != -1)ret = a[0] * 1000 + a[1] * 100 + a[2] * 10 + a[3];
	else if (a[2] != -1)ret = a[0] * 100 + a[1] * 10 + a[2];
	else if (a[1] != -1)ret = a[0] * 10 + a[1];
	else if (a[0] != -1)ret = a[0];
	else ret = 0;
	if (ret > 0) {
		//cout << "Attribute" << i << ": " << ret << endl;
		recastdata[i][ret]++;
	}
	return attribute[i] = ret;
}
bool Equal(float a, float b) {
	return (int(a * 1000 + 0.5) == int(b * 1000 + 0.5));
}
void ReadRecast(HDC hdc, int m) {
	COLORREF pixel;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			pixel = ::GetPixel(hdc, j, i);
			charac[m][i][j] = !(GetRValue(pixel) < 100 && GetGValue(pixel) < 100 && GetBValue(pixel) < 100);
		}
	}
	/*
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			if (charac[m][i][j] == 1)cout << "0";
			else cout << "_";
		}
		cout << endl;
	}
	cout << endl;*/
	for (int n = 0; n < 1; n++) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 6; j++) {
				pixel = ::GetPixel(hdc, j + 6 * n, i);
				figure[m][n][i][j] = !(GetRValue(pixel) < 100 && GetGValue(pixel) < 100 && GetBValue(pixel) < 100);
			}
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 6; j++) {
				if (figure[m][n][i][j] == 1)cout << "O";
				else cout << "_";
			}
			cout << endl;
		}
		cout << endl;

	}
	//Recognize(0, 0);
	//GetAttribute(m);
}

float Normal(float mean, float stddev) {
	random_device rd;
	mt19937 gen(rd());
	float sample;
	normal_distribution<float> d(mean, stddev);
	sample = d(gen);
	return sample;
}
float GetRand(float l, float r) {
	float out = l - 1;
	while (out <= l || out >= r)out = Normal((l + r) / 2, (r - l) / 6);
	return out;
}
void Click(int l, int u, int r, int d, int t) {
	if (t == 1000)t = clickInterval;
	SetCursorPos(GetRand(l, r), GetRand(u, d));
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(GetRand(77, 113));
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(GetRand(t, t + 64));
}


