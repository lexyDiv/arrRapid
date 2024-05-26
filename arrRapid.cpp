#include <iostream>
#include "rapid.h"
#include <functional>

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

void test(int num, function<void(int)> func)
{
    func(num);
};

int main()
{

    //    int* h = new int(1);
    //    [h](int num){
    //     num++;
    //       cout << " this is lambda " << num << endl;
    //    };

    test(1, [](int num)
         { cout << " this is lambda " << num << endl; });

    int LENGTH = 100;

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
    arr->norm();

   rapid<int>* test = arr->filter([](int a, int i, int* arr){
    return i % 2 == 0;
   });
   test->printArr();
    // rapid<int> newRapid = arr->filter([](int a){
    //     if(a % 2 == 0) {
    //         return true;
    //     };
    //     return false;
    // });

    int b;
    cin >> b;
    delete arr;
    while (true)
    {
    }
}
