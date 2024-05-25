#include <iostream>
#include "rapid.h"

using namespace std;

int main()
{
    int LENGTH = 10;

    rapid<rapid<rapid<int> *> *> *in3d = new rapid<rapid<rapid<int> *> *>;

    int a;
    cin >> a;

    rapid<int> *arr = new rapid<int>;
     arr->backForce(LENGTH + 1);
    //arr->frontForce(LENGTH + 100);
   // arr->print();
    for (int i = 0; i < LENGTH; i++)
    {
         arr->push(i);
       // arr->unshift(i);

    }
   // arr->print();
    //arr->printArr();
    arr->norm();
    arr->print();
    int* el = arr->pop();
    int* el2 = arr->pop();
    int* el3 = arr->pop();
    arr->norm();
    //arr->pop();
    arr->printArr();
    arr->print();

    cout << " complite !!! " << " el : " << *el << " el 2 : " << *el2 << " el 3 : " << *el3 << endl;

    while (true)
    {
    }
}
