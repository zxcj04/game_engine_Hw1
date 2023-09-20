#include "ROV.hpp"
#include "TURTLE.hpp"
#include "ROCK.hpp"

ROV::ROV()
{
    position = {48, 40, 49};
    facing = {0, 0, -1};

    double len = my_distance(facing, {0, 0, 0});

    facing[0] /= len;
    facing[1] /= len;
    facing[2] /= len;

    speed = {0, 0, 0};
    acceleration = {0, 0, 0};
    acc = {false, false, false};

    // auto calc angle for facing
    angle = asin(facing[0]) * 180 / 3.14159;

    // fix arcsin duplicate value of two angle
    if(facing[2] < 0)
        angle += 180 - angle * 2;

    update_coord_max_min();

    blade_angle = {0, 0, 0, 0, 0};

    can_catch = false;
    catching_turtle = false;
    catching_vector = {0, 0, 0};
    catching_angle = 0;

    this->structure = {

        // {
        //     color,
        //     position,
        //     scale
        // },

        //base
        {
            0.0, 0.0, 0.0,
            0, -5.5, 0,
            5, 1, 12
        },

        // face
        {
            0.5, 0.5, 0.5,
            2, 0, 0,
            1, 10, 12
        },
        {
            0.5, 0.5, 0.5,
            -2, 0, 0,
            1, 10, 12
        },
        {
            0.3, 0.3, 0.3,
            0, 0, 0.25,
            1, 10, 10.5
        },
        {
            0.5, 0.5, 0.5,
            0, 0, 6,
            3, 10, 1
        },

        // // texture(X)
        // {
        //     0.3, 0.3, 0.3,
        //     1.49, 0, 0.25,
        //     0.01, 10, 10.49
        // },
        // {
        //     0.3, 0.3, 0.3,
        //     -1.49, 0, 0.25,
        //     0.01, 10, 10.49
        // },
        // {
        //     0.45, 0.45, 0.45,
        //     0, -4.99, 0,
        //     5, 0.01, 12
        // },
        // {
        //     0.4, 0.4, 0.4,
        //     0, 0, 5.49,
        //     3, 10, 0.01
        // },
        // {
        //     0.4, 0.4, 0.4,
        //     0, 0, -4.74,
        //     3, 10, 0.01
        // },

        // pillar
        {
            0.5, 0.5, 0.5,
            1, 0, -5.25,
            1, 10, 1
        },
        {
            0.5, 0.5, 0.5,
            -1, 0, -5.25,
            1, 10, 1
        },
        {
            0.0, 0.0, 0.0,
            0, -5.5, 6.25,
            3, 1, 0.5
        },

        //small barrier
        {
            0.4, 0.4, 0.4,
            0, 4.5, -5.5,
            1, 1, 1
        },
        {
            0.4, 0.4, 0.4,
            0, -4.5, -5.5,
            1, 1, 1
        },

    };


}

void ROV::set_c(float r, float g, float b, float a)
{
    c[0] = r;
    c[1] = g;
    c[2] = b;
    c[3] = a;
}

vector<vector<double>> ROV::get_coord()
{
    return {
        calc_real_position(position, -2.5,  5,  7, facing),
        calc_real_position(position,  2.5,  5,  7, facing),
        calc_real_position(position,  2.5,  5, -7, facing),
        calc_real_position(position, -2.5,  5, -7, facing),

        calc_real_position(position, -2.5, -5,  7, facing),
        calc_real_position(position,  2.5, -5,  7, facing),
        calc_real_position(position,  2.5, -5, -7, facing),
        calc_real_position(position, -2.5, -5, -7, facing),
    };
}

void ROV::update_coord_max_min()
{
    vector<vector<double>> coords = get_coord();

    coord_max_min = {
        make_pair(coords[0][0], coords[0][0]),
        make_pair(coords[0][1], coords[0][1]),
        make_pair(coords[0][2], coords[0][2]),
    };

    for(int i = 1 ; i < coords.size() ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
            if(coords[i][j] > coord_max_min[j].first)
                coord_max_min[j].first  = coords[i][j];
            else if(coords[i][j] < coord_max_min[j].second)
                coord_max_min[j].second = coords[i][j];
    }
}

