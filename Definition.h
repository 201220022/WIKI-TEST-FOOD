#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#pragma warning(disable:4267)
#pragma warning(disable:4244)
#pragma warning(disable:4305)
#pragma warning(disable:26451)
#ifndef _DEFINITION_H_
#define _DEFINITION_H_
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <cstring>
#include <conio.h>
#include <atlimage.h>
#include <fstream>
#include <tchar.h>
#include <locale>
#include <comdef.h>
#include <atlconv.h>
#include <vector>
#include <map>
#include <sstream>
#include <random>
#include <shlwapi.h>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

#define MAX_ATTRIBUTE 27
#define plank 0.05

#define 力量编号           0
#define 魔力编号           1
#define 技巧编号           2
#define 速度编号           3
#define 体质编号           4
#define 护甲编号           5
#define 抗性编号           6
#define 武威编号           7
#define 物伤编号           8
#define 魔伤编号           9
#define 持续编号           10
#define 物理单吸编号       11
#define 物理群吸编号       12
#define 魔法单吸编号       13
#define 魔法群吸编号       14
#define 命中率编号         15
#define 闪避率编号         16
#define 暴击率编号         17
#define 异常附加率编号     18
#define 卸负编号           19
#define 无视护甲编号       20
#define 无视抗性编号       21
#define 物伤格挡编号       22
#define 魔伤格挡编号       23
#define 回复效果编号       24
#define 吸血效果编号       25
#define 治疗效果编号       26

#define 力量           Attribute(力量编号)
#define 魔力           Attribute(魔力编号)
#define 技巧           Attribute(技巧编号)
#define 速度           Attribute(速度编号)
#define 体质           Attribute(体质编号)
#define 护甲           Attribute(护甲编号)
#define 抗性           Attribute(抗性编号)
#define 武威           Attribute(武威编号)
#define 物伤           Attribute(物伤编号)
#define 魔伤           Attribute(魔伤编号)
#define 持续           Attribute(持续编号)
#define 物理单吸       Attribute(物理单吸编号)
#define 物理群吸       Attribute(物理群吸编号)
#define 魔法单吸       Attribute(魔法单吸编号)
#define 魔法群吸       Attribute(魔法群吸编号)
#define 命中率         Attribute(命中率编号)
#define 闪避率         Attribute(闪避率编号)
#define 暴击率         Attribute(暴击率编号)
#define 异常附加率     Attribute(异常附加率编号)
#define 卸负           Attribute(卸负编号)
#define 无视护甲       Attribute(无视护甲编号)
#define 无视抗性       Attribute(无视抗性编号)
#define 物伤格挡       Attribute(物伤格挡编号)
#define 魔伤格挡       Attribute(魔伤格挡编号)
#define 回复效果       Attribute(回复效果编号)
#define 吸血效果       Attribute(吸血效果编号)
#define 治疗效果       Attribute(治疗效果编号)
#define 增幅力量       增幅[力量编号]
#define 增幅魔力       增幅[魔力编号]
#define 增幅技巧       增幅[技巧编号]
#define 增幅速度       增幅[速度编号]
#define 增幅体质       增幅[体质编号]
#define 增幅护甲       增幅[护甲编号]
#define 增幅抗性       增幅[抗性编号]
#define 增幅武威       增幅[武威编号]
#define 增幅物伤       增幅[物伤编号]
#define 增幅魔伤       增幅[魔伤编号]
#define 增幅持续       增幅[持续编号]
#define 增幅物理单吸   增幅[物理单吸编号]
#define 增幅物理群吸   增幅[物理群吸编号]
#define 增幅魔法单吸   增幅[魔法单吸编号]
#define 增幅魔法群吸   增幅[魔法群吸编号]
#define 增幅命中率     增幅[命中率编号]
#define 增幅闪避率     增幅[闪避率编号]
#define 增幅暴击率     增幅[暴击率编号]
#define 增幅异常附加率 增幅[异常附加率编号]
#define 增幅卸负       增幅[卸负编号]
#define 增幅无视护甲   增幅[无视护甲编号]
#define 增幅无视抗性   增幅[无视抗性编号]
#define 增幅物伤格挡   增幅[物伤格挡编号]
#define 增幅魔伤格挡   增幅[魔伤格挡编号]
#define 增幅回复效果   增幅[回复效果编号]
#define 增幅吸血效果   增幅[吸血效果编号]
#define 增幅治疗效果   增幅[治疗效果编号]
#define 面板力量       面板[力量编号]
#define 面板魔力       面板[魔力编号]
#define 面板技巧       面板[技巧编号]
#define 面板速度       面板[速度编号]
#define 面板体质       面板[体质编号]
#define 面板护甲       面板[护甲编号]
#define 面板抗性       面板[抗性编号]
#define 面板武威       面板[武威编号]
#define 面板物伤       面板[物伤编号]
#define 面板魔伤       面板[魔伤编号]
#define 面板持续       面板[持续编号]
#define 面板物理单吸   面板[物理单吸编号]
#define 面板物理群吸   面板[物理群吸编号]
#define 面板魔法单吸   面板[魔法单吸编号]
#define 面板魔法群吸   面板[魔法群吸编号]
#define 面板命中率     面板[命中率编号]
#define 面板闪避率     面板[闪避率编号]
#define 面板暴击率     面板[暴击率编号]
#define 面板异常附加率 面板[异常附加率编号]
#define 面板卸负       面板[卸负编号]
#define 面板无视护甲   面板[无视护甲编号]
#define 面板无视抗性   面板[无视抗性编号]
#define 面板物伤格挡   面板[物伤格挡编号]
#define 面板魔伤格挡   面板[魔伤格挡编号]
#define 面板回复效果   面板[回复效果编号]
#define 面板吸血效果   面板[吸血效果编号]
#define 面板治疗效果   面板[治疗效果编号]

