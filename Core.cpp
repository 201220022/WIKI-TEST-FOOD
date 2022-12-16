#include "Definition.h"
#include "Core.h"
#include "Tools.h"
using namespace std;
extern Entity entity[2][MAX_GROUP];
extern int order[7];
extern bool openmouse;
extern int cursuit, curplace;
extern RelicInfo 遗迹;
extern InputInfo inputs[5][4];
Status mem("");

void InputInfo::Clear() {
	职业 = "未选择";
	武器 = "未选择";
	铠甲 = "未选择";
	饰品1 = "未选择";
	饰品2 = "未选择";
	魔石 = 0;
	魔石参数a = 0;
	魔石参数b = 0;
	环 = 0;
	环特效级别 = 0;
	for (int i = 0; i < 8; i++)面板[i] = 0;
	for (int i = 0; i < 10; i++)战利品[i] = 0;
	先发 = 0;
	for (int i = 0; i < 4; i++)技能设置[i] = 0;
	攻击偏好 = 0;
}

Status::Status(string name) {
	名称 = name;
	类型 = -1;
}
Status::Status(Skill* skill, Entity* src) {
	int value = skill->状态常数;
	for (int i = 0; i < 8; i++)value += Int(skill->状态系数[i] * src->Attribute(i));
	value += Int(skill->状态系数[8] * src->当前生命值);
	value += Int(skill->状态系数[9] * (src->体质 * 10 - src->当前生命值));
	if (skill->状态类型 == dot)value = Int(value * src->持续);
	名称 = skill->状态名称;
	特效名称 = skill->名称;
	类型 = skill->状态类型;
	剩余时间 = skill->持续时间;
	每层数值 = value;
	当前层数 = 0;
	最大层数 = skill->最大层数;
	允许状态效果 = src->阵营;
	附加者 = src;
}
Status::Status(EquipEffect content, Entity* src) {
	int value = content.常数;
	for (int i = 0; i < 8; i++)value += Int(content.系数[i] * src->Attribute(i));
	value += Int(content.系数[8] * src->当前生命值);
	value += Int(content.系数[9] * (src->体质 * 10 - src->当前生命值));
	名称 = content.状态名称;
	特效名称 = content.名称;
	类型 = content.状态类型;
	剩余时间 = content.持续时间;
	每层数值 = value;
	当前层数 = 0;
	最大层数 = content.最大层数;
	允许状态效果 = src->阵营;
	附加者 = src;
}
int Status::Value() {
	//给出状态数值
	int ret =  每层数值 * 当前层数 * (1 + 允许状态效果 * 遗迹.遗迹战斗 * 遗迹.遗迹状态效果);
	if (类型 == dot)ret *= 附加者->持续;
	return ret;
}

bool Equip::Load(string src) {
	ifstream file("JSON/装备数据.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	for (int i = 0; i < dom["装备数据"].Size(); i++) {
		rapidjson::Value& data = dom["装备数据"][i];
		if (src == data["名称"].GetString()) {
			名称 = data["名称"].GetString();
			属性[0] = data.HasMember("命中") ? data["命中"].GetFloat() : 0;
			属性[1] = data.HasMember("闪避") ? data["闪避"].GetFloat() : 0;
			属性[2] = data.HasMember("暴击") ? data["暴击"].GetFloat() : 0;
			属性[3] = data.HasMember("回复") ? data["回复"].GetFloat() : 0;
			属性[4] = data.HasMember("异常") ? data["异常"].GetFloat() : 0;
			属性[5] = data.HasMember("吸血") ? data["吸血"].GetFloat() : 0;
			属性[6] = data.HasMember("卸负") ? data["卸负"].GetInt() : 0;
			属性[7] = data.HasMember("无视护甲") ? data["无视护甲"].GetInt() : 0;
			属性[8] = data.HasMember("无视抗性") ? data["无视抗性"].GetInt() : 0;
			属性[9] = data.HasMember("治疗抑制") ? data["治疗抑制"].GetFloat() : 0;
			if (data.HasMember("免疫")) {
				for (int j = 0; j < data["免疫"].Size(); j++) {
					免疫列表.push_back(data["免疫"][j].GetString());
				}
			}
			if (data.HasMember("特效")) {
				for (int j = 0; j < data["特效"].Size(); j++) {
					EquipEffect tempEffect;
					tempEffect.类型 = data["特效"][j].HasMember("类型") ? data["特效"][j]["类型"].GetString() : "";
					tempEffect.名称 = data["特效"][j].HasMember("名称") ? data["特效"][j]["名称"].GetString() : "";
					tempEffect.触发 = data["特效"][j].HasMember("触发") ? data["特效"][j]["触发"].GetString() : "";
					tempEffect.概率 = data["特效"][j].HasMember("概率") ? data["特效"][j]["概率"].GetFloat() : 0;
					tempEffect.对象 = data["特效"][j].HasMember("对象") ? data["特效"][j]["对象"].GetString() : "对自身";
					tempEffect.常数 = data["特效"][j].HasMember("常数") ? data["特效"][j]["常数"].GetInt() : 0;
					tempEffect.系数[0] = data["特效"][j].HasMember("力量系数") ? data["特效"][j]["力量系数"].GetFloat() : 0;
					tempEffect.系数[1] = data["特效"][j].HasMember("魔力系数") ? data["特效"][j]["魔力系数"].GetFloat() : 0;
					tempEffect.系数[2] = data["特效"][j].HasMember("技巧系数") ? data["特效"][j]["技巧系数"].GetFloat() : 0;
					tempEffect.系数[3] = data["特效"][j].HasMember("速度系数") ? data["特效"][j]["速读系数"].GetFloat() : 0;
					tempEffect.系数[4] = data["特效"][j].HasMember("体质系数") ? data["特效"][j]["体质系数"].GetFloat() : 0;
					tempEffect.系数[5] = data["特效"][j].HasMember("护甲系数") ? data["特效"][j]["护甲系数"].GetFloat() : 0;
					tempEffect.系数[6] = data["特效"][j].HasMember("抗性系数") ? data["特效"][j]["抗性系数"].GetFloat() : 0;
					tempEffect.系数[7] = data["特效"][j].HasMember("武威系数") ? data["特效"][j]["武威系数"].GetFloat() : 0;
					tempEffect.系数[8] = data["特效"][j].HasMember("当前生命系数") ? data["特效"][j]["当前生命系数"].GetFloat() : 0;
					tempEffect.系数[9] = data["特效"][j].HasMember("已损生命系数") ? data["特效"][j]["已损生命系数"].GetFloat() : 0;
					tempEffect.状态名称 = data["特效"][j].HasMember("状态名称") ? data["特效"][j]["状态名称"].GetString() : "";
					tempEffect.持续时间 = data["特效"][j].HasMember("持续时间") ? data["特效"][j]["持续时间"].GetFloat() : -1;
					tempEffect.最大层数 = data["特效"][j].HasMember("最大层数") ? data["特效"][j]["最大层数"].GetFloat() : 1;
					tempEffect.状态类型 = !data["特效"][j].HasMember("状态类型") ? -1 :
						data["特效"][j]["状态类型"].GetString() == "力量buff" ? 力量buff :
						data["特效"][j]["状态类型"].GetString() == "魔力buff" ? 魔力buff :
						data["特效"][j]["状态类型"].GetString() == "技巧buff" ? 技巧buff :
						data["特效"][j]["状态类型"].GetString() == "速度buff" ? 速度buff :
						data["特效"][j]["状态类型"].GetString() == "体质buff" ? 体质buff :
						data["特效"][j]["状态类型"].GetString() == "护甲buff" ? 护甲buff :
						data["特效"][j]["状态类型"].GetString() == "抗性buff" ? 抗性buff :
						data["特效"][j]["状态类型"].GetString() == "dot" ? dot :
						data["特效"][j]["状态类型"].GetString() == "hot" ? hot :
						data["特效"][j]["状态类型"].GetString() == "反伤" ? 反伤 :
						data["特效"][j]["状态类型"].GetString() == "眩晕" ? 眩晕 :
						data["特效"][j]["状态类型"].GetString() == "物理承伤" ? 物理承伤 :
						data["特效"][j]["状态类型"].GetString() == "魔法承伤" ? 魔法承伤 : -1;
					if (data["特效"][j].HasMember("增幅系数")) {
						for (int k = 0; k < data["特效"][j]["增幅系数"].Size(); k++) {
							float a = data["特效"][j]["增幅系数"][k]["系数"].GetFloat();
							int b =
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "力量" ? 0 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "魔力" ? 1 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "技巧" ? 2 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "速度" ? 3 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "体质" ? 4 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "护甲" ? 5 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "抗性" ? 6 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "武威" ? 7 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "当前生命" ? 8 :
								data["特效"][j]["增幅系数"][k]["源属性"].GetString() == "已损生命" ? 9 : -1;
							int c =
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "力量" ? 0 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "魔力" ? 1 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "技巧" ? 2 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "速度" ? 3 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "体质" ? 4 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "护甲" ? 5 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "抗性" ? 6 :
								data["特效"][j]["增幅系数"][k]["目的属性"].GetString() == "武威" ? 7 : -1;
							pair<int, int> d;
							pair<float, pair<int, int>> e(a, d);
							tempEffect.增幅系数.push_back(e);
						}
					}
					装备特效.push_back(tempEffect);
				}
			}
			return 1;
		}
	}
	return "未选择";
	return 0;
}
bool Equip::Affect(Entity* owner, string condition) {
	//触发装备特效。若触发，返回1.
	bool ret = 0;
	for (vector<EquipEffect>::iterator i = 装备特效.begin(); i != 装备特效.end(); i++) {
		if ((*i).触发 == condition && Rand((*i).概率)) {
			ret = 1;
			if ((*i).类型 == "状态") {
				if ((*i).对象 == "对自身" || (*i).对象 == "对我方全体" || (*i).对象 == "对我方单体" && owner->我方目标 == owner->站位) {
					Status status0((*i).状态名称);
					owner->Attached(status0);
				}
				Status status((*i), owner);
				owner->Attach((*i).对象, status);
			}
			else if ((*i).类型 == "增幅") {
				For((*i).增幅系数, j) {
					if ((*j).second.first < 8) {
						owner->增幅[(*j).second.second] += (*j).first * owner->Attribute((*j).second.first);
					}
					else if ((*j).second.first == 8) {
						owner->增幅[(*j).second.second] += (*j).first * owner->当前生命值;
					}
					else if ((*j).second.first == 9) {
						owner->增幅[(*j).second.second] += (*j).first * (owner->体质 * 10 - owner->当前生命值);
					}
				}
			}
			else if ((*i).类型 == "连击") {
				owner->冷却时间增加 = -4;
			}
			else if ((*i).类型 == "回复") {
				int value = (*i).常数;
				for (int j = 0; j < 8; j++)value += Int((*i).系数[j] * owner->Attribute(j));
				value += Int((*i).系数[8] * owner->当前生命值);
				value += Int((*i).系数[9] * (owner->体质 * 10 - owner->当前生命值));
				if ((*i).对象 == "对自身") {
					owner->Healed(owner->回复效果 * value);
				}
				if ((*i).对象 == "对我方单体") {
					entity[owner->阵营][owner->我方目标].Healed(owner->回复效果 * value);
				}
				else if ((*i).对象 == "对我方全体") {
					for (int i = 0; i < MAX_GROUP; i++) {
						if (entity[owner->阵营][i].存活 != 0)entity[owner->阵营][i].Healed(owner->回复效果 * value);
					}
				}
			}
			else if ((*i).类型 == "真伤") {
				int value = (*i).常数;
				for (int j = 0; j < 8; j++)value += Int((*i).系数[j] * owner->体质);
				value += Int((*i).系数[8] * owner->当前生命值);
				value += Int((*i).系数[9] * (owner->体质 * 10 - owner->当前生命值));
				if ((*i).对象 == "对敌方单体") {
					entity[1 - owner->阵营][owner->敌方目标].Attacked(value);
				}
				else if ((*i).对象 == "对敌方全体") {
					for (int i = 0; i < MAX_GROUP; i++) {
						if (entity[1 - owner->阵营][i].存活 != 0)entity[1 - owner->阵营][i].Attacked(value);
					}
				}
			}
		}
	}
	return ret;
}

