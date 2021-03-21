#include "ROCK.hpp"

int ROCK::count = 0;

ROCK::ROCK()
{
    gen = default_random_engine(rd());

    dis_color = uniform_real_distribution<double> (-0.105, 0.105);
    dis_position = uniform_real_distribution<double> (-2000, 2000);
    dis_size = uniform_real_distribution<double> (0, 90);

    do
    {
        position = { dis_position(gen), 0, dis_position(gen) };
    }
    while(( position[0] > -200 && position[0] < 200 ) &&
            ( position[2] > -200 && position[2] < 200 )
    );

    // position = { -100, 0, -100 };

    size = {10 + dis_size(gen), 10 + dis_size(gen), 10 + dis_size(gen)};

    update_coord_max_min();

    color = {0.175 + dis_color(gen), 0.225 + dis_color(gen), 0.07 + dis_color(gen)};  // 0.105

    index = count++;
}

vector<vector<double>> ROCK::get_coord()
{
    return {
        calc_real_position(position, -size[0] * 1.050,  size[1] * 1.050,  size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position,  size[0] * 1.050,  size[1] * 1.050,  size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position,  size[0] * 1.050,  size[1] * 1.050, -size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position, -size[0] * 1.050,  size[1] * 1.050, -size[2] * 1.050, {0, 0, 1}),

        calc_real_position(position, -size[0] * 1.050, -size[1] * 1.050,  size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position,  size[0] * 1.050, -size[1] * 1.050,  size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position,  size[0] * 1.050, -size[1] * 1.050, -size[2] * 1.050, {0, 0, 1}),
        calc_real_position(position, -size[0] * 1.050, -size[1] * 1.050, -size[2] * 1.050, {0, 0, 1}),
    };
}

void ROCK::update_coord_max_min()
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
        {
            if(coords[i][j] > coord_max_min[j].first)
                coord_max_min[j].first  = coords[i][j];
            else if(coords[i][j] < coord_max_min[j].second)
                coord_max_min[j].second = coords[i][j];
        }
    }
}

void ROCK::test_draw_cube()
{
    static float normal[][4] = {{0.0, 0.0, -1.0}, {0.0, -1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {-1.0, 0.0, 0.0}};
    static float points[][3] = {
        {-1.0, 0.0, -1.0},
        {1.0, 0.0, -1.0},
        {1.0, 1.0, -1.0},
        {-1.0, 1.0, -1.0},
        {-1.0, 0.0, 1.0},
        {1.0, 0.0, 1.0},
        {1.0, 1.0, 1.0},
        {-1.0, 1.0, 1.0}
    };

    static int face[][4] = {{0, 3, 2, 1}, {0, 1, 5, 4}, {1, 2, 6, 5}, {4, 5, 6, 7}, {2, 3, 7, 6}, {0, 4, 7, 3}};

    int i;
    float range;

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    // glTranslatef(ds, dt, 0.0);
    glScalef(1.0, 3.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    for (i = 0; i < 6; i++)
    { /* draw the six faces one by one */
        range = 1.0;
        glNormal3fv(normal[i]);
        glBegin(GL_POLYGON); /* Draw the face */
        glTexCoord2f(0.0, 0.0);
        glVertex3fv(points[face[i][0]]);
        glTexCoord2f(0.0, range);
        glVertex3fv(points[face[i][1]]);
        glTexCoord2f(range, range);
        glVertex3fv(points[face[i][2]]);
        glTexCoord2f(range, 0.0);
        glVertex3fv(points[face[i][3]]);
        glEnd();
    }
}

void ROCK::draw(unsigned int textName[], bool show_shadow_points)
{
    static float black[4] = {0, 0, 0, 1};
    static float white[4] = {1, 1, 1, 1};

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

        glTranslatef(position[0], position[1], position[2]);

        glScalef(size[0], size[1], size[2]);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

        glBindTexture(GL_TEXTURE_2D, textName[1]);

        // glutSolidDodecahedron();

        test_draw_cube();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    if(show_shadow_points)
        for(auto &p: get_coord())
        {

            glPushMatrix();

                glTranslatef(p[0], p[1], p[2]);

                glScalef(2.5, 2.5, 2.5);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

                draw_cube();

            glPopMatrix();

        }
}