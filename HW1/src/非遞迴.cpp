#include <iostream>
#include <stack>
using namespace std;

int funtion(int m, int n) {
    stack<int> stk;

    stk.push(m);

    while (!stk.empty()) {
        m = stk.top();
        stk.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            // A(m - 1, 1)
            stk.push(m - 1);
            n = 1;
        } else {

            stk.push(m - 1);   
            stk.push(m);       
            n = n - 1;
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "½Ð¿é¤J m ©M n¡G";
    cin >> m >> n;

    int result = funtion(m, n);
    cout << "Funtion(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
