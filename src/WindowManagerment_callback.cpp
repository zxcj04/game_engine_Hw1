#include "WindowManagement.hpp"

void WindowManagement::keyboard_down(int key)
{
    // cout << (char) tolower(key) << endl;

    static double x, y;

    switch(key)
    {
        case GLFW_KEY_ESCAPE:  // ESC
            exit(0);

        case GLFW_KEY_G:
            delete this->entity_handler->rov;

            this->entity_handler->rov = new ROV();

            delete this->entity_handler->turtle;

            this->entity_handler->turtle = new TURTLE();

            for(auto &r: this->entity_handler->rocks)
            {
                delete r;

                r = new ROCK();
            }

            for(auto &s: this->entity_handler->straws)
            {
                delete s;

                s = new STRAW();
            }

            break;

        case GLFW_KEY_T:
            this->show_shadow_points = !this->show_shadow_points;

            break;

        case GLFW_KEY_Y:
            if(!this->entity_handler->rov->catching_turtle)
                this->entity_handler->turtle->can_move = !this->entity_handler->turtle->can_move;

            break;

        case GLFW_KEY_KP_ADD:
            if(this->entity_handler->turtle->size < 10)
                this->entity_handler->turtle->size += 1;

            break;

        case GLFW_KEY_KP_SUBTRACT:
            if(this->entity_handler->turtle->size > 1)
                this->entity_handler->turtle->size -= 1;

            break;

        case GLFW_KEY_KP_1:
            this->enable_lit0 = !this->enable_lit0;

            break;

        case GLFW_KEY_KP_2:
            this->enable_lit1 = !this->enable_lit1;

            break;

        case GLFW_KEY_KP_3:
            this->enable_lit2 = !this->enable_lit2;

            break;

        case GLFW_KEY_Q:
            this->enable_cursor = !this->enable_cursor;

            if(enable_cursor)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                glfwGetCursorPos(window, &x, &y);

                this->last_x = x;
                this->last_y = y;
            }
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            break;

        case GLFW_KEY_R:

            this->shader.load("./src/shaders/test.vert", "./src/shaders/test.frag");

            break;

        // case GLFW_KEY_LEFT_SHIFT:
        //     this->pressing.insert(112);

        //     break;


        // case '.':
        // case '>':
        //     this->pressing.insert('>');

        //     break;

        // case ',':
        // case '<':
        //     this->pressing.insert('<');

        //     break;

        // default:
        //     this->pressing.insert(tolower(key));

        //     break;
    }
}

void WindowManagement::keyboard_up(int key)
{
    switch(key)
    {

        // case '.':
        // case '>':
        //     pressing.erase('>');

        //     break;

        // case ',':
        // case '<':
        //     pressing.erase('<');

        //     break;

        // case GLFW_KEY_LEFT_SHIFT:
        //     this->pressing.erase(112);

        //     break;

        // default:
        //     this->pressing.erase(tolower(key));

        //     break;
    }
}

void WindowManagement::keyboard_repeat(int key)
{
    // switch(key)
    // {

    //     case GLFW_KEY_KP_4:
    //         this->lit1_diffuse[0] -= 0.005;

    //         break;

    //     case GLFW_KEY_KP_5:
    //         this->lit1_diffuse[1] -= 0.005;

    //         break;

    //     case GLFW_KEY_KP_6:
    //         this->lit1_diffuse[2] -= 0.005;

    //         break;

    //     case GLFW_KEY_KP_7:
    //         this->lit1_diffuse[0] += 0.005;

    //         break;

    //     case GLFW_KEY_KP_8:
    //         this->lit1_diffuse[1] += 0.005;

    //         break;

    //     case GLFW_KEY_KP_9:
    //         this->lit1_diffuse[2] += 0.005;

    //         break;

    //     default:
    //         this->pressing.erase(tolower(key));

    //         break;
    // }
}

