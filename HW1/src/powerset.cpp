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
