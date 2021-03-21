#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define GLT_IMPLEMENTATION
#include <gltext.h>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

class ROV;
class TURTLE;

void draw_sphere(GLUquadric *sphere);

void draw_cylinder(GLUquadric *cylind);

void draw_cube();

void draw_blade_model();

void draw_blade(double size);

void draw_propeller(double angle, double size, GLUquadric *sphere);

void draw_billboard(double w, double h, vector<double> facing);

void draw_floor(int dis, GLuint textName[]);

void draw_cao(GLUquadric *cylind);

void draw_coord_sys(GLUquadric *cylind);

void draw_info_background(GLfloat info_width, GLfloat info_height);

// void draw_string(string inp, int x, int y);

void draw_speed_bar(int y, double billy, GLfloat info_width);