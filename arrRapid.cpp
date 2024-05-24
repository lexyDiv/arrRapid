#include <iostream>
#include "rapid.h"

using namespace std;



int main()
{
    int LENGTH = 100000000;

    rapid<rapid<rapid<int>*>*>* in3d = new rapid<rapid<rapid<int>*>*>;

    int a;
    cin >> a;

    rapid<int>* arr = new rapid<int>;
    arr->backForce(LENGTH + 10000000);
    for (int i = 0; i < LENGTH; i++) 
    {
        arr->push(i);
    }
    arr->print();
    arr->norm();
    arr->print();

    cout << " complite !!! " << endl;

    while (true) {}
}