void Ring::Init(int type, int level) {
	类型 = type;
	特效数值 = level;
}
float Ring::Value(int level) {
	//返回环的特效的数值
	switch (类型) {
	case 0:return 0;
	case 1:return (1.4 + 0.12 * level) * 5;
	case 2:return (1.4 + 0.12 * level) * 5;
	case 3:return (1.4 + 0.12 * level) * 5;
	case 4:return (1.4 + 0.12 * level) * 7.5;
	case 5:return (1.4 + 0.12 * level) * 7.5;
	case 6:return (1.4 + 0.12 * level) * 7.5;
	case 7:return (1.4 + 0.12 * level) * 5;
	case 8:return (1.4 + 0.12 * level) * 5;
	case 9:return (1.4 + 0.12 * level) * 5;
	case 10:return (1.4 + 0.12 * level) * 5;
	case 11:return (1.4 + 0.12 * level) * 5;
	case 12:return (1.4 + 0.12 * level) * 5;
	case 13:return (1.4 + 0.12 * level) * 7.5;
	case 14:return (1.4 + 0.12 * level) * 7.5;
	case 15:return (1.4 + 0.12 * level) * 7.5;
	case 16:return (1.4 + 0.12 * level) * 3;
	case 17:return (1.4 + 0.12 * level) * 3;
	case 18:return (1.4 + 0.12 * level) * 3;
	case 19:return (1.4 + 0.12 * level) * 10;
	case 20:return (1.4 + 0.12 * level) * 7.5;
	case 21:return (1.4 + 0.12 * level) * 7.5;
	case 22:return (1.4 + 0.12 * level) * 7.5;
	case 23:return (1.4 + 0.12 * level) * 7.5;
	case 24:return (1.4 + 0.12 * level) * 7.5;
	case 25:return (1.4 + 0.12 * level) * 7.5;
	case 26:return (1.4 + 0.12 * level) * 10;
	case 27:return (1.4 + 0.12 * level) * 10;
	case 28:return (1.4 + 0.12 * level) * 500;
	case 29:return (1.4 + 0.12 * level) * 500;
	case 30:return (1.4 + 0.12 * level) * 250;
	case 31:return (1.4 + 0.12 * level) * 750;
	case 32:return (1.4 + 0.12 * level) * 750;
	case 33:return (1.4 + 0.12 * level) * 375;
	case 34:return (1.4 + 0.12 * level) * 750;
	case 35:return (1.4 + 0.12 * level) * 750;
	case 36:return (1.4 + 0.12 * level) * 375;
	case 37:return (1.4 + 0.12 * level) * 375;
	case 38:return (1.4 + 0.12 * level) * 375;
	case 39:return (1.4 + 0.12 * level) * 187.5;
	}
	return 0;
}
string Ring::Discription() {
	switch (类型) {
	case 未选择:return "未选择";
	case 无限制伤害空环:return FloatTran(Value(特效数值)) + "无限制伤害空";
	case 无限制命中空环:return FloatTran(Value(特效数值)) + "无限制命中空";
	case 无限制持续空环:return FloatTran(Value(特效数值)) + "无限制持续空";
	case 多人伤害空环:return FloatTran(Value(特效数值)) + "多人伤害空";
	case 多人命中空环:return FloatTran(Value(特效数值)) + "多人命中空";
	case 多人持续空环:return FloatTran(Value(特效数值)) + "多人持续空";
	case 孤儿伤害空环:return FloatTran(Value(特效数值)) + "孤儿伤害空";
	case 孤儿命中空环:return FloatTran(Value(特效数值)) + "孤儿命中空";
	case 孤儿持续空环:return FloatTran(Value(特效数值)) + "孤儿持续空";
	case 无限制治疗水环:return FloatTran(Value(特效数值)) + "无限制治疗水";
	case 无限制异常水环:return FloatTran(Value(特效数值)) + "无限制异常水";
	case 无限制闪避水环:return FloatTran(Value(特效数值)) + "无限制闪避水";
	case 多人治疗水环:return FloatTran(Value(特效数值)) + "多人治疗水";
	case 多人异常水环:return FloatTran(Value(特效数值)) + "多人异常水";
	case 多人闪避水环:return FloatTran(Value(特效数值)) + "多人闪避水";
	case 孤儿治疗水环:return FloatTran(Value(特效数值)) + "孤儿治疗水";
	case 孤儿异常水环:return FloatTran(Value(特效数值)) + "孤儿异常水";
	case 孤儿闪避水环:return FloatTran(Value(特效数值)) + "孤儿闪避水";
	case 承伤伤害火环:return FloatTran(Value(特效数值)) + "承伤伤害火";
	case 承伤命中火环:return FloatTran(Value(特效数值)) + "承伤命中火";
	case 承伤持续火环:return FloatTran(Value(特效数值)) + "承伤持续火";
	case 减疗伤害火环:return FloatTran(Value(特效数值)) + "减疗伤害火";
	case 减疗命中火环:return FloatTran(Value(特效数值)) + "减疗命中火";
	case 减疗持续火环:return FloatTran(Value(特效数值)) + "减疗持续火";
	case 自杀伤害火环:return FloatTran(Value(特效数值)) + "自杀伤害火";
	case 自杀命中火环:return FloatTran(Value(特效数值)) + "自杀命中火";
	case 自杀持续火环:return FloatTran(Value(特效数值)) + "自杀持续火";
	case 无限制物理格挡土环:return FloatTran(Value(特效数值)) + "无限制物格挡";
	case 无限制魔法格挡土环:return FloatTran(Value(特效数值)) + "无限制魔格挡";
	case 无限制双格挡土环:return FloatTran(Value(特效数值)) + "无限制双格挡";
	case 多人物理格挡土环:return FloatTran(Value(特效数值)) + "多人物格挡";
	case 多人魔法格挡土环:return FloatTran(Value(特效数值)) + "多人魔格挡";
	case 多人双格挡土环: return FloatTran(Value(特效数值)) + "多人双格挡";
	case 满生命物理格挡土环:return FloatTran(Value(特效数值)) + "满血物格挡";
	case 满生命魔法格挡土环:return FloatTran(Value(特效数值)) + "满血魔格挡";
	case 满生命双格挡土环:return FloatTran(Value(特效数值)) + "满血双格挡";
	case 孤儿物理格挡土环:return FloatTran(Value(特效数值)) + "孤儿物格挡";
	case 孤儿魔法格挡土环:return FloatTran(Value(特效数值)) + "孤儿魔格挡";
	case 孤儿双格挡土环:return FloatTran(Value(特效数值)) + "孤儿双格挡";
	}
	return "未选择";
}
void Ring::Affect(Entity* owner, string condition) {

}

