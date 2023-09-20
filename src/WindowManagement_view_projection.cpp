#include "WindowManagement.hpp"
#include "draw_f.hpp"

void WindowManagement::make_view(int scene)
{

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // gluLookAt(0.0, 50.0, 0.0,
    //           10.0, 50.0, 10.0,
    //           0.0, 1.0, 0.0);

    // return;

    switch (scene)
    {
        case FIRST:

            gluLookAt(this->entity_handler->rov->position[0] + this->entity_handler->rov->facing[0] * 6, this->entity_handler->rov->position[1] , this->entity_handler->rov->position[2] + this->entity_handler->rov->facing[2] * 6,
                      this->entity_handler->rov->position[0] + this->entity_handler->rov->facing[0] * 7, this->entity_handler->rov->position[1] + this->entity_handler->rov->facing[1] * 7 , this->entity_handler->rov->position[2] + this->entity_handler->rov->facing[2] * 7,
                      0.0, 1.0, 0.0);

            // gluLookAt(this->entity_handler->rov->position[0], this->entity_handler->rov->position[1] + 30, this->entity_handler->rov->position[2],
            //           this->entity_handler->rov->position[0], this->entity_handler->rov->position[1], this->entity_handler->rov->position[2],
            //           this->entity_handler->rov->facing[0], this->entity_handler->rov->facing[1], this->entity_handler->rov->facing[2]);

            break;

        // case SECOND:

        //     gluLookAt(this->entity_handler->rov->position[0] + this->entity_handler->rov->facing[0] * 20, this->entity_handler->rov->position[1] + 5, this->entity_handler->rov->position[2] + this->entity_handler->rov->facing[2] * 20,
        //               this->entity_handler->rov->position[0], this->entity_handler->rov->position[1], this->entity_handler->rov->position[2],
        //               0.0, 1.0, 0.0);

            break;

        case THIRD:

            gluLookAt(this->entity_handler->rov->position[0] - this->entity_handler->rov->facing[0] * 20, this->entity_handler->rov->position[1] + 20, this->entity_handler->rov->position[2] - this->entity_handler->rov->facing[2] * 20,
                      this->entity_handler->rov->position[0], this->entity_handler->rov->position[1], this->entity_handler->rov->position[2],
                      0.0, 1.0, 0.0);

            break;

        case GOD:

            gluLookAt(60.0, 30.0, 60.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

            break;

        case INFO:
            break;

        default:

            gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

            break;
    }
}

void WindowManagement::make_projection(int scene)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch (scene)
    {
        case FIRST:

            gluPerspective(90.0, (double) width/ (double) height, 1.5, 400.0);

            break;

        // case SECOND:

        //     gluPerspective(90.0, (double) width/ (double) height, 1.5, 400.0);

        //     break;

        case THIRD:

            gluPerspective(90.0, (double) width/ (double) height, 1.5, 400.0);

            break;

        case GOD:

            gluPerspective(90.0, (double) width/ (double) height, 1.5, 400.0);

            break;

        case INFO:

            gluOrtho2D(0.0, info_width, 0.0, info_height);

            break;

        default:

            gluPerspective(90.0, (double) width/ (double) height, 1.5, 100.0);

            break;
    }

    glMatrixMode(GL_MODELVIEW);
}

void WindowManagement::make_scene(int scene)
{
    switch(scene)
    {
        case FIRST:
        // case SECOND:
        case THIRD:
        case GOD:
            draw_coord_sys(cylind);

            this->entity_handler->rov->draw(
                this->entity_handler->turtle,
                lit2_angle,
                lit2_angle_y,
                enable_lit2,
                sphere,
                cylind
            );

            this->entity_handler->turtle->draw(
                lit1_diffuse,
                enable_lit1
            );

            // for(auto &t: titanics)
            //     t->draw();

            for(auto &r: this->entity_handler->rocks)
                r->draw(textName, show_shadow_points);

            for(auto &s: this->entity_handler->straws)
                s->draw(cylind);

            draw_floor(horizon_distance, textName);

            glEnable(GL_TEXTURE_2D);

            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

            glBindTexture(GL_TEXTURE_2D, textName[3]);

            draw_billboard(25, 1000, this->entity_handler->rov->facing);

            glDisable(GL_TEXTURE_2D);

            glPushMatrix();

                glTranslatef(100, 0, 350);

                glEnable(GL_TEXTURE_2D);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

                glBindTexture(GL_TEXTURE_2D, textName[3]);

                draw_billboard(25, 1000, this->entity_handler->rov->facing);

                glDisable(GL_TEXTURE_2D);

            glPopMatrix();

            glPushMatrix();

                glTranslatef(500, 0, -100);

                glEnable(GL_TEXTURE_2D);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

                glBindTexture(GL_TEXTURE_2D, textName[3]);

                draw_billboard(25, 1000, this->entity_handler->rov->facing);

                glDisable(GL_TEXTURE_2D);

            glPopMatrix();

            glPushMatrix();

                glTranslatef(-150, 0, -450);

                glEnable(GL_TEXTURE_2D);

                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);

                glBindTexture(GL_TEXTURE_2D, textName[3]);

                draw_billboard(25, 1000, this->entity_handler->rov->facing);

                glDisable(GL_TEXTURE_2D);

            glPopMatrix();

            check_catch(
                this->entity_handler->rov,
                this->entity_handler->turtle,
                show_shadow_points
            );

            break;

        case INFO:
            glDisable(GL_LIGHTING);
            // glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);

            draw_info_background(info_width, info_height);
            show_info();

            glEnable(GL_LIGHTING);
            // glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);

            break;

        default:
            break;
    }
}

