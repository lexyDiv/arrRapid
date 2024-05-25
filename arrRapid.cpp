#include <iostream>
#include "rapid.h"

using namespace std;

class Unit
{
public:
    int type;
    Unit(int type)
    {
        this->type = type;
    }
};

int main()
{
    int LENGTH = 1000000000;

    rapid<rapid<rapid<int> *> *> *in3d = new rapid<rapid<rapid<int> *> *>;

    int a;
    cin >> a;

    rapid<int> *arr = new rapid<int>;
    // rapid<Unit*> *arr = new rapid<Unit*>;
    // arr->backForce(LENGTH + 1);
    arr->frontForce(LENGTH + 100);
    // arr->print();
    for (int i = 0; i < LENGTH; i++)
    {
        // arr->push(i);
        arr->unshift(i);
    }
    // arr->print();
    // arr->printArr();
    arr->norm();
   // arr->print();
    int el = arr->pop();
    int el2 = arr->pop();
    int el3 = arr->pop();
    arr->norm();
    int el4 = arr->shift();
    arr->norm();
    // arr->pop();
   // arr->printArr();
    arr->print();
   // arr->printArr();
    cout << " complite !!! " << " el : " << el << " el 2 : " << el2 << " el 3 : " << el3 << endl;

    int b;
    cin >> b;
    delete arr;
    while (true)
    {
    }
}
