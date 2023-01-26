#include "Definition.h"
#include "Pub.h"
#include "Core.h"
#include "Tools.h"
#include "WarForce.h"
HWND hwndApp, hwndEye, hwndGame, hwndDesk;
HDC hdc, hdcApp, hdcEye, hdcGame, hdcDesk;
vector<Entity> entity[2];
InputInfo inputs[5][4];
RelicInfo 遗迹;
int state, curplace, cursuit;
float timeClock; fstream timeLine; bool timePrinted; bool allowInterval = 1; bool painted = 0;
int tempa = 0; string monster, tstr; int th, th2, th3;

void Select() {
	//跟据选择的装备、输入的属性，显示冒险者的各种信息
	Picture(hdc, "Pictures/背景/出征.jpg");
	Picture(hdc, "Pictures/英雄/" + inputs[cursuit][curplace].职业 + "/海报.jpg");
	Picture(hdc, "Pictures/英雄/" + inputs[cursuit][curplace].职业 + "/技能.jpg", 650, 360, 300, 320);
	PBSelect(hdc, pen_brown, brush_brown);
	Rectangle(hdc, 0, 0, 357, 40);
	TextSelect(hdc, font_job, 0, 0, 0);
	StringOut(hdc, 188 - inputs[cursuit][curplace].职业.length() * 8, 9, inputs[cursuit][curplace].职业);
	TextOut(hdc, 15, 9, TEXT("<"), wcslen(TEXT("<")));
	TextOut(hdc, 330, 9, TEXT(">"), wcslen(TEXT(">")));
	TextSelect(hdc, font_curplace, 141, 130, 112);
	FigureOut(hdc, 15, 45, curplace+1);

	PBSelect(hdc, pen_white, brush_white);
	Rectangle(hdc, 697 + cursuit * 50.5, 34, 738 + cursuit * 50.5, 40);

	TextSelect(hdc, font_equip, 200, 200, 200);
	StringOut(hdc, 470, 96, inputs[cursuit][curplace].武器);
	StringOut(hdc, 470, 128, inputs[cursuit][curplace].铠甲);
	StringOut(hdc, 470, 161, inputs[cursuit][curplace].饰品1);
	StringOut(hdc, 470, 193, inputs[cursuit][curplace].饰品2);
	if (entity[1][curplace].环.类型 >= 1 && entity[1][curplace].环.类型 <= 9) { TextSelect(hdc, font_equip, 200, 200, 200); }
	else if (entity[1][curplace].环.类型 >= 10 && entity[1][curplace].环.类型 <= 18) { TextSelect(hdc, font_equip, 111, 153, 193); }
	else if (entity[1][curplace].环.类型 >= 19 && entity[1][curplace].环.类型 <= 27) { TextSelect(hdc, font_equip, 180, 40, 40); }
	else if (entity[1][curplace].环.类型 >= 28 && entity[1][curplace].环.类型 <= 39) { TextSelect(hdc, font_equip, 141, 130, 112); }
	StringOut(hdc, 470, 227, entity[1][curplace].环.Discription());
	TextSelect(hdc, font_equip, 200, 200, 200);
	StringOut(hdc, 470, 260, entity[1][curplace].魔石.ShortDiscription().substr(0, 13));
	if (inputs[cursuit][curplace].先发 == 0)StringOut(hdc, 470, 293, "不带先发");
	TextSelect(hdc, font_equip, 180, 40, 40);
	if (inputs[cursuit][curplace].先发 == 1)StringOut(hdc, 470, 293, "带先发");
	TextSelect(hdc, font_attribute, 0,0,0); 
	StringOut(hdc, 708, 120, "力量 :"); FigureOut(hdc, 757, 120, inputs[cursuit][curplace].面板[0]);
	StringOut(hdc, 708, 146, "魔力 :"); FigureOut(hdc, 757, 146, inputs[cursuit][curplace].面板[1]);
	StringOut(hdc, 708, 172, "技巧 :"); FigureOut(hdc, 757, 172, inputs[cursuit][curplace].面板[2]);
	StringOut(hdc, 708, 198, "速度 :"); FigureOut(hdc, 757, 198, inputs[cursuit][curplace].面板[3]);
	StringOut(hdc, 708, 224, "体质 :"); FigureOut(hdc, 757, 224, inputs[cursuit][curplace].面板[4]);
	StringOut(hdc, 708, 250, "护甲 :"); FigureOut(hdc, 757, 250, inputs[cursuit][curplace].面板[5]);
	StringOut(hdc, 708, 276, "抗性 :"); FigureOut(hdc, 757, 276, inputs[cursuit][curplace].面板[6]);
	StringOut(hdc, 708, 302, "武威 :"); FigureOut(hdc, 757, 302, inputs[cursuit][curplace].面板[7]);

	StringOut(hdc, 820, 120, "命中 :"); StringOut(hdc, 869, 120, FloatTran(entity[1][curplace].面板命中率 * 100) + "%");
	StringOut(hdc, 820, 146, "闪避 :"); StringOut(hdc, 869, 146, FloatTran(entity[1][curplace].面板闪避率 * 100) + "%");
	StringOut(hdc, 820, 172, "暴击 :"); StringOut(hdc, 869, 172, FloatTran(entity[1][curplace].面板暴击率 * 100) + "%");
	StringOut(hdc, 820, 198, "异常 :"); StringOut(hdc, 869, 198, FloatTran(entity[1][curplace].面板异常附加率 * 100) + "%");
	StringOut(hdc, 820, 224, "回复 :"); StringOut(hdc, 869, 224, FloatTran(entity[1][curplace].面板回复效果 * 100) + "%");
	StringOut(hdc, 820, 250, "无视 :"); StringOut(hdc, 869, 250, FloatTran(max(entity[1][curplace].面板无视护甲, entity[1][curplace].面板无视抗性)));
	if (entity[1][curplace].面板物伤 >= entity[1][curplace].面板魔伤) {
		StringOut(hdc, 820, 276, "物伤 :"); StringOut(hdc, 869, 276, FloatTran(entity[1][curplace].面板物伤 * 100) + "%");
	}
	else {
		StringOut(hdc, 820, 276, "魔伤 :"); StringOut(hdc, 869, 276, FloatTran(entity[1][curplace].面板魔伤 * 100) + "%");
	}
	if (max(entity[1][curplace].面板物理单吸, entity[1][curplace].面板魔法单吸) == max(entity[1][curplace].面板物理群吸, entity[1][curplace].面板魔法群吸)) {
		StringOut(hdc, 820, 302, "吸血 :"); StringOut(hdc, 869, 302, FloatTran(max(entity[1][curplace].面板物理单吸, entity[1][curplace].面板魔法单吸) * 100) + "%");
	}
	else if (max(entity[1][curplace].面板物理单吸,entity[1][curplace].面板魔法单吸) > max(entity[1][curplace].面板物理群吸, entity[1][curplace].面板魔法群吸)) {
		StringOut(hdc, 820, 302, "单吸 :"); StringOut(hdc, 869, 302, FloatTran(max(entity[1][curplace].面板物理单吸, entity[1][curplace].面板魔法单吸) * 100) + "%");
	}
	else {
		StringOut(hdc, 820, 302, "群吸 :"); StringOut(hdc, 869, 302, FloatTran(max(entity[1][curplace].面板物理群吸, entity[1][curplace].面板魔法群吸) * 100) + "%");
	}
	TextSelect(hdc, font_outSkillSet, 255, 255, 255);
	for (int i = 0; i < 5; i++) StringOut(hdc, 862 - 2 * entity[1][curplace].Discription(i).size(), 395 + i * 58, entity[1][curplace].Discription(i));
	for (int i = 0; i < 5; i++) Picture(hdc, "Pictures/背景/选择钮.bmp", 825 + Int(70 * entity[1][curplace].P(i)), 412 + i * 58, 1);
}
void SelectMagicStone() {
	Picture(hdc, "Pictures/背景/魔石.jpg");
	MagicStone m;
	m.Init(th, th2, th3);
	TextSelect(hdc, font_msin, 180, 180, 180);
	StringOut(hdc, 520, 375, "输入特效概率 : ");
	StringOut(hdc, 520, 415, "输入特效数值 : ");
	FigureOut(hdc, 670, 375, inputs[cursuit][curplace].魔石参数a);
	FigureOut(hdc, 670, 415, inputs[cursuit][curplace].魔石参数b);
	TextSelect(hdc, font_ring, 220, 220, 220);
	if (entity[1][curplace].魔石.Discription().length() > 30) {
		int cut = 0;
		for (int i = 0; i < entity[1][curplace].魔石.Discription().length(); i++)if (entity[1][curplace].魔石.Discription()[i] == ',')cut = i + 2;
		StringOut(hdc, 230, 480, entity[1][curplace].魔石.Discription().substr(0, cut));
		StringOut(hdc, 300, 520, entity[1][curplace].魔石.Discription().substr(cut, entity[1][curplace].魔石.Discription().length()));
	}
	else {
		StringOut(hdc, 400, 500, entity[1][curplace].魔石.Discription());
	}
}
void SelectRelic() {
	Picture(hdc, "Pictures/背景/选怪.jpg");
	TextSelect(hdc, font_relic, 220, 220, 220);
	string s = 遗迹.遗迹战斗 == 0 ? "否" : "是";
	StringOut(hdc, 120, 120, "遗  迹  战  斗 ：" + s);
	StringOut(hdc, 120, 160, "遗迹状态效果 ：" + FloatTran(遗迹.遗迹状态效果) + "%");
	StringOut(hdc, 120, 200, "遗  迹  生  命 ：" + FloatTran(遗迹.遗迹生命) + "%");
	StringOut(hdc, 120, 240, "遗  迹  护  甲 ：" + FloatTran(遗迹.遗迹护甲));
	StringOut(hdc, 120, 280, "遗  迹  抗  性 ：" + FloatTran(遗迹.遗迹抗性));
	StringOut(hdc, 120, 320, "遗  迹  物  伤 ：" + FloatTran(遗迹.遗迹物伤) + "%");
	StringOut(hdc, 120, 360, "遗  迹  魔  伤 ：" + FloatTran(遗迹.遗迹魔伤) + "%");
	StringOut(hdc, 120, 400, "遗迹回复效果 ：" + FloatTran(遗迹.遗迹回复效果) + "%");
	StringOut(hdc, 120, 440, "遗迹吸血效果 ：" + FloatTran(遗迹.遗迹吸血效果) + "%");
	StringOut(hdc, 120, 480, "遗迹治疗效果 ：" + FloatTran(遗迹.遗迹治疗效果) + "%");
	StringOut(hdc, 120, 520, "遗 迹 命 中 率：" + FloatTran(遗迹.遗迹命中率) + "%");
	StringOut(hdc, 120, 560, "遗 迹 暴 击 率：" + FloatTran(遗迹.遗迹暴击率) + "%");
	TextSelect(hdc, font_monsterSearch, 220, 220, 220);
	StringOut(hdc, 630 - monster.length() * 8, 208, monster);
}
void StartWar() {
	for (int i = 0; i < entity[1].size(); i++)entity[1][i].Init(i);
	LoadMonster(monster);
	for(int i=0;i < entity[1].size(); i++) {
		if (entity[1][i].存活 != 0) {
			entity[1][i].面板[回复效果编号] += 1;
			entity[1][i].面板[吸血效果编号] += 1;
			entity[1][i].面板[治疗效果编号] += 1;
		}
	}
	for (int i = 0; i < entity[0].size(); i++) {
		if (entity[0][i].存活 != 0) {
			entity[0][i].面板[回复效果编号] += 1;
			entity[0][i].面板[吸血效果编号] += 1;
			entity[0][i].面板[治疗效果编号] += 1;
		}
	}
	for (int i = 0; i < entity[1].size(); i++)if (entity[1][i].存活 != 0) entity[1][i].Prepare("战斗开始");
	for (int i = 0; i < entity[0].size(); i++)if (entity[0][i].存活 != 0) {
		if (entity[0][i].狂暴技能.回复抑制 != 0) {
			for (int j = 0; j < entity[0].size(); j++) {
				if (entity[0][j].存活 != 0) {
					entity[0][j].面板[回复效果编号] *= (1 - entity[0][i].狂暴技能.回复抑制);
				}
			}
		}
		if (entity[0][i].狂暴技能.吸血抑制 != 0) {
			for (int j = 0; j < entity[0].size(); j++) {
				if (entity[0][j].存活 != 0) {
					entity[0][j].面板[吸血效果编号] *= (1 - entity[0][i].狂暴技能.吸血抑制);
				}
			}
		}
		if (entity[0][i].狂暴技能.治疗抑制 != 0) {
			for (int j = 0; j < entity[0].size(); j++) {
				if (entity[0][j].存活 != 0) {
					entity[0][j].面板[治疗效果编号] *= (1 - entity[0][i].狂暴技能.治疗抑制);
				}
			}
		}
	}
	timeClock = 0;
}
void TxtFight() {
	allowInterval = 0;
	timeLine.open("Texts/temp.txt", ofstream::out | ofstream::ate);
	timeLine << endl <<  "战斗开始" << endl; timePrinted = 1; StartWar();
	timeLine << endl << "当前属性" << endl;
	for (int i = 0; i < entity[1].size(); i++)if (entity[1][i].存活 != 0) {
		timeLine << "    " << entity[1][i].名称 << "：";
		timeLine << "力" << entity[1][i].力量 << "  ";
		timeLine << "魔" << entity[1][i].魔力 << "  ";
		timeLine << "技" << entity[1][i].技巧 << "  ";
		timeLine << "速" << entity[1][i].速度 << "  ";
		timeLine << "甲" << entity[1][i].护甲 << "  ";
		timeLine << "抗" << entity[1][i].抗性 << endl;
	}
	while(!End() && timeClock <= 3600) {
		timePrinted = 0;
		timeClock += plank; timeClock = float(Int(timeClock * 1000)) / 1000;
		for (int i = 0; i < entity[0].size(); i++)if (!End() && entity[0][i].存活 != 0) entity[0][i].ViolentTime(); 
		for (int i = 0; i < entity[0].size(); i++)if (!End() && entity[0][i].存活 != 0) entity[0][i].StatusTime();
		for (int i = 0; i < entity[1].size(); i++)if (!End() && entity[1][i].存活 != 0) entity[1][i].StatusTime();
		for (int i = 0; i < entity[0].size(); i++)if (!End() && entity[0][i].存活 != 0) entity[0][i].SkillTime(); 
		for (int i = 0; i < entity[1].size(); i++)if (!End() && entity[1][i].存活 != 0) entity[1][i].SkillTime(); 
	}
	timeLine.close();
	fstream infile, outfile;
	infile.open("Texts/temp.txt");
	outfile.open("Texts/时间轴.txt", ofstream::out | ofstream::ate);
	if (End() == 1)outfile << "VICTORY" << endl << endl;
	else if (End() == 2) {
		outfile << "DEFEAT" << endl;
		//outfile << "    战斗失败原因：" << endl;
		//outfile << "    致死伤害类型：" << endl;
		//outfile << "    致死伤害来源：" << endl;
	}
	else outfile << "TIME OVER" << endl << endl;
	outfile << "输出量：" << endl;
	for (int i = 0; i < 4; i++)if (entity[1][i].名称 != "未选择")outfile << "    " << entity[1][i].名称 << " " << entity[1][i].总伤害 << endl;
	outfile << "最低血线：" << endl;
	for (int i = 0; i < 4; i++)if (entity[1][i].名称 != "未选择")outfile << "    " << entity[1][i].名称 << " " << entity[1][i].最低血线 << endl;
	while (!infile.eof()) {
		string s;
		getline(infile, s);
		outfile << s << endl;
	}
	infile.close();
	outfile.close();
	remove("Texts/temp.txt");
	ShellExecute(NULL, _T("open"), _T("notepad.exe"), _T("Texts/时间轴.txt"), NULL, SW_SHOW);
	allowInterval = 1;
}

