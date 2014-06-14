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
    
    while (glfwGetWindowParam(GLFW_OPENED)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        static const GLfloat vtx[] = {0.0f, 0.0f};
        
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