//状态类型
#define 力量buff  0
#define 魔力buff  1
#define 技巧buff  2
#define 速度buff  3
#define 体质buff  4
#define 护甲buff  5
#define 抗性buff  6
#define hot       7
#define dot       8
#define 反伤      9
#define 眩晕      10
#define 物理承伤  11
#define 魔法承伤  12

//Skill::技能类型  Entity::循环模式  Entity::攻击偏好
#define 生命少于百分比时施放 0
#define 生命足够多时保持嘲讽 1
#define 经常或始终保持反击   2
#define 友方生命少于百分比时 3
#define 至少有多个敌人时施放 4
#define 可设为始终轮流或循环 5
#define 默认施放 0
#define 轮流施放 1
#define 随机施放 2
#define 剩余生命最少 0
#define 剩余生命最多 1
#define 总生命值最多 2
#define 随意攻击     3
#define 护甲最少     4
#define 护甲最多     5
#define 抗性最少     6
#define 抗性最多     7

#define 未选择 0
#define 无限制伤害空环     1
#define 无限制命中空环     2
#define 无限制持续空环     3
#define 多人伤害空环       4
#define 多人命中空环       5
#define 多人持续空环       6
#define 孤儿伤害空环       7
#define 孤儿命中空环       8
#define 孤儿持续空环       9
#define 无限制治疗水环     10
#define 无限制异常水环     11
#define 无限制闪避水环     12
#define 多人治疗水环       13
#define 多人异常水环       14
#define 多人闪避水环       15
#define 孤儿治疗水环       16
#define 孤儿异常水环       17
#define 孤儿闪避水环       18
#define 承伤伤害火环       19
#define 承伤命中火环       20
#define 承伤持续火环       21
#define 减疗伤害火环       22
#define 减疗命中火环       23
#define 减疗持续火环       24
#define 自杀伤害火环       25
#define 自杀命中火环       26
#define 自杀持续火环       27
#define 无限制物理格挡土环 28
#define 无限制魔法格挡土环 29
#define 无限制双格挡土环   30
#define 多人物理格挡土环   31
#define 多人魔法格挡土环   32
#define 多人双格挡土环     33
#define 满生命物理格挡土环 34
#define 满生命魔法格挡土环 35
#define 满生命双格挡土环   36
#define 孤儿物理格挡土环   37
#define 孤儿魔法格挡土环   38
#define 孤儿双格挡土环     39

#define 命中暴君 1
#define 无视暴君 2
#define 增幅暴君 3
#define 连击暴君 4
#define 命中古精灵 5
#define 无视古精灵 6
#define 增幅古精灵 7
#define 魔法盾古精灵 8
#define 命中乌鸦 9
#define 异常乌鸦 10
#define 回复巧手乌鸦 11
#define 物攻巧手乌鸦 12
#define 魔攻巧手乌鸦 13
#define 命中猎神 14
#define 先发猎神 15
#define 速攻猎神 16
#define 物理矫捷猎神 17
#define 魔法矫捷猎神 18
#define 物理守护巨龙 19
#define 魔法守护巨龙 20
#define 物理强健巨龙 21
#define 魔法强健巨龙 22

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define Inbox(l, u, r, d) InBox(mouse_x,mouse_y,l,u,r,d)
#define Pen(name,r,g,b) HPEN name = CreatePen(PS_SOLID, 1, RGB(r,g,b));
#define Brush(name,r,g,b) HBRUSH name = CreateSolidBrush(RGB(r,g,b));
#define Font(name,size,broad,type) HFONT name = CreateFont(size, 0, 0, 0, broad, 0, 0, 0, 0, 0, 0, 0, 0, type);
#define TextSelect(hdc, hfont, r, g, b) extern HFONT hfont;	SelectObject(hdc, hfont); SetBkMode(hdc, TRANSPARENT); SetTextColor(hdc, RGB(r,g,b));
#define PBSelect(hdc, hpen, hbrush) extern HPEN hpen; extern HBRUSH hbrush;SelectObject(hdc, hpen); SelectObject(hdc, hbrush); 
#define For(a,b) for (auto b = a.begin(); b != a.end(); b++) 
#endif
