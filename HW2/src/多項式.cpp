#include <iostream>
using namespace std;

int main() {
    int Max;
    cout << "�п�J�A�n�䴩���̰�����G";
    cin >> Max;

    int* arr1 = new int[Max + 1]();
    int* arr2 = new int[Max + 1]();
    int* arr3 = new int[Max + 1]();

    int C;

 
    cout << "�п�J�Ĥ@�Ӧh���������ơG";
    cin >> C;

    cout << "�п�J " << C << " �ա]�Y�� ���ơ^�G\n";
    for (int i = 0; i < C; i++) {
        int coef, exp;
        cin >> coef >> exp;
        arr1[exp] += coef;
    }

    cout << "�п�J�ĤG�Ӧh���������ơG";
    cin >> C;

    cout << "�п�J " << C << " �ա]�Y�� ���ơ^�G\n";
    for (int i = 0; i < C; i++) {
        int coef, exp;
        cin >> coef >> exp;
        arr2[exp] += coef;
    }

    for (int i = 0; i <= Max; ++i) {
        arr3[i] = arr1[i] + arr2[i];
    }

    bool first = true;
    for (int i = Max; i >= 0; --i) {
        if (arr3[i] != 0) {
            if (!first) cout << " + ";
            cout << arr3[i] << "x^" << i;
            first = false;
        }
    }
    if (first) cout << "0"; 
    cout << endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;
}

