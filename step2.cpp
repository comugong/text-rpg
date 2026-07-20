#include <iostream>
using namespace std;

void printStatus(string name, int stat[]);

int main(void) {                                                // 캐릭터 생성 화면
	string name;
	const int SIZE = 4;
	int stat[SIZE] = { 0 };

	cout << "======================================" << endl;
	cout << "       [ 던전 탈출 텍스트 RPG ]" << endl;
	cout << "======================================" << endl;
	cout << "용사의 이름을 입력해 주세요: ";
	cin >> name;
	cout << endl;
	while (true) {
		cout << "HP와 MP를 입력해주세요: ";
		cin >> stat[0] >> stat[1];                              // stat[0]: HP, stat[1]: MP

		if (stat[0] >= 50 && stat[1] >= 50) break;

		cout << "HP나 MP의 값이 너무 작습니다. 다시 입력해주세요." << endl;
	}
	while (true) {
		cout << "공격력과 방어력을 입력해주세요: ";
		cin >> stat[2] >> stat[3];                              // stat[2]: 공격력, stat[3]: 방어력

		if (stat[2] >= 50 && stat[3] >= 50) break;

		cout << "공격력이나 방어력이 너무 작습니다. 다시 입력해주세요." << endl;
	}
	cout << endl;

	printStatus(name, stat);

	return 0;
}

void printStatus(string name, int stat[]) {
	cout << "======================================" << endl;
	cout << "         " << name << " 의 현재 능력치" << endl;
	cout << "======================================" << endl;
	cout << "HP: " << stat[0] << "   MP: " << stat[1] << endl;
	cout << "공격력: " << stat[2] << "   방어력: " << stat[3] << endl;
	cout << "======================================" << endl;
}
