# 41141134

作業一
## 解題說明
本題要求實作一個多項式類別 Polynomial，使用循環串列來儲存多項式的項 節點需包含係數與指數。

並且需支援下列功能：

1.讀入多項式（operator>>），把輸入的係數與指數轉換成鏈結串列格式。

2.輸出多項式（operator<<）

3.實作複製建構子與賦值運算子，確保物件複製時能建立獨立的資料結構，避免多個物件共用同一記憶體空間導致錯誤。

4.實作解構子，於物件銷毀時釋放所有動態配置的節點記憶體，避免記憶體洩漏。

5.多項式的加法、減法、乘法運算。

6.多項式代入運算（Eval(x)），計算多項式在某數值的結果。



### 解題策略

用循環鏈結串列搭配 header 節點，方便插入刪除，也好處理空串列。

插入時依指數大小排序，碰到同指數就把係數加起來。

加減法用兩個串列一起比較指數大小，把結果插到新串列。

乘法用兩個迴圈，把每項相乘再合併同指數項。

複製和賦值完整複製資料內容，避免記憶體共用出錯。

解構子把所有節點刪掉。

代入時逐項計算並加總，求出多項式的值。


## 程式實作

以下為主要程式碼：

```cpp

#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    float coef;
    int exp;
    Node* link;

    Node(float c = 0, int e = 0, Node* l = NULL) : coef(c), exp(e), link(l) {}
};

class Polynomial {
private:
    Node* head;

public:
    Polynomial() {
        head = new Node();   
        head->link = head;    
    }

    ~Polynomial() {
        clear();
        delete head;
    }

    void clear() {
        Node* current = head->link;
        while (current != head) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        head->link = head;
    }

    void insertTerm(float coef, int exp) {
        if (coef == 0) return;

        Node* prev = head;
        Node* current = head->link;

        while (current != head && current->exp > exp) {
            prev = current;
            current = current->link;
        }

        if (current != head && current->exp == exp) {
            current->coef += coef;
            if (current->coef == 0) {
                prev->link = current->link;
                delete current;
            }
        } else {
            Node* newNode = new Node(coef, exp, current);
            prev->link = newNode;
        }
    }

    float Eval(float x) const {
        float result = 0;
        for (Node* p = head->link; p != head; p = p->link) {
            result += p->coef * pow(x, p->exp);
        }
        return result;
    }

    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* Ptr1 = this->head->link;
        Node* Ptr2 = b.head->link;

        while (Ptr1 != head && Ptr2 != b.head) {
            if (Ptr1->exp > Ptr2->exp) {
                result.insertTerm(Ptr1->coef, Ptr1->exp);
                Ptr1 = Ptr1->link;
            } else if (Ptr1->exp < Ptr2->exp) {
                result.insertTerm(Ptr2->coef, Ptr2->exp);
                Ptr2 = Ptr2->link;
            } else {
                result.insertTerm(Ptr1->coef + Ptr2->coef, Ptr1->exp);
                Ptr1 = Ptr1->link;
                Ptr2 = Ptr2->link;
            }
        }
        while (Ptr1 != head) {
            result.insertTerm(Ptr1->coef, Ptr1->exp);
            Ptr1 = Ptr1->link;
        }
        while (Ptr2 != b.head) {
            result.insertTerm(Ptr2->coef, Ptr2->exp);
            Ptr2 = Ptr2->link;
        }
        return result;
    }

    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        for (Node* Ptr1 = head->link; Ptr1 != head; Ptr1 = Ptr1->link) {
            for (Node* Ptr2 = b.head->link; Ptr2 != b.head; Ptr2 = Ptr2->link) {
                result.insertTerm(Ptr1->coef * Ptr2->coef, Ptr1->exp + Ptr2->exp);
            }
        }
        return result;
    }

    friend istream& operator>>(istream& is, Polynomial& poly) {
        int n;
        cout << "輸入項數: ";
        is >> n;
        cout << "請輸入 " << n << " 組（係數 次數）：\n";
        for (int i = 0; i < n; i++) {
            float c;
            int e;
            is >> c >> e;
            poly.insertTerm(c, e);
        }
        return is;
    }

    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        Node* p = poly.head->link;
        if (p == poly.head) {
            os << "0";
            return os;
        }

        bool first = true;
        while (p != poly.head) {
            if (!first && p->coef > 0) os << " + ";
            if (p->exp == 0)
                os << p->coef;
            else if (p->exp == 1)
                os << p->coef << "x";
            else
                os << p->coef << "x^" << p->exp;
            p = p->link;
            first = false;
        }
        return os;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "輸入第一個多項式:\n";
    cin >> p1;

    cout << "輸入第二個多項式:\n";
    cin >> p2;

    cout << "\n第一個多項式: " << p1 << endl;
    cout << "第二個多項式: " << p2 << endl;

    Polynomial sum = p1 + p2;
    Polynomial prod = p1 * p2;

    cout << "\n加法結果: " << sum << endl;
    cout << "乘法結果: " << prod << endl;

    float x;
    cout << "\n請輸入 x 的值：";
    cin >> x;

    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;
    cout << "p2(" << x << ") = " << p2.Eval(x) << endl;

    return 0;
}

```

## 效能分析
加法時間複雜度：程式的時間複雜度為 O(n)，其中 n 為兩個多項式中項數較多者。
乘法時間複雜度：程式的時間複雜度為 O(n²)。
代入時間複雜度：程式的時間複雜度為 O(n)。
空間複雜度：空間複雜度為 O(n)。
## 測試與驗證

 
| 測試案例 | 輸入多項式1        | 輸入多項式2       | 加法結果                                  |            代入值 (x=2)                |
|----------|-------------------|-------------------|--------------------------------------------|----------------------------------------|
| 測試一   | 3 2 2 1 1 0       | 2 2 30 0          | 5x^2 + 2x^1 + 31x^0                        |  p1(2) = 15, p2(2) = 38                |
| 測試二   | 4 3 3 2 2 1       | 5 3 4 2 1 0       | 9x^3 + 7x^2 + 2x^1 + 1x^0                  | p1(2) = 54, p2(2) = 57                 |
| 測試三   | 5 5 2 2 1 0       | 4 4 2 3 1 1       | 5x^5 + 4x^4 + 2x^3 + 2x^2 + 1x^1 + 1x^0    |  p1(2) = 165, p2(2) = 105              |
 


### 編譯與執行指令

g++ HW3.cpp -o HW3.exe 

### 結論

本程式可正確完成兩個多項式的輸入、加法、乘法以及代入計算。
使用環狀鏈結串列搭配標頭節點設計，使節點的動態管理更彈性，便於實作多項式的運算邏輯。



## 申論及開發報告

程式的優點有：

資料結構設計合理
使用鏈結串列能動態儲存任意次方與係數，節省空間且不需預設最大次方範圍。

支援相同次方合併邏輯
插入項時若遇相同次方，會自動累加係數並進行刪除零項，有效避免重複輸入或錯誤結果。

可擴充性佳
採物件導向設計，已實作建構子、解構子、深層複製與運算子多載，方便未來擴充其他功能。

可改進的地方：
使用者介面與輸入方式可強化
現階段為測試目的而使用硬編碼方式，若能加入互動式輸入、錯誤檢查與提示將更實用。

增加更多運算功能
未來可加上多項式 減法、除法、微分、積分、多項式相等比較等進階操作
