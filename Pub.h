#ifndef _PUB_H_
#define _PUB_H_
class Pub {
public:
	string ģ��;
	string ְҵ;
	string ģʽ;
	int ��;
	int ħ;
	int ��;
	int ��;
	int ��;
	int ��;
	int ��;
	int ��;
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