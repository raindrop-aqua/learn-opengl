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
#include <fstream>
#include <vector>

#if defined (_MSC_VER)
#pragma comment(lib, "GLFWDLL.lib")
#pragma comment(lib, "opengl32.lib")
#ifdef _DEBUG
#pragma comment(lib, "glewsd.lib")
#else
#pragma comment(lib, "glew32s.lib")
#endif
#endif

bool setupTexture(const GLuint id, const char* file, const int width, const int height) {
    std::ifstream fstr(file, std::ios::binary);

    if (!fstr) {
        return false;
    }
    
    const size_t file_size = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
    fstr.seekg(0, fstr.beg);
    
    std::vector<char> texture_buffer(file_size);
    fstr.read(&texture_buffer[0], file_size);
    
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture_buffer[0]);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    return true;
}

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

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    
    if (!setupTexture(texture_id, "sample.raw", 256, 256)) {
        glDeleteTextures(1, &texture_id);
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    while (glfwGetWindowParam(GLFW_OPENED)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        static const GLfloat vtx[] = {
            -0.8f, -0.8f,
             0.8f, -0.8f,
             0.8f,  0.8f,
            -0.8f,  0.8f,
        };
        glVertexPointer(2, GL_FLOAT, 0, vtx);

        static const GLfloat texture_uv[] = {
             0.0f, 1.0f,
             1.0f, 1.0f,
             1.0f, 0.0f,
             0.0f, 0.0f,
        };
        glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_TEXTURE_2D);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        
        glDrawArrays(GL_QUADS, 0, 4);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        
        glfwSwapBuffers();
    }
    glDeleteTextures(1, &texture_id);
    
    glfwTerminate();

    return EXIT_SUCCESS;
}
