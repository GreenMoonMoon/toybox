//
// Created by josue on 2023-06-13.
//

#ifndef TOYBOX_SRC_GRAPHIC_DEBUG_H_
#define TOYBOX_SRC_GRAPHIC_DEBUG_H_

#include <stdio.h>
#include <assert.h>
#include "glad/gl.h"

void GLAPIENTRY print_graphic_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void* user_param){
    char* src_str;
    switch(source){
        case GL_DEBUG_SOURCE_API: src_str = "API\0"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: src_str = "WINDOW SYSTEM\0"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: src_str = "SHADER COMPILER\0"; break;
        default: src_str = "OTHER\0";
    }

    char *type_str;
    switch(type){
        case GL_DEBUG_TYPE_ERROR: type_str = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "DEPRECATED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: type_str = "UNDEFINED BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY: type_str = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: type_str = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_MARKER: type_str = "MARKER"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP: type_str = "PUSH_GROUP"; break;
        case GL_DEBUG_TYPE_POP_GROUP: type_str = "POP GROUP"; break;
        default: type_str = "OTHER\0";
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            // All OpenGL Errors, shader compilation/linking errors, or highly-dangerous undefined behavior
            fprintf(stderr, "GRAPHIC ERROR | %d:%s:%s: %s\n", id, src_str, type_str, message);
            assert(false);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            // Major performance warnings, shader compilation/linking warnings, or the use of deprecated functionality
            fprintf(stderr, "GRAPHIC WARNING | %d:%s:%s: %s\n", id, src_str, type_str, message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            // Redundant state change performance warning, or unimportant undefined behavior
            fprintf(stderr, "GRAPHIC LOG | %d:%s:%s: %s\n", id, src_str, type_str, message);
            break;
        default:
            // Anything that isn't an error or performance issue.
            fprintf(stderr, "GRAPHIC INFO | %d:%s:%s: %s\n", id, src_str, type_str, message);
    }
}

#endif //TOYBOX_SRC_GRAPHIC_DEBUG_H_