void WindowManagement::make_view_port(int scene)
{
    switch(scene)
    {
        case FIRST:
            glViewport(0, height/2, width/2, height/2);

            break;

        // case SECOND:

        //     break;

        case THIRD:
            glViewport(0, 0, width/2, height/2);

            break;

        case GOD:
            glViewport(width/2, height/2, width/2, height/2);

            break;

        case INFO:
            // glViewport(width/2, 0, width/2, height/2);
            glViewport(width - info_width, 0, info_width, info_height);

            break;

        default:
            glViewport(0, 0, width/2, height/2);

            break;
    }
}

void WindowManagement::make_light()
{
    static float lit_position[4] = {0.0, 1.0, 0.0, 0};
    static float lit1_position[4] = {0.0, 50.0, 0.0, 1};
    static float lit2_position[4] = {0.0, 50.0, 0.0, 1};
    static float lit2_direction[4] = {0.0, 50.0, 0.0, 1};
    static float tmp[4];
    static float tmp2[4];

    static double angle = 0.001;

    if(lit_position[1] < 0)
        angle = 0.003;
    else
        angle = 0.001;

    tmp[0] = cos(angle) * lit_position[0]
           - sin(angle) * lit_position[1]
           + 0 * lit_position[2];
    tmp[1] = sin(angle) * lit_position[0]
           + cos(angle) * lit_position[1]
           + 0 * lit_position[2];

    lit_position[0] = tmp[0];
    lit_position[1] = tmp[1];

    glEnable(GL_LIGHTING);      /* Turn on lighting */

    glLightfv(GL_LIGHT0, GL_POSITION, lit_position);

    lit1_position[0] = this->entity_handler->turtle->position[0];
    lit1_position[1] = this->entity_handler->turtle->position[1];
    lit1_position[2] = this->entity_handler->turtle->position[2];

    glLightfv(GL_LIGHT1, GL_POSITION, lit1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);

    vector<double> rov_pos = this->entity_handler->rov->get_left_hand();
    vector<double> rov_face = this->entity_handler->rov->facing;

    lit2_position[0] = rov_pos[0];
    lit2_position[1] = rov_pos[1];
    lit2_position[2] = rov_pos[2];

    tmp[0] = 0;
    tmp[1] = -sin((lit2_angle_y) * (3.14159 / 180));
    tmp[2] =  cos((lit2_angle_y) * (3.14159 / 180));

    lit2_direction[0] =   cos((this->entity_handler->rov->angle + lit2_angle) * (3.14159 / 180)) * tmp[0]
                        + 0                                             * tmp[1]
                        + sin((this->entity_handler->rov->angle + lit2_angle) * (3.14159 / 180)) * tmp[2];
    lit2_direction[1] =   0                                             * tmp[0]
                        + 1                                             * tmp[1]
                        + 0                                             * tmp[2];
    lit2_direction[2] = - sin((this->entity_handler->rov->angle + lit2_angle) * (3.14159 / 180)) * tmp[0]
                        + 0                                             * tmp[1]
                        + cos((this->entity_handler->rov->angle + lit2_angle) * (3.14159 / 180)) * tmp[2];

    glLightfv(GL_LIGHT2, GL_POSITION, lit2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lit2_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lit2_cutoff);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lit2_exponent);

    if(enable_lit0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);

    if(enable_lit1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);

    if(enable_lit2)
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);
}

void WindowManagement::render_scene(int scene)
{
    make_view(scene);

    make_projection(scene);

    make_view_port(scene);

    make_light();

    make_scene(scene);
}