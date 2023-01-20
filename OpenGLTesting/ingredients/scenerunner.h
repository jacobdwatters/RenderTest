#include <glad/glad.h>
#include "scene.h"
#include <GLFW/glfw3.h>
#include "glutils.h"

#define WIN_WIDTH 800 // Default window width
#define WIN_HEIGHT 600 // Default window height

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>

/**
 * Runs simple scene objects in a loop.
 */
class SceneRunner {
private:
    GLFWwindow * window;
    int fbw, fbh, lastTime, nFrames;
	bool debug;           // Set true to enable debug messages
    std::string wTitle;

public:
    SceneRunner(const std::string & windowTitle, int width = WIN_WIDTH, int height = WIN_HEIGHT, int samples = 0) : debug(true) {
        // Set window title
        wTitle = windowTitle;

        // Initialize GLFW
        if( !glfwInit() ) exit( EXIT_FAILURE );

        // Select OpenGL 4.6 (Apple must use OpenGL 4.1)
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        if(debug) 
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        if(samples > 0) {
            glfwWindowHint(GLFW_SAMPLES, samples);
        }

        // Open the window
        window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, windowTitle.c_str(), NULL, NULL );
        glfwMakeContextCurrent(window);

        // Get framebuffer size
        glfwGetFramebufferSize(window, &fbw, &fbh);

        // Load the OpenGL functions.
        if(!gladLoadGL()) { exit(-1); }

        GLUtils::dumpGLInfo();

        // Initialization
        glClearColor(0.5f,0.5f,0.5f,1.0f);
    }

    int run(std::unique_ptr<Scene> scene) {        
        // Enter the main loop
        mainLoop(window, std::move(scene));

		// Close window and terminate GLFW
		glfwTerminate();

        // Exit program
        return EXIT_SUCCESS;
    }

    static std::string parseCLArgs(int argc, char ** argv, std::map<std::string, std::string> & sceneData) {
        if( argc < 2 ) {
            printHelpInfo(argv[0], sceneData);
            exit(EXIT_FAILURE);
        }

        std::string recipeName = argv[1];
        auto it = sceneData.find(recipeName);
        if( it == sceneData.end() ) {
            printf("Unknown recipe: %s\n\n", recipeName.c_str());
            printHelpInfo(argv[0], sceneData);
            exit(EXIT_FAILURE);
        }

        return recipeName;
    }

private:
    static void printHelpInfo(const char * exeFile,  std::map<std::string, std::string> & sceneData) {
        printf("Usage: %s scene-name\n\n", exeFile);
        printf("Scene names: \n");
        for( auto it : sceneData ) {
            printf("  %11s : %s\n", it.first.c_str(), it.second.c_str());
        }
    }

    /**
     * Shows fps in window bar.
     * @param window Window to show fps in.
     */
    void showFPS(GLFWwindow* window) {
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        char ss[500] = {};
        nFrames++;
        if ( delta >= 1.0 ){ // If last update was more than 1 second ago
            double fps = ((double)(nFrames)) / delta;
            sprintf(ss,"%s running at %lf FPS.",wTitle.c_str(),fps);
            glfwSetWindowTitle(window, ss);
            nFrames = 0;
            lastTime = currentTime;
        }
    }

    // Main rendering loop.
    void mainLoop(GLFWwindow * window, std::unique_ptr<Scene> scene) {

        // Initialize parameters
        lastTime=0;
        nFrames=0;
        scene->setDimensions(fbw, fbh);
        scene->initScene();
        scene->resize(fbw, fbh);

        while( !glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) {
            GLUtils::checkForOpenGLError(__FILE__,__LINE__);
			
            scene->update(float(glfwGetTime()));
            scene->render();
            showFPS(window);
            glfwSwapBuffers(window);

            glfwPollEvents();
			int state = glfwGetKey(window, GLFW_KEY_SPACE);
			if (state == GLFW_PRESS)
				scene->animate(!scene->animating());
        }
    }
};
