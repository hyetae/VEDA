#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

set<int> isUsed;
vector<string> words;

bool game() {
    int n;
    while (1) {
        srand((unsigned) time(0));
        n = rand() % 6;

        if (isUsed.insert(n).second)
            break;
    }

    string word = words[n];
    int h1 = rand() % word.size();
    int h2 = h1;
    while (h2 == h1)
        h2 = rand() % word.size();

    char s1 = word[h1];
    char s2 = word[h2];
    word[h1] = '-';
    word[h2] = '-';

    int cnt = 0;
    int life = 5;
    while (life) {
        char input;
        cout << word << "\n>> ";
        cin >> input;

        if (input == s1) {
            cnt++;
            word[h1] = s1;
        } else if (input == s2) {
            cnt++;
            word[h2] = s2;
        }else
            life--;

        if (cnt == 2)
            break;
    }

    if (cnt != 2) {
        word[h1] = s1;
        word[h2] = s2;
        cout << "5번 실패하였습니다.\n" << word << '\n';
    }

    char isCon;
    cout << "Next(y/n)? ";
    cin >> isCon;

    if (isCon == 'y')
        return true;
    return false;
}

int main() {
    string word;
    ifstream f("/Users/yunhyegyeong/Documents/coding-test-study/hyetae/words.txt");
    while (getline(f, word))
        words.push_back(word);

    cout << "------------------------------\n";
    cout << "지금부터 행맨 게임을 시작합니다.\n";
    cout << "------------------------------\n";

    while (1)
        if (!game())
            break;

    f.close();
    return 0;
}