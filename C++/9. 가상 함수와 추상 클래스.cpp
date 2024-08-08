// Human의 Food 먹기 게임

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Human;
class Monster;
class Food;

class Game {
    static void print(Human *human, Monster* monster, Food* food);
public:
    Game();
    void play(Human *human, Monster *monster, Food* food);
};

class GameObject {
protected:
    int d, x, y;
public:
    GameObject(int startX, int startY, int distance);
    virtual ~GameObject() {};

    virtual void move() = 0;
    virtual char getShape() = 0;

    int getX();
    int getY();
    bool collide(GameObject* p);
};

class Human : public GameObject{
public:
    Human(int x, int y, int d);
    void move();
    char getShape();
};

class Monster : public GameObject {
public:
    Monster(int x, int y, int d);
    void move();
    char getShape();
};

class Food : public GameObject {
    int cnt;
public:
    Food(int x, int y, int d);
    void move();
    char getShape();
};

Game::Game() {
    cout << "** Human의 Food 먹기 게임을 시작합니다. **\n";
}

void Game::print(Human *human, Monster *monster, Food *food) {
    int hx = human->getX();
    int hy = human->getY();
    int mx = monster->getX();
    int my = monster->getY();
    int fx = food->getX();
    int fy = food->getY();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            if (hx == i && hy == j)
                cout << human->getShape();
            else if (mx == i && my == j)
                cout << monster->getShape();
            else if (fx == i && fy == j)
                cout << food->getShape();
            else
                cout << '-';
        }
        cout << endl;
    }
}

void Game::play(Human *human, Monster *monster, Food *food) {
    while (true) {
        this->print(human, monster, food);
        human->move();
        monster->move();
        food->move();
        if (human->collide(monster)) {
            this->print(human, monster, food);
            cout << "Human lose...";
            break;
        }
        if (human->collide(food)) {
            this->print(human, monster, food);
            cout << "Human win!!!";
            break;
        }
    }
}

GameObject:: GameObject(int startX, int startY, int distance) { this->x = startX; this->y = startY; this->d = distance; }
int GameObject::getX() { return x; }
int GameObject::getY() { return y; }
bool GameObject::collide(GameObject* p) {
    if (this->x == p->getX() && this->y == p->getY())
        return true;
    return false;
}

Human::Human(int x, int y, int d) : GameObject(x, y, d) {};
void Human::move() {
    cout << "왼쪽(a), 아래(s), 위(d), 오른쪽(f) >> ";
    char input;
    cin >> input;
    if (input == 'a')
        this->y -= this->d;
    else if (input == 's')
        this->x += this->d;
    else if (input == 'd')
        this->x -= this->d;
    else if (input == 'f')
        this->y += this->d;

    this->x = this->x < 0 ? 9 : this->x;
    this->x = this->x > 9 ? 0 : this->x;
    this->y = this->y < 0 ? 19 : this->y;
    this->y = this->y > 19 ? 0 : this->y;
}
char Human::getShape() { return 'H'; }

Monster::Monster(int x, int y, int d) : GameObject(x, y, d) {};
void Monster::move() {
    int d = rand() % 4;
    if (d == 0)
        this->y -= this->d;
    else if (d == 1)
        this->x += this->d;
    else if (d == 2)
        this->x -= this->d;
    else if (d == 3)
        this->y += this->d;

    this->x = this->x < 0 ? 9 : this->x;
    this->x = this->x > 9 ? 0 : this->x;
    this->y = this->y < 0 ? 19 : this->y;
    this->y = this->y > 19 ? 0 : this->y;
}
char Monster::getShape() { return 'M'; }

Food::Food(int x, int y, int d) : GameObject(x, y, d) { cnt = 0; }
void Food::move() {
    if (cnt >= 2) {
        int d = rand() % 4;
        if (d == 0)
            this->y -= this->d;
        else if (d == 1)
            this->x += this->d;
        else if (d == 2)
            this->x -= this->d;
        else if (d == 3)
            this->y += this->d;

        this->x = this->x < 0 ? 9 : this->x;
        this->x = this->x > 9 ? 0 : this->x;
        this->y = this->y < 0 ? 19 : this->y;
        this->y = this->y > 19 ? 0 : this->y;
    }
    cnt++;
    this->cnt = this->cnt >= 4 ? 0 : this->cnt;
}
char Food::getShape() { return '@'; }

int main() {
    srand((unsigned)time(0));

    Game game;
    Human human(0, 0, 1);
    Monster monster(5, 5, 2);
    Food food(9, 9, 1);
    game.play(&human, &monster, &food);
    return 0;
}
