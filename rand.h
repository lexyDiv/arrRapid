#pragma once

#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include <cstdlib>
#include <ctime>
#include <functional>
#include <set>
#include <algorithm>
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cmath>


int intRand(int start, int finish)
{
    int random_number = (std::rand() % finish) + start; // rand() return a number between ​0​ and RAND_MAX
   // std::string ret = "random = " + std::to_string(random_number);
   // printf(ret.c_str());
    return random_number; // random_number;
};