vector<double> ROV::get_hand()
{
    return calc_real_position(position, -3.5, -2, 8.732, facing);
}

vector<double> ROV::get_left_hand()
{
    return calc_real_position(position, 3.5, -2, 8.732, facing);
}

double ROV::breath_size()
{
    static double interval = 0.00125;
    static double size = 0.25;

    if(size < 0.25 || size > 0.5)
        interval = -interval;

    size += interval;

    return size;
}

void ROV::draw_structure(double position_x, double position_y, double position_z, double scale_x, double scale_y, double scale_z)
{
    glPushMatrix();

        glTranslatef(position_x, position_y, position_z);

        glScalef(scale_x, scale_y, scale_z);

        draw_cube();

    glPopMatrix();
}

void ROV::draw_back_propeller(GLUquadric *sphere, GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(0, 3, -4.5);

            glPushMatrix();

                glScalef(0.5, 0.5, 0.5);

                set_c(0.8, 0.8, 0.8);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4, 0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_sphere(sphere);

            glPopMatrix();

        glRotatef(180, 0.0, 1.0, 0);

            glPushMatrix();

                glScalef(1, 1, 2.5);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

        glTranslatef(0, 0, 2.5);

        draw_propeller(blade_angle[0], 3, sphere);

    glPopMatrix();
}

void ROV::draw_down_propeller(GLUquadric *sphere, GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(2, -5, -6);

        glRotatef(180, 0.0, 1.0, 0);

            glPushMatrix();

                glScalef(0.25, 0.25, 0.5);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

        glTranslatef(0, 0, 0.5);

        draw_propeller(blade_angle[4], 1, sphere);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(-2, -5, -6);

        glRotatef(180, 0.0, 1.0, 0);

            glPushMatrix();

                glScalef(0.25, 0.25, 0.5);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

        glTranslatef(0, 0, 0.5);

        draw_propeller(blade_angle[3], 1, sphere);

    glPopMatrix();
}

void ROV::draw_left_propeller(GLUquadric *sphere, GLUquadric *cylind)
{
    for(double i = -5.5 ; i <= 5.5 ; i += 1.5)
    {
        glPushMatrix();

            glTranslatef(2.5, -5.5, i);

            glRotatef(90, 0.0, 1.0, 0);

                glPushMatrix();

                    glScalef(0.25, 0.25, 0.5);

                    set_c(0.5, 0.5, 0.5);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                    set_c(0.4, 0.4,  0.4);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                    draw_cylinder(cylind);

                glPopMatrix();

            glTranslatef(0, 0, 0.5);

            draw_propeller(blade_angle[1], 0.5, sphere);

        glPopMatrix();
    }
}

void ROV::draw_right_propeller(GLUquadric *sphere, GLUquadric *cylind)
{
    for(double i = -5.5 ; i <= 5.5 ; i += 1.5)
    {
        glPushMatrix();

            glTranslatef(-2.5, -5.5, i);

            glRotatef(-90, 0.0, 1.0, 0);

                glPushMatrix();

                    glScalef(0.25, 0.25, 0.5);

                    set_c(0.5, 0.5, 0.5);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                    set_c(0.4, 0.4,  0.4);

                    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                    draw_cylinder(cylind);

                glPopMatrix();

            glTranslatef(0, 0, 0.5);

            draw_propeller(blade_angle[1], 0.5, sphere);

        glPopMatrix();
    }
}

