#include <iostream>
#include "rapid.h"
#include <functional>
#include <vector>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>

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
  void reType(int a){
       this->type = a;
  };
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
void round2(int &a);

int main()
{

  //////////////////////////////////////////
  vector<Unit *> vec;
  for (int i = 0; i < 10; i++)
  {
    vec.push_back(new Unit(i));
  }
  auto filtred = remove_if(vec.begin(), vec.end(), [](Unit *unit)
                           { return unit->type % 2 == 0; });
  vec.erase(filtred, vec.end());
  for (Unit *el : vec)
  {
    cout << " type = " << el->type << endl;
  }
  ///////////////////////////////////////////////////////////////////////

  Unit* newUnit = new Unit(99);
  thread rt(&Unit::reType, newUnit, 1000);
  // thread forUnit([&](){
  //      newUnit->type = 100;
  //      cout << " newUnit type = " << newUnit->type << endl;
  // });
  cout << " newUnit type = " << newUnit->type << endl;

  auto start = chrono::high_resolution_clock::now();
  int a = 10;

  thread th(round2, ref(a));

  round();
  // round2(a);

  th.join();
  rt.join();

  auto finish = chrono::high_resolution_clock::now();
  chrono::duration<float> resault = finish - start;
  cout << " timing = " << resault.count() << endl;

  while (true)
  {
    this_thread::sleep_for(20ms);
  }
}

void round()
{
  cout << " stream id = " << this_thread::get_id() << endl;
  int LENGTH = 10;
  rapid<Unit *> *arr = new rapid<Unit *>;
  arr->backForce(LENGTH);
  for (int i = 0; i < LENGTH; i++)
  {
    arr->push(new Unit(i));
  }
  arr->norm();
  arr->forEach([](Unit *unit)
               {
    delete unit;
    unit = nullptr; });
  delete arr;
  cout << " all deleted ! " << endl;
};

void round2(int &a)
{
  int LENGTH = 10;
  rapid<Unit *> *arr2 = new rapid<Unit *>;
  arr2->backForce(LENGTH);
  for (int i = 0; i < LENGTH; i++)
  {
    arr2->push(new Unit(i));
    // if(i % 10000000 == 0) {
    //   this_thread::sleep_for(20ms);
    //   cout << " sleeping " << endl;
    // }
  }
  arr2->norm();
  arr2->forEach([](Unit *unit)
                {
    delete unit;
    unit = nullptr; });
  delete arr2;
  cout << " all deleted 2 ! " << endl;
}