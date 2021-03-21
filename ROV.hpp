#pragma once

#include <vector>
#include <set>

#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>

#include "math_f.hpp"
#include "draw_f.hpp"

using namespace std;

class TURTLE;
class ROCK;

class ROV
{
    public:

        vector<double> position;
        vector<double> facing;


        vector<double> speed;
        vector<double> acceleration;
        vector<bool> acc;

        vector<vector<double>> structure;

        double angle;
        vector<double> blade_angle;

        vector<pair<double, double>> coord_max_min;

        bool can_catch;
        bool catching_turtle;
        vector<double> catching_vector;
        double catching_angle;

        float c[4];

        ROV();

        void set_c(float r, float g, float b, float a = 1);

        vector<vector<double>> get_coord();

        void update_coord_max_min();

        vector<double> get_hand();

        vector<double> get_left_hand();

        double breath_size();

        void draw_structure(double position_x, double position_y, double position_z, double scale_x, double scale_y, double scale_z);

        void draw_back_propeller(GLUquadric *sphere, GLUquadric *cylind);

        void draw_down_propeller(GLUquadric *sphere, GLUquadric *cylind);

        void draw_left_propeller(GLUquadric *sphere, GLUquadric *cylind);

        void draw_right_propeller(GLUquadric *sphere, GLUquadric *cylind);

        void draw_right_arm(TURTLE *turtle, GLUquadric *sphere, GLUquadric *cylind);

        void draw_left_arm(float lit2_angle, float lit2_angle_y, bool enable_lit2, GLUquadric *sphere, GLUquadric *cylind);

        void draw_camera(GLUquadric *sphere, GLUquadric *cylind);

        void draw_plant(GLUquadric *sphere, GLUquadric *cylind);

        void draw(TURTLE *turtle, float lit2_angle, float lit2_angle_y, bool enable_lit2, GLUquadric *sphere, GLUquadric *cylind);

        bool is_too_close_to_turtle(TURTLE *turtle);

        int is_too_close_to_rock(vector<ROCK*> rocks);

        void avoid_collision(TURTLE *turtle, vector<ROCK*> rocks);

        void move(TURTLE *turtle, vector<ROCK*> rocks, set<int> pressing, float lit2_angle, float lit2_angle_y, float lit2_exponent, float lit2_cutoff, float lit1_diffuse[]);

        void catch_turtle(TURTLE *turtle);

        void move_turtle(TURTLE *turtle);

        void control_turtle(TURTLE *turtle, bool in);

        void release_turtle(TURTLE *turtle);
};