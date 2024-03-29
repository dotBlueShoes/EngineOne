#pragma once

#include "types.hpp"
#include "global.hpp"

namespace WIN {

    static void glfwErrorCallback(int error, const char* description) {
        spdlog::error ("Glfw Error {0}: {1}\n", error, description);
        //fprintf (stderr, "Glfw Error %d: %s\n", error, description);
    }

    void Initialize (const GLFWerrorfun& errorCallback) {
        glfwSetErrorCallback (errorCallback);
        if (!glfwInit()) throw;
    };

    void SetVersion() {
        #if defined(IMGUI_IMPL_OPENGL_ES2) 										// GLES 2.0 + GLSL 100
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);						//
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);						//
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);				//
		#elif defined(__APPLE__) 												// GLES 3.2 + GLSL 150
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);						//
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  	// 3.2+ only
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            	// Required on Mac
		#else 																	// GLES 3.0 + GLSL 130
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);						//
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// 3.2+ only
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);          	// 3.0+ only
		#endif
    }

    void Create (Window& window) {

		Initialize (&glfwErrorCallback);
        SetVersion ();

        window = glfwCreateWindow (GLOBAL::windowTransform[2], GLOBAL::windowTransform[3], "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
        if (window == NULL) throw;
        glfwMakeContextCurrent (window);
        glfwSwapInterval (1); // Enable vsync

		//Initialize GLAD 
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		DEBUG { spdlog::info ("Window succesfully Created"); }

		IMGUI::Create (window);

        GLOBAL::Initialize();
    }

    void Destroy (const Window& window) {
        glfwDestroyWindow (window);
		IMGUI::Destroy ();
        glfwTerminate ();
    }
}