#include <iostream>

using namespace std;

int main() {
    short a;// �������� ������ ����� � ������� short
    short b;// �������� ������ ����� � ������� short
    float h;// �������� ����� � ��������� ������ � ������� float
    float S;// �������� ����� � ��������� ������ � ������� float
    cin >> a >> b >> h;//input
    S = h / 2 * (a + b);// ��������� ������� ��������
    cout << "������� ��������: " << S << " float" << endl;// ����� ����������
    cout << "short " << "16 ���, " << -32768 << " " << 32767 << endl;
    cout << "float " << "32 ����, " << -3.4E+38 << " " << 3.4E+38 << endl;
    return 0;
}