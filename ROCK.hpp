#pragma once

#include <iostream>
#include <vector>
#include <random>

#include "math_f.hpp"

using namespace std;

class ROCK
{
    public:

    vector<double> position;

    vector<double> size;

    vector<pair<double, double>> coord_max_min;

    vector<double> color;

    random_device rd;
    default_random_engine gen;

    uniform_real_distribution<double> dis_color;
    uniform_real_distribution<double> dis_position;
    uniform_real_distribution<double> dis_size;

    static int count;
    int index;

    ROCK();

    vector<vector<double>> get_coord();

    void update_coord_max_min();

    void test_draw_cube();

    void draw(unsigned int textName[], bool show_shadow_points);
};