void MagicStone::Init(int type, int x, int y) {
	类型 = type;
	概率 = x;
	数值 = y;
}
string MagicStone::ShortDiscription() {
	switch (类型) {
	case 未选择: return "未选择";
	case 命中暴君: return "命中暴君";
	case 无视暴君: return "无视暴君";
	case 增幅暴君: return "增幅暴君";
	case 连击暴君: return "连击暴君";
	case 命中古精灵: return "命中古精灵";
	case 无视古精灵: return "无视古精灵";
	case 增幅古精灵: return "增幅古精灵";
	case 魔法盾古精灵: return "魔法盾古精灵";
	case 命中乌鸦: return "命中乌鸦";
	case 异常乌鸦: return "异常乌鸦";
	case 回复巧手乌鸦: return "回复巧手乌鸦";
	case 物攻巧手乌鸦: return "物攻巧手乌鸦";
	case 魔攻巧手乌鸦: return "魔攻巧手乌鸦";
	case 命中猎神: return "命中猎神";
	case 先发猎神: return "先发猎神";
	case 速攻猎神: return "速攻猎神";
	case 物理矫捷猎神: return "物理矫捷猎神";
	case 魔法矫捷猎神: return "魔法矫捷猎神";
	case 物理守护巨龙: return "物理守护巨龙";
	case 魔法守护巨龙: return "魔法守护巨龙";
	case 物理强健巨龙: return "物理强健巨龙";
	case 魔法强健巨龙: return "魔法强健巨龙";
	}
	return "未选择";
}
string MagicStone::Discription() {
	switch (类型) {
	case 未选择: return "未选择";
	case 命中暴君: return "命中率 + " + FloatTran(概率) + "%";
    case 无视暴君: return "无视护甲 + " + FloatTran(数值);
    case 增幅暴君: return "能量增幅 : 在发动物理攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的力量";
    case 连击暴君: return "狂暴 : 在发动物理攻击时 , 15%概率立即执行下次行动(可连续出发)";
    case 命中古精灵: return "命中率 + " + FloatTran(概率) + "%";
    case 无视古精灵: return "无视抗性 + " + FloatTran(数值);
    case 增幅古精灵: return "魔能增幅 : 在发动魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的魔力";
    case 魔法盾古精灵: return "魔法盾 : 在受到魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅将" + FloatTran(数值) + "%的魔力附加为抗性";
    case 命中乌鸦: return "命中率 + " + FloatTran(概率) + "%";
    case 异常乌鸦: return "异常附加率 + " + FloatTran(概率) + "%";
    case 回复巧手乌鸦: return "巧手 : 在使用回复技能的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的技巧";
    case 物攻巧手乌鸦: return "巧手 : 在发动物理攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的技巧";
    case 魔攻巧手乌鸦: return "巧手 : 在发动魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的技巧";
    case 命中猎神: return "命中率 + " + FloatTran(概率) + "%";
    case 速攻猎神: return "速攻 : 在发动物理攻击的瞬间 , " + FloatTran(概率) + "%的概率将" + FloatTran(数值) + "%的速度附加为力量";
    case 先发猎神: return "先发制人";
    case 物理矫捷猎神: return "矫捷 : 在受到物理攻击的瞬间 , " + FloatTran(概率) + "%的概率将" + FloatTran(数值) + "%的速度附加为护甲";
    case 魔法矫捷猎神: return "矫捷 : 在受到魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率将" + FloatTran(数值) + "%的速度附加为抗性";
    case 物理守护巨龙: return "守护 : 在受到物理攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的护甲";
    case 魔法守护巨龙: return "守护 : 在受到魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率增幅" + FloatTran(数值) + "%的抗性";
    case 物理强健巨龙: return "强健 : 在受到物理攻击的瞬间 , " + FloatTran(概率) + "%的概率将" + FloatTran(数值) + "%的体质附加为护甲";
    case 魔法强健巨龙: return "强健 : 在受到魔法攻击的瞬间 , " + FloatTran(概率) + "%的概率将" + FloatTran(数值) + "%的体质附加为抗性";
	}
	return "未选择";
}
void MagicStone::Affect(Entity* owner, string condition) {

}

