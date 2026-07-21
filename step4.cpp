//main.cpp
#include <iostream>
#include "Player.h"
using namespace std;

const int MIN_STAT = 50;
enum StatNum {
	HP,      // 체력
	MP,      // 마나
	AP,      // 공격력
	DP,      // 방어력
	SIZE     // 스텟 개수
};
const int POTION_POINTUP = 20;

void setName(string& name);
void setStatus(int stat[]);
void updateStatus(int stat[], int& hpPotion, int& mpPotion, const string& name);
void printStatus(const string& name, const int stat[]);
void useHpPotion(int stat[], int& hpPotion);
void useMpPotion(int stat[], int& mpPotion);
void doubleAttackPoint(int stat[]);
void doubleDefensePoint(int stat[]);
void classChange(const string& name, int stat[], Player*& player);

int main(void) {                                                // 캐릭터 생성 화면
	string name;
	int stat[SIZE] = { 0 };
	int hpPotion = 5, mpPotion = 5;
	Player* player = nullptr;

	cout << "======================================" << endl;
	cout << "       [ 던전 탈출 텍스트 RPG ]" << endl;
	cout << "======================================" << endl;

	setName(name);
	setStatus(stat);
	printStatus(name, stat);
	updateStatus(stat, hpPotion, mpPotion, name);
	classChange(name, stat, player);

	delete player;

	return 0;
}

void setName(string& name) {                                    // 이름 설정
	cout << "용사의 이름을 입력해 주세요: ";
	cin >> name;
	cout << endl;
}

void setStatus(int stat[]) {                                    // 기본 스테이터스 설정
	while (true) {
		cout << "HP와 MP를 입력해주세요: ";
		cin >> stat[HP] >> stat[MP];                            // 체력과 마나 입력

		if (stat[HP] >= MIN_STAT && stat[MP] >= MIN_STAT) break;

		cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
	}
	while (true) {
		cout << "공격력과 방어력을 입력해주세요: ";
		cin >> stat[AP] >> stat[DP];                            // 공격력과 방어력 입력

		if (stat[AP] >= MIN_STAT && stat[DP] >= MIN_STAT) break;

		cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
	}
	cout << endl;
}

void printStatus(const string& name, const int stat[]) {       // 스테이터스 출력
	cout << "======================================" << endl;
	cout << "         " << name << " 의 현재 능력치" << endl;
	cout << "======================================" << endl;
	cout << "HP: " << stat[HP] << "   MP: " << stat[MP] << endl;
	cout << "공격력: " << stat[AP] << "   방어력: " << stat[DP] << endl;
	cout << "======================================" << endl;
	cout << endl;
}

void useHpPotion(int stat[], int &hpPotion) {                 // hp 포션 사용, hp 증가
	if (hpPotion > 0) {
		--hpPotion;
		stat[HP] += POTION_POINTUP;
		cout << "HP가 증가하였습니다. 현재 HP는 " << stat[HP] << "입니다." << endl;
		cout << "남은 HP 포션은 " << hpPotion << "개 입니다." << endl;
		cout << endl;
	}
	else {
		cout << "남은 HP 포션이 없습니다." << endl;
		cout << endl;
	}
}

void useMpPotion(int stat[], int& mpPotion) {                 // mp 포션 사용, mp 증가
	if (mpPotion > 0) {
		--mpPotion;
		stat[MP] += POTION_POINTUP;
		cout << "MP가 증가하였습니다. 현재 MP는 " << stat[MP] << "입니다." << endl;
		cout << "남은 MP 포션은 " << mpPotion << "개 입니다." << endl;
		cout << endl;
	}
	else {
		cout << "남은 MP 포션이 없습니다." << endl;
	}
}

void doubleAttackPoint(int stat[]) {                          // 공격력 2배 증가
	stat[AP] *= 2;
	cout << "공격력이 2배 증가했습니다. 현재 공격력은 "<< stat[AP] << "입니다." << endl;
	cout << endl;
}

void doubleDefensePoint(int stat[]) {                          // 방어력 2배 증가
	stat[DP] *= 2;
	cout << "방어력이 2배 증가했습니다. 현재 방어력은 " << stat[DP] << "입니다." << endl;
	cout << endl;
}

