#ifndef _PUB_H_
#define _PUB_H_
class Pub {
public:
	string 模型;
	string 职业;
	string 模式;
	int 力;
	int 魔;
	int 技;
	int 速;
	int 体;
	int 甲;
	int 抗;
	int 分;
	fstream log;
	Pub();
	~Pub();
	int SSAppear();
	void Piao();
	void ReadModel();
	bool ReadJob();
	void ReadAttribute();
	int JobPlace(int star);
	void Disemploy();
	void Star4();
	bool ReadStar4();
	void Star5();
	bool ReadStar5();
	bool PrintLess();
};
#endif