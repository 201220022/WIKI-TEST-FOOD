#ifndef _CORE_H_
#define _CORE_H_
class InputInfo {
public:
	string 职业;
	string 武器;
	string 铠甲;
	string 饰品1;
	string 饰品2;
	int 环;
	int 环特效级别;
	int 魔石;
	int 魔石参数a;
	int 魔石参数b;
	int 面板[8];
	float 战利品[10];
	bool 先发;
	int 技能设置[4];
	int 攻击偏好;
	void Clear();
};
struct RelicInfo {
	bool 遗迹战斗;
	int 遗迹状态效果;
	int 遗迹生命;
	int 遗迹护甲;
	int 遗迹抗性;
	int 遗迹物伤;
	int 遗迹魔伤;
	int 遗迹回复效果;
	int 遗迹吸血效果;
	int 遗迹治疗效果;
	int 遗迹命中率;
	int 遗迹暴击率;
};
struct EquipEffect {
	string 类型;       //状态, 增幅, 连击, 真伤，回复
	string 名称;       
	string 触发;       //战斗开始, 发动物理攻击, 发动魔法攻击, 受到物理攻击, 受到魔法攻击, 
	float 概率;        //0.3
	string 对象;       //对敌方全体，对敌方单体，对自身，对我方全体，对我方单体
	int 常数;
	float 系数[10];    //力魔技速体甲抗 武威 剩余生命 已损生命

	string 状态名称; int 状态类型; float 持续时间; int 最大层数;
	vector<pair<float,pair<int,int>>> 增幅系数;
};

class Status; class Equip; class Ring; class MagicStone; class Skill; class ViolentSkill; class Entity;
class Status {
public:
	string 名称;
	string 特效名称;
	int 类型;
	float 剩余时间;
	int 每层数值;
	int 当前层数;
	int 最大层数;
	Entity* 附加者;
	Status(string name);
	Status(Skill* skill, Entity* src);
	Status(EquipEffect content, Entity* src);
	void Set(EquipEffect content, Entity* src);
	int Value();
};
class Equip {
public:
	string 名称;
	vector<string> 简称;             //简称。即首字母大写，或者其他的。用户可以在文件中自定义。
	int 类型, 稀有度, 来源;          //法杖，红装，唯一装备。
	float 属性[10];                  //命中 闪避 暴击 回复 异常 吸血 卸负 无视 无视 抑制
	int 初始锻造; int 八维[4][8];    //初始锻造，当前数值、上下限、区间分布特征
	vector<string> 免疫列表;
	vector<EquipEffect> 装备特效;
	bool Load(string abbr);
	bool Effect(Entity* owner, string condition);
};
class Ring {
public:
	int 类型;
	int 特效数值;
	void Init(int type, int level);
	float Value(int level);
	string Discription();
	bool Effect(Entity* owner, string condition);
};
class MagicStone {
public:
	int 类型;
	int 力;
	int 魔;
	int 技;
	int 速;
	int 体;
	int 概率;
	int 数值;
	void Init(int type, int x, int y);
	string Discription();
	string ShortDiscription();
	bool Effect(Entity* owner, string condition);
};
class Skill {
public:
	string 名称;
	int 等级;

	string 对象;
	int 常数; float 系数[8];//力魔技速体甲抗 武威
	string 伤害类型;

	float 概率;
	string 状态名称;
	int 状态类型;
	int 状态常数; float 状态系数[10];
	float 持续时间;
	float 最大层数;

	string 额外伤害种族; float 额外伤害比例;
	float 吸血;
	bool 无视嘲讽;
	float 基础命中率, 基础暴击率, 冷却时间增加;

	int 施放条件, 技能设置a, 技能设置b;
	void Clear();
	int  AllowRelease(Entity* owner);
	void TargetSelect(Entity* owner);
	void Release(Entity* owner);
	string Discription(int index);
	void Add(int index);
	void Minus(int index);
	void Click(float p, int inde);
	float P(int index = 0);
};
class ViolentSkill {
public:
	string 名称;
	bool 重伤失效;
	float 回复抑制, 吸血抑制, 治疗抑制;
	string 类型;
	float 首次施放时间;
	float 冷却等待时间;
	string 死亡关联;
	Skill 内容;
	void Clear();
};
class Entity {
public:
	string 名称;
	string 种族;
	bool 阵营; int 站位; int 存活, 当前生命值;
	float 冷却时间增加, 冷却等待时间; int 循环模式; string 上个技能; int 下个技能;
	int 攻击偏好, 我方目标, 敌方目标;

	float 面板[28], 增幅[28];
	vector<Status> 状态;
	vector<string> 免疫;
	vector<Skill> 技能;
	ViolentSkill 狂暴技能;
	Equip 武器, 铠甲, 饰品1, 饰品2;	MagicStone 魔石; Ring 环;

	long long int 总伤害;
	int 最低血线;
	vector<pair<string, int>> 伤害类型占比;
	vector<pair<string, int>> 伤害来源占比;
	
	Entity();
	void Clear(int place);
	void Init(int place);
	bool LoadHero(string src);
	string Discription(int n);
	void Add(int n);
	void Minus(int n);
	void Click(int n, float p);
	float P(int n);
	float RingEffect(int i);
	float Attribute(int i);
	bool HasStatus(string statusName);
	void StatusTime();
	void SkillTime();
	void ViolentTime();
	void Attached(Status status);
	void Attached(float p, Status status);
	void Attach(string group, Status status);
	void Attach(float p, string 对象, Status status);
	void Prepare(string condition);
	void Dead();
	void Healed(int heal);
	void Attacked();
	void Attacked(int value);
	int  Attacked(int harm, string type, int oppoplace, float oppoignore, float oppohitrate, int opposkill);
	int  Attacked(int harm, string type, int oppoplace, float oppoignore, float oppohitrate, int opposkill, float p, Status status);
};

//跟据输入的简称，查找装备名称
string ReadEquipAbbr(string abbr);
string ReadMonsterAbbr(string abbr);
void LoadMonster(string src);
#endif