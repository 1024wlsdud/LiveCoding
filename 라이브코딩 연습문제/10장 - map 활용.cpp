#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;
/******************************************************************************
 * Class Rand
 ******************************************************************************/
 /*
 #include <random>

 class Rand {
     // 난수를 생성하는 엔진
     default_random_engine re;
     // 발생된 난수 값들이 일정 범위의 균등 분포(unfiform)로 매핑
     uniform_int_distribution<int> dist;
 public:
     // [low, high] 범위 내의 값이 발생하도록 dist 초기화
     Rand(int low, int high) : dist(low, high) { }
     // [low, high] 범위 내의 난수 발생하는 함수
     int operator() () { return dist(re); }
 };
 */

 // 프로그램 테스트할 때는 아래 클래스를 사용하고 실제 때는 위 클래스를 사용하라.
class Rand {
    int low, max, cur;

public:
    Rand(int low, int high) {
        this->low = low, this->max = high - low + 1, this->cur = (high - low + 1) / 2;
    }
    // [low, high] 범위 내의 난수 발생
    int operator() () { cur = (cur + 1) % max; return low + cur; }
};

// [0, 99] 범위의 난수 발생기, x 또는 y 좌표 값 생성시 사용
static Rand randXY(0, 99);

/******************************************************************************
 * Class Point
 ******************************************************************************/
class Point {
    static int cur_id;

    int id; // 점의 유일한 ID
    int x;  // 점의 x 좌표 값
    int y;  // 점의 y 좌표 값

public:
    void setXY(int x, int y) { this->x = x;   this->y = y; }
    Point() { this->id = cur_id++;   setXY(randXY(), randXY()); }
    void print() { cout << "(" << "[" << id << "]," << x << "," << y << ")" << endl; }
    int getID() { return id; }
};

int Point::cur_id = 0; // static 변수 초기화

/******************************************************************************
 * Class Manager
 ******************************************************************************/
class Manager {

    // map 선언 key값으로 int를, value값으로 Point 클래스에 대한 포인터를 저장하는
    // 변수 m을 선언
    map<int, Point*> m;
    

public:
    ~Manager();
    void println(string msg = "") { cout << msg << endl; }
    int  printGetInt(string msg) { cout << msg; int i; cin >> i; return i; }

    void printAllPoints();
    void createAllPoints(int count);
    void removeAllPoints();
    void findPoint();
    void removePoint();
    void removeFrontPoints();
    void run();
};

Manager::~Manager() {
    // map형 변수 m을 담는 pair은 m의 일번지부터 끝까지 반복
    // 포인터형 p에 map의 value의 주소를(Point *) 저장
    // delete로 날려줌 
    for (auto pair : m) {
        Point* p = pair.second;
        delete p;
    }
}

// 벡터의 처음부터 끝까지 모든 점들의 정보를 출력한다.
void Manager::printAllPoints() {
    println("printAllPoints():");

    //for (auto p : v)를 이용하여 벡터의 각 원소 p를 방문하면서
     //   원소 p의 print()를 호출하라.원소는 Point* 을 명심하라.
    for (auto pair : m) {
        Point* p = pair.second;
        // pair.second에 저장된 value(Point *)를 저장하고
        // p->print()로 출력(포인터는 함수를 쓸 때 ->이런식으로 써야함)
        p->print();
    }
    if (m.size() == 0)
        println("벡터가 비었습니다.");
    else
        println();
}

// count개의 Point 객체를 생성하여 벡터에 추가한다.
void Manager::createAllPoints(int count) {
    println("createALLPoints():");

    //Point 객체를 동적으로 생성하고 즉, new Point()
      //  그 포인터를 벡터의 맨 뒤에 바로 추가한다.한 문장으로 완성할 것.
        //이를 count 개수만큼 반복한다.
    for (int i = 0; i < count; i++) {
        Point* p = new Point();
        m.insert(make_pair(p->getID(), p));
        // m[p->getID()] = p;
    }
     

    printAllPoints();
}

// 벡터의 모든 객체를 제거한다.
void Manager::removeAllPoints() {
    println("deleteALLPoints():");

    /* 벡터의 각 원소 v[i]에 대해(for와 인덱스 i를 사용할 것)
         해당 원소의 내용을 출력하고, (v[i]는 벡터에 저장된 각 점 객체의 포인터임)
         동적으로 할당받은 Point 객체를 반납한다.

         모든 벡터의 원소들을 한번에 제거(벡터의 적절한 멤버함수를 사용해 비운다.)*/
    for (auto pair : m) {
        Point *p = pair.second;
        p->print();
        delete p;
    }
    m.clear();
    printAllPoints();
}

