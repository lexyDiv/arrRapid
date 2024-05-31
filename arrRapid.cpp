#include <iostream>
#include "rapid.h"
#include <functional>
#include <vector>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Unit
{
public:
  int type = 100;
  Unit()
  {
    // cout << " unit conctructor " << endl;
  }
  Unit(int type)
  {
    this->type = type;
  }
  ~Unit()
  {
    // cout << " unit destractor " << endl;
  }
};

// template<class T>
// class box{
//   public:
//   arr
// }

void round();

int main()
{

  int a = 0;
  cin >> a;
  round();
  while (true)
  {
    // round();
    std::this_thread::sleep_for(20ms);
    // a++;
    // cout << " a = " << a << endl;
  }
}

void round()
{

  int rounds = 0;
  int LENGTH = 10;

  rapid<Unit *> *arr = new rapid<Unit *>;
  arr->backForce(LENGTH + 100);
  for (int i = 0; i < LENGTH; i++)
  {
    arr->push(new Unit(i));
  }
  arr->norm();
  rapid<Unit *> *arr2 = arr->filter([](Unit *unit, int index)
                                    { return unit->type % 2 == 0; });
  // cout << " info = " << arr->arr[1]->type << endl;

  cout << " indexOf " << arr->indexOf(arr2->getItem(2)) << endl;

  // arr->printArr();
  // cout << "-------------------" << endl;
  // arr2->printArr();
  // cout << "-------------------" << endl;
  // cout << " bool " << (bool)(arr->getItem(2) == arr2->getItem(1)) << endl;

  arr->forEach([](Unit *unit)
               {
    delete unit;
    unit = nullptr; });

  delete arr2;
  delete arr;
  arr2 = nullptr;
  arr = nullptr;

  // cout << " ALL DELETED !!! " << *a << endl;
};