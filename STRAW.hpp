#pragma once

#include <iostream>
#include <vector>
#include <random>

#include "math_f.hpp"

using namespace std;

class STRAW
{
    public:

    vector<double> position;

    double size;
    double angle;

    vector<pair<double, double>> coord_max_min;

    float color[4];

    random_device rd;
    default_random_engine gen;

    uniform_real_distribution<float> dis_color;
    uniform_real_distribution<float> dis_position;
    uniform_real_distribution<float> dis_size;

    static int count;
    int index;

    STRAW();

    void draw(GLUquadric *cylind);

    void move();
};