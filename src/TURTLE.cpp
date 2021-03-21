#include "TURTLE.hpp"

TURTLE::TURTLE()
{
    // position = {48, 5, 49};
    position = {30, 15, 0};
    facing = {0, 0, -1};

    y_movement = 0;

    double len = my_distance(facing, {0, 0, 0});

    facing[0] /= len;
    facing[1] /= len;
    facing[2] /= len;

    // auto calc angle for facing
    angle = asin(facing[0]) * 180 / M_PI;

    // fix arcsin duplicate value of two angle
    if(facing[2] < 0)
        angle += 180 - angle * 2;

    timer = 0;

    can_move = true;

    size = 3;

    update_coord_max_min();

    gen = default_random_engine(rd());

    dis_angle = uniform_real_distribution<double> (0, 360);
    dis_y = uniform_real_distribution<double> (0, 1);
    dis_timer = uniform_int_distribution<int> (100, 200);
}

vector<vector<double>> TURTLE::get_body()
{
    return {
        // body
        calc_real_position(position, -size * 3 / 2,  size * 1 / 2,  size * 3 / 2, facing),
        calc_real_position(position,  size * 3 / 2,  size * 1 / 2,  size * 3 / 2, facing),
        calc_real_position(position,  size * 3 / 2,  size * 1 / 2, -size * 3 / 2, facing),
        calc_real_position(position, -size * 3 / 2,  size * 1 / 2, -size * 3 / 2, facing),
        calc_real_position(position, -size * 3 / 2, -size * 1 / 2,  size * 3 / 2, facing),
        calc_real_position(position,  size * 3 / 2, -size * 1 / 2,  size * 3 / 2, facing),
        calc_real_position(position,  size * 3 / 2, -size * 1 / 2, -size * 3 / 2, facing),
        calc_real_position(position, -size * 3 / 2, -size * 1 / 2, -size * 3 / 2, facing),

        //head
        calc_real_position(position, -size / 2,  size * 1 / 2,  size / 2 + size * 2, facing),
        calc_real_position(position,  size / 2,  size * 1 / 2,  size / 2 + size * 2, facing),
        calc_real_position(position,  size / 2,  size * 1 / 2, -size / 2 + size * 2, facing),
        calc_real_position(position, -size / 2,  size * 1 / 2, -size / 2 + size * 2, facing),
        calc_real_position(position, -size / 2, -size * 1 / 2,  size / 2 + size * 2, facing),
        calc_real_position(position,  size / 2, -size * 1 / 2,  size / 2 + size * 2, facing),
        calc_real_position(position,  size / 2, -size * 1 / 2, -size / 2 + size * 2, facing),
        calc_real_position(position, -size / 2, -size * 1 / 2, -size / 2 + size * 2, facing),
    };
}

void TURTLE::update_coord_max_min()
{
    vector<vector<double>> coords = get_body();

    coord_max_min = {
        make_pair(coords[0][0], coords[0][0]),
        make_pair(coords[0][1], coords[0][1]),
        make_pair(coords[0][2], coords[0][2]),
    };

    for(int i = 1 ; i < coords.size() ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            if(coords[i][j] > coord_max_min[j].first)
                coord_max_min[j].first  = coords[i][j];
            else if(coords[i][j] < coord_max_min[j].second)
                coord_max_min[j].second = coords[i][j];
        }
    }
}

int TURTLE::is_too_close_to_rock(vector<ROCK*> rocks)
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

bool TURTLE::avoid_collision(vector<ROCK*> rocks)
{
    int rock_index = is_too_close_to_rock(rocks);

    if(rock_index > -1)
    {
        auto rock = rocks[rock_index];

        vector<double> to_rock = {
            rock->position[0] - position[0],
            rock->position[1] - position[1],
            rock->position[2] - position[2]
        };

        position[0] = position[0] - to_rock[0] * 0.05;
        position[1] = position[1] - to_rock[1] * 0.05;
        position[2] = position[2] - to_rock[2] * 0.05;

        return true;
    }

    return false;
}

void TURTLE::draw(float lit1_diffuse[], bool enable_lit1)
{
    glPushMatrix();

        glTranslatef(position[0], position[1], position[2]);

        glRotatef(angle, 0.0, 1.0, 0.0);

        glScalef(size, size, size);

        float emission[] = {lit1_diffuse[0] * 10, lit1_diffuse[1] * 10, lit1_diffuse[2] * 10};

        static float black[] = {0, 0, 0};

        if(enable_lit1)
            glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        else
            glMaterialfv(GL_FRONT, GL_EMISSION, black);

        // body
        glPushMatrix();

            glScalef(3, 1, 3);

            static float cb[4] = {0.075, 0.125, 0.075, 1};

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cb);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();

        glMaterialfv(GL_FRONT, GL_EMISSION, black);

        // head
        glPushMatrix();

            glTranslatef(0, 0, 2);

            glScalef(1, 1, 1);

            static float ch[4] = {0.15, 0.25, 0.15, 1};

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();

        // legs
        glPushMatrix();

            glTranslatef(-1.5, 0, 0.75);

            glRotatef(-90, 0.0, 1.0, 0.0);

            glScalef(0.5, 0.1, 1.5);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();
        glPushMatrix();

            glTranslatef(-1.5, 0, -0.75);

            glRotatef(-90, 0.0, 1.0, 0.0);

            glScalef(0.5, 0.1, 1.5);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();
        glPushMatrix();

            glTranslatef(1.5, 0, 0.75);

            glRotatef(90, 0.0, 1.0, 0.0);

            glScalef(0.5, 0.1, 1.5);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();
        glPushMatrix();

            glTranslatef(1.5, 0, -0.75);

            glRotatef(90, 0.0, 1.0, 0.0);

            glScalef(0.5, 0.1, 1.5);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();

        //tail
        glPushMatrix();

            glTranslatef(0, -0.25, -1.5);

            glRotatef(-25, 1.0, 0.0, 0.0);

            glScalef(0.25, 0.14, 1);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ch);

            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

            draw_cube();

        glPopMatrix();

    glPopMatrix();
}

void TURTLE::move(vector<ROCK*> rocks)
{
    if(can_move)
    {
        if(timer <= 0 || avoid_collision(rocks))
        {
            angle = dis_angle(gen);

            facing[0] = sin(angle * M_PI / 180);
            facing[1] = facing[1];
            facing[2] = cos(angle * M_PI / 180);

            timer = dis_timer(gen);
        }
        else
            timer--;

        if(timer_y <= 0 || avoid_collision(rocks))
        {
            double choice = dis_y(gen);

            if(choice < 0.2)
                y_movement = -0.25;
            else if(choice > 0.8)
                y_movement = 0.25;
            else
                y_movement = 0;

            timer_y = dis_timer(gen);
        }
        else
            timer_y--;

        position[0] += facing[0] * 0.25;
        position[1] += facing[1] * 0.25 + y_movement;
        position[2] += facing[2] * 0.25;

        if(position[0] < -2000)
            position[0] = -2000;
        else if(position[0] > 2000)
            position[0] = 2000;
        if(position[2] < -2000)
            position[2] = -2000;
        else if(position[2] > 2000)
            position[2] = 2000;

        if(position[1] < 3)
            position[1] = 3;
        else if(position[1] > 199)
            position[1] = 199;
    }
}