#include <iostream>
using namespace std;

class alu {
public:
    unsigned int r1, r2;
    char oper;
    alu() : r1(1), r2(3), oper('*') {}
    int calc() {
        switch (oper) {
        case '+':
            return r1 + r2;
        case '-':
            return r1 - r2;
        case '*':
            return r1 * r2;
        }
    }
};
int main()
{
    alu machine; //생성자 구현하여 아래 출력 결과 1*3처럼 출력되게 각 멤버를 초기화 시킬 것
    cout << machine.r1 << machine.oper << machine.r2 << endl; // 출력 결과:1*3
    cin >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:7 + 7
    cout << machine.calc() << endl;                           // 출력 예시:14
    cin >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:25 - 8
    cout << machine.calc() << endl;                           // 출력 예시:17
    cin >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:9 * 25
    cout << machine.calc() << endl;                           // 출력 예시:225
}