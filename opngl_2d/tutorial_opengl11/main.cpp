//
//  main.cpp
//  tutorial_opengl
//
//  Created by 渥美 政廣 on 2014/06/12.
//  Copyright (c) 2014年 masahiro atsumi. All rights reserved.
//

#define GLFW_DLL

#include <GL/glfw.h>
#include <cstdlib>

#if defined (_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")
#endif


int main() {
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }
    
    if (!glfwOpenWindow(640, 480,
                        0, 0, 0,
                        0,
                        0, 0,
                        GLFW_WINDOW)) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    
    float max_speed = 0.05f;
    float accel = 0.001f;
    float vx = 0;
    
    float pos_x = 0.0f;
    float pos_y = 0.0f;

    while (glfwGetWindowParam(GLFW_OPENED)) {
        if (glfwGetKey(GLFW_KEY_ESC)) {
            break;
        }
        
        if (glfwGetKey('A') == GLFW_PRESS) {
//            pos_x -= 0.02f;
            vx += accel;
            pos_x -= vx;
        }
        if (glfwGetKey('D') == GLFW_PRESS) {
//            pos_x += 0.02f;
            vx += accel;
            pos_x += vx;
        }
        if (glfwGetKey('W') == GLFW_PRESS) {
            pos_y += 0.02f;
        }
        if (glfwGetKey('X') == GLFW_PRESS) {
            pos_y -= 0.02f;
        }
        
        
        vx -= accel * 0.7f;
        
        if (vx < 0.0f) {
            vx = 0.0f;
        }
        if (vx > max_speed) {
            vx = max_speed;
        }
        
        
        if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            int mouse_x, mouse_y;
            glfwGetMousePos(&mouse_x, &mouse_y);
            
            pos_x =   mouse_x * 2.0f / 640.0f - 1.0f;
            pos_y = -(mouse_y * 2.0f / 480.0f - 1.0f);
            
        }
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        const GLfloat vtx[] = {
            pos_x, pos_y,
        };
        
        glVertexPointer(2, GL_FLOAT, 0, vtx);
        glPointSize(5.0f);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, 1);
        glDisableClientState(GL_VERTEX_ARRAY);
        
        glfwSwapBuffers();
    }
    glfwTerminate();

    return EXIT_SUCCESS;
}