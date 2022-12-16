//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
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
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

#define MAX_GROUP 7
#define plank 0.05

#define 力量           Attribute(0)
#define 魔力           Attribute(1)
#define 技巧           Attribute(2)
#define 速度           Attribute(3)
#define 体质           Attribute(4)
#define 护甲           Attribute(5)
#define 抗性           Attribute(6)
#define 武威           Attribute(7)
#define 物伤           Attribute(8)
#define 魔伤           Attribute(9)
#define 持续           Attribute(10)
#define 物理单吸       Attribute(11)
#define 物理群吸       Attribute(12)
#define 魔法单吸       Attribute(13)
#define 魔法群吸       Attribute(14)
#define 命中率         Attribute(15)
#define 闪避率         Attribute(16)
#define 暴击率         Attribute(17)
#define 异常附加率     Attribute(18)
#define 卸负           Attribute(19)
#define 无视护甲       Attribute(20)
#define 无视抗性       Attribute(21)
#define 物伤格挡       Attribute(22)
#define 魔伤格挡       Attribute(23)
#define 回复效果       Attribute(24)
#define 吸血效果       Attribute(25)
#define 治疗效果       Attribute(26)
#define 挨打效果       Attribute(27)

#define 增幅力量       增幅[0]
#define 增幅魔力       增幅[1]
#define 增幅技巧       增幅[2]
#define 增幅速度       增幅[3]
#define 增幅体质       增幅[4]
#define 增幅护甲       增幅[5]
#define 增幅抗性       增幅[6]
#define 增幅武威       增幅[7]
#define 增幅物伤       增幅[8]
#define 增幅魔伤       增幅[9]
#define 增幅持续       增幅[10]
#define 增幅物理单吸   增幅[11]
#define 增幅物理群吸   增幅[12]
#define 增幅魔法单吸   增幅[13]
#define 增幅魔法群吸   增幅[14]
#define 增幅命中率     增幅[15]
#define 增幅闪避率     增幅[16]
#define 增幅暴击率     增幅[17]
#define 增幅异常附加率 增幅[18]
#define 增幅卸负       增幅[19]
#define 增幅无视护甲   增幅[20]
#define 增幅无视抗性   增幅[21]
#define 增幅物伤格挡   增幅[22]
#define 增幅魔伤格挡   增幅[23]
#define 增幅回复效果   增幅[24]
#define 增幅吸血效果   增幅[25]
#define 增幅治疗效果   增幅[26]
#define 增幅挨打效果   增幅[27]

#define 面板力量       面板[0]
#define 面板魔力       面板[1]
#define 面板技巧       面板[2]
#define 面板速度       面板[3]
#define 面板体质       面板[4]
#define 面板护甲       面板[5]
#define 面板抗性       面板[6]
#define 面板武威       面板[7]
#define 面板物伤       面板[8]
#define 面板魔伤       面板[9]
#define 面板持续       面板[10]
#define 面板物理单吸   面板[11]
#define 面板物理群吸   面板[12]
#define 面板魔法单吸   面板[13]
#define 面板魔法群吸   面板[14]
#define 面板命中率     面板[15]
#define 面板闪避率     面板[16]
#define 面板暴击率     面板[17]
#define 面板异常附加率 面板[18]
#define 面板卸负       面板[19]
#define 面板无视护甲   面板[20]
#define 面板无视抗性   面板[21]
#define 面板物伤格挡   面板[22]
#define 面板魔伤格挡   面板[23]
#define 面板回复效果   面板[24]
#define 面板吸血效果   面板[25]
#define 面板治疗效果   面板[26]
#define 面板挨打效果   面板[27]

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

#define Inbox(l, u, r, d) InBox(mouse_x,mouse_y,l,u,r,d)
#define Pen(name,r,g,b) HPEN name = CreatePen(PS_SOLID, 1, RGB(r,g,b));
#define Brush(name,r,g,b) HBRUSH name = CreateSolidBrush(RGB(r,g,b));
#define Font(name,size,broad,type) HFONT name = CreateFont(size, 0, 0, 0, broad, 0, 0, 0, 0, 0, 0, 0, 0, type);
#define TextSelect(hdc, hfont, r, g, b) extern HFONT hfont;	SelectObject(hdc, hfont); SetBkMode(hdc, TRANSPARENT); SetTextColor(hdc, RGB(r,g,b));
#define PBSelect(hdc, hpen, hbrush) extern HPEN hpen; extern HBRUSH hbrush;SelectObject(hdc, hpen); SelectObject(hdc, hbrush); 
#define For(b,c) for (auto c = b.begin(); c != b.end(); c++) 
#endif
