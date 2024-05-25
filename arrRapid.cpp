#include <iostream>
#include "rapid.h"

using namespace std;

int main()
{
    int LENGTH = 100000000;

    rapid<rapid<rapid<int> *> *> *in3d = new rapid<rapid<rapid<int> *> *>;

    int a;
    cin >> a;

    rapid<int> *arr = new rapid<int>;
    // arr->backForce(LENGTH + 1);
    arr->frontForce(LENGTH + 100);
    arr->print();
    for (int i = 0; i < LENGTH; i++)
    {
        // arr->push(10);
        arr->unshift(i);

    }
    arr->print();
    //arr->printArr();
    arr->norm();
    arr->print();
   // arr->printArr();

    cout << " complite !!! " << endl;

    while (true)
    {
    }
}
