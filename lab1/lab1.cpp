#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    short a;// �������� ������ ����� � ������� short
    short b;// �������� ������ ����� � ������� short
    short h;// �������� ����� � ��������� ������ � ������� short
    float S;// �������� ����� � ��������� ������ � ������� float
    cin >> a >> b >> h;// input
    S = h * 0.5 * (a + b);// ���������� ������� ��������
    cout << "������� ��������: " << S << " float" << endl;// ����� ����������
    cout << "short " << sizeof(short) << " �����, " << numeric_limits<short>::min() << " " << numeric_limits<short>::max() << endl;
    cout << "float " << sizeof(float) << " �����, " << numeric_limits<float>::lowest() << " " << numeric_limits<float>::max() << endl;
    return 0;
}