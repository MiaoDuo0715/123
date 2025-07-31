# 41141134

作業一
## 解題說明

本題要求實作多項式類別 Polynomial 的 ADT，還要提供多項式的輸入、輸出、加法、乘法以及數值計算功能。
並且需要重載 >> 和 << 運算子以方便多項式的輸入與輸出


### 解題策略

使用一維陣列存放多項式係數，索引值代表次方，陣列元素值代表該次方的係數。

加法：對應次方係數直接相加
乘法：使用雙迴圈遍歷兩個多項式，將係數相乘並加到 i+j 次方的位置

將多項式操作封裝成 Polynomial 類別，包含：

   建構子（建立零多項式）

   運算子重載 >> 與 <<（輸入、輸出）

   運算子重載 + 與 *（加法、乘法）

   Eval() 方法（代入數值計算）


## 程式實作

以下為主要程式碼：

```cpp

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polynomial {
private:
    vector<int> coef; 
public:
    Polynomial(int Max = 0) {
        coef.resize(Max + 1, 0);
    }

    friend istream& operator>>(istream& in, Polynomial& p) {
        int terms;
        cout << "輸入多項式的項數";
        in >> terms;
        cout << "請輸入 " << terms << " 組（係數 次數）：\n";
        for (int i = 0; i < terms; i++) {
            int c, e;
            in >> c >> e;
            if (e >= p.coef.size()) p.coef.resize(e + 1, 0);
            p.coef[e] += c;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        bool first = true;
        for (int i = p.coef.size() - 1; i >= 0; i--) {
            if (p.coef[i] != 0) {
                if (!first) out << " + ";
                out << p.coef[i] << "x^" << i;
                first = false;
            }
        }
        if (first) out << "0";
        return out;
    }

    Polynomial operator+(const Polynomial& other) const {
        int maxDeg = max(coef.size(), other.coef.size());
        Polynomial result(maxDeg - 1);
        for (int i = 0; i < maxDeg; i++) {
            int a = (i < coef.size()) ? coef[i] : 0;
            int b = (i < other.coef.size()) ? other.coef[i] : 0;
            result.coef[i] = a + b;
        }
        return result;
    }

    Polynomial operator*(const Polynomial& other) const {
        int newDeg = (coef.size() - 1) + (other.coef.size() - 1);
        Polynomial result(newDeg);
        for (int i = 0; i < coef.size(); i++) {
            for (int j = 0; j < other.coef.size(); j++) {
                result.coef[i + j] += coef[i] * other.coef[j];
            }
        }
        return result;
    }

    float Eval(float x) const {
        float sum = 0;
        for (int i = 0; i < coef.size(); i++) {
            if (coef[i] != 0) {
                sum += coef[i] * pow(x, i);
            }
        }
        return sum;
    }
};

int main() {
    Polynomial arr1, arr2;

    cout << "輸入第一個多項式:\n";
    cin >> arr1;

    cout << "輸入第二個多項式:\n";
    cin >> arr2;

    cout << "\n第一個多項式: " << arr1 << endl;
    cout << "第二個多項式: " << arr2 << endl;

    Polynomial sum = arr1 + arr2;
    Polynomial P = arr1 * arr2;

    cout << "\n加法結果: " << sum << endl;
    cout << "乘法結果: " << P << endl;

    float x;
    cout << "\n輸入要代入的 x 值：";
    cin >> x;
    cout << "p1(" << x << ") = " << arr1.Eval(x) << endl;
    cout << "p2(" << x << ") = " << arr2.Eval(x) << endl;

    return 0;
}

```

## 效能分析
加法時間複雜度：程式的時間複雜度為 O(n)
乘法時間複雜度：程式的時間複雜度為 O(n^2)
空間複雜度：空間複雜度為 O(n)
## 測試與驗證

 
| 測試案例 | 輸入多項式1        | 輸入多項式2       | 加法結果                                   | 乘法結果                                                                    代入值 (x=2)                           |
|----------|-------------------|-------------------|--------------------------------------------|-----------------------------------------------------------------|----------------------------------------|
| 測試一   | 3 2 2 1 1 0       | 2 2 30 0          | 5x^2 + 2x^1 + 31x^0                        | 6x^4 + 4x^3 + 93x^2 + 60x^1 + 30x^0                             | p1(2) = 15, p2(2) = 38                 |
| 測試二   | 4 3 3 2 2 1       | 5 3 4 2 1 0       | 9x^3 + 7x^2 + 2x^1 + 1x^0                  | 20x^6 + 31x^5 + 22x^4 + 13x^3 + 6x^2 + 2x^1                     | p1(2) = 54, p2(2) = 57                 |
| 測試三   | 5 5 2 2 1 0       | 4 4 2 3 1 1       | 5x^5 + 4x^4 + 2x^3 + 2x^2 + 1x^1 + 1x^0    | 20x^9 + 8x^8 + 18x^7 + 8x^6 + 9x^5 + 6x^4 + 4x^3 + 1x^2 + 1x^1  | p1(2) = 165, p2(2) = 105               |
 


### 編譯與執行指令

g++ -o HW2.cpp 

### 結論

程式可以正確完成兩個多項式的輸入、加法、乘法以及代入計算。
使用陣列讓多項式的次方作為索引來儲存係數，讓運算方式簡單一點。
不過在格式輸出和使用方便性上還有改進空間。



## 申論及開發報告

程式的優點有：

結構簡單清晰
使用陣列儲存係數，以次方為索引，方便加法與乘法運算。

避免重複輸入錯誤
相同次方的項會自動累加，例如輸入兩個 2x 2次方項時，程式會幫你相加。

可改進的地方：

輸出格式可更美觀
目前負號與正號的顯示不夠漂亮，可能會出現 + -3x^2 這種情況。

最大次方需更彈性
雖然現在會自動擴充，但可以加上檢查機制，避免輸入不合理的次方。

可加入更多運算
目前支援加法、乘法和求值，未來可以加上減法、除法、多項式微分等功能。



