#include "Definition.h"
#include "Tools.h"
#include "Pub.h"
int forceExit;
Pub::Pub() {
	ģʽ = "�ű�";
	log.open("Texts/�ƹ���־.txt", ofstream::out | ofstream::app);
}
Pub::~Pub() {
	log.close();
}
int Pub::SSAppear() {
	extern HWND hwndDesk;
	extern HDC hdcDesk;
	hwndDesk = GetDesktopWindow();
	hdcDesk = GetDC(hwndDesk);
	COLORREF pixel;
	pixel = ::GetPixel(hdcDesk, 66, 233);
	if (GetRValue(pixel) - GetGValue(pixel) > 50 && GetRValue(pixel) - GetBValue(pixel) > 50)return 1;
	pixel = ::GetPixel(hdcDesk, 173, 233);
	if (GetRValue(pixel) - GetGValue(pixel) > 50 && GetRValue(pixel) - GetBValue(pixel) > 50)return 2;
	pixel = ::GetPixel(hdcDesk, 281, 233);
	if (GetRValue(pixel) - GetGValue(pixel) > 50 && GetRValue(pixel) - GetBValue(pixel) > 50)return 3;
	return 0;
}
void Pub::Piao() {
	log << endl;
	Click(21, 677, 122, 697); Sleep(500); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	while (1) {
		Click(37, 401, 168, 423); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(105, 435, 280, 474); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		int ret = SSAppear();
		if (ret == 0)continue;
		else if (ret == 1)Click(68, 222, 115, 268);
		else if (ret == 2)Click(172, 220, 226, 280);
		else if (ret == 3)Click(278, 225, 331, 278); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Sleep(200);
		Click(129, 583, 188, 604); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(126, 394, 300, 433); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(234, 399, 343, 418); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		break;
	}
	Click(96, 147, 306, 195); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
}
void Pub::ReadModel() {
	ShellExecute(NULL, _T("open"), _T("detect-hero-model.exe"), NULL, _T("PyScript\\"), SW_SHOW);
	Sleep(3500);
	int modelIndex = 0;
	fstream file("Texts/hero-model.txt");
	file >> modelIndex;
	file.close();
	fstream file1("Texts/hero-model.txt", ofstream::out | ofstream::ate);
	file1.close();
	switch (modelIndex) {
	case 1: {ģ�� = "սʿ"; break; }
	case 2: {ģ�� = "��ʦ"; break; }
	case 3: {ģ�� = "��ǹ��"; break; }
	case 4: {ģ�� = "Ǳ����"; break; }
	case 5: {ģ�� = "Ұ����"; break; }
	case 6: {ģ�� = "ʥְ"; break; }
	case 7: {ģ�� = "��֮����ʿ"; break; }
	case 8: {ģ�� = "���䷨ʦ"; break; }
	case 9: {ģ�� = "Ů�̿�"; break; }
	case 10: {ģ�� = "����"; break; }
	case 11: {ģ�� = "�ʼ�ǹ��"; break; }
	case 12: {ģ�� = "���ͼ�˾"; break; }
	case 13: {ģ�� = "���齣ʿ"; break; }
	case 14: {ģ�� = "����"; break; }
	case 15: {ģ�� = "��ɭ������"; break; }
	case 16: {ģ�� = "��֮���̿�"; break; }
	case 17: {ģ�� = "��ʿ"; break; }
	case 18: {ģ�� = "Ů��ʿ"; break; }
	case 19: {ģ�� = "����ѷ"; break; }
	case 20: {ģ�� = "����սʿ"; break; }
	case 21: {ģ�� = "���鷨ʦ"; break; }
	case 22: {ģ�� = "Ů��"; break; }
	case 23: {ģ�� = "��ҽ"; break; }
	case 24: {ģ�� = "������"; break; }
	case 25: {ģ�� = "׿���̿�"; break; }
	case 26: {ģ�� = "����"; break; }
	case 27: {ģ�� = "Ӷ��"; break; }
	case 28: {ģ�� = "ʥ��ʿ"; break; }
	case 29: {ģ�� = "���"; break; }
	case 30: {ģ�� = "��������"; break; }
	case 31: {ģ�� = "�ֵ�"; break; }
	case 32: {ģ�� = "��֮����ʿ"; break; }
	case 33: {ģ�� = "��ѻǹ��"; break; }
	case 0: {ģ�� = "ָ����ļȯ"; break; }
	}
	log << "ģ�ͣ�" << ģ�� << endl;
}
bool Pub::ReadJob() {
	if (ģ��.c_str() == "ָ����ļȯ") {
		ְҵ = "ָ����ļȯ";
		return 0;
	}
	ifstream file("JSON/ģ��תְ.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(ģ��.c_str()))ְҵ = string(data[ģ��.c_str()]["תְ"].GetString());
	else ְҵ = string("ָ����ļȯ");
	log << "ְҵ��" << ְҵ << endl;
	if (ְҵ == "ָ����ļȯ")return 0;
	return 1;
}
void Pub::ReadAttribute() {
	ShellExecute(NULL, _T("open"), _T("extract-attributes.exe"), NULL, _T("PyScript\\"), SW_SHOW);
	Sleep(2500);
	int modelIndex = 0;
	fstream file("Texts/attributes.txt");
	file >> ��;
	file >> ħ;
	file >> ��;
	file >> ��;
	file >> ��;
	file >> ��;
	file >> ��;
	if (ְҵ == "ʥ������" || ְҵ == "��ʥ" || ְҵ == "ս��" || ְҵ == "���̹�") �� = Int(1.6 * �� + 0.2 * ħ + 1.4 * �� + 1.3 * �� + 1.5 * �� + 3.0 * �� + 2.0 * ��);
	else if (ְҵ == "Ԧħ��ʹ") �� = Int(1.37 * �� + 1.37 * ħ + 1.4 * �� + 1.3 * �� + 1.5 * �� + 3.0 * �� + 2.0 * ��);
	else if (ְҵ == "��ϯ��ʦ" || ְҵ == "֯�η�ʦ" || ְҵ == "������֪") �� = Int(0.5 * �� + 1.7 * ħ + 1.4 * �� + 1.2 * �� + 1.2 * �� + 3.0 * �� + 2.0 * ��);
	else if (ְҵ == "��������" || ְҵ == "ҹħ" || ְҵ == "ǹ��" || ְҵ == "��Ұ����") �� = Int(1.4 * �� + 0.3 * ħ + 1.6 * �� + 1.4 * �� + 1.3 * �� + 3.0 * �� + 2.0 * ��);
	else if (ְҵ == "������" || ְҵ == "�������") �� = Int(1 * �� + 1.8 * ħ + 1.0 * �� + 1.3 * �� + 1.3 * �� + 3.0 * �� + 2.0 * ��);
	else �� = 0;
	file.close();
	fstream file1("Texts/attributes.txt", ofstream::out | ofstream::ate);
	file1.close();
	log << "���ԣ�" << �� << " " << ħ << " " << �� << " " << �� << " " << �� << " " << �� << endl;
}
int Pub::JobPlace(int star) {
	if (ְҵ == "ʥ������") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "��ʥ") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "Ԧħ��ʹ") {
		if (star == 1)return 2;
		if (star == 2)return 2;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "��ϯ��ʦ") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "֯�η�ʦ") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "������֪") {
		if (star == 1)return 3;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "������") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "�������") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "��������") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "ҹħ") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "ǹ��") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "��Ұ����") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "ս��") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (ְҵ == "���̹�") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
}
void Pub::Disemploy() {
	log << "���" << endl;
	Click(47, 578, 107, 600); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(120, 381, 307, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Sleep(3000);
	Click(120, 381, 307, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
}
void Pub::Star4() {
	if (ģʽ == "�ű�") {
		Click(125, 578, 184, 601);
	}
	else {
		for (int i = 0; i < 9; i++)Click(199, 582, 261, 605, GetRand(230, 270));
	}
	if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(199, 582, 261, 605); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (JobPlace(1) == 1) Click(134, 413, 289, 453);
	if (JobPlace(1) == 2) Click(134, 471, 289, 505);
	if (JobPlace(1) == 3) Click(134, 520, 289, 560); 
	if (PrintLess())forceExit = 2; if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(134, 413, 289, 453); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(138, 386, 284, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (ģʽ == "�ű�") {
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	}
	else {
		for (int i = 0; i < 29; i++) {
			Click(199, 582, 261, 605, 230);
			if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		}
	}if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(199, 582, 261, 605); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (JobPlace(2) == 1) Click(134, 413, 289, 453);
	if (JobPlace(2) == 2) Click(134, 471, 289, 505);
	if (JobPlace(2) == 3) Click(134, 520, 289, 560); 
	if (PrintLess())forceExit = 2; if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(134, 413, 289, 453); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(138, 386, 284, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (ģʽ == "�ű�") {
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	}
	else {
		for (int i = 0; i < 39; i++) {
			Click(199, 582, 261, 605, 230);
			if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		}
	}
	Click(199, 582, 261, 605); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (JobPlace(3) == 1) Click(134, 413, 289, 453); 
	if (JobPlace(3) == 2) Click(134, 471, 289, 505); 
	if (JobPlace(3) == 3) Click(134, 520, 289, 560); 
	if (PrintLess())forceExit = 2; if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(134, 413, 289, 453); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(138, 386, 284, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (ģʽ == "�ű�") {
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	}
	else {
		for (int i = 0; i < 49; i++) {
			Click(199, 582, 261, 605, 230);
			if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		}
	}
}
bool Pub::ReadStar4() {
	Click(285, 420, 321, 439); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return 0;
	ReadAttribute();
	Click(165, 580, 223, 600); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return 0;
	ifstream file("JSON/ģ��תְ.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(ģ��.c_str())) {
		rapidjson::Value& require = data[ģ��.c_str()]["����50��"];
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("ħ") && require["ħ"].GetInt() <= ħ)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		return 0;
	}
	else throw("ģ�����ƴ���");
}
void Pub::Star5() {
	Click(199, 582, 261, 605); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (JobPlace(4) == 1) Click(134, 413, 289, 453);
	if (JobPlace(4) == 2) Click(134, 471, 289, 505);
	if (JobPlace(4) == 3) Click(134, 520, 289, 560); 
	if (PrintLess())forceExit = 2; if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(134, 413, 289, 453); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(138, 386, 284, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (ģʽ == "�ű�") {
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		Click(125, 578, 184, 601); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	}
	else {
		for (int i = 0; i < 59; i++) {
			Click(199, 582, 261, 605, 230);
			if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
		}
	}
}
bool Pub::ReadStar5() {
	Click(285, 420, 321, 439); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return 0;
	ReadAttribute();
	Click(165, 580, 223, 600); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return 0;
	ifstream file("JSON/ģ��תְ.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(ģ��.c_str())) {
		rapidjson::Value& require = data[ģ��.c_str()]["����60��"];
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("ħ") && require["ħ"].GetInt() <= ħ)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		if (require.HasMember("��") && require["��"].GetInt() <= ��)return 1;
		return 0;
	}
	else throw("ģ�����ƴ���");
}
bool Pub::PrintLess() {
	extern HWND hwndDesk; 
	extern HDC hdcDesk;
	hwndDesk = GetDesktopWindow();
	hdcDesk = GetDC(hwndDesk);
	COLORREF pixel;
	pixel = ::GetPixel(hdcDesk, 189, 351);
	if (GetRValue(pixel) - GetGValue(pixel) > 100 && GetRValue(pixel) - GetBValue(pixel) > 100)return 1;
	pixel = ::GetPixel(hdcDesk, 190, 351);
	if (GetRValue(pixel) - GetGValue(pixel) > 100 && GetRValue(pixel) - GetBValue(pixel) > 100)return 1;
	pixel = ::GetPixel(hdcDesk, 191, 351);
	if (GetRValue(pixel) - GetGValue(pixel) > 100 && GetRValue(pixel) - GetBValue(pixel) > 100)return 1;
	pixel = ::GetPixel(hdcDesk, 192, 351);
	if (GetRValue(pixel) - GetGValue(pixel) > 100 && GetRValue(pixel) - GetBValue(pixel) > 100)return 1;
	return 0;
}
