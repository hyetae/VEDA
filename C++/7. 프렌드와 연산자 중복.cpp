// 히스토그램 클래스에 <<, ! 연산자 작성

#include <iostream>
using namespace std;

class Histogram {
	int total;
	int cnt[26];
	string str;
public:
	Histogram(string str) {
		total = 0;
		memset(cnt, 0, sizeof(cnt));
		this->str = str;
	}
	Histogram& operator<<(char c);
	Histogram& operator<<(string s);
	void operator!();
};

Histogram& Histogram::operator<<(char c) {
	this->str += c;
	return *this;
}

Histogram& Histogram::operator<<(string s) {
	this->str += s;
	return *this;
}

void Histogram::operator!() {
	for (auto s: this->str) {
		if (isalpha(s)) {
			s = tolower(s);
			cnt[(int)s - 97]++;
			this->total++;
		}
	}
	
	cout << this->str << endl;
	cout << endl;

	cout << "총 알파벳 수 " << this->total << endl;

	for (int i = 0; i < 26; i++) {
		cout << (char)(i + 97) << ':';
		for (int j = 0; j < cnt[i]; j++)
			cout << '*';
		cout << endl;
	}
}

int main() {
	Histogram song("Wise men say, \nonly fools rush in But I can't help,\n");
	song << "falling" << " in love with you." << "- by ";
	song << 'k' << 'i' << 't';
	!song;
}
