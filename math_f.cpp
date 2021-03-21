#include "math_f.hpp"
#include "ROV.hpp"
#include "TURTLE.hpp"

template <typename T>
T my_distance(vector<T> a, vector<T> b)
{
    T ret = 0;

    for(int i = 0; i < a.size(); ++i)
    {
        ret += (a[i] - b[i]) * (a[i] - b[i]);
    }

    return sqrt(ret);
}

double point_to_surface_distance(vector<double> facing, vector<double> origin, vector<double> point)
{
    vector<double> ret;

    double len = my_distance(facing, {0, 0, 0});

    if(len == 0)
    {
        cout << "BROKEN" << endl;

        return 0;
    }

    facing[0] /= len;
    facing[1] /= len;
    facing[2] /= len;

    vector<double> r = {
        point[0] - origin[0],
        point[1] - origin[1],
        point[2] - origin[2]
    };

    return facing[0] * r[0] + facing[1] * r[1] + facing[2] * r[2];
}

vector<double> map_to_surface(ROV *rov, vector<double> facing, vector<double> origin, vector<double> point, bool show_shadow_points)
{
    vector<double> ret;

    double len = my_distance(facing, {0, 0, 0});

    if(len == 0)
    {
        cout << "BROKEN" << endl;

        return {0, 0, 0};
    }

    facing[0] /= len;
    facing[1] /= len;
    facing[2] /= len;

    vector<double> r = {
        point[0] - origin[0],
        point[1] - origin[1],
        point[2] - origin[2]
    };

    double inner = facing[0] * r[0] + facing[1] * r[1] + facing[2] * r[2];

    ret = {
        point[0] - facing[0] * inner,
        point[1] - facing[1] * inner,
        point[2] - facing[2] * inner,
    };

    glPushMatrix();

        if(show_shadow_points)
        {
            glTranslatef(ret[0], ret[1], 0);

            float c[4] = {0, 0, 0, 0.5};

            if(rov->catching_turtle)
            {
                c[0] = 1; c[1] = 0; c[2] = 0;
            }
            else if(rov->can_catch)
            {
                c[0] = 0; c[1] = 1; c[2] = 0;
            }
            else
            {
                c[0] = 1; c[1] = 1; c[2] = 1;
            }

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

            float black[4] = {0, 0, 0, 1};

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            glScalef(0.5, 0.5, 0.5);

            draw_cube();
        }

    glPopMatrix();

    return ret;
}

bool in_rectangle(ROV *rov, TURTLE *turtle, vector<double> origin, vector<vector<double>> points, vector<double> turtle_point)
{
    if(my_distance(origin, turtle_point) - (turtle->size / 2) > 100)
        return false;

    vector<double> to_turtle = {
        turtle_point[0] - origin[0],
        turtle_point[1] - origin[1],
        turtle_point[2] - origin[2],
    };

    if( rov->facing[0] * to_turtle[0] + rov->facing[1] * to_turtle[1] + rov->facing[2] * to_turtle[2] < 0)
        return false;

    double y_min, y_max, y;

    y = y_min = y_max = points[0][1];

    vector<vector<double>> side1, side2;

    for(auto &p : points)
    {
        if(p[1] < y_min)
            y_min = p[1];
        else if(p[1] > y_max)
            y_max = p[1];

        if(p[1] == y)
            side1.push_back(p);
        else
            side2.push_back(p);
    }

    if(origin[1] > y_max || origin[1] < y_min)
        return false;

    vector<double> v = {
        points[0][0] - origin[0],
        points[0][1] - origin[1],
        points[0][2] - origin[2]
    };

    bool flag = (v[0] > 0)? true : false;

    for(auto &p: side1)
    {
        v = {p[0] - origin[0], p[1] - origin[1], p[2] - origin[2]};

        bool tmp = (v[0] >= 0)? true : false;

        if(tmp != flag)
            return true;
    }

    return false;
}

void check_catch(ROV *rov, TURTLE *turtle, bool show_shadow_points)
{
    vector<vector<double>> on_face;
    vector<double> hand;

    bool result = false;

    hand = rov->get_hand();

   vector<vector<double>> target = turtle->get_body();

    for(auto & p: target)
    {
        glPushMatrix();

            if(show_shadow_points)
            {
                glTranslatef(p[0], p[1], p[2]);

                float c[4] = {0, 0, 0, 0.5};

                if(rov->catching_turtle)
                {
                    c[0] = 1; c[1] = 0; c[2] = 0;
                }
                else if(rov->can_catch)
                {
                    c[0] = 0; c[1] = 1; c[2] = 0;
                }
                else
                {
                    c[0] = 1; c[1] = 1; c[2] = 1;
                }

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

                float black[4] = {0, 0, 0, 1};

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

                glScalef(0.5, 0.5, 0.5);

                draw_cube();
            }

        glPopMatrix();
    }

    glPushMatrix();

        if(show_shadow_points)
        {
            glTranslatef(hand[0], hand[1], 0);

            float c[4] = {0, 0, 0, 0.5};

            if(rov->catching_turtle)
            {
                c[0] = 1; c[1] = 0; c[2] = 0;
            }
            else if(rov->can_catch)
            {
                c[0] = 0; c[1] = 1; c[2] = 0;
            }
            else
            {
                c[0] = 1; c[1] = 1; c[2] = 1;
            }

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

            float black[4] = {0, 0, 0, 1};

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            glScalef(0.5, 0.5, 0.5);

            draw_cube();
        }

    glPopMatrix();

    for(auto &p: target)
    {
        vector<double> m = map_to_surface(
            rov,
            rov->facing,
            hand,
            p,
            show_shadow_points
        );

        on_face.push_back({m[0], m[1], m[2]});

        // if(show_shadow_points)
        // {
        //     glPushMatrix();

        //         glTranslatef(m[0], m[1], m[2]);

        //         glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

        //         if(rov->catching_turtle)
        //             glColor4f(1, 0, 0, 0.5);
        //         else if(rov->can_catch)
        //             glColor4f(0, 1, 0, 0.5);
        //         else
        //             glColor4f(1, 1, 1, 0.5);

        //         glScalef(0.5, 0.5, 0.5);

        //         draw_cube();

        //     glPopMatrix();
        // }

        if(in_rectangle(rov, turtle, hand, on_face, turtle->position))
            result = true;
    }

    if(result)
    {
        rov->can_catch = true;
    }
    else
    {
        rov->can_catch = false;
    }

}

vector<double> calc_real_position(vector<double> origin, double x, double y, double z, vector<double> facing)
{
    return {
        origin[0] + facing[2] * x + facing[0] * z,
        origin[1] + y,
        origin[2] - facing[0] * x + facing[2] * z
    };
}

vector<float> calc_normal(vector<float> a, vector<float> b, vector<float> c, vector<float> d)
{
    vector<float> v1 = { b[0] - a[0], b[1] - a[1], b[2] - a[2] };
    vector<float> v2 = { d[0] - c[0], d[1] - c[1], d[2] - c[2] };

    return {
        v1[1] * v2[2] - v1[2] * v2[1],
        -(v1[0] * v2[2] - v1[2] * v2[0]),
        v1[0] * v2[1] - v1[1] * v2[0],
    };
}

vector<float> calc_normal(vector<float> a, vector<float> b, vector<float> c)
{
    return calc_normal(a, b, b, c);
}