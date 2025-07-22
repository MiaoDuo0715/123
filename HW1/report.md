# 41141134

#作業一
**Problem1**
## 解題說明

本題要求使用遞回和非遞回方式來實現阿克曼函數
### 解題策略

製作一個funtion函數將輸入的m和n進行計算直到把m變為0為止即可把n輸出

## 程式實作

以下為主要程式碼：
遞迴:

```cpp
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

    cout << "請輸入 m 和 n：";
    cin >> m >> n;

    int result = funtion(m, n);

    cout << "funtion(" << m << ", " << n << ") = " << result << endl;

    return 0;
}

}
```
非遞迴:

```cpp
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
    cout << "請輸入 m 和 n：";
    cin >> m >> n;

    int result = funtion(m, n);
    cout << "Funtion(" << m << ", " << n << ") = " << result << endl;

    return 0;
}
```
## 效能分析

時間複雜度：程式的時間複雜度為 O(A(m, n))
空間複雜度：空間複雜度為 O(A(m, n))
## 測試與驗證


| 測試案例 | 輸入參數     | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | m=1 n=0      | 2        | 2        |
| 測試二   | m=0 n=1      | 2        | 2        |
| 測試三   | m=2 n=1      | 5        | 5        |
| 測試四   | m=2 n=2      | 7        | 7        |
| 測試五   | m=3 n=4      | 125      | 125      |

### 編譯與執行指令

g++ funtion.cpp -o ack

### 結論

1. 程式能正確計算將m與n輸入後的值
2. 由於阿克曼函數能把數字放到極大的關係導致輸入的數字太大的話會無法輸出


## 申論及開發報告

**遞迴寫法的優點：**
程式碼簡潔、可讀性高

容易撰寫與維護（對初學者而言）

適合問題規模不大時使用


**非遞迴寫法的優點：**
可以用 while 或 for 精確控制流程，不依賴系統堆疊

不會因為遞迴太深導致 stack overflow

執行效率較高




#**Problem2**

## 解題說明

本題要求輸出ABC的所有子集合

### 解題策略

我的策略是用一個遞迴函數，每次根據目前處理的第幾個元素，有兩種分支：

一個分支把它加進目前的子集合

另一個分支不加它

當遞迴到底時，就輸出一個完成的子集合。用二元決策的方式走完所有路徑，就能完整列出 Power Set。



## 程式實作

**以下為主要程式碼：**

```cpp
#include <iostream>
using namespace std;

char set[] = {'a','b','c'}; 
const int N = sizeof(set) / sizeof(set[0]);
char subset[10]; 
void powerset(int index, int subsetSize) {
    if (index == N) {
        cout << "{ ";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i] << " ";
        }
        cout << "}" << endl;
        return;
    }
   
    powerset(index + 1, subsetSize);

    subset[subsetSize] = set[index];
    powerset(index + 1, subsetSize + 1);
}

int main() {
    cout << "Powerset of the input set:" << endl;
    powerset(0, 0);
    return 0;
}
```
## 效能分析

時間複雜度：程式的時間複雜度為O(2^n)
空間複雜度：程式的空間複雜度為O(n)

## 測試與驗證

| 測試案例 | 輸入參數     | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | {a}          | { }{a}   | { }{a}  |
| 測試二   | {a,b}        |{ }{ b }{ a }{ a b }|{ }{ b }{ a }{ a b }|
| 測試三   | {a,b,c}          |{ }{ c }{ b }{ b c }{ a }{ a c }{ a b }{ a b c }| { }{ c }{ b }{ b c }{ a }{ a c }{ a b }{ a b c }|


### 編譯與執行指令
g++ powerset.cpp -o powerset
### 結論

1.程式能正確計把所有子集合列出

## 申論及開發報告

此種寫法簡單、邏輯清楚

能處理所有組合情況

利用遞迴自然展開所有選擇分支
