// Up & Down 게임 만들기

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class UpAndDown {
	static int answer;
	static int start;
	static int end;
	static bool flag;

public:
	UpAndDown() {
		this->answer = rand() % 100;
		cout << "Up & Down 게임을 시작합니다.\n";
		cout << "답은 " << start << "와(과) " << end << " 사이에 있습니다.\n";
	}
	static bool getFlag() {
		return flag;
	}
	void play(string name) {
		while (1) {
			cout << name << ">> ";
			int tmp;
			cin >> tmp;

			if (tmp == this->answer) {
				cout << name << "(이)가 이겼습니다!\n";
				this->flag = 0;
				return;
			}

			if (tmp > this->start && tmp < this->end) {
				if (tmp < this->answer) {
					this->start = tmp;
					cout << "답은 " << tmp << "와(과) " << end << " 사이에 있습니다.\n";
					return;
				}
				else if (tmp > this->answer) {
					this->end = tmp;
					cout << "답은 " << start << "와(과) " << tmp << " 사이에 있습니다.\n";
					return;
				}
				else {
					cout << name << "(이)가 이겼습니다!\n";
					this->flag = 0;
					return;
				}
			}
			else cout << "다시 입력하세요\n";
		}
	}
};

int UpAndDown::answer = 0; 
int UpAndDown::start = 0;
int UpAndDown::end = 99;
bool UpAndDown::flag = true;

class Person {
	string name;
	int num;
public:
	Person() { 
		cout << "사용자의 이름 입력하기: ";
		cin >> name;
		this->name = name;
	}
	string getName() {
		return this->name;
	}
};

int main() {
	srand((unsigned)time(0));

	Person p1 = Person();
	Person p2 = Person();

	UpAndDown game = UpAndDown();
	
	while (UpAndDown::getFlag()) {
		game.play(p1.getName());
		game.play(p2.getName());
	}
}
