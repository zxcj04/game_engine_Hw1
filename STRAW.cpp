#include "STRAW.hpp"

int STRAW::count = 0;

STRAW::STRAW()
{
    gen = default_random_engine(rd());

    dis_color = uniform_real_distribution<float> (-0.105, 0.105);
    dis_position = uniform_real_distribution<float> (-200, 200);
    dis_size = uniform_real_distribution<float> (0, 5);

    position = { dis_position(gen), fabs(dis_position(gen)) / 2, dis_position(gen) };

    // position = { -100, 0, -100 };

    size = dis_size(gen);
    angle = dis_size(gen) * 18;

    color[0] = 0.175 + dis_color(gen);
    color[1] = 0.225 + dis_color(gen);
    color[2] = 0.07 + dis_color(gen);  // 0.105
    color[3] = 1;

    index = count++;
}

void STRAW::draw(GLUquadric *cylind)
{
    glPushMatrix();

        glTranslatef(position[0], position[1], position[2]);

        glRotatef(angle, 1.0, 0.0, 0.0);

        glRotatef(angle, 0.0, 1.0, 0.0);

        glScalef(size / 1.5, size / 1.5, size * 10);

        static float c2[4] = {0.3, 0.3, 0.3};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c2);

        draw_cylinder(cylind);

    glPopMatrix();
}

void STRAW::move()
{
    if(position[1] > 2)
        position[1] -= 0.2;

}