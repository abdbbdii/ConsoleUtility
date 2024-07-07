#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector v = {1, 2, 3, 4, 5};
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    return 0;
}