Entity::Entity() {
	名称 = "未选择";
}
void Entity::Init(int place){
	//跟据inputs[cursuit][place]中的信息，初始化entity[1][place]
	名称 = inputs[cursuit][place].职业;
	种族 = "人型生物";
	阵营 = 1; 站位 = place; 存活 = 1;
	for (int i = 0; i < 28; i++)面板[i] = 0;
	for (int i = 0; i < 8; i++)面板[i] = inputs[cursuit][place].面板[i];
	LoadHero(名称);
	武器.Load(inputs[cursuit][place].武器);
	铠甲.Load(inputs[cursuit][place].铠甲);
	饰品1.Load(inputs[cursuit][place].饰品1);
	饰品2.Load(inputs[cursuit][place].饰品2);
	环.Init(inputs[cursuit][place].环, inputs[cursuit][place].环特效级别);
	魔石.Init(inputs[cursuit][place].魔石, inputs[cursuit][place].魔石参数a, inputs[cursuit][place].魔石参数b);
	面板命中率 = 面板命中率 + 武器.属性[0] + 铠甲.属性[0] + 饰品1.属性[0] + 饰品2.属性[0];
	面板闪避率 = 面板闪避率 + 武器.属性[1] + 铠甲.属性[1] + 饰品1.属性[1] + 饰品2.属性[1];
	面板暴击率 = 面板暴击率 + 武器.属性[2] + 铠甲.属性[2] + 饰品1.属性[2] + 饰品2.属性[2];
	面板回复效果 = 面板回复效果 + 武器.属性[3] + 铠甲.属性[3] + 饰品1.属性[3] + 饰品2.属性[3];
	面板异常附加率 = 面板异常附加率 + 武器.属性[4] + 铠甲.属性[4] + 饰品1.属性[4] + 饰品2.属性[4];
	面板物理单吸 = 面板物理单吸 + 武器.属性[5] + 铠甲.属性[5] + 饰品1.属性[5] + 饰品2.属性[5];
	面板物理群吸 = 面板物理群吸 + 武器.属性[5] + 铠甲.属性[5] + 饰品1.属性[5] + 饰品2.属性[5];
	面板魔法单吸 = 面板魔法单吸 + 武器.属性[5] + 铠甲.属性[5] + 饰品1.属性[5] + 饰品2.属性[5];
	面板魔法群吸 = 面板魔法群吸 + 武器.属性[5] + 铠甲.属性[5] + 饰品1.属性[5] + 饰品2.属性[5];
	面板卸负 = 面板卸负 + 武器.属性[6] + 铠甲.属性[6] + 饰品1.属性[6] + 饰品2.属性[6];
	面板无视护甲 = 面板无视护甲 + 武器.属性[7] + 铠甲.属性[7] + 饰品1.属性[7] + 饰品2.属性[7];
	面板无视抗性 = 面板无视抗性 + 武器.属性[8] + 铠甲.属性[8] + 饰品1.属性[8] + 饰品2.属性[8];
	if (魔石.类型 == 命中暴君 || 魔石.类型 == 命中古精灵 || 魔石.类型 == 命中乌鸦)面板命中率 += float(魔石.概率)/100;
	if (魔石.类型 == 无视暴君)面板无视护甲 += 魔石.数值;
	if (魔石.类型 == 无视古精灵)面板无视抗性 += 魔石.数值;
	if (魔石.类型 == 异常乌鸦)面板异常附加率 += float(魔石.概率) / 100;
	面板物伤 += inputs[cursuit][place].战利品[0] / 100;
	面板魔伤 += inputs[cursuit][place].战利品[1] / 100;
	面板物理单吸 += inputs[cursuit][place].战利品[2] / 100;
	面板物理群吸 += inputs[cursuit][place].战利品[3] / 100;
	面板魔法单吸 += inputs[cursuit][place].战利品[4] / 100;
	面板魔法群吸 += inputs[cursuit][place].战利品[5] / 100;
	面板命中率 += inputs[cursuit][place].战利品[6] / 100;
	面板闪避率 += inputs[cursuit][place].战利品[7] / 100;
	面板暴击率 += inputs[cursuit][place].战利品[8] / 100;
	面板回复效果 += inputs[cursuit][place].战利品[9] / 100;
	冷却时间增加 = 0;
	冷却等待时间 = 0; if (inputs[cursuit][place].先发 == 1)冷却等待时间 = 4.5;
	循环模式 = 默认施放;
	上个技能 = ""; 下个技能 = 0;
	当前生命值 = 体质 * 10;
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { (*i).技能设置b = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { (*i).技能设置a = inputs[cursuit][place].技能设置[k]; k++; }

}
bool Entity::LoadHero(string src) {
	ifstream file("JSON/冒险者数据.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	for (int i = 0; i < dom["冒险者数据"].Size(); i++) {
		if (src == dom["冒险者数据"][i]["名称"].GetString()) {
			技能.clear();
			for (int j = 0; j < dom["冒险者数据"][i]["技能"].Size(); j++) {
				rapidjson::Value& data = dom["冒险者数据"][i]["技能"][j];
				Skill tempSkill;
				tempSkill.名称 = data.HasMember("名称") ? data["名称"].GetString() : "";
				tempSkill.等级 = data.HasMember("等级") ? data["等级"].GetInt() : 0;
				tempSkill.对象 = data.HasMember("对象") ? data["对象"].GetString() : "对自身";
				tempSkill.常数 = data.HasMember("常数") ? data["常数"].GetInt() : 0;
				tempSkill.系数[0] = data.HasMember("力量系数") ? data["力量系数"].GetFloat() : 0;
				tempSkill.系数[1] = data.HasMember("魔力系数") ? data["魔力系数"].GetFloat() : 0;
				tempSkill.系数[2] = data.HasMember("技巧系数") ? data["技巧系数"].GetFloat() : 0;
				tempSkill.系数[3] = data.HasMember("速度系数") ? data["速度系数"].GetFloat() : 0;
				tempSkill.系数[4] = data.HasMember("体质系数") ? data["体质系数"].GetFloat() : 0;
				tempSkill.系数[5] = data.HasMember("护甲系数") ? data["护甲系数"].GetFloat() : 0;
				tempSkill.系数[6] = data.HasMember("抗性系数") ? data["抗性系数"].GetFloat() : 0;
				tempSkill.系数[7] = data.HasMember("武威系数") ? data["武威系数"].GetFloat() : 1;
				tempSkill.伤害类型 = data.HasMember("伤害类型") ? data["伤害类型"].GetString() : "";
				tempSkill.概率 = data.HasMember("概率") ? data["概率"].GetFloat() : 0;
				tempSkill.状态名称 = data.HasMember("状态名称") ? data["状态名称"].GetString() : "";
				tempSkill.状态类型 = !data.HasMember("状态类型") ? -1 :
					string(data["状态类型"].GetString()) == "力量buff" ? 力量buff :
					string(data["状态类型"].GetString()) == "魔力buff" ? 魔力buff :
					string(data["状态类型"].GetString()) == "技巧buff" ? 技巧buff :
					string(data["状态类型"].GetString()) == "速度buff" ? 速度buff :
					string(data["状态类型"].GetString()) == "体质buff" ? 体质buff :
					string(data["状态类型"].GetString()) == "护甲buff" ? 护甲buff :
					string(data["状态类型"].GetString()) == "抗性buff" ? 抗性buff :
					string(data["状态类型"].GetString()) == "dot" ? dot :
					string(data["状态类型"].GetString()) == "hot" ? hot :
					string(data["状态类型"].GetString()) == "反伤" ? 反伤 :
					string(data["状态类型"].GetString()) == "眩晕" ? 眩晕 :
					string(data["状态类型"].GetString()) == "物理承伤" ? 物理承伤 :
					string(data["状态类型"].GetString()) == "魔法承伤" ? 魔法承伤 : -1;
				tempSkill.状态常数 = data.HasMember("常数") ? data["常数"].GetInt() : 0;
				tempSkill.状态系数[0] = data.HasMember("状态力量系数") ? data["状态力量系数"].GetFloat() : 0;
				tempSkill.状态系数[1] = data.HasMember("状态魔力系数") ? data["状态魔力系数"].GetFloat() : 0;
				tempSkill.状态系数[2] = data.HasMember("状态技巧系数") ? data["状态技巧系数"].GetFloat() : 0;
				tempSkill.状态系数[3] = data.HasMember("状态速度系数") ? data["状态速度系数"].GetFloat() : 0;
				tempSkill.状态系数[4] = data.HasMember("状态体质系数") ? data["状态体质系数"].GetFloat() : 0;
				tempSkill.状态系数[5] = data.HasMember("状态护甲系数") ? data["状态护甲系数"].GetFloat() : 0;
				tempSkill.状态系数[6] = data.HasMember("状态抗性系数") ? data["状态抗性系数"].GetFloat() : 0;
				tempSkill.状态系数[7] = data.HasMember("状态武威系数") ? data["状态武威系数"].GetFloat() : 1;
				tempSkill.持续时间 = data.HasMember("状态持续时间") ? data["状态持续时间"].GetFloat() : -1;
				tempSkill.最大层数 = data.HasMember("状态最大层数") ? data["状态最大层数"].GetInt() : 1;
				tempSkill.基础命中率 = data.HasMember("基础命中率") ? data["基础命中率"].GetFloat() : 0;
				tempSkill.基础暴击率 = data.HasMember("基础暴击率") ? data["基础暴击率"].GetFloat() : -1;
				tempSkill.额外伤害种族 = data.HasMember("额外伤害种族") ? data["额外伤害种族"].GetString() : "";
				tempSkill.额外伤害比例 = data.HasMember("额外伤害比例") ? data["额外伤害比例"].GetFloat() : 0;
				tempSkill.吸血 = data.HasMember("吸血") ? data["吸血"].GetFloat() : 0;
				tempSkill.无视嘲讽 = data.HasMember("无视嘲讽") ? data["无视嘲讽"].GetInt() : 0;
				tempSkill.冷却时间增加 = data.HasMember("冷却时间增加") ? data["冷却时间增加"].GetFloat() : 0;
				if (data.HasMember("施放条件")) {
					tempSkill.施放条件 = 
						string(data["施放条件"].GetString()) == "生命少于百分比时施放" ? 生命少于百分比时施放 :
						string(data["施放条件"].GetString()) == "生命足够多时保持嘲讽" ? 生命足够多时保持嘲讽 :
						string(data["施放条件"].GetString()) == "经常或始终保持反击" ? 经常或始终保持反击 :
						string(data["施放条件"].GetString()) == "友方生命少于百分比时" ? 友方生命少于百分比时 :
						string(data["施放条件"].GetString()) == "至少有多个敌人时施放" ? 至少有多个敌人时施放 :
						string(data["施放条件"].GetString()) == "可设为始终轮流或循环" ? 可设为始终轮流或循环 : -1;
				}
				else {
					tempSkill.施放条件 =
						(tempSkill.伤害类型 == "回复" && tempSkill.对象 != "对自身") ? 友方生命少于百分比时 :
						(tempSkill.状态名称 == "嘲讽") ? 生命足够多时保持嘲讽 :
						(tempSkill.状态名称 == "反击") ? 经常或始终保持反击 :
						(tempSkill.伤害类型 == "回复" && tempSkill.对象 == "对自身") ? 生命少于百分比时施放 :
						(tempSkill.对象 == "对敌方全体") ? 至少有多个敌人时施放 :
						可设为始终轮流或循环;
				}
				if (data.HasMember("技能设置a"))tempSkill.技能设置a = data["技能设置a"].GetInt();
				if (data.HasMember("技能设置b"))tempSkill.技能设置b = data["技能设置b"].GetInt();
				技能.push_back(tempSkill);
			}
			return 1;
		}
	}
	return 0;
}
float Entity::Attribute(int i) {
	//跟据面板和增幅，返回属性
	float cur = 0;
	if (i < 7) {
		cur = 面板[i] + 增幅[i];
		for (vector<Status>::iterator it = 状态.begin(); it != 状态.end(); it++) {
			if ((*it).类型 == i) {
				cur = Int(cur + (*it).Value());
			}
		}
		if (i == 4)cur = Int(cur * (1.0 + 阵营 * float(遗迹.遗迹生命) / 100));
		if (i == 5)cur = Int(cur + 阵营 * float(遗迹.遗迹护甲) / 100);
		if (i == 6)cur = Int(cur + 阵营 * float(遗迹.遗迹抗性) / 100);
	}
	if (i == 7)cur = 面板[i];
	if (i == 8)cur = (1.0 + 面板[i] + 增幅[i]) * (1.0 + 阵营 * float(遗迹.遗迹物伤) / 100);
	if (i == 9)cur = (1.0 + 面板[i] + 增幅[i]) * (1.0 + 阵营 * float(遗迹.遗迹魔伤) / 100);
	if (i == 10)cur = (1.0 + 面板[i] + 增幅[i]);
	if (i == 11)cur = 面板[i] + 增幅[i];
	if (i == 12)cur = 面板[i] + 增幅[i];
	if (i == 13)cur = 面板[i] + 增幅[i];
	if (i == 14)cur = 面板[i] + 增幅[i];
	if (i == 15)cur = 面板[i] + 增幅[i] + 阵营 * float(遗迹.遗迹命中率) / 100;
	if (i == 16)cur = 面板[i] + 增幅[i];
	if (i == 17)cur = 面板[i] + 增幅[i] + 阵营 * float(遗迹.遗迹暴击率) / 100;
	if (i == 18)cur = 面板[i] + 增幅[i];
	if (i == 19)cur = 面板[i];
	if (i == 20)cur = 面板[i];
	if (i == 21)cur = 面板[i];
	if (i == 22)cur = 增幅[i];
	if (i == 23)cur = 增幅[i];
	if (i == 24)cur = 1.0 + 面板[i] + 增幅[i] + 阵营 * float(遗迹.遗迹回复效果) / 100;
	if (i == 25)cur = 1.0 + 面板[i] + 增幅[i] + 阵营 * float(遗迹.遗迹吸血效果) / 100;
	if (i == 26)cur = 1.0 + 面板[i] + 增幅[i] + 阵营 * float(遗迹.遗迹治疗效果) / 100;
	if (i == 27)cur = 1.0 + 面板[i];
	return max(cur, float(0));
}
void Entity::Attached(Status status) {
	if (status.类型 == -1) {
		for (vector<Status>::iterator it = 状态.begin(); it != 状态.end(); it++) {
			if ((*it).名称 == status.名称) 状态.erase(it);
		}
		return;
	}
	for (vector<string>::iterator it = 免疫.begin(); it != 免疫.end(); it++) {
		if ((*it) == status.名称) {
			return;
		}
	}
	int curlayer = 0;
	for (vector<Status>::iterator it = 状态.begin(); it != 状态.end(); it++) {
		if ((*it).名称 == status.名称) {
			if ((*it).特效名称 == status.特效名称) {
				curlayer = (*it).当前层数;
			}
			状态.erase(it);
		}
	}
	status.当前层数 = max(curlayer + 1, status.最大层数);
	状态.push_back(status);
}
void Entity::Attached(float p, Status status) {
	if (Rand(p - 抗性 / 1000.0)) {
		if (status.类型 == -1) {
			for (vector<Status>::iterator it = 状态.begin(); it != 状态.end(); it++) {
				if ((*it).名称 == status.名称) 状态.erase(it);
			}
			return;
		}
		for (vector<string>::iterator it = 免疫.begin(); it != 免疫.end(); it++) {
			if ((*it) == status.名称) {
				return;
			}
		}
		int curlayer = 0;
		for (vector<Status>::iterator it = 状态.begin(); it != 状态.end(); it++) {
			if ((*it).名称 == status.名称) {
				if ((*it).特效名称 == status.特效名称) {
					curlayer = (*it).当前层数;
				}
				状态.erase(it);
			}
		}
		status.当前层数 = max(curlayer + 1, status.最大层数);
		状态.push_back(status);
	}
}
void Entity::Attach(string 对象, Status status) {
	if (status.类型 == hot) status.每层数值 = Int(status.每层数值 * 回复效果);
	else if (status.类型 == dot) status.每层数值 = Int(status.每层数值 * 持续);
	if (对象 == "对敌方单体") {
		entity[1 - 阵营][敌方目标].Attached(status);
	}
	if (对象 == "对敌方全体") {
		for (int i = 0; i < 7; i++) {
			if (entity[1 - 阵营][i].存活 != 0)entity[1 - 阵营][i].Attached(status);
		}
	}
	if (对象 == "对自身") {
		Attached(status);
	}
	if (对象 == "对我方单体") {
		entity[阵营][我方目标].Attached(status);
	}
	if (对象 == "对我方全体") {
		for (int i = 0; i < 7; i++) {
			if (entity[阵营][i].存活 != 0)entity[阵营][i].Attached(status);
		}
	}
}
void Entity::Attach(float p, string 对象, Status status) {
	if (status.类型 == hot) status.每层数值 = Int(status.每层数值 * 回复效果);
	else if (status.类型 == dot) status.每层数值 = Int(status.每层数值 * 持续);
	if (对象 == "对敌方单体") {
		entity[1 - 阵营][敌方目标].Attached(p, status);
	}
	if (对象 == "对敌方全体") {
		for (int i = 0; i < 7; i++) {
			if (entity[1 - 阵营][i].存活 != 0)entity[1 - 阵营][i].Attached(p, status);
		}
	}
	if (对象 == "对自身") {
		Attached(p, status);
	}
	if (对象 == "对我方单体") {
		entity[阵营][我方目标].Attached(p, status);
	}
	if (对象 == "对我方全体") {
		for (int i = 0; i < 7; i++) {
			if (entity[阵营][i].存活 != 0)entity[阵营][i].Attached(p, status);
		}
	}
}
void Entity::Prepare(string condition) {
	if (condition == "在战斗开始时") {
		环.Affect(this, condition);
		武器.Affect(this, condition);
		铠甲.Affect(this, condition);
		饰品1.Affect(this, condition);
		饰品2.Affect(this, condition);
		魔石.Affect(this, condition);
		return;
	}
	环.Affect(this, condition);
	if (武器.Affect(this, condition)) return;
	if (铠甲.Affect(this, condition)) return;
	if (饰品1.Affect(this, condition)) return;
	if (饰品2.Affect(this, condition)) return;
	魔石.Affect(this, condition);
}
void Entity::Dead() {
	存活 = 0;
	//redraw = 1;
	for (int i = 0; i < MAX_GROUP; i++) {
		if (entity[1 - 阵营][i].存活 == 1) {
			entity[1 - 阵营][i].面板治疗效果 /= (1 - 武器.属性[17]);
			entity[1 - 阵营][i].面板治疗效果 /= (1 - 铠甲.属性[17]);
			entity[1 - 阵营][i].面板治疗效果 /= (1 - 饰品1.属性[17]);
			entity[1 - 阵营][i].面板治疗效果 /= (1 - 饰品2.属性[17]);
		}
	}
	if (遗迹.遗迹战斗) {
		遗迹.遗迹物伤 += 0.05;
		遗迹.遗迹魔伤 += 0.05;
		遗迹.遗迹状态效果 += 0.05;
	}
}
void Entity::Healed(int heal) {
	if (存活 != 0) {
		存活 = 1;
		heal = Int(heal * 治疗效果);
		heal = max(1, heal);
		//HarmAdd(heal, 4);
		当前生命值 = min(Int(当前生命值 + heal), Int(体质) * 10);
	}
}
void Entity::Attacked(int harm) {
	harm = max(harm, 1);
	//HarmAdd(damage, 3);
	当前生命值 -= min(harm, 当前生命值);
	if (当前生命值 == 0)Dead();
}
int  Entity::Attacked(int harm, string type, int oppoplace, float oppoignore, float oppohitrate, int opposkill) {
	int damage = 0;
	敌方目标 = oppoplace;
	if (Rand(oppohitrate + opposkill / (速度 * 0.3) - 闪避率)) {
		if (type == "物理伤害") {
			Prepare("在受到物理攻击的瞬间");
			damage = Int(harm * 50.0 / (50 + max(int(护甲 - Int(oppoignore)), 0)));
			For(状态, it) if ((*it).类型 == 物理承伤)damage = Int(damage * ((*it).Value() + 1));
			damage = Int(damage * 挨打效果);
			damage -= 物伤格挡;
			damage = max(damage, 1);
			//HarmAdd(damage, 1);
		}
		if (type == "魔法伤害") {
			Prepare("在受到魔法攻击的瞬间");
			damage = Int(harm * 50.0 / (50 + max(int(抗性 - Int(oppoignore)), 0)));
			For(状态, it) if ((*it).类型 == 魔法承伤)damage = Int(damage * ((*it).Value() + 1));
			damage = Int(damage * 挨打效果);
			damage -= 魔伤格挡;
			damage = max(damage, 1);
			//HarmAdd(damage, 2);
		}
		当前生命值 -= min(damage, 当前生命值);
		if (当前生命值 == 0)Dead();
		else For(状态, it) if ((*it).类型 == 反伤)entity[1 - 阵营][oppoplace].Attacked(Int(damage * (*it).Value()));
	}
	for (int i = 0; i < 28; i++)增幅[i] = 0;
	return damage;
}
int  Entity::Attacked(int harm, string type, int oppoplace, float oppoignore, float oppohitrate, int opposkill, float p, Status status) {
	int damage = 0;
	敌方目标 = oppoplace;
	if (Rand(oppohitrate + opposkill / (速度 * 0.3) - 闪避率)) {
		if (type == "物理伤害") {
			Prepare("受到物理攻击");
			damage = Int(harm * 50.0 / (50 + max(int(护甲 - Int(oppoignore)), 0)));
			For(状态, it) if ((*it).类型 ==物理承伤)damage = Int(damage * ((*it).Value() + 1));
			damage = Int(damage * 挨打效果);
			damage -= 物伤格挡;
			damage = max(damage, 1);
			//HarmAdd(damage, 1);
		}
		if (type == "魔法伤害") {
			Prepare("受到魔法攻击");
			damage = Int(harm * 50.0 / (50 + max(int(抗性 - Int(oppoignore)), 0)));
			For(状态, it) if ((*it).类型 == 魔法承伤)damage = Int(damage * ((*it).Value() + 1));
			damage = Int(damage * 挨打效果);
			damage -= 魔伤格挡;
			damage = max(damage, 1);
			//HarmAdd(damage, 2);
		}
		当前生命值 -= min(damage, 当前生命值);
		if (当前生命值 == 0)Dead();
		else For(状态, it) if ((*it).类型 == 反伤)entity[1 - 阵营][oppoplace].Attacked(Int(damage * (*it).Value()));
		Attached(p, status);
	}
	for (int i = 0; i < 28; i++)增幅[i] = 0;
	return damage;
}
bool Entity::HasStatus(string statusName) {
	For(状态, it) {
		if ((*it).名称 == statusName)return 1;
	}
	return 0;
}
void Entity::StatusTime() {
	//for (int i = 0; i < 5; i++) { if (harmArray[i][0] > 0)harmArray[i][0]--; }
	For(状态, it) {
		(*it).剩余时间 -= plank;
		if ((*it).类型 == hot && int((*it).剩余时间 / plank) % int(1.0 / plank) == 0)Healed((*it).Value());
		if ((*it).类型 == dot && int((*it).剩余时间 / plank) % int(1.0 / plank) == 0)Attacked((*it).Value());
		if ((*it).剩余时间 == 0) 状态.erase(it);
	}
}
void Entity::SkillTime() {
	if (HasStatus("眩晕"))return;
	冷却等待时间 += plank;
	float 卸负后力量 = max(力量 - 卸负, 1.0);
	float 力速比 = min(float(int(卸负后力量 * 10.0 / 速度)) / 10, 3.0);
	float curcd = max(1.5 + 力速比 + 冷却时间增加, 0.5);
	if (Int(冷却等待时间 / plank) < Int(curcd / plank)) return;
	
	冷却等待时间 = 0;
	for (int i = 0; i < 6; i++) {
		For(技能, it) {
			if ((*it).施放条件 == i && (*it).AllowRelease(this)) {
				上个技能 = (*it).名称;
				(*it).Release(this); return;
			}
		}
	}
	int skillcount = 0; For(技能, it)if ((*it).施放条件 == 5 && (*it).技能设置a == 1) skillcount++;
	if (循环模式 == 轮流施放 || 循环模式 == 默认施放 && skillcount <= 2) {
		int on = 0;
		For(技能, it) {
			if ((*it).名称 == 上个技能)on = 1;
			else if (on == 1 && (*it).施放条件 == 5 && (*it).技能设置a == 1) {
				上个技能 = (*it).名称;
				(*it).Release(this); return;
			}
		}
		For(技能, it) {
			if ((*it).施放条件 == 5 && (*it).技能设置a == 1) {
				上个技能 = (*it).名称;
				(*it).Release(this); return;
			}
		}
	}
	else if (循环模式 == 随机施放 || 循环模式 == 默认施放 && skillcount >= 3) {
		Order();
		for (int i = 0; i < MAX_GROUP; i++) {
			if (order[i] < 技能.size() && 技能[i].施放条件 == 5 && 技能[i].技能设置a == 1) {
				上个技能 = 技能[i].名称;
				技能[i].Release(this); return;
			}
		}
	}
}
string Entity::Discription(int n) {
	//返回在技能设置面板的第n行应该出现的文本，n范围0至4
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { if (k == n) { return (*i).Discription(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { return (*i).Discription(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { if (k == n) { return (*i).Discription(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { if (k == n) { return (*i).Discription(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { return (*i).Discription(1); }; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { if (k == n) { return (*i).Discription(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { if (k == n) { return (*i).Discription(0); }; k++; }
	if (k == 3 && n == 4) return "";
	return
		攻击偏好 == 剩余生命最少 ? "剩余生命最少" :
		攻击偏好 == 剩余生命最多 ? "剩余生命最多" :
		攻击偏好 == 总生命值最多 ? "总生命值最多" :
		攻击偏好 == 随意攻击 ? "随意攻击" : "";
}
void Entity::Add(int n) {
	//点击了技能设置面板第n行的+号
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Add(1); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置b; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { if (k == n) { (*i).Add(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	if (k == 3 && n == 4) return;
	if (攻击偏好 < 3)攻击偏好++;
}
void Entity::Minus(int n) {
	//点击了技能设置面板第n行的-号
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Minus(1); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置b; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { if (k == n) { (*i).Minus(0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	if (k == 3 && n == 4) return;
	if (攻击偏好 > 0)攻击偏好--;
}
void Entity::Click(int n, float p) {
	//点击在了技能设置面板第n行的滑动条的比例为p的位置
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { (*i).Click(p, 1); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置b; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { if (k == n) { (*i).Click(p, 0); inputs[cursuit][curplace].技能设置[n] = (*i).技能设置a; return; }; k++; }
	if (k == 3 && n == 4) return;
	for (int i = 0; i < 3; i++) {
		if (p < (float(i) + 0.5) / 3.0) { 攻击偏好 = i; return; }
	}
	攻击偏好 = 3; return;
}
float Entity::P(int n) {
	//技能设置面板第n行的选择钮所处的位置
	int k = 0;
	For(技能, i) if ((*i).施放条件 == 0) { if (k == n) { return (*i).P(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { return (*i).P(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 1) { if (k == n) { return (*i).P(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 2) { if (k == n) { return (*i).P(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 3) { if (k == n) { return (*i).P(1); }; k++; }
	For(技能, i) if ((*i).施放条件 == 4) { if (k == n) { return (*i).P(0); }; k++; }
	For(技能, i) if ((*i).施放条件 == 5) { if (k == n) { return (*i).P(0); }; k++; }
	if (k == 3 && n == 4) return 10000;
	return
		攻击偏好 == 剩余生命最少 ? 0 :
		攻击偏好 == 剩余生命最多 ? 1.0 / 3.0 :
		攻击偏好 == 总生命值最多 ? 2.0 / 3.0 :
		攻击偏好 == 随意攻击 ? 1 : 10000;
}

bool Skill::AllowRelease(Entity* owner) {
	if ((施放条件 == 生命少于百分比时施放 || 施放条件 == 友方生命少于百分比时) && 技能设置a != 0) {
		if ((10.0 * owner->当前生命值) * 10.0 / owner->体质 < 技能设置a)return 1;
	}
	else if (施放条件 == 生命足够多时保持嘲讽 && 技能设置a != 0) {
		if ((10.0 * owner->当前生命值) * 10.0 / owner->体质 > (100 - 技能设置a) && owner->HasStatus("嘲讽") == false)return 1;
	}
	else if (施放条件 == 经常或始终保持反击 && 技能设置a != 0) {
		if (owner->HasStatus("反击") == false) {
			if (技能设置a == 2)return 1;
			if (技能设置a == 1) {
				For(owner->技能, it) {
					if ((*it).施放条件 >= 3 && (*it).AllowRelease(owner))return Rand(0.5);
				}
				return 1;
			}
		}
	}
	else if (施放条件 == 友方生命少于百分比时 && 技能设置b != 0) {
		for (int i = 0; i < MAX_GROUP; i++) {
			if (entity[owner->阵营][i].存活 != 0 && entity[owner->阵营][i].站位 != owner->站位) {
				if ((10.0 * entity[owner->阵营][i].当前生命值) * 10.0 / entity[owner->阵营][i].体质 < 技能设置b)return 1;
			}
		}
	}
	else if (施放条件 == 至少有多个敌人时施放 && 技能设置a != 0) {
		int count = 0;
		for (int i = 0; i < MAX_GROUP; i++) {
			if (entity[1 - owner->阵营][i].存活 != 0) count++;
		}
		if (count >= Int(5 - 技能设置a))return 1;
	}
	else if (施放条件 == 可设为始终轮流或循环 && 技能设置a == 2) return 1;
	return 0;
}
void Skill::TargetSelect(Entity* owner) {
#define curTarget entity[1 - owner->阵营][order[i]]
	Order(); owner->敌方目标 = -1;
	if (!无视嘲讽) {
		if (owner->攻击偏好 == 剩余生命最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.当前生命值 < entity[1 - owner->阵营][owner->敌方目标].当前生命值))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 剩余生命最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.当前生命值 > entity[1 - owner->阵营][owner->敌方目标].当前生命值))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 总生命值最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.体质 > entity[1 - owner->阵营][owner->敌方目标].体质))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 护甲最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.护甲 < entity[1 - owner->阵营][owner->敌方目标].护甲))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 护甲最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.护甲 > entity[1 - owner->阵营][owner->敌方目标].护甲))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 抗性最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.抗性 < entity[1 - owner->阵营][owner->敌方目标].抗性))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 抗性最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && (owner->敌方目标 == -1 ||
					curTarget.抗性 > entity[1 - owner->阵营][owner->敌方目标].抗性))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && curTarget.HasStatus("嘲讽") && owner->敌方目标 == -1)
				{
					owner->敌方目标 = order[i];
				}
			}
		}
	}
	if (owner->敌方目标 == -1) {
		if (owner->攻击偏好 == 剩余生命最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.当前生命值 < entity[1 - owner->阵营][owner->敌方目标].当前生命值))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 剩余生命最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.当前生命值 > entity[1 - owner->阵营][owner->敌方目标].当前生命值))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 总生命值最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.体质 > entity[1 - owner->阵营][owner->敌方目标].体质))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 护甲最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.护甲 < entity[1 - owner->阵营][owner->敌方目标].护甲))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 护甲最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.护甲 > entity[1 - owner->阵营][owner->敌方目标].护甲))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 抗性最少) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.抗性 < entity[1 - owner->阵营][owner->敌方目标].抗性))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else if (owner->攻击偏好 == 抗性最多) {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && (owner->敌方目标 == -1 ||
					curTarget.抗性 > entity[1 - owner->阵营][owner->敌方目标].抗性))
				{
					owner->敌方目标 = order[i];
				}
			}
		}
		else {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (curTarget.存活 && owner->敌方目标 == -1)
				{
					owner->敌方目标 = order[i];
				}
			}
		}
	}
	Order(); owner->我方目标 = -1;
	for (int i = 0; i < MAX_GROUP; i++) {
		if (entity[owner->阵营][order[i]].存活 && (owner->我方目标 == -1 ||
			entity[owner->阵营][order[i]].当前生命值 / entity[owner->阵营][order[i]].体质 < entity[owner->阵营][owner->我方目标].当前生命值 / entity[owner->阵营][owner->我方目标].体质))
		{
			owner->我方目标 = order[i];
		}
	}
}
void Skill::Release(Entity* owner) {
	mem.名称 = "";
	if (伤害类型 == "物理伤害")owner->Prepare("发动物理攻击");
	if (伤害类型 == "魔法伤害")owner->Prepare("发动魔法攻击");
	if (伤害类型 == "回复")owner->Prepare("使用回复技能");
	int value = 常数;
	for (int i = 0; i < 8; i++)value += Int(系数[i] * owner->Attribute(i));
	value += Int(系数[8] * owner->当前生命值);
	value += Int(系数[9] * (owner->体质 * 10 - owner->当前生命值));
	if (伤害类型 == "物理伤害") value = Int(value * owner->物伤);
	if (伤害类型 == "魔法伤害") value = Int(value * owner->魔伤);
	if (伤害类型 == "回复") value = Int(value * owner->回复效果);
	Status status(this, owner); Status status0(状态名称);
	float total_critrate = owner->暴击率 + 基础暴击率 + owner->技巧 / 2000.0;
	Order();
	if (对象 == "对敌方单体") {
		if (伤害类型 == "物理伤害") {
			if (Rand(total_critrate)) value = Int(value * 1.5);
			if (entity[1 - owner->阵营][owner->敌方目标].种族 == 额外伤害种族)value = Int(value + value * 额外伤害比例);
			int ret = 0;
			if (状态名称 == "")ret = entity[1 - owner->阵营][owner->敌方目标].Attacked(value, 伤害类型, owner->站位, owner->无视护甲, 基础命中率 + owner->命中率, owner->技巧);
			else ret = entity[1 - owner->阵营][owner->敌方目标].Attacked(value, 伤害类型, owner->站位, owner->无视护甲, 基础命中率 + owner->命中率, owner->技巧, 概率 + owner->异常附加率, status);
			if (ret != 0 && owner->物理单吸 != 0)owner->Healed(ret * owner->物理单吸 * owner->吸血效果);
		}
		if (伤害类型 == "魔法伤害") {
			if (Rand(total_critrate)) value = Int(value * 1.5);
			if (entity[1 - owner->阵营][owner->敌方目标].种族 == 额外伤害种族)value = Int(value + value * 额外伤害比例);
			int ret = 0;
			if (状态名称 == "")ret = entity[1 - owner->阵营][owner->敌方目标].Attacked(value, 伤害类型, owner->站位, owner->无视护甲, 基础命中率 + owner->命中率, owner->技巧);
			else ret = entity[1 - owner->阵营][owner->敌方目标].Attacked(value, 伤害类型, owner->站位, owner->无视抗性, 基础命中率 + owner->命中率, owner->技巧, 概率 + owner->异常附加率, status);
			if (ret != 0 && owner->魔法单吸 != 0)owner->Healed(ret * owner->魔法单吸 * owner->吸血效果);
		}
	}
	if (对象 == "对敌方全体") {
		if (伤害类型 == "物理伤害") {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (entity[1 - owner->阵营][order[i]].存活 != 0) {
					if (Rand(total_critrate)) value = Int(value * 1.5);
					if (entity[1 - owner->阵营][order[i]].种族 == 额外伤害种族)value = Int(value + value * 额外伤害比例);
					int ret = 0;
					if (状态名称 == "")ret = entity[1 - owner->阵营][order[i]].Attacked(value, 伤害类型, owner->站位, owner->无视护甲, 基础命中率 + owner->命中率, owner->技巧);
					else ret = entity[1 - owner->阵营][order[i]].Attacked(value, 伤害类型, owner->站位, owner->无视护甲, 基础命中率 + owner->命中率, owner->技巧, 概率 + owner->异常附加率, status);
					if (ret != 0 && owner->物理单吸 != 0)owner->Healed(ret * owner->物理单吸 * owner->吸血效果);
				}
			}
		}
		if (伤害类型 == "魔法伤害") {
			for (int i = 0; i < MAX_GROUP; i++) {
				if (entity[1 - owner->阵营][order[i]].存活 != 0) {
					if (Rand(total_critrate)) value = Int(value * 1.5);
					if (entity[1 - owner->阵营][order[i]].种族 == 额外伤害种族)value = Int(value + value * 额外伤害比例);
					int ret = 0;
					if (状态名称 == "")ret = entity[1 - owner->阵营][order[i]].Attacked(value, 伤害类型, owner->站位, owner->无视抗性, 基础命中率 + owner->命中率, owner->技巧);
					else ret = entity[1 - owner->阵营][order[i]].Attacked(value, 伤害类型, owner->站位, owner->无视抗性, 基础命中率 + owner->命中率, owner->技巧, 概率 + owner->异常附加率, status);
					if (ret != 0 && owner->魔法单吸 != 0)owner->Healed(ret * owner->魔法单吸 * owner->吸血效果);
				}
			}
		}
	}
	if (对象 == "对自身") {
		if (伤害类型 == "回复") {
			owner->Healed(value);
			owner->Attached(status0);
			owner->Attached(status);
		}
	}
	if (对象 == "对我方单体") {
		if (伤害类型 == "回复") {
			if (owner->我方目标 == owner->站位) owner->Attached(status0);
			entity[owner->阵营][owner->我方目标].Healed(value);
			if (状态名称 != "" && !Equal(概率, -1))entity[owner->阵营][owner->我方目标].Attached(status);
		}
	}
	if (对象 == "对我方全体") {
		if (伤害类型 == "回复") {
			owner->Attached(status0);
			for (int i = 0; i < MAX_GROUP; i++) {
				if (entity[owner->阵营][order[i]].存活 != 0) {
					entity[owner->阵营][order[i]].Healed(value);
					if (状态名称 != "" && !Equal(概率, -1))entity[owner->阵营][order[i]].Attached(status);
				}
			}
		}

	}
	if (状态名称 != "" && Equal(概率, -1)) { owner->Attached(status0); owner->Attached(status); }
	if (mem.名称 != "") owner->Attach(对象, mem);
	for (int i = 0; i < 28; i++)owner->增幅[i] = 0;
}
string Skill::Discription(int index) {
	//返回技能设置的描述，和游戏里一模一样。
    //群奶技能有两个描述，index = 0返回自奶的奶线，index = 1返回奶队友奶线
	if (index == 0) {
		if (技能设置a == 0)return "从不施放";
		if (施放条件 == 生命少于百分比时施放) {
			if (技能设置a == 101)return "始终施放";
			else return "生命少于" + FloatTran(技能设置a) + "%时施放";
		}
		if (施放条件 == 生命足够多时保持嘲讽) {
			if (技能设置a == 100)return "始终保持"; 
			else return "自身生命多于" + FloatTran(100 - 技能设置a) + "%时施放";
		}
		if (施放条件 == 经常或始终保持反击) {
			if (技能设置a == 2)return "始终保持";
			else return "偶尔施放";
		}
		if (施放条件 == 友方生命少于百分比时) {
			if (技能设置a == 101)return "始终施放";
			else return "生命少于" + FloatTran(技能设置a) + "%时施放";
		}
		if (施放条件 == 至少有多个敌人时施放) {
			if (技能设置a == 5)return "始终施放";
			else return "至少有" + FloatTran(6 - 技能设置a) + "个敌人时施放";
		}
		if (施放条件 == 可设为始终轮流或循环) {
			if (技能设置a == 2)return "始终施放";
			else return "经常施放";
		}
	}
	else  {
		if (技能设置b == 0)return "从不施放";
		if (施放条件 == 友方生命少于百分比时) {
			if (技能设置b == 101)return "始终施放";
			return "友方生命少于" + FloatTran(技能设置b) + "%时";
		}
	}
}
void Skill::Add(int index) {
	//技能设置点击+号
	if (index == 0) {
		if (施放条件 == 生命少于百分比时施放) {
			if (技能设置a < 101)技能设置a++;
		}
		if (施放条件 == 生命足够多时保持嘲讽) {
			if (技能设置a < 100)技能设置a++;
		}
		if (施放条件 == 经常或始终保持反击) {
			if (技能设置a < 2)技能设置a++;
		}
		if (施放条件 == 友方生命少于百分比时) {
			if (技能设置a < 101)技能设置a++;
		}
		if (施放条件 == 至少有多个敌人时施放) {
			if (技能设置a < 5)技能设置a++;
		}
		if (施放条件 == 可设为始终轮流或循环) {
			if (技能设置a < 2)技能设置a++;
		}
	}
	else if (index == 1) {
		if (施放条件 == 友方生命少于百分比时) {
			if (技能设置b < 101)技能设置b++;
		}
	}
}
void Skill::Minus(int index) {
	//技能设置点击-号
	if (index == 0) {
		if (技能设置a > 0) 技能设置a--;
	}
	else {
		if (技能设置b > 0) 技能设置b--;
	}
}
void Skill::Click(float p, int index) {
	//点击在了技能设置滑动条的比例为p的位置
	int maxset =
		施放条件 == 生命少于百分比时施放 ? 100 :
		施放条件 == 生命足够多时保持嘲讽 ? 99 :
		施放条件 == 经常或始终保持反击 ? 2 :
		施放条件 == 友方生命少于百分比时 ? 100 :
		施放条件 == 至少有多个敌人时施放 ? 5 :
		施放条件 == 可设为始终轮流或循环 ? 2 : 0;
	if (index == 0) {
		for (int i = 0; i < maxset; i++) {
			if (p < (float(i) + 0.5) / float(maxset)) { 技能设置a = i; return; }
		}
		技能设置a = maxset; return;
	}
	else if (index == 1) {
		for (int i = 0; i < maxset; i++) {
			if (p < (float(i) + 0.5) / float(maxset)) { 技能设置b = i; return; }
		}
		技能设置b = maxset; return;
	}
}
float Skill::P(int index) {
	//该技能对应的选择钮所处的位置
	int maxset =
		施放条件 == 生命少于百分比时施放 ? 100 :
		施放条件 == 生命足够多时保持嘲讽 ? 99 :
		施放条件 == 经常或始终保持反击 ? 2 :
		施放条件 == 友方生命少于百分比时 ? 100 :
		施放条件 == 至少有多个敌人时施放 ? 5 :
		施放条件 == 可设为始终轮流或循环 ? 2 : 0;
	if (index == 0) {
		return float(技能设置a) / float(maxset);
	}
	else {
		return float(技能设置b) / float(maxset);
	}
}
void BossSkill::Release(Entity* owner) {

}

string ReadEquipAbbr(string abbr) {
	//TODO: 输入装备首字母大写LY，输出装备名称裂狱
	//装备可有多个简称，输入DYJ，XTDK，都应得到邪瞳大铠
	//无匹配的装备返回未选择
	ifstream file("JSON/装备数据.json");
	string json_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	rapidjson::Document dom;
	dom.Parse(UTF8_2_GBK(json_content).c_str());
	rapidjson::Value& data = dom["装备数据"];
	for (int i = 0; i < data.Size(); i++) {
		for (int j = 0; j < data[i]["简称"].Size(); j++) {
			if (abbr == data[i]["简称"][j].GetString()) {
				return data[i]["名称"].GetString();
			}
		}
	}
	return "";
}