// 사용자가 지정한 ID를 가진 객체를 검색한다.
void Manager::findPoint() {
    int id = printGetInt("검색할 도형의 ID는? ");

    /*  for (auto p : v)를 이용하여 벡터의 각 원소 p를 방문하면서(p는 벡터에 저장된 각 점 객체의 포인터임)
          p의 id가 사용자가 지정한 id와 동일하면
          p의 내용을 출력하고 바로 리턴*/  
    auto pair = m.find(id);
    if (pair == m.end())
        println("존재하지 않는 도형 ID입니다.");
    else
        m[id]->print();
}

// 사용자가 지정한 ID를 가진 객체를 제거한다.
void Manager::removePoint() {
    int id = printGetInt("삭제할 도형의 ID는? ");

    auto pair = m.find(id);
    if (pair == m.end())
        println("존재하지 않는 도형 ID입니다.");
    else {
        Point* p = m[id];
        delete p;
        m.erase(id);
    }
    printAllPoints();
}

// 벡터의 앞쪽에서부터 사용자가 지정한 개수만큼의 원소들을 제거한다.
void Manager::removeFrontPoints() {
    int count = printGetInt("앞쪽의 삭제할 도형의 개수는? ");
    println("removeFrontPoints():");

    //count가 벡터의 원소의 개수보다 클 경우 벡터의 원소 개수로 설정함
    //    벡터의 iterator 변수 it를 선언하고 v.begin()으로 초기화
    //    coun 개수만큼 for문을 돌면서
    //    it을 이용하여 해당 원소의 내용을 출력하고(참고) (*it)는 벡터에 저장된 해당 점 객체의 포인트임
    //    해당 원소가 포인터하는 객체 메모리(동적으로 할당받은 메모리)를 반납하고
    //    it = erase(it); 해당 원소를 벡터에서 제거하고 삭제된 원소의 그 다음 원소를 it에 저장
    if (count > m.size())
        count = m.size();
   
    auto it = m.begin();
    for (int i = 0; i < count; i++) {
        Point* p = it->second;
        p->print();
        delete p;
        it = m.erase(it);
    }
    printAllPoints();
}

void Manager::run() {
    int count = printGetInt("생성할 점들의 개수는? ");
    createAllPoints(count);
    findPoint();
    removePoint();
    removeFrontPoints();
    removePoint();
    findPoint();
    println("\n벡터의 남은 원소들을 삭제하고 종료합니다.");
    removeAllPoints();
}

/******************************************************************************
 * main()
 ******************************************************************************/
int main()
{
    map<int, char> s;
    s.insert(pair<int, char>(40, 'sa'));
    s.at(40);
    Manager().run();
}

/******************************************************************
 프로그램의 실행결과는 다음과 같다.: 결과 1
 ******************************************************************
생성할 점들의 개수는? 6
createALLPoints():
printAllPoints():
([0],52,51)
([1],54,53)
([2],56,55)
([3],58,57)
([4],60,59)
([5],62,61)

검색할 도형의 ID는? 4
([4],60,59)
삭제할 도형의 ID는? 5
([5],62,61)
printAllPoints():
([0],52,51)
([1],54,53)
([2],56,55)
([3],58,57)
([4],60,59)

앞쪽의 삭제할 도형의 개수는? 3
removeFrontPoints():
([0],52,51)
([1],54,53)
([2],56,55)
printAllPoints():
([3],58,57)
([4],60,59)

삭제할 도형의 ID는? 3
([3],58,57)
printAllPoints():
([4],60,59)

검색할 도형의 ID는? 4
([4],60,59)

벡터의 남은 원소들을 삭제하고 종료합니다.
deleteALLPoints():
([4],60,59)
printAllPoints():
벡터가 비었습니다.
*******************************************************************/

/******************************************************************
 프로그램의 실행결과 2
 ******************************************************************
생성할 점들의 개수는? 2
createALLPoints():
printAllPoints():
([0],52,51)
([1],54,53)

검색할 도형의 ID는? 1
([1],54,53)
삭제할 도형의 ID는? 1
([1],54,53)
printAllPoints():
([0],52,51)

앞쪽의 삭제할 도형의 개수는? 1
removeFrontPoints():
([0],52,51)
printAllPoints():
벡터가 비었습니다.
삭제할 도형의 ID는? 1
존재하지 않는 도형 ID입니다.
검색할 도형의 ID는? 1
존재하지 않는 도형 ID입니다.

벡터의 남은 원소들을 삭제하고 종료합니다.
deleteALLPoints():
printAllPoints():
벡터가 비었습니다.
*******************************************************************/