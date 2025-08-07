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

