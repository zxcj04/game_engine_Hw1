#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <glad/glad.h>

#include "draw_f.hpp"

class ROV;
class TURTLE;

using namespace std;

template <typename T>
T my_distance(vector<T> a, vector<T> b);

double point_to_surface_distance(vector<double> facing, vector<double> origin, vector<double> point);

vector<double> map_to_surface(ROV *rov, vector<double> facing, vector<double> origin, vector<double> point, bool show_shadow_points);

bool in_rectangle(ROV *rov, TURTLE *turtle, vector<double> origin, vector<vector<double>> points, vector<double> turtle_point);

void check_catch(ROV *rov, TURTLE *turtle, bool show_shadow_points);

vector<double> calc_real_position(vector<double> origin, double x, double y, double z, vector<double> facing);

vector<float> calc_normal(vector<float> a, vector<float> b, vector<float> c, vector<float> d);
vector<float> calc_normal(vector<float> a, vector<float> b, vector<float> c);