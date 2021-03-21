#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include <glad/glad.h>

#include "math_f.hpp"
#include "draw_f.hpp"
#include "ROCK.hpp"

class ROCK;

using namespace std;

class TURTLE
{
    public:

    vector<double> position;
    vector<double> facing;

    double y_movement;

    int timer;
    int timer_y;

    double size;

    vector<pair<double, double>> coord_max_min;

    double angle;

    bool can_move;

    random_device rd;
    default_random_engine gen;

    uniform_real_distribution<double> dis_angle;
    uniform_real_distribution<double> dis_y;
    uniform_int_distribution<int> dis_timer;

    TURTLE();

    vector<vector<double>> get_body();

    void update_coord_max_min();

    int is_too_close_to_rock(vector<ROCK*> rocks);

    bool avoid_collision(vector<ROCK*> rocks);

    void draw(float lit1_diffuse[], bool enable_lit1);

    void move(vector<ROCK*> rocks);

};