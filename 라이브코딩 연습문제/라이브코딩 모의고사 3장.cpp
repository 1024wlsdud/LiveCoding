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
    alu machine; //������ �����Ͽ� �Ʒ� ��� ��� 1*3ó�� ��µǰ� �� ����� �ʱ�ȭ ��ų ��
    cout << machine.r1 << machine.oper << machine.r2 << endl; // ��� ���:1*3
    cin >> machine.r1 >> machine.oper >> machine.r2;         // �Է� ����:7 + 7
    cout << machine.calc() << endl;                           // ��� ����:14
    cin >> machine.r1 >> machine.oper >> machine.r2;         // �Է� ����:25 - 8
    cout << machine.calc() << endl;                           // ��� ����:17
    cin >> machine.r1 >> machine.oper >> machine.r2;         // �Է� ����:9 * 25
    cout << machine.calc() << endl;                           // ��� ����:225
}