void ROV::draw_right_arm(TURTLE *turtle, GLUquadric *sphere, GLUquadric *cylind)
{
    double size = breath_size();

    glPushMatrix();

        glTranslatef(-2.5, -2, 5);

            glPushMatrix();

                glScalef(0.25, 0.25, 0.25);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_sphere(sphere);

            glPopMatrix();

            // glRotatef(15, 1.0, 0.0, 0.0);

            glRotatef(-30, 0.0, 1.0, 0.0);

            glPushMatrix();

                glScalef(0.5, 0.5, 2);

                set_c(0.25, 0.25, 0.25);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

            glTranslatef(0, 0, 2);

            // glPushMatrix();

            //     glScalef(0.25, 0.25, 0.25);

            //     glColor3f(0.5, 0.5, 0.5);

                // draw_sphere(sphere);

            // glPopMatrix();

            glPushMatrix();

                glScalef(0.125, 0.125, 0.3);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                // glutSolidTorus(0.25, 2, 30, 50);

            glPopMatrix();

            // glRotatef(0, 1.0, 0.0, 0.0);

            glRotatef(30, 0.0, 1.0, 0.0);

            glPushMatrix();

                glScalef(0.5, 0.5, 2);

                set_c(0.25, 0.25, 0.25);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

            glTranslatef(0, 0, 2);

            glPushMatrix();

                glScalef(0.18, 0.18, 0.18);

                if(catching_turtle)
                    set_c(1, 0, 0, 0.5);
                else if(can_catch)
                    set_c(0, 1, 0, 0.5);
                else
                    set_c(0, 1, 1, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_sphere(sphere);

            glPopMatrix();

            glPushMatrix();

                if(catching_turtle)
                    glScalef(size, size, 0.3);
                else
                    glScalef(size, size, 0.3);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                // glutSolidTorus(0.25, 2, 30, 50);

            glPopMatrix();

            glPushMatrix();

                if(catching_turtle)
                {
                    glScalef(size / 3, size / 3, my_distance(get_hand(), turtle->position));

                    set_c(1, 0, 0, 0.5);
                }
                else if(can_catch)
                {
                    glScalef(size / 3, size / 3, my_distance(get_hand(), turtle->position));

                    set_c(0, 1, 0, 0.5);
                }
                else
                {
                    glScalef(size / 3, size / 3, 100);

                    set_c(0, 1, 1, 0.5);
                }

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

            // float m[16];

            // glGetFloatv(GL_MODELVIEW_MATRIX, m);

            // for(int i = 0; i < 4 ; i++)
            // {
            //     for(int j = 0; j < 4 ; j++)
            //     {
            //         cout << m[i * 4 + j] << " ";
            //     }

            //     cout << endl;
            // }cout << "--------------------" << endl;

    glPopMatrix();
}

void ROV::draw_left_arm(float lit2_angle, float lit2_angle_y, bool enable_lit2, GLUquadric *sphere, GLUquadric *cylind)
{
    double size = 0.25;

    glPushMatrix();

        glTranslatef(2.5, -2, 5);

            glPushMatrix();

                glScalef(0.25, 0.25, 0.25);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_sphere(sphere);

            glPopMatrix();

            // glRotatef(15, 1.0, 0.0, 0.0);

            glRotatef(30, 0.0, 1.0, 0.0);

            glPushMatrix();

                glScalef(0.5, 0.5, 2);

                set_c(0.25, 0.25, 0.25);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

            glTranslatef(0, 0, 2);

            // glPushMatrix();

            //     glScalef(0.25, 0.25, 0.25);

            //     glColor3f(0.5, 0.5, 0.5);

                // draw_sphere(sphere);

            // glPopMatrix();

            glPushMatrix();

                glScalef(0.125, 0.125, 0.3);

                set_c(0.5, 0.5, 0.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                // glutSolidTorus(0.25, 2, 30, 50);

            glPopMatrix();

            // glRotatef(0, 1.0, 0.0, 0.0);

            glRotatef(-30, 0.0, 1.0, 0.0);

            glPushMatrix();

                glScalef(0.5, 0.5, 2);

                set_c(0.25, 0.25, 0.25);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_cylinder(cylind);

            glPopMatrix();

            glTranslatef(0, 0, 2);

            glPushMatrix();

                glScalef(0.12, 0.12, 0.12);

                set_c(0.25, 0.25, 0.25);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                glRotatef(lit2_angle_y, 1.0, 0.0, 0.0);

                glRotatef(lit2_angle, 0.0, 1.0, 0.0);

                draw_sphere(sphere);

                glTranslatef(0, 0, 2);

                static float emission[] = {1.0, 1.0, 1.0};

                static float black[] = {0, 0, 0};

                if(enable_lit2)
                    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
                else
                    glMaterialfv(GL_FRONT, GL_EMISSION, black);

                set_c(1, 1, 1);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                set_c(0.4, 0.4,  0.4);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

                draw_sphere(sphere);

                glMaterialfv(GL_FRONT, GL_EMISSION, black);

            glPopMatrix();

    glPopMatrix();
}

void ROV::draw_camera(GLUquadric *sphere, GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(0, 4.5, 6.5);

        glScalef(0.05, 0.05, 0.05);

        glPushMatrix();

            glScalef(0.75, 0.75, 0.75);

            set_c(0, 0, 0);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

            set_c(0.4, 0.4, 0.4);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

            draw_sphere(sphere);

        glPopMatrix();

        glPushMatrix();

            set_c(0, 0, 0, 0.5);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

            set_c(0.4, 0.4, 0.4);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

            draw_sphere(sphere);

        glPopMatrix();

    glPopMatrix();
}

void ROV::draw_plant(GLUquadric *sphere, GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(-2.5, 5, 4);

        glRotatef(-90, 0, 1, 0);

        glRotatef(-45, 1, 0, 0);

        glScalef(0.5, 0.5, 0.5);

        draw_cao(cylind);

    glPopMatrix();
}

void ROV::draw(TURTLE *turtle, float lit2_angle, float lit2_angle_y, bool enable_lit2, GLUquadric *sphere, GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(position[0], position[1], position[2]);

        glRotatef(angle, 0.0, 1.0, 0.0);

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

        for(auto &s: structure)
        {
            set_c(s[0], s[1], s[2]);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

            set_c(0.6, 0.6, 0.6);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

            draw_structure(s[3], s[4], s[5],
                            s[6], s[7], s[8]);
        }

        draw_back_propeller(sphere, cylind);

        draw_down_propeller(sphere, cylind);

        draw_right_propeller(sphere, cylind);

        draw_left_propeller(sphere, cylind);

        draw_right_arm(turtle, sphere, cylind);

        draw_left_arm(lit2_angle, lit2_angle_y, enable_lit2, sphere, cylind);

        draw_camera(sphere, cylind);

        set_c(0.0, 0.0, 0.0);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 16);

        draw_plant(sphere, cylind);

    glPopMatrix();
}

bool ROV::is_too_close_to_turtle(TURTLE *turtle)
{
    if(catching_turtle)
        return false;

    if( turtle->position[1] > position[1] + 5 || turtle->position[1] < position[1] - 8 )
        return false;

    if(my_distance(position, turtle->position) < 20)
        return true;

    return false;
}

int ROV::is_too_close_to_rock(vector<ROCK*> rocks)
{
    update_coord_max_min();

    for(int r = 0 ; r < rocks.size() ; r++)
    {
        rocks[r]->update_coord_max_min();

        bool collision = true;

        for(int i = 0; i < 3; i++)
        {
            if( coord_max_min[i].first  < rocks[r]->coord_max_min[i].second ||
                coord_max_min[i].second > rocks[r]->coord_max_min[i].first
            )
                collision = false;
        }

        if(collision)
            return r;
    }

    return -1;
}

void ROV::avoid_collision(TURTLE *turtle, vector<ROCK*> rocks)
{
    if(is_too_close_to_turtle(turtle))
    {
        vector<double> to_turtle = {
            turtle->position[0] - position[0],
            turtle->position[1] - position[1],
            turtle->position[2] - position[2]
        };

        speed[0] = -speed[0];
        speed[1] = -speed[1];
        speed[2] = -speed[2];

        position[0] = position[0] - to_turtle[0] * 0.01;
        position[1] = position[1] - to_turtle[1] * 0.01;
        position[2] = position[2] - to_turtle[2] * 0.01;

        return;
    }

    int rock_index = is_too_close_to_rock(rocks);

    if(rock_index > -1)
    {
        auto rock = rocks[rock_index];

        vector<double> to_rock = {
            rock->position[0] - position[0],
            rock->position[1] - position[1],
            rock->position[2] - position[2]
        };

        speed[0] = -speed[0];
        speed[1] = -speed[1];
        speed[2] = -speed[2];

        position[0] = position[0] - to_rock[0] * 0.01;
        position[1] = position[1] - to_rock[1] * 0.01;
        position[2] = position[2] - to_rock[2] * 0.01;
    }
}

void ROV::move(TURTLE *turtle, vector<ROCK*> rocks, set<int> pressing, float lit2_angle, float lit2_angle_y, float lit2_exponent, float lit2_cutoff, float lit1_diffuse[])
{
    // for(int i = 0; i < 3; i++)
    //     if(speed[i] > 0)
    //         acceleration[i] = -0.05;
    //     else if(speed[i] < 0)
    //         acceleration[i] =  0.05;
    //     else
    //         acceleration[i] = 0;

    // for(auto &key: pressing)
    // {
    //     switch(key)
    //     {
    //         case 'w':

    //             acceleration[0] += 0.07;

    //             acc[0] = true;

    //             break;

    //         case 's':

    //             acceleration[0] += -0.07;

    //             acc[0] = true;

    //             break;

    //         case 'a':
    //             angle += 2;

    //             if(angle > 360)
    //                 angle -= 360;

    //             blade_angle[3] += 20;

    //             if(blade_angle[3] > 360)
    //                 blade_angle[3] -= 360;

    //             facing[0] = sin(angle * 3.14159 / 180);
    //             facing[1] = facing[1];
    //             facing[2] = cos(angle * 3.14159 / 180);

    //             break;

    //         case 'd':
    //             angle -= 2;

    //             if(angle < 0)
    //                 angle += 360;

    //             blade_angle[4] -= 20;

    //             if(blade_angle[4] < 0)
    //                 blade_angle[4] += 360;

    //             facing[0] = sin(angle * 3.14159 / 180);
    //             facing[1] = facing[1];
    //             facing[2] = cos(angle * 3.14159 / 180);

    //             break;

    //         case 'q':

    //             acceleration[1] += 0.07;

    //             acc[1] = true;

    //             break;

    //         case 'e':

    //             acceleration[1] += -0.07;

    //             acc[1] = true;

    //             break;

    //         case ' ':
    //         case 'c':

    //             acceleration[2] += 0.07;

    //             acc[2] = true;

    //             break;

    //         case 'z':
    //         case 112:

    //             acceleration[2] += -0.07;

    //             acc[2] = true;

    //             break;

    //         case 'h':
    //             lit2_angle += 2;

    //             break;

    //         case 'l':
    //             lit2_angle -= 2;

    //             break;

    //         case 'k':
    //             lit2_angle_y -= 2;

    //             break;

    //         case 'j':
    //             lit2_angle_y += 2;

    //             break;

    //         case 'n':
    //             lit2_exponent -= 0.5;

    //             break;

    //         case 'm':
    //             lit2_exponent += 0.5;

    //             break;

    //         case '<':
    //             lit2_cutoff -= 2;

    //             break;

    //         case '>':
    //             lit2_cutoff += 2;

    //             break;
    //     }
    // }

    if(lit2_exponent > 128)
        lit2_exponent = 128;
    else if(lit2_exponent < 0)
        lit2_exponent = 0;

    if(lit2_cutoff > 90)
        lit2_cutoff = 90;
    else if(lit2_cutoff < 10)
        lit2_cutoff = 10;

    if(lit1_diffuse[0] > 1.0)
        lit1_diffuse[0] = 1.0;
    else if(lit1_diffuse[0] < 0.0)
        lit1_diffuse[0] = 0.0;

    if(lit1_diffuse[1] > 1.0)
        lit1_diffuse[1] = 1.0;
    else if(lit1_diffuse[1] < 0.0)
        lit1_diffuse[1] = 0.0;

    if(lit1_diffuse[2] > 1.0)
        lit1_diffuse[2] = 1.0;
    else if(lit1_diffuse[2] < 0.0)
        lit1_diffuse[2] = 0.0;

    if(lit2_angle < 0)
        lit2_angle += 360;
    else if(lit2_angle > 360)
        lit2_angle -= 360;

    if(lit2_angle_y < 0)
        lit2_angle_y += 360;
    else if(lit2_angle_y > 360)
        lit2_angle_y -= 360;

    for(int i = 0; i < 3; i++)
    {
        speed[i] += acceleration[i];

        if(speed[i] > 4)
            speed[i] = 4;
        else if(speed[i] < -4)
            speed[i] = -4;
        else if(!acc[i] && speed[i] < 0.05 && speed[i] > -0.05)
            speed[i] = 0;
    }

    acc[0] = false;
    acc[1] = false;
    acc[2] = false;

    for(int i = 0; i < 3; i++)
    {
        blade_angle[i] += speed[i] * 10;

        if(blade_angle[i] > 360)
            blade_angle[i] -= 360;
        else if(blade_angle[i] < 0)
            blade_angle[i] += 360;
    }

    position[0] += facing[0] * speed[0];
    position[1] += facing[1] * speed[0];
    position[2] += facing[2] * speed[0];

    position[0] += facing[2] * speed[1];
    position[1] -= 0;
    position[2] -= facing[0] * speed[1];

    position[0] += 0;
    position[1] += speed[2];
    position[2] += 0;

    if(position[0] < -2000 || position[0] > 2000 || position[2] < -2000 || position[2] > 2000)
    {
        speed[0] = -speed[0];
        speed[1] = -speed[1];
    }

    if(position[0] < -2000)
        position[0] = -2000;
    else if(position[0] > 2000)
        position[0] = 2000;
    if(position[2] < -2000)
        position[2] = -2000;
    else if(position[2] > 2000)
        position[2] = 2000;

    if(position[1] < 5 || position[1] > 200)
        speed[2] = -speed[2];

    if(position[1] < 5)
        position[1] = 5;
    else if(position[1] > 200)
        position[1] = 200;

    avoid_collision(turtle, rocks);
}

void ROV::catch_turtle(TURTLE *turtle)
{
    if(!can_catch)
        return;

    catching_turtle = true;

    turtle->can_move = false;

    catching_vector = {
        turtle->position[0] - get_hand()[0],
        turtle->position[1] - get_hand()[1],
        turtle->position[2] - get_hand()[2]
    };

    catching_angle = angle;
}

void ROV::move_turtle(TURTLE *turtle)
{
    // if(!catching_turtle)
    //     return;

    vector<double> new_vector = {
            cos((angle - catching_angle) * 3.14159 / 180) * catching_vector[0] + sin((angle - catching_angle) * 3.14159 / 180) * catching_vector[2],
            catching_vector[1],
        -sin((angle - catching_angle) * 3.14159 / 180) * catching_vector[0] + cos((angle - catching_angle) * 3.14159 / 180) * catching_vector[2]
    };

    catching_vector = new_vector;

    new_vector = {
            cos((angle - catching_angle) * 3.14159 / 180) * turtle->facing[0] + sin((angle - catching_angle) * 3.14159 / 180) * turtle->facing[2],
            turtle->facing[1],
        -sin((angle - catching_angle) * 3.14159 / 180) * turtle->facing[0] + cos((angle - catching_angle) * 3.14159 / 180) * turtle->facing[2]
    };

    turtle->facing = new_vector;
    turtle-> angle = turtle-> angle + angle - catching_angle;

    catching_angle = angle;

    turtle->position[0] = get_hand()[0] + catching_vector[0];
    turtle->position[1] = get_hand()[1] + catching_vector[1];
    turtle->position[2] = get_hand()[2] + catching_vector[2];
}

void ROV::control_turtle(TURTLE *turtle, bool in)
{
    if(!catching_turtle)
        return;

    for(int i = 0; i < 3; i++)
        if( in && my_distance(position, turtle->position) - (turtle->size / 2) >= 20)
            catching_vector[i] -= facing[i];
        else if( !in && my_distance(position, turtle->position) - (turtle->size / 2) <= 100)
            catching_vector[i] += facing[i];
}

void ROV::release_turtle(TURTLE *turtle)
{
    if(!catching_turtle)
        return;

    catching_turtle = false;

    turtle->can_move = true;
}