//main.cpp
#include <iostream>
#include "Player.h"
#include "Monster.h"
using namespace std;

const int MIN_STAT = 50;
enum PlayerStatNum {
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
void fight(Player& player);

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
	fight(*player);

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

	cout << "* HP 포션 " << hpPotion <<"개, MP 포션 "<< mpPotion << "개가 기본 지급되었습니다." << endl;
	while (true) {
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
				return;
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
				continue;
		}
		cout << endl;
	}
}

void classChange(const string& name, int stat[], Player*& player) {         // 전직 시스템
	int classNumber = -1;

	cout << "< 전직 시스템 >" << endl;
	cout << name << "님, 직업을 선택해주세요!" << endl;
	while (true) {
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
				continue;
		}
		player->classChangeMessage();
		player->attackMessage();
		player->printPlayerStatus();
		cout << endl;
		break;
	}
}

void fight(Player& player) {
	Monster monster("슬라임", 30, 20, 10, "슬라임의 끈적한 젤리");

	cout << "[ 전투 시작! ] " << player.getName() << "(" << player.getJob() << ") vs " << monster.getName() << endl;
	cout << endl;
	while (player.getHp() > 0 && monster.getHp() > 0) {
		cout << "--- 플레이어 턴 ---" << endl;
		player.attack(monster);
		if (monster.getHp() <= 0) break;
		cout << " --- 몬스터 턴 ---" << endl;
		monster.attack(player);
	}

	if (player.getHp() <= 0) cout << "패배" << endl;
	else {
		cout << "★ 전투 승리!" << endl;
		cout << "   -> " << monster.getDropItemName() << " 획득!" << endl;
		cout << "   (다음 단계에서 인벤토리에 저장됩니다.)" << endl;
	}
}

//Player.h
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;

class Monster;

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
	Player(const string& name, string job, int hp, int mp, int ap, int dp) :name(name), job(job), hp(hp), mp(mp), ap(ap), dp(dp), level(1) {}

	virtual void classChangeMessage() const = 0;
	virtual void attackMessage() const = 0;
	void printPlayerStatus() const;
	const string& getName() const;
	const string& getJob() const;
	int getHp() const;
	void setHp(int hp);
	int getAp() const;
	int getDp() const;
	void attack(Monster& monster);
	virtual ~Player() {}
};

class Warrior : public Player {
public:
	Warrior(const string& name, int hp, int mp, int ap, int dp) : Player(name, "전사", hp + 30, mp, ap, dp) {}

	void classChangeMessage() const override{
		cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
	}
	void attackMessage() const override{
		cout << "* 대검을 휘두른다!" << endl;
	}
};

class Magician : public Player {
public:
	Magician(const string& name, int hp, int mp, int ap, int dp) : Player(name, "마법사", hp, mp + 30, ap, dp) {}

	void classChangeMessage() const override{
		cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
	}
	void attackMessage() const override{
		cout << "* 파이어볼을 발사한다!" << endl;
	}
};

class Thief : public Player {
public:
	Thief(const string& name, int hp, int mp, int ap, int dp) : Player(name, "도적", hp, mp, ap + 30, dp) {}

	void classChangeMessage() const override{
		cout << "* 도적으로 전직하였습니다. (AP +30)" << endl;
	}
	void attackMessage() const override {
		cout << "* 표창을 날린다!" << endl;
	}
};

class Archer : public Player {
public:
	Archer(const string& name, int hp, int mp, int ap, int dp) : Player(name, "궁수", hp, mp, ap + 30, dp) {}

	void classChangeMessage() const override{
		cout << "* 궁수로 전직하였습니다. (AP +30)" << endl;
	}
	void attackMessage() const override{
		cout << "* 화살을 날린다!" << endl;
	}
};
#endif

//Player.cpp
#include "Player.h"
#include "Monster.h"
#include <iostream>
using namespace std;

void Player::printPlayerStatus() const {
	cout << "------------------------------------" << endl;
	cout << "닉네임: " << name << " | 직업: " << job << " | Lv." << level << endl;
	cout << "HP: " << hp << " | MP: " << mp << " | 공격력: " << ap << " | 방어력: " << dp << endl;
	cout << "------------------------------------" << endl;
}

const string& Player::getName() const { return name; }

const string& Player::getJob() const { return job; }

int Player::getHp() const { return hp; }

void Player::setHp(int hp) { this->hp = hp; }

int Player::getAp() const { return ap; }

int Player::getDp() const { return dp; }

void Player::attack(Monster& monster) {
	int monsterHp = monster.getHp();
	int damage = ap - monster.getDp();
	if (damage <= 0) damage = 1;
	int monsterNewHp = monsterHp - damage;
	if (monsterNewHp < 0) monsterNewHp = 0;
	attackMessage();
	cout << monster.getName() << "에게 " << damage << " 데미지!" << endl;
	cout << monster.getName() << " HP: " << monsterHp << " -> " << monsterNewHp;
	if (monsterNewHp == 0) cout << " (사망)";
	cout << endl;
	monster.setHp(monsterNewHp);
}

//Monster.h
#ifndef MONSTER_H
#define MONSTER_H
#include <iostream>
using namespace std;

class Player;

class Monster {
protected:
	string name;
	int hp;
	int ap;
	int dp;
	string dropItemName;
	int dropItemPrice;

public:
	Monster(const string& name, int hp, int ap, int dp, const string& dropItemName) : name(name), hp(hp), ap(ap), dp(dp), dropItemName(dropItemName), dropItemPrice(0) {}

	void attack(Player& player);
	const string& getName() const { return name; }
	const string& getDropItemName() const { return dropItemName; }
	int getHp() const { return hp; }
	int getDp() const { return dp; }
	void setHp(int hp) { this->hp = hp; }
};

#endif

//Monster.cpp
#include "Monster.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Monster::attack(Player& player) {
	int playerHp = player.getHp();
	int damage = ap - player.getDp();
	if (damage <= 0) damage = 1;
	int playerNewHp = playerHp - damage;
	if (playerNewHp < 0) playerNewHp = 0;
	cout << name << "이 공격했다!" << endl;
	cout << player.getName() << "에게 " << damage << " 데미지!" << endl;
	cout << player.getName() << " HP: " << playerHp << " -> " << playerNewHp;
	if (playerNewHp == 0) cout << " (사망)";
	cout << endl;
	player.setHp(playerNewHp);
}