void WindowManagement::check_keyboard_pressing()
{
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    {
        this->lit1_diffuse[0] -= 0.005;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
        this->lit1_diffuse[1] -= 0.005;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    {
        this->lit1_diffuse[2] -= 0.005;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
        this->lit1_diffuse[0] += 0.005;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    {
        this->lit1_diffuse[1] += 0.005;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    {
        this->lit1_diffuse[2] += 0.005;
    }

    for(int i = 0; i < 3; i++)
        if(this->entity_handler->rov->speed[i] > 0)
            this->entity_handler->rov->acceleration[i] = -0.05;
        else if(this->entity_handler->rov->speed[i] < 0)
            this->entity_handler->rov->acceleration[i] =  0.05;
        else
            this->entity_handler->rov->acceleration[i] = 0;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->entity_handler->rov->acceleration[0] += 0.07;

        this->entity_handler->rov->acc[0] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->entity_handler->rov->acceleration[0] += -0.07;

        this->entity_handler->rov->acc[0] = true;
    }

    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    // {
    //     this->entity_handler->rov->angle += 2;

    //     if(this->entity_handler->rov->angle > 360)
    //         this->entity_handler->rov->angle -= 360;

    //     this->entity_handler->rov->blade_angle[3] += 20;

    //     if(this->entity_handler->rov->blade_angle[3] > 360)
    //         this->entity_handler->rov->blade_angle[3] -= 360;

    //     this->entity_handler->rov->facing[0] = sin(this->entity_handler->rov->angle * 3.14159 / 180);
    //     this->entity_handler->rov->facing[1] = this->entity_handler->rov->facing[1];
    //     this->entity_handler->rov->facing[2] = cos(this->entity_handler->rov->angle * 3.14159 / 180);
    // }

    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    // {
    //     this->entity_handler->rov->angle -= 2;

    //     if(this->entity_handler->rov->angle < 0)
    //         this->entity_handler->rov->angle += 360;

    //     this->entity_handler->rov->blade_angle[4] -= 20;

    //     if(this->entity_handler->rov->blade_angle[4] < 0)
    //         this->entity_handler->rov->blade_angle[4] += 360;

    //     this->entity_handler->rov->facing[0] = sin(this->entity_handler->rov->angle * 3.14159 / 180);
    //     this->entity_handler->rov->facing[1] = this->entity_handler->rov->facing[1];
    //     this->entity_handler->rov->facing[2] = cos(this->entity_handler->rov->angle * 3.14159 / 180);
    // }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->entity_handler->rov->acceleration[1] += 0.07;

        this->entity_handler->rov->acc[1] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->entity_handler->rov->acceleration[1] += -0.07;

        this->entity_handler->rov->acc[1] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        this->entity_handler->rov->acceleration[2] += 0.07;

        this->entity_handler->rov->acc[2] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {

        this->entity_handler->rov->acceleration[2] += -0.07;

        this->entity_handler->rov->acc[2] = true;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        lit2_angle += 2;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        lit2_angle -= 2;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        lit2_angle_y -= 2;
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        lit2_angle_y += 2;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        lit2_exponent -= 0.5;
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        lit2_exponent += 0.5;
    }

    // case '<':
    //     lit2_cutoff -= 2;

    //     break;

    // case '>':
    //     lit2_cutoff += 2;

    //     break;
}


void WindowManagement::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(!this->enable_cursor)
        return;

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        if(!this->entity_handler->rov->catching_turtle)
            this->entity_handler->rov->catch_turtle(this->entity_handler->turtle);
        else
            this->entity_handler->rov->release_turtle(this->entity_handler->turtle);
    }

}

void WindowManagement::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(!this->enable_cursor)
        return;

    // cout << xoffset << " " << yoffset << endl;

    if (yoffset == 1)  // WHEEL UP
        this->entity_handler->rov->control_turtle(this->entity_handler->turtle, false);
    else if (yoffset == -1) //WHEEL DOWN
        this->entity_handler->rov->control_turtle(this->entity_handler->turtle, true);

}

void WindowManagement::cursor_callback(GLFWwindow * window, double x, double y)
{
    if(!this->enable_cursor)
        return;

    const float sensitivity = 0.15f;

    float x_offset = x - this->last_x;
    float y_offset = y - this->last_y;

    this->last_x = x;
    this->last_y = y;

    this->entity_handler->rov->angle -= x_offset * sensitivity;

    if(this->entity_handler->rov->angle > 360)
        this->entity_handler->rov->angle -= 360;

    if(x_offset < 0)
    {
        this->entity_handler->rov->blade_angle[3] += 20;

        if(this->entity_handler->rov->blade_angle[3] > 360)
            this->entity_handler->rov->blade_angle[3] -= 360;
    }
    else if(x_offset > 0)
    {
        this->entity_handler->rov->blade_angle[4] += 20;

        if(this->entity_handler->rov->blade_angle[4] > 360)
            this->entity_handler->rov->blade_angle[4] -= 360;
    }

    this->entity_handler->rov->facing[0] = sin(this->entity_handler->rov->angle * 3.14159 / 180);
    this->entity_handler->rov->facing[1] = this->entity_handler->rov->facing[1];
    this->entity_handler->rov->facing[2] = cos(this->entity_handler->rov->angle * 3.14159 / 180);
}

void WindowManagement::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        keyboard_down(key);
    // else if(action == GLFW_RELEASE)
    //     keyboard_up(key);
    // else if(action == GLFW_REPEAT)
    //     keyboard_repeat(key);
}

void WindowManagement::framebuffer_callback(GLFWwindow * w, int new_w, int new_h)
{
    this->width = new_w;
    this->height = new_h;

    this->info_width = this->width / 2;
    this->info_height = this->height / 2;
}