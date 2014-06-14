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
    
    if (!glfwOpenWindow(0, 0,
                        0, 0, 0,
                        0,
                        0, 0,
                        GLFW_FULLSCREEN)) {
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    glfwSwapInterval(1);
    
    while (glfwGetWindowParam(GLFW_OPENED)) {
        glfwSwapBuffers();
    }
    glfwTerminate();

    return EXIT_SUCCESS;
}