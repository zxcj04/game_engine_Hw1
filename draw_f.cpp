#include "draw_f.hpp"
#include "math_f.hpp"

class ROV;

void draw_sphere(GLUquadric *sphere)
{
    gluSphere(sphere, 2.0,   /* radius=2.0 */
              12,            /* composing of 12 slices*/
              12);           /* composing of 12 stacks */
}

void draw_cylinder(GLUquadric *cylind)
{
    gluCylinder(cylind,
                0.5, 0.5,         /* radius of top and bottom circle */
                1.0,              /* height of the cylinder */
                12,               /* use 12-side polygon approximating circle*/
                3);               /* Divide it into 3 sections */

}

void draw_cube()
{
    vector<float> vertices[] = {
        { 0.5, -0.5,  0.5},
        {-0.5, -0.5,  0.5},
        {-0.5,  0.5,  0.5},
        { 0.5,  0.5,  0.5},
        { 0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
        {-0.5,  0.5, -0.5},
        { 0.5,  0.5, -0.5},
    };

    vector<float> normal[] = {
        calc_normal(vertices[0], vertices[3], vertices[2]),
        calc_normal(vertices[0], vertices[4], vertices[7]),
        calc_normal(vertices[4], vertices[5], vertices[6]),
        calc_normal(vertices[1], vertices[2], vertices[6]),
        calc_normal(vertices[2], vertices[3], vertices[7]),
        calc_normal(vertices[0], vertices[1], vertices[5])
    };

    glNormal3fv( &(normal[0][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[0][0]) );
        glVertex3fv( &(vertices[3][0]) );
        glVertex3fv( &(vertices[2][0]) );
        glVertex3fv( &(vertices[1][0]) );
    glEnd();

    glNormal3fv( &(normal[1][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[0][0]) );
        glVertex3fv( &(vertices[4][0]) );
        glVertex3fv( &(vertices[7][0]) );
        glVertex3fv( &(vertices[3][0]) );
    glEnd();

    glNormal3fv( &(normal[2][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[4][0]) );
        glVertex3fv( &(vertices[5][0]) );
        glVertex3fv( &(vertices[6][0]) );
        glVertex3fv( &(vertices[7][0]) );
    glEnd();

    glNormal3fv( &(normal[3][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[1][0]) );
        glVertex3fv( &(vertices[2][0]) );
        glVertex3fv( &(vertices[6][0]) );
        glVertex3fv( &(vertices[5][0]) );
    glEnd();

    glNormal3fv( &(normal[4][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[2][0]) );
        glVertex3fv( &(vertices[3][0]) );
        glVertex3fv( &(vertices[7][0]) );
        glVertex3fv( &(vertices[6][0]) );
    glEnd();

    glNormal3fv( &(normal[5][0]) );

    glBegin(GL_POLYGON);
        glVertex3fv( &(vertices[0][0]) );
        glVertex3fv( &(vertices[1][0]) );
        glVertex3fv( &(vertices[5][0]) );
        glVertex3fv( &(vertices[4][0]) );
    glEnd();
}

void draw_blade_model()
{
    glBegin(GL_POLYGON);
        glVertex3f( 0.0,  0.0,  0.0);
        glVertex3f(-1.0, -1.0,  1.0);
        glVertex3f(-1.0,  1.0,  1.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f( 0.0,  0.0,  0.0);
        glVertex3f( 1.0,  1.0,  1.0);
        glVertex3f( 1.0, -1.0,  1.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f( 0.0,  0.0,  0.0);
        glVertex3f(-1.0,  1.0,  1.0);
        glVertex3f( 1.0,  1.0,  1.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f( 0.0,  0.0,  0.0);
        glVertex3f( 1.0, -1.0,  1.0);
        glVertex3f(-1.0, -1.0,  1.0);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3f( 1.0,  1.0,  1.0);
        glVertex3f(-1.0,  1.0,  1.0);
        glVertex3f(-1.0, -1.0,  1.0);
        glVertex3f( 1.0, -1.0,  1.0);
    glEnd();
}

void draw_blade(double size)
{
    glPushMatrix();

        glScalef(0.125, size / 3, size);

        draw_blade_model();

    glPopMatrix();
}

void draw_propeller(double angle, double size, GLUquadric *sphere)
{
    float white[4] = {1, 1, 1, 1};

    glPushMatrix();

        glScalef(0.25 / 3 * size, 0.25 / 3 * size, 0.25 / 3 * size);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

        float c[3] = {0.4, 0.4, 0.4};

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

        draw_sphere(sphere);

    glPopMatrix();

    glPushMatrix();

        float cc[4] = {1.0, 1.0, 0.5, 0.5};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cc);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

        glRotatef(90.0, 0.0, 1.0, 0.0);

        glRotatef(angle, 1.0, 0.0, 0.0);

        draw_blade(size);

        glRotatef(120.0, 1.0, 0.0, 0.0);

        draw_blade(size);

        glRotatef(120.0, 1.0, 0.0, 0.0);

        draw_blade(size);

    glPopMatrix();
}

void draw_billboard(double w, double h, vector<double> facing)
{
    glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0);
        glVertex3f(
            facing[2] * w,
            0,
            -facing[0] * w
        );

        glTexCoord2f(0.0, 1.0);
        glVertex3f(
            facing[2] * w,
            h,
            -facing[0] * w
        );

        glTexCoord2f(1.0, 1.0);
        glVertex3f(
            -facing[2] * w,
            h,
            facing[0] * w
        );

        glTexCoord2f(1.0, 0.0);
        glVertex3f(
            -facing[2] * w,
            0,
            facing[0] * w
        );

    glEnd();
}

void draw_floor(int dis, GLuint textName[])
{
    // int startx = max(-200.0, rov->position[0] / 10.0 + 1 - dis);
    // int endx   = min( 200.0, rov->position[0] / 10.0 + 1 + dis);

    // int startz = max(-200.0, rov->position[2] / 10.0 + 1 - dis);
    // int endz   = min( 200.0, rov->position[2] / 10.0 + 1 + dis);

    int startx = -200.0;
    int endx   = 200.0;

    int startz = -200.0;
    int endz   = 200.0;

    static float c[4] = {0.7, 0.7, 0.7, 1.0};

    glNormal3f(0,1,0);

    glEnable(GL_TEXTURE_2D);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

    glBindTexture(GL_TEXTURE_2D, textName[2]);

    glBegin(GL_POLYGON);

        glTexCoord2f(0.0, 0.0);

        glVertex3f(startx * 10.0, -2.2, startz * 10.0);

        glTexCoord2f(0.0, 20.0);

        glVertex3f(startx * 10.0, -2.2, endz * 10.0);

        glTexCoord2f(20.0, 20.0);

        glVertex3f(endx * 10.0, -2.2, endz * 10.0);

        glTexCoord2f(20.0, 0.0);

        glVertex3f(endx * 10.0, -2.2, startz * 10.0);

    glEnd();

    glDisable(GL_TEXTURE_2D);

    // int i, j;

    // int startx = max(-200.0, rov->position[0] / 10.0 + 1 - dis);
    // int endx   = min( 200.0, rov->position[0] / 10.0 + 1 + dis);

    // int startz = max(-200.0, rov->position[2] / 10.0 + 1 - dis);
    // int endz   = min( 200.0, rov->position[2] / 10.0 + 1 + dis);

    // glNormal3f(0,1,0);

    // float c1[4], c2[4], c3[4], c4[4];

    // c1[3] = 1;
    // c2[3] = 1;
    // c3[3] = 1;
    // c4[3] = 1;

    // for(i = startx ; i < endx ; i++)
    //     for(j = startz ; j < endz ; j++)
    //     {
    //         glBegin(GL_POLYGON);

    //             for(int k = 0 ; k < 3; k++)
    //                 c1[k] = color[i + 201][j + 201][k];

    //             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c1);

    //             glVertex3f(i * 10.0, -2.2, j * 10.0);

    //             for(int k = 0 ; k < 3; k++)
    //                 c2[k] = color[i + 201][j + 200][k];

    //             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c2);

    //             glVertex3f(i * 10.0, -2.2, (j - 1.0) * 10.0);

    //             for(int k = 0 ; k < 3; k++)
    //                 c3[k] = color[i + 200][j + 200][k];

    //             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c3);

    //             glVertex3f((i - 1.0) * 10.0, -2.2, (j - 1.0) * 10.0);

    //             for(int k = 0 ; k < 3; k++)
    //                 c4[k] = color[i + 200][j + 201][k];

    //             glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c4);

    //             glVertex3f((i - 1.0) * 10.0, -2.2, j * 10.0);

    //         glEnd();
    //     }
}

void draw_cao(GLUquadric *cylind)
{
    float black[4] = {0, 0, 0, 1};

    glPushMatrix();

        glScalef(1, 1, 10);

        glRotatef(-30, 1, 0, 0);

        glTranslatef(0, 0, 0.45);

        glRotatef(180, 0, 1, 0);

        static float c[4] = {0.0, 0.3, 0.0, 1.0};

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c);

        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);

        glTranslatef(0, 0, -0.45);

        // glutSolidCone(
        //     1, 1, 12, 12
        // );

        draw_cylinder(cylind);

    glPopMatrix();
}

void draw_coord_sys(GLUquadric *cylind)
{
    glPushMatrix();

        glPushMatrix();

            draw_cao(cylind);

        glPopMatrix();

        glPushMatrix();

            glRotatef(90.0, 0.0, 1.0, 0.0);

            draw_cao(cylind);

        glPopMatrix();

        glPushMatrix();

            glRotatef(215.0, 0.0, 1.0, 0.0);

            draw_cao(cylind);

        glPopMatrix();

        glPushMatrix();

            glRotatef(345.0, 0.0, 1.0, 0.0);

            draw_cao(cylind);

        glPopMatrix();

        glPushMatrix();

            glRotatef(-90.0, 1.0, 0.0, 0.0);

            draw_cao(cylind);

        glPopMatrix();

    glPopMatrix();
}

void draw_info_background(GLfloat info_width, GLfloat info_height)
{
    glColor3f(0.2, 0.2, 0.2);

    glBegin(GL_POLYGON);

        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, info_height);
        glVertex2f(info_width, info_height);
        glVertex2f(info_width, 0.0);

    glEnd();
}

void draw_speed_bar(int y, double billy, GLfloat info_width)
{
    double start = 9;
    double end   = min(info_width - 18.0, start + 400);

    double bar_height = 26;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);

        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(start, y - bar_height);

        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(start, y);

        glColor3f(1.0, (1.0 - 1.0 * billy), 0.0);
        glVertex2f(end - (end - start) * (1 - billy)  , y);

        glColor3f(1.0, (1.0 - 1.0 * billy), 0.0);
        glVertex2f(end - (end - start) * (1 - billy)  , y - bar_height);

    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);

        glVertex2f(start, y - bar_height);
        glVertex2f(start, y + 1);
        glVertex2f(end + 1  , y + 1);
        glVertex2f(end + 1  , y - bar_height);

    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}