void State(int state_) {
	//点击修改输入属性时，自动把之前的输入清零
	if (state != state_)tstr = "";
	if (state_ >= 13 && state_ <= 22 && state != state_)inputs[cursuit][curplace].战利品[state_ - 13] = 0;
	if (state_ >= 24 && state_ <= 31 && state != state_)inputs[cursuit][curplace].面板[state_ - 24] = 0;
	if (state_ == 33 && state != state_)遗迹.遗迹状态效果 = 0;
	if (state_ == 34 && state != state_)遗迹.遗迹生命 = 0;
	if (state_ == 35 && state != state_)遗迹.遗迹护甲 = 0;
	if (state_ == 36 && state != state_)遗迹.遗迹抗性 = 0;
	if (state_ == 37 && state != state_)遗迹.遗迹物伤 = 0;
	if (state_ == 38 && state != state_)遗迹.遗迹魔伤 = 0;
	if (state_ == 39 && state != state_)遗迹.遗迹回复效果 = 0;
	if (state_ == 40 && state != state_)遗迹.遗迹吸血效果 = 0;
	if (state_ == 41 && state != state_)遗迹.遗迹治疗效果 = 0;
	if (state_ == 42 && state != state_)遗迹.遗迹命中率 = 0;
	if (state_ == 43 && state != state_)遗迹.遗迹暴击率 = 0;
	//切换state
	state = state_;
	//显示该state对应的显示界面
	entity[1][curplace].Init(curplace);
	if (state == -1) {
		Picture(hdc, "Pictures/背景/封面.jpg");
	}
	else if (state == 0) {
		Picture(hdc, "Pictures/背景/庇护所.jpg");
	}
	else if (state == 1) {
		PutInput();
		Select();
	}
	else if (state == 2) {
		Picture(hdc, "Pictures/背景/选将.jpg");
	}
	else if (state >= 3 && state <= 6) {
		Select();
		PBSelect(hdc, pen_recast, brush_recast);
		Rectangle(hdc, 470, 100 + 32 * (state - 3), 600, 128 + 32 * (state - 3));
		TextSelect(hdc, font_equip, 200, 200, 200);
		TextOut(hdc, 585, 96 + 32 * (state - 3), TEXT("⇦"), wcslen(TEXT("⇦")));
		if (ReadEquipAbbr(tstr) != "")StringOut(hdc, 470, 96 + 32 * (state - 3), ReadEquipAbbr(tstr));
		else StringOut(hdc, 470, 96 + 32 * (state - 3), tstr);
	}
	else if (state == 7) {
		Picture(hdc, "Pictures/背景/环.jpg");
	}
	else if (state == 8) {
		Picture(hdc, "Pictures/背景/环特效.jpg");
		TextSelect(hdc, font_ring, 200, 200, 200);
		Ring r;
		r.Init(th, 0);
		for (int i = 0; i <= 10; i++) {
			FloatOut(hdc, 463, 80 + i * 45, r.Value(i));
		}
	}
	else if (state == 9) {
		SelectMagicStone();
	}
	else if (state == 10) {
		SelectMagicStone();
		TextSelect(hdc, font_attribute, 200, 200, 200);
		TextOut(hdc, 730, 380, TEXT("⇦"), wcslen(TEXT("⇦")));
	}
	else if (state == 11) {
		SelectMagicStone();
		TextSelect(hdc, font_attribute, 200, 200, 200);
		TextOut(hdc, 730, 420, TEXT("⇦"), wcslen(TEXT("⇦")));
	}
	else if (state >= 12 && state <= 23) {
		Picture(hdc, "Pictures/背景/战利品.jpg");
		TextSelect(hdc, font_zlp, 200, 200, 200);
		StringOut(hdc, 360, 90 + 45 * 0, "物    伤 : ");
		StringOut(hdc, 360, 90 + 45 * 1, "魔    伤 : ");
		StringOut(hdc, 360, 90 + 45 * 2, "物理单吸 : ");
		StringOut(hdc, 360, 90 + 45 * 3, "物理群吸 : ");
		StringOut(hdc, 360, 90 + 45 * 4, "魔法单吸 : ");
		StringOut(hdc, 360, 90 + 45 * 5, "魔法群吸 : ");
		StringOut(hdc, 360, 90 + 45 * 6, "命 中 率 : ");
		StringOut(hdc, 360, 90 + 45 * 7, "闪 避 率 : ");
		StringOut(hdc, 360, 90 + 45 * 8, "暴 击 率 : ");
		StringOut(hdc, 360, 90 + 45 * 9, "回复效果 : ");
		StringOut(hdc, 360, 90 + 45 * 10, "先    发 : ");
		TextSelect(hdc, font_zlp2, 200, 200, 200);
		for (int i = 0; i < 10; i++)StringOut(hdc, 510, 87 + 45 * i, FloatTran(inputs[cursuit][curplace].战利品[i]) + "%");
		if (inputs[cursuit][curplace].先发 == 0)StringOut(hdc, 510, 87 + 45 * 10, "不带");
		if (inputs[cursuit][curplace].先发 == 1)StringOut(hdc, 510, 87 + 45 * 10, "带");
		if (state >= 13) {
			TextOut(hdc, 600, 87 + 45 * (state - 13), TEXT("⇦"), wcslen(TEXT("⇦")));
		}
	}
	else if (state >= 24 && state <= 31) {
		Select();
		PBSelect(hdc, pen_brown, brush_brown);
		Rectangle(hdc, 754, 119 + 26.1 * (state - 24), 817, 143 + 26.1 * (state - 24));
		TextSelect(hdc, font_attribute, 0, 0, 0);
		TextOut(hdc, 800, 120 + 26.1 * (state - 24), TEXT("⇦"), wcslen(TEXT("⇦")));
		FigureOut(hdc, 757, 120 + 26.1 * (state - 24), inputs[cursuit][curplace].面板[state - 24]);
	}
	else if (state == 32) {
		PutInput();
		SelectRelic();
	}
	else if (state >= 33 && state <= 43) {
		SelectRelic();
		TextSelect(hdc, font_relicpoint, 220, 220, 220);
		TextOut(hdc, 350, 157 + 40 * (state - 33), TEXT("⇦"), wcslen(TEXT("⇦")));
	}
	else if (state == 44) {
		SelectRelic();
		PBSelect(hdc, pen_coffee, brush_coffee);
		Rectangle(hdc, 481, 175, 782, 280);
		TextSelect(hdc, font_monsterSearchPoint, 220, 220, 220);
		TextOut(hdc, 625, 140, TEXT("⇩"), wcslen(TEXT("⇩")));
		TextSelect(hdc, font_monsterSearch, 220, 220, 220);
		StringOut(hdc, 630 - tstr.length() * 8, 208, tstr);
	}
	else if (state == 101) {
		Picture(hdc, "Pictures/背景/酒馆.jpg");
		timeClock = -1;
		extern int forceExit;
		forceExit = 0;
	}
	else if (state == 111) {
		Picture(hdc, "Pictures/背景/教会.jpg");
		hwndDesk = GetDesktopWindow();
		hdcDesk = GetDC(hwndDesk);
		BitBlt(hdc, 0, -31, 380, 727, hdcDesk, 0, 0, SRCCOPY);
		PBSelect(hdc, pen_red, brush_red);
		MoveToEx(hdc, 37, 145, NULL); LineTo(hdc, 37, 543);
		MoveToEx(hdc, 350, 141, NULL); LineTo(hdc, 350, 550);
		MoveToEx(hdc, 85, 598, NULL); LineTo(hdc, 302, 598);
		MoveToEx(hdc, 57, 200, NULL); LineTo(hdc, 112, 200);
		MoveToEx(hdc, 51, 378, NULL); LineTo(hdc, 110, 378);
	}
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	//PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_CLOSE: DestroyWindow(hwnd); break;
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_PAINT: {
		if (painted == 0) {
			GetBase();
			LoadKeyboardLayout(L"00000804", KLF_ACTIVATE | KLF_SETFORPROCESS);
			keybd_event(17, 0, 0, 0);
			keybd_event(163, 0, 0, 0);
			keybd_event(32, 0, 0, 0);
			keybd_event(32, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(163, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(17, 0, 0, 0);
			keybd_event(163, 0, 0, 0);
			keybd_event(17, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(163, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(13, 0, 0, 0);
			keybd_event(13, 0, KEYEVENTF_KEYUP, 0);
			for (int i = 0; i < 4; i++) { Entity a; entity[1].push_back(a); }
			State(-1);
			painted = 1;
		}
		break;
	}
	case WM_LBUTTONUP: {
		int mouse_x, mouse_y;
		mouse_x = LOWORD(lparam); mouse_y = HIWORD(lparam);
		if (tempa == 0) { cout << "if (Inbox(" << mouse_x << "," << mouse_y << ","; tempa = 1; }
		else {
			cout << mouse_x << "," << mouse_y << ")){  }" << endl; tempa = 0;
			//COLORREF pixel = ::GetPixel(hdc, mouse_x, mouse_y);
			//cout << int(GetRValue(pixel)) << ", " << int(GetGValue(pixel)) << ", " << int(GetBValue(pixel)) << endl;
		}
		if (state == -1) {
			State(0);
			break;
		}
		else if (state == 0) {
			//庇护所大厅
			if (Inbox(383, 547, 567, 651) || Inbox(460, 495, 496, 551)) { GetInput(); State(1); }
			else if (Inbox(239, 294, 339, 397) || Inbox(262, 399, 366, 501)) { State(101);}
			else if (Inbox(169, 157, 243, 253)) { State(111); }
		}
		else if (state == 1) {
			//出征的配装选择界面
			if (Inbox(556, 638, 625, 675)) { State(0); }//点击返回
			if (Inbox(695, 44, 739, 78)) { cursuit = 0; curplace = 0; State(1); }//切换至套装1
			if (Inbox(747, 45, 789, 79)) { cursuit = 1; curplace = 0; State(1); }//切换至套装2
			if (Inbox(798, 47, 840, 79)) { cursuit = 2; curplace = 0; State(1);	}//切换至套装3
			if (Inbox(848, 45, 890, 79)) { cursuit = 3; curplace = 0; State(1);	}//切换至套装4
			if (Inbox(898, 46, 941, 79)) { cursuit = 4; curplace = 0; State(1);	}//切换至套装5
			if (Inbox(0, 0, 40, 40) && curplace != 0) { curplace--; State(1); }  //左右切换队伍第1至第4号位
			if (Inbox(320, 0, 360, 40) && curplace != 3) { curplace++; State(1); }
			if (Inbox(120, 0, 240, 40)) State(2);                                //点击英雄名称选择英雄
			if (inputs[cursuit][curplace].职业 != "未选择") {
				//点击输入装备环魔石战利品
				if (Inbox(427, 93, 452, 120)) State(3);
				if (Inbox(426, 126, 453, 154)) State(4);
				if (Inbox(427, 160, 454, 185)) State(5);
				if (Inbox(426, 190, 453, 220)) State(6);
				if (Inbox(428, 226, 452, 251)) State(7);
				if (Inbox(428, 259, 454, 284)) State(9);
				if (Inbox(426, 291, 453, 314)) State(12);

				//点击输入面板属性
				if (Inbox(706, 121, 810, 144)) State(24);
				if (Inbox(705, 146, 813, 166)) State(25);
				if (Inbox(704, 171, 814, 195)) State(26);
				if (Inbox(708, 199, 815, 219)) State(27);
				if (Inbox(706, 223, 812, 245)) State(28);
				if (Inbox(707, 249, 816, 275)) State(29);
				if (Inbox(706, 274, 817, 298)) State(30);
				if (Inbox(705, 304, 818, 321)) State(31);
				
				for (int i = 0; i < 5; i++) {
					//点击了技能设置的加减号
					if (Inbox(803, 410 + 58 * i, 819, 424 + 58 * i)) { entity[1][curplace].Minus(i); State(1); }
					if (Inbox(913, 410 + 58 * i, 928, 424 + 58 * i)) { entity[1][curplace].Add(i); State(1); }
					//点击了技能设置的滑块
					if (Inbox(820, 410 + 58 * i, 830, 424 + 58 * i)) { entity[1][curplace].Click(i, 0); State(1); }
					if (Inbox(830, 410 + 58 * i, 902, 424 + 58 * i)) { entity[1][curplace].Click(i, float(mouse_x - 830) / 72.0); State(1); }
					if (Inbox(902, 410 + 58 * i, 912, 424 + 58 * i)) { entity[1][curplace].Click(i, 1); State(1); }
				}
			}
			//再点出征，进入选怪界面
			if (Inbox(383, 547, 567, 651) || Inbox(460, 495, 496, 551)) { State(32); }
		}
		else if (state == 2) {
			//英雄选择界面
			if (Inbox(328, 58, 387, 86)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "未选择"; State(1); }
			else if (Inbox(325, 114, 369, 151)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "教宗"; State(1); }
			else if (Inbox(379, 117, 468, 155)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "圣光贤者"; State(1); }
			else if (Inbox(485, 114, 566, 154)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "神官骑士"; State(1); }
			else if (Inbox(580, 118, 658, 150)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "圣殿骑士"; State(1); }
			else if (Inbox(317, 203, 399, 238)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "圣龙将军"; State(1); }
			else if (Inbox(420, 207, 482, 235)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "黑骑士"; State(1); }
			else if (Inbox(503, 205, 547, 237)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "剑豪"; State(1); }
			else if (Inbox(570, 206, 612, 238)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "剑宗"; State(1); }
			else if (Inbox(618, 202, 662, 236)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "剑魔"; State(1); }
			else if (Inbox(320, 277, 405, 305)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "传奇法师"; State(1); }
			else if (Inbox(412, 275, 488, 306)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "岩浆法师"; State(1); }
			else if (Inbox(504, 272, 590, 309)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "霜寒法师"; State(1); }
			else if (Inbox(597, 273, 660, 300)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "血法师"; State(1); }
			else if (Inbox(318, 309, 395, 342)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "灵魂贤者"; State(1); }
			else if (Inbox(407, 307, 494, 347)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "幻境先知"; State(1); }
			else if (Inbox(506, 313, 587, 345)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "虚空法师"; State(1); }
			else if (Inbox(595, 313, 654, 343)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "大巫医"; State(1); }
			else if (Inbox(319, 399, 363, 430)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "夜莺"; State(1); }
			else if (Inbox(398, 400, 447, 430)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "夜魇"; State(1); }
			else if (Inbox(479, 394, 553, 432)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "诡术大师"; State(1); }
			else if (Inbox(580, 392, 667, 436)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "幻术刺客"; State(1); }
			else if (Inbox(324, 483, 380, 522)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "圣枪侠"; State(1); }
			else if (Inbox(399, 481, 469, 521)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "烈枪侠"; State(1); }
			else if (Inbox(488, 485, 573, 522)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "传奇猎人"; State(1); }
			else if (Inbox(587, 481, 663, 526)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "巨龙猎人"; State(1); }
			else if (Inbox(316, 568, 379, 605)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "狂战神"; State(1); }
			else if (Inbox(400, 571, 477, 605)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "蛮荒之王"; State(1); }
			else if (Inbox(513, 572, 577, 611)) { inputs[cursuit][curplace].Clear(); inputs[cursuit][curplace].职业 = "火刑官"; State(1); }
			else if (Inbox(446, 623, 534, 665)) { State(1); }
		}
		else if (state >= 3 && state <= 6) {
			//武器，铠甲，饰品1，饰品2输入界面
			if (Inbox(427, 93, 452, 120)) { State(3); }
			else if (Inbox(426, 126, 453, 154)) { State(4); }
			else if (Inbox(427, 160, 454, 185)) { State(5); }
			else if (Inbox(426, 190, 453, 220)) { State(6); }
			else State(1);
		}
		else if (state == 7) {
			//环类型选择界面
			if (Inbox(546, 155, 587, 186)) { th = 1; State(8); }
			else if (Inbox(670, 158, 712, 187)) { th = 2; State(8); }
			else if (Inbox(589, 151, 661, 187)) { th = 3; State(8); }
			else if (Inbox(547, 85, 588, 116)) { th = 4; State(8); }
			else if (Inbox(668, 86, 717, 117)) { th = 5; State(8); }
			else if (Inbox(591, 84, 664, 118)) { th = 6; State(8); }
			else if (Inbox(547, 122, 586, 153)) { th = 7; State(8); }
			else if (Inbox(672, 124, 712, 154)) { th = 8; State(8); }
			else if (Inbox(589, 122, 667, 151)) { th = 9; State(8); }
			else if (Inbox(589, 279, 668, 311)) { th = 10; State(8); }
			else if (Inbox(547, 278, 585, 309)) { th = 11; State(8); }
			else if (Inbox(669, 279, 709, 308)) { th = 12; State(8); }
			else if (Inbox(588, 245, 665, 278)) { th = 16; State(8); }
			else if (Inbox(547, 248, 584, 281)) { th = 17; State(8); }
			else if (Inbox(669, 246, 715, 279)) { th = 18; State(8); }
			else if (Inbox(587, 212, 669, 248)) { th = 13; State(8); }
			else if (Inbox(546, 214, 586, 242)) { th = 14; State(8); }
			else if (Inbox(670, 214, 716, 244)) { th = 15; State(8); }
			else if (Inbox(545, 461, 583, 487)) { th = 19; State(8); }
			else if (Inbox(667, 460, 709, 487)) { th = 20; State(8); }
			else if (Inbox(589, 462, 669, 490)) { th = 21; State(8); }
			else if (Inbox(544, 490, 584, 519)) { th = 22; State(8); }
			else if (Inbox(676, 496, 712, 521)) { th = 23; State(8); }
			else if (Inbox(582, 488, 659, 519)) { th = 24; State(8); }
			else if (Inbox(542, 518, 584, 553)) { th = 25; State(8); }
			else if (Inbox(665, 518, 712, 554)) { th = 26; State(8); }
			else if (Inbox(586, 520, 663, 554)) { th = 27; State(8); }
			else if (Inbox(521, 411, 596, 437)) { th = 28; State(8); }
			else if (Inbox(600, 411, 677, 440)) { th = 29; State(8); }
			else if (Inbox(680, 411, 741, 441)) { th = 30; State(8); }
			else if (Inbox(518, 333, 595, 360)) { th = 31; State(8); }
			else if (Inbox(604, 329, 677, 359)) { th = 32; State(8); }
			else if (Inbox(681, 333, 738, 359)) { th = 33; State(8); }
			else if (Inbox(520, 388, 595, 411)) { th = 34; State(8); }
			else if (Inbox(599, 384, 672, 414)) { th = 35; State(8); }
			else if (Inbox(677, 389, 735, 411)) { th = 36; State(8); }
			else if (Inbox(517, 360, 593, 385)) { th = 37; State(8); }
			else if (Inbox(597, 361, 672, 385)) { th = 38; State(8); }
			else if (Inbox(676, 360, 737, 389)) { th = 39; State(8); }
			else if (Inbox(362, 597, 461, 644)) { th = 0; State(1); }
			else if (Inbox(503, 592, 600, 641)) { th = 0; inputs[cursuit][curplace].环 = 0; inputs[cursuit][curplace].环特效级别 = 5; State(1); }
		}
		else if (state == 8){
			//环特效选择界面
			if (Inbox(439, 75, 555, 119)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 0; State(1); }
			else if (Inbox(434, 118, 557, 165)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 1; State(1); }
			else if (Inbox(425, 165, 569, 209)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 2; State(1); }
			else if (Inbox(422, 209, 560, 253)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 3; State(1); }
			else if (Inbox(424, 255, 564, 304)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 4; State(1); }
			else if (Inbox(420, 299, 570, 345)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 5; State(1); }
			else if (Inbox(414, 341, 568, 392)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 6; State(1); }
			else if (Inbox(419, 388, 572, 438)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 7; State(1); }
			else if (Inbox(416, 433, 573, 479)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 8; State(1); }
			else if (Inbox(420, 479, 571, 531)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 9; State(1); }
			else if (Inbox(417, 523, 569, 573)) { inputs[cursuit][curplace].环 = th; inputs[cursuit][curplace].环特效级别 = 10; State(1); }
			else if (Inbox(432, 593, 529, 643)) { th = 0; State(1); }
		}
		else if (state >= 9 && state <= 11) {
			//魔石类型选择界面，魔石概率输入，魔石特效输入
			if (Inbox(314, 78, 363, 114)) { inputs[cursuit][curplace].魔石 = 1; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(407, 77, 460, 120)) { inputs[cursuit][curplace].魔石 = 2; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 150; State(9); }
			else if (Inbox(408, 120, 463, 164)) { inputs[cursuit][curplace].魔石 = 3; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(315, 127, 372, 160)) { inputs[cursuit][curplace].魔石 = 4; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(313, 201, 371, 245)) { inputs[cursuit][curplace].魔石 = 5; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(404, 201, 463, 251)) { inputs[cursuit][curplace].魔石 = 6; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 150; State(9); }
			else if (Inbox(407, 251, 462, 296)) { inputs[cursuit][curplace].魔石 = 7; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(311, 247, 386, 293)) { inputs[cursuit][curplace].魔石 = 8; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 30; State(9); }
			else if (Inbox(318, 330, 369, 371)) { inputs[cursuit][curplace].魔石 = 9; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(314, 371, 371, 409)) { inputs[cursuit][curplace].魔石 = 10; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(377, 413, 466, 447)) { inputs[cursuit][curplace].魔石 = 11; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(376, 373, 468, 411)) { inputs[cursuit][curplace].魔石 = 12; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(376, 336, 467, 370)) { inputs[cursuit][curplace].魔石 = 13; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(665, 201, 716, 244)) { inputs[cursuit][curplace].魔石 = 14; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(663, 244, 714, 287)) { inputs[cursuit][curplace].魔石 = 15; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(563, 287, 619, 331)) { inputs[cursuit][curplace].魔石 = 16; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(566, 205, 655, 241)) { inputs[cursuit][curplace].魔石 = 17; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 30; State(9); }
			else if (Inbox(566, 246, 655, 289)) { inputs[cursuit][curplace].魔石 = 18; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 30; State(9); }
			else if (Inbox(568, 76, 653, 110)) { inputs[cursuit][curplace].魔石 = 19; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(661, 71, 749, 111)) { inputs[cursuit][curplace].魔石 = 20; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(9); }
			else if (Inbox(565, 122, 649, 165)) { inputs[cursuit][curplace].魔石 = 21; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 30; State(9); }
			else if (Inbox(665, 119, 746, 172)) { inputs[cursuit][curplace].魔石 = 22; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 30; State(9); }
			else if (Inbox(514, 371, 720, 411)) { inputs[cursuit][curplace].魔石参数a = 0; State(10); }
			else if (Inbox(510, 411, 720, 445)) { inputs[cursuit][curplace].魔石参数b = 0; State(11); }
			else if (Inbox(350, 592, 445, 638)) { State(1); }
			else if (Inbox(507, 596, 602, 640)) { inputs[cursuit][curplace].魔石 = 0; inputs[cursuit][curplace].魔石参数a = 15; inputs[cursuit][curplace].魔石参数b = 100; State(1); }
		}
		else if (state >= 12 && state <= 22) {
		    //战利品输入界面
			if (Inbox(446, 624, 535, 663)) { State(1); }
			else if (Inbox(357, 88, 622, 123)) { State(13); }
			else if (Inbox(349, 129, 618, 166)) { State(14); }
			else if (Inbox(352, 175, 623, 214)) { State(15); }
			else if (Inbox(350, 222, 632, 259)) { State(16); }
			else if (Inbox(347, 265, 625, 300)) { State(17); }
			else if (Inbox(348, 309, 619, 350)) { State(18); }
			else if (Inbox(351, 355, 624, 390)) { State(19); }
			else if (Inbox(351, 401, 623, 440)) { State(20); }
			else if (Inbox(348, 445, 625, 478)) { State(21); }
			else if (Inbox(344, 490, 620, 533)) { State(22); }
			else if (Inbox(348, 535, 626, 578)) { inputs[cursuit][curplace].先发 = 1 - inputs[cursuit][curplace].先发;  State(12); }
			else State(12);
		}
		else if (state >= 24 && state <= 31) {
		    //属性输入界面
			if (Inbox(706, 121, 810, 144)) State(24);
			else if (Inbox(705, 146, 813, 166)) State(25);
			else if (Inbox(704, 171, 814, 195)) State(26);
			else if (Inbox(708, 199, 815, 219)) State(27);
			else if (Inbox(706, 223, 812, 245)) State(28);
			else if (Inbox(707, 249, 816, 275)) State(29);
			else if (Inbox(706, 274, 817, 298)) State(30);
			else if (Inbox(705, 304, 818, 321)) State(31);
			else State(1);
		}
		else if (state >= 32 && state <= 43) {
			if (Inbox(577, 609, 692, 644)) { State(1); }
			else if (Inbox(115, 118, 357, 152)) { 遗迹.遗迹战斗 = 1 - 遗迹.遗迹战斗; State(32); }
			else if (Inbox(114, 152, 361, 189)) { State(33); }
			else if (Inbox(117, 193, 354, 231)) { State(34); }
			else if (Inbox(116, 238, 360, 275)) { State(35); }
			else if (Inbox(113, 278, 357, 311)) { State(36); }
			else if (Inbox(114, 316, 356, 350)) { State(37); }
			else if (Inbox(111, 353, 361, 390)) { State(38); }
			else if (Inbox(110, 396, 355, 432)) { State(39); }
			else if (Inbox(111, 435, 353, 472)) { State(40); }
			else if (Inbox(109, 475, 341, 510)) { State(41); }
			else if (Inbox(110, 514, 361, 551)) { State(42); }
			else if (Inbox(101, 553, 362, 592)) { State(43); }
			else if (Inbox(484, 175, 791, 264)) { State(44); }
			else if (Inbox(514, 325, 666, 365)) { TxtFight(); State(32); }
			else State(32);
		}
		else if (state == 44) {
			State(32);
		}
		else if (state == 101) {
			extern int forceExit;
			forceExit = 1;
			cout << "1111111";
			break;
		}
		else if (state == 111) {
			if (Inbox(834, 606, 942, 659)) State(0);
			else State(111);
			break;
		}
		break;
	}
	case WM_KEYDOWN: {
		//for (int i = 0; i < 300; i++)if (KEY_DOWN(i))cout << i << endl;;
		if (KEY_DOWN(VK_ESCAPE)) {
			PostQuitMessage(0);
			break;
		}
		else if (state >= 3 && state <= 6) {
			if (KEY_DOWN(VK_BACK))tstr = tstr.substr(0, max(tstr.length() - 1, 0));
			if (tstr.length() < 8) {
				if (KEY_DOWN(56))tstr += "*";
				for (int i = 65; i <= 90; i++) if (KEY_DOWN(i))tstr += i;
			}
			if (ReadEquipAbbr(tstr) != "") {
				if (state == 3)inputs[cursuit][curplace].武器 = ReadEquipAbbr(tstr);
				if (state == 4)inputs[cursuit][curplace].铠甲 = ReadEquipAbbr(tstr);
				if (state == 5)inputs[cursuit][curplace].饰品1 = ReadEquipAbbr(tstr);
				if (state == 6)inputs[cursuit][curplace].饰品2 = ReadEquipAbbr(tstr);
			}
			if (KEY_DOWN(VK_RETURN))State(state + 1);
			else State(state);
			break;
		}
		else if (state == 10) {
			if (KEY_DOWN(VK_BACK))inputs[cursuit][curplace].魔石参数a = inputs[cursuit][curplace].魔石参数a / 10;
			for (int i = 48; i < 58; i++) {
				if (inputs[cursuit][curplace].魔石参数a <= 9 && KEY_DOWN(i))inputs[cursuit][curplace].魔石参数a = inputs[cursuit][curplace].魔石参数a * 10 + i - 48;
			}
			if (KEY_DOWN(VK_RETURN))State(9);
			else State(state);
			break;
		}
		else if (state == 11) {
			if (KEY_DOWN(VK_BACK))inputs[cursuit][curplace].魔石参数b = inputs[cursuit][curplace].魔石参数b / 10;
			for (int i = 48; i < 58; i++) {
				if (inputs[cursuit][curplace].魔石参数b <= 99 && KEY_DOWN(i))inputs[cursuit][curplace].魔石参数b = inputs[cursuit][curplace].魔石参数b * 10 + i - 48;
			}
			if (KEY_DOWN(VK_RETURN))State(9);
			else State(state);
			break;
		}
		else if (state >= 13 && state <= 22) {
			if (KEY_DOWN(VK_BACK)) {
				tstr = "";
				if (Int(inputs[cursuit][curplace].战利品[state - 13] * 10) % 10 != 0) {
					inputs[cursuit][curplace].战利品[state - 13] = float(int(inputs[cursuit][curplace].战利品[state - 13]));
				}
				else {
					inputs[cursuit][curplace].战利品[state - 13] = float(int(inputs[cursuit][curplace].战利品[state - 13] / 10));
				}
			}
			if (KEY_DOWN(190)) {
				tstr = ".";
			}
			for (int i = 48; i < 58; i++) {
				if (KEY_DOWN(i) && Int(inputs[cursuit][curplace].战利品[state - 13] * 10) % 10 == 0) {
					if (Int(inputs[cursuit][curplace].战利品[state - 13] * 10) % 10 == 0 && tstr == ".") {
						inputs[cursuit][curplace].战利品[state - 13] += 0.1 * (i - 48);
						tstr = "";
					}
					else {
						inputs[cursuit][curplace].战利品[state - 13] = inputs[cursuit][curplace].战利品[state - 13] * 10 + i - 48;
					}
				}
			}
			if (KEY_DOWN(VK_RETURN) && state < 22)State(state + 1);
			else if (KEY_DOWN(VK_RETURN) && state == 22)State(12);
			else State(state);
			break;
		}
		else if (state >= 24 && state <= 31) {
			if (KEY_DOWN(VK_BACK))inputs[cursuit][curplace].面板[state - 24] = inputs[cursuit][curplace].面板[state - 24] / 10;
			for (int i = 48; i < 58; i++) {
				if (inputs[cursuit][curplace].面板[state - 24] <= 9999 && KEY_DOWN(i))inputs[cursuit][curplace].面板[state - 24] = inputs[cursuit][curplace].面板[state - 24] * 10 + i - 48;
			}
			if (KEY_DOWN(VK_RETURN) && state < 31)State(state + 1);
			else if (KEY_DOWN(VK_RETURN) && state == 31)State(1);
			else State(state);
			break;
		}
		else if (state >= 33 && state <= 43) {
			int* p =
				state == 33 ? &遗迹.遗迹状态效果 :
				state == 34 ? &遗迹.遗迹生命 :
				state == 35 ? &遗迹.遗迹护甲 :
				state == 36 ? &遗迹.遗迹抗性 :
				state == 37 ? &遗迹.遗迹物伤 :
				state == 38 ? &遗迹.遗迹魔伤 :
				state == 39 ? &遗迹.遗迹回复效果 :
				state == 40 ? &遗迹.遗迹吸血效果 :
				state == 41 ? &遗迹.遗迹治疗效果 :
				state == 42 ? &遗迹.遗迹命中率 : &遗迹.遗迹暴击率;
			if (KEY_DOWN(189))*p = -*p;
			if (KEY_DOWN(VK_BACK))*p = *p / 10;
			for (int i = 48; i < 58; i++) {
				if (*p <= 9999 && KEY_DOWN(i))*p = *p * 10 + i - 48;
			}
			if (KEY_DOWN(VK_RETURN) && state < 43)State(state + 1);
			else if (KEY_DOWN(VK_RETURN) && state == 43)State(32);
			else State(state);
			break;
		}
		else if (state == 44) {
			if (KEY_DOWN(VK_BACK))tstr = tstr.substr(0, max(tstr.length() - 1, 0));
			if (KEY_DOWN(190)|| KEY_DOWN(192))tstr += ".";
			for (int i = 48; i <= 90; i++) if (KEY_DOWN(i))tstr += i;
			if (ReadMonsterAbbr(tstr) != "") {
				monster = ReadMonsterAbbr(tstr);
				LoadMonster(monster);
			    State(32);
			}
			else State(44);
			break;
		}
		else if (state == 101) {
			state = 0;
			break;
		}
		else if (state == 111) {
			hwndDesk = GetDesktopWindow();
			hdcDesk = GetDC(hwndDesk);
			BitBlt(hdc, 0, -31, 380, 727, hdcDesk, 0, 0, SRCCOPY);
			break;
		}
	}
	case WM_TIMER: {
		if (state == 101) {
			extern int forceExit;
			if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break;}
			timeClock += plank;
			if (timeClock > 0.5) {
				Pub pub;
				pub.Piao(); 
				if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
				pub.ReadModel();
				if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
				if (pub.ReadJob() == 0) {
					if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
					pub.Disemploy();
					if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
				}
				else {
					pub.Star4();
					if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
					if (pub.ReadStar4() == 0) {
						if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
						pub.Disemploy();
						if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
					}
					else {
						pub.Star5();
						if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
						if (pub.ReadStar5() == 0) {
							if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
							pub.Disemploy();
							if (forceExit != 0 || KEY_DOWN(VK_BACK)) { State(0); break; }
						}
						else {
							Click(278, 578, 337, 599); 
							State(0);
						}
					}
				}
				timeClock = 0;
			}
			break;
		}
		
	}
	default: break;
	}
	BitBlt(hdcApp, 0, 0, 995, 727, hdc, 0, 0, SRCCOPY);
	return DefWindowProc(hwnd, uMsg, wparam, lparam);
}

void Change(string& str, string src, string dst) {
	if (src.size() != dst.size())return;
	for (int i = 0; i < str.size() - src.size() + 1; i++) {
		if (str.substr(i, src.size()) == src) {
			for (int j = 0; j < src.size(); j++) {
				str[i + j] = dst[j];
			}
		}
	}
}
bool Divide(string& src, string str, string& dst0, string& dst1) {
	string b = src;
	int p = -1;
	for (int i = 0; i <= b.size() - str.size(); i++) {
		if (b.substr(i, str.size()) == str) {
			dst0 = b.substr(0, i);
			dst1 = b.substr(i + str.size(), b.size() - i - str.size());
			return 1;
		}
	}
	return 0;
}
void Erase(string& src, char ch) {
	for (int i = 0; i < src.size(); i++) {
		for (auto j = src.begin(); j != src.end(); j++) {
			if ((*j) == ch) {
				src.erase(j);
				break;
			}
		}
	}
}
int Find(string& src, char ch1, char ch2 = '@', char ch3 = '@') {
	for (int i = 0; i < src.size(); i++) {
		if (src[i] == ch1 || src[i] == ch2 || src[i] == ch3)return i;
	}
	return -1;
}
int main() {
	try {
		//Distribution();
		//ShellExecute(NULL, _T("open"), _T("msedge.exe"), _T("https://wiki.biligame.com/dxcb2/index.php?title=%E6%AC%A3%E9%85%B1%E7%9A%84%E6%88%98%E5%8A%9B%E5%88%86%E6%9E%901#%E6%9C%9F%E6%9C%9B%E7%9F%A9%E9%98%B5%E8%AE%A1%E7%AE%97%E5%99%A8"), NULL, SW_SHOW);
		srand(time(0));
		MoveWindow(GetConsoleWindow(), -5, 0, 416, 727, 1);
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASS wc;
		wc.lpfnWndProc = WindowProc;
		wc.style = 0;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.lpszMenuName = NULL;
		wc.hInstance = hInstance;
		wc.lpszClassName = TEXT("wiki测试服");
		wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		RegisterClass(&wc);
		hwndApp = CreateWindow(wc.lpszClassName, TEXT("wiki测试服"),
			(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU),
			378, 0, 995, 727,
			NULL, NULL, hInstance, NULL);
		hdcApp = GetDC(hwndApp);
		hwndGame = GetWindowHandleByPID(Getpid(1));
		if (hwndGame != NULL)MoveWindow(hwndGame, 0, 0, 387, 720, 1);
		else {
			hwndGame = GetWindowHandleByPID(Getpid(2));
			for (int i = 0; i < 1000; i++)MoveWindow(hwndGame, 0, 0, 387, i, 1);
		}
		hdcGame = GetDC(hwndGame);
		hwndDesk = GetDesktopWindow();
		hdcDesk = GetDC(hwndDesk);
		HBITMAP hBitmap;
		hdc = CreateCompatibleDC(hdcApp);
		hBitmap = CreateCompatibleBitmap(hdcApp, 995, 727);
		SelectObject(hdc, hBitmap);
		ShowWindow(hwndApp, SW_SHOWNORMAL);
		UpdateWindow(hwndApp);
		SetTimer(hwndApp, 1, 1000 * plank, NULL);
		MSG msg;
		//Piao();
		while (1) {
			if (allowInterval) {
				if (GetMessage(&msg, NULL, 0, 0) == 0)break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	catch (string src) {
		cout << src << endl;
	}
	return 0;
}