void updateStatus(int stat[], int& hpPotion, int& mpPotion, const string& name) {          // 게임 시작 전 메뉴
	int menuNumber = -1;
	bool isGameStart = false;

	cout << "* HP 포션 " << hpPotion <<"개, MP 포션 "<< mpPotion << "개가 기본 지급되었습니다." << endl;
	while (!isGameStart) {
		cout << "======================================" << endl;
		cout << "          < 캐릭터 강화 >" << endl;
		cout << "1. HP UP    2. MP UP    3. 공격력 2배" << endl;
		cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;
		cout << "======================================" << endl;
		
		cout << "번호를 선택해주세요: ";
		cin >> menuNumber;

		switch (menuNumber) {
			case 0:
				cout << "게임을 시작합니다!" << endl;
				isGameStart = true;
				break;
			case 1:
				useHpPotion(stat, hpPotion);
				break;
			case 2:
				useMpPotion(stat, mpPotion);
				break;
			case 3:
				doubleAttackPoint(stat);
				break;
			case 4:
				doubleDefensePoint(stat);
				break;
			case 5:
				printStatus(name, stat);
				break;
			default:
				cout << "잘못된 입력입니다." << endl;
				cout << endl;
				break;
		}
		cout << endl;
	}
}

void classChange(const string& name, int stat[], Player*& player) {         // 전직 시스템
	int classNumber = -1;
	bool isclassChange = false;

	cout << "< 전직 시스템 >" << endl;
	cout << name << "님, 직업을 선택해주세요!" << endl;
	while (!isclassChange) {
		cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
		cout << "선택: ";
		cin >> classNumber;
		switch (classNumber) {
			case 1:
				player = new Warrior(name, stat[HP], stat[MP], stat[AP], stat[DP]);
				break;
			case 2:
				player = new Magician(name, stat[HP], stat[MP], stat[AP], stat[DP]);
				break;
			case 3:
				player = new Thief(name, stat[HP], stat[MP], stat[AP], stat[DP]);
				break;
			case 4:
				player = new Archer(name, stat[HP], stat[MP], stat[AP], stat[DP]);
				break;
			default:
				cout << "잘못된 입력입니다." << endl;
				break;
		}
		player->classChangeMessage();
		player->attack();
		player->printPlayerStatus();
		cout << endl;
		isclassChange = true;
	}
}


//Player.h
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
using namespace std;

class Player {
protected:
	string name;
	string job;
	int level;
	int hp;
	int mp;
	int ap;
	int dp;
public:
	Player(string name, string job, int hp, int mp, int ap, int dp) :name(name), job(job), hp(hp), mp(mp), ap(ap), dp(dp), level(1) {}

	virtual void classChangeMessage() const = 0;
	virtual void attack() const = 0;
	void printPlayerStatus() const {
		cout << "------------------------------------" << endl;
		cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
		cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << ap << " | 방어력: " << dp << endl;
		cout << "------------------------------------" << endl;
	}
	virtual ~Player() {}
};

class Warrior : public Player {
public:
	Warrior(string name, int hp, int mp, int ap, int dp) : Player(name, "전사", hp + 30, mp, ap, dp) {}

	void classChangeMessage() const override{
		cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
	}
	void attack() const override{
		cout << "* 대검을 휘두른다!" << endl;
	}
};

class Magician : public Player {
public:
	Magician(string name, int hp, int mp, int ap, int dp) : Player(name, "마법사", hp, mp + 30, ap, dp) {}

	void classChangeMessage() const override{
		cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
	}
	void attack() const override{
		cout << "* 파이어볼을 발사한다!" << endl;
	}
};

class Thief : public Player {
public:
	Thief(string name, int hp, int mp, int ap, int dp) : Player(name, "도적", hp, mp, ap + 30, dp) {}

	void classChangeMessage() const override{
		cout << "* 도적으로 전직하였습니다. (AP +30)" << endl;
	}
	void attack() const override {
		cout << "* 표창을 날린다!" << endl;
	}
};

class Archer : public Player {
public:
	Archer(string name, int hp, int mp, int ap, int dp) : Player(name, "궁수", hp, mp, ap + 30, dp) {}

	void classChangeMessage() const override{
		cout << "* 궁수로 전직하였습니다. (AP +30)" << endl;
	}
	void attack() const override{
		cout << "* 화살을 날린다!" << endl;
	}
};
#endif
