#include <iostream>
using namespace std;

int main() {
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i = 0;

    while (i < 10) {
        if (data[i] % 2 == 0) {
            cout << "Boom!" << endl;
        } else {
            cout << data[i] << endl;
        }
        i++;
    }

    return 0;
}
