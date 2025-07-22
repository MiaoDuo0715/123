#include <iostream>
using namespace std;

int funtion(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
	if (n == 0) {
        return funtion(m - 1, 1);
    } 
	else {
        return funtion(m - 1, funtion(m, n - 1));
    }
}

int main() {
    int m, n;

    cout << "½Ð¿é¤J m ©M n¡G";
    cin >> m >> n;

    int result = funtion(m, n);

    cout << "funtion(" << m << ", " << n << ") = " << result << endl;

    return 0;
}


