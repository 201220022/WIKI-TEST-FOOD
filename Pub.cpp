#include "Definition.h"
#include "Tools.h"
#include "Pub.h"
int forceExit;
Pub::Pub() {
	模式 = "脚本";
	log.open("Texts/酒馆日志.txt", ofstream::out | ofstream::app);
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
	case 1: {模型 = "战士"; break; }
	case 2: {模型 = "法师"; break; }
	case 3: {模型 = "火枪手"; break; }
	case 4: {模型 = "潜行者"; break; }
	case 5: {模型 = "野蛮人"; break; }
	case 6: {模型 = "圣职"; break; }
	case 7: {模型 = "云之国剑士"; break; }
	case 8: {模型 = "部落法师"; break; }
	case 9: {模型 = "女刺客"; break; }
	case 10: {模型 = "异族"; break; }
	case 11: {模型 = "皇家枪手"; break; }
	case 12: {模型 = "神谕祭司"; break; }
	case 13: {模型 = "幽灵剑士"; break; }
	case 14: {模型 = "神侍"; break; }
	case 15: {模型 = "古森林贤者"; break; }
	case 16: {模型 = "云之国刺客"; break; }
	case 17: {模型 = "剑士"; break; }
	case 18: {模型 = "女剑士"; break; }
	case 19: {模型 = "亚马逊"; break; }
	case 20: {模型 = "矮人战士"; break; }
	case 21: {模型 = "精灵法师"; break; }
	case 22: {模型 = "女巫"; break; }
	case 23: {模型 = "巫医"; break; }
	case 24: {模型 = "半身人"; break; }
	case 25: {模型 = "卓尔刺客"; break; }
	case 26: {模型 = "游侠"; break; }
	case 27: {模型 = "佣兵"; break; }
	case 28: {模型 = "圣骑士"; break; }
	case 29: {模型 = "神官"; break; }
	case 30: {模型 = "白袍贤者"; break; }
	case 31: {模型 = "怪盗"; break; }
	case 32: {模型 = "星之国剑士"; break; }
	case 33: {模型 = "乌鸦枪手"; break; }
	case 0: {模型 = "指定招募券"; break; }
	}
	log << "模型：" << 模型 << endl;
}
bool Pub::ReadJob() {
	if (模型.c_str() == "指定招募券") {
		职业 = "指定招募券";
		return 0;
	}
	ifstream file("JSON/模型转职.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(模型.c_str()))职业 = string(data[模型.c_str()]["转职"].GetString());
	else 职业 = string("指定招募券");
	log << "职业：" << 职业 << endl;
	if (职业 == "指定招募券")return 0;
	return 1;
}
void Pub::ReadAttribute() {
	ShellExecute(NULL, _T("open"), _T("extract-attributes.exe"), NULL, _T("PyScript\\"), SW_SHOW);
	Sleep(2500);
	int modelIndex = 0;
	fstream file("Texts/attributes.txt");
	file >> 力;
	file >> 魔;
	file >> 技;
	file >> 速;
	file >> 体;
	file >> 甲;
	file >> 抗;
	if (职业 == "圣龙铁卫" || 职业 == "剑圣" || 职业 == "战神" || 职业 == "行刑官") 分 = Int(1.6 * 力 + 0.2 * 魔 + 1.4 * 技 + 1.3 * 速 + 1.5 * 体 + 3.0 * 甲 + 2.0 * 抗);
	else if (职业 == "驭魔剑使") 分 = Int(1.37 * 力 + 1.37 * 魔 + 1.4 * 技 + 1.3 * 速 + 1.5 * 体 + 3.0 * 甲 + 2.0 * 抗);
	else if (职业 == "首席法师" || 职业 == "织梦法师" || 职业 == "诅咒先知") 分 = Int(0.5 * 力 + 1.7 * 魔 + 1.4 * 技 + 1.2 * 速 + 1.2 * 体 + 3.0 * 甲 + 2.0 * 抗);
	else if (职业 == "诡术猎手" || 职业 == "夜魔" || 职业 == "枪侠" || 职业 == "狂野游侠") 分 = Int(1.4 * 力 + 0.3 * 魔 + 1.6 * 技 + 1.4 * 速 + 1.3 * 体 + 3.0 * 甲 + 2.0 * 抗);
	else if (职业 == "大主教" || 职业 == "光辉领主") 分 = Int(1 * 力 + 1.8 * 魔 + 1.0 * 技 + 1.3 * 速 + 1.3 * 体 + 3.0 * 甲 + 2.0 * 抗);
	else 分 = 0;
	file.close();
	fstream file1("Texts/attributes.txt", ofstream::out | ofstream::ate);
	file1.close();
	log << "属性：" << 力 << " " << 魔 << " " << 技 << " " << 速 << " " << 体 << " " << 分 << endl;
}
int Pub::JobPlace(int star) {
	if (职业 == "圣龙铁卫") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "剑圣") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "驭魔剑使") {
		if (star == 1)return 2;
		if (star == 2)return 2;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "首席法师") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "织梦法师") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "诅咒先知") {
		if (star == 1)return 3;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "大主教") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "光辉领主") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "诡术猎手") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "夜魔") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "枪侠") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "狂野游侠") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "战神") {
		if (star == 1)return 1;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
	if (职业 == "行刑官") {
		if (star == 1)return 2;
		if (star == 2)return 1;
		if (star == 3)return 1;
		if (star == 4)return 1;
	}
}
void Pub::Disemploy() {
	log << "解雇" << endl;
	Click(47, 578, 107, 600); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(120, 381, 307, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Sleep(3000);
	Click(120, 381, 307, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
}
void Pub::Star4() {
	if (模式 == "脚本") {
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
	if (模式 == "脚本") {
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
	if (模式 == "脚本") {
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
	if (模式 == "脚本") {
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
	ifstream file("JSON/模型转职.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(模型.c_str())) {
		rapidjson::Value& require = data[模型.c_str()]["四星50级"];
		if (require.HasMember("力") && require["力"].GetInt() <= 力)return 1;
		if (require.HasMember("魔") && require["魔"].GetInt() <= 魔)return 1;
		if (require.HasMember("技") && require["技"].GetInt() <= 技)return 1;
		if (require.HasMember("速") && require["速"].GetInt() <= 速)return 1;
		if (require.HasMember("体") && require["体"].GetInt() <= 体)return 1;
		if (require.HasMember("分") && require["分"].GetInt() <= 分)return 1;
		return 0;
	}
	else throw("模型名称错误");
}
void Pub::Star5() {
	Click(199, 582, 261, 605); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (JobPlace(4) == 1) Click(134, 413, 289, 453);
	if (JobPlace(4) == 2) Click(134, 471, 289, 505);
	if (JobPlace(4) == 3) Click(134, 520, 289, 560); 
	if (PrintLess())forceExit = 2; if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(134, 413, 289, 453); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	Click(138, 386, 284, 419); if (forceExit != 0 || KEY_DOWN(VK_BACK)) return;
	if (模式 == "脚本") {
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
	ifstream file("JSON/模型转职.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom;
	if (data.HasMember(模型.c_str())) {
		rapidjson::Value& require = data[模型.c_str()]["五星60级"];
		if (require.HasMember("力") && require["力"].GetInt() <= 力)return 1;
		if (require.HasMember("魔") && require["魔"].GetInt() <= 魔)return 1;
		if (require.HasMember("技") && require["技"].GetInt() <= 技)return 1;
		if (require.HasMember("速") && require["速"].GetInt() <= 速)return 1;
		if (require.HasMember("体") && require["体"].GetInt() <= 体)return 1;
		if (require.HasMember("分") && require["分"].GetInt() <= 分)return 1;
		return 0;
	}
	else throw("模型名称错误");
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
