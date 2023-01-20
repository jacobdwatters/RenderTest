#pragma once

#include <glm/glm.hpp>


/**
 * Simple scene object to store basic information about the scene such as window size, projection matrices, etc.
 */
class Scene {
    protected:
        glm::mat4 model, view, projection;

    public:
        int width;
        int height;

        Scene() : m_animate(true), width(800), height(600) { }
        virtual ~Scene() {}

        void setDimensions( int w, int h ) {
            width = w;
            height = h;
        }

        /**
          Load textures, initialize shaders, etc.
          */
        virtual void initScene() = 0;

        /**
          Called prior to every frame to update animation.
          */
        virtual void update( float t ) = 0;

        /**
          Draw scene.
          */
        virtual void render() = 0;

        /**
          Called when screen is resized
          */
        virtual void resize(int, int) = 0;

        void animate( bool value ) { m_animate = value; }
        bool animating() { return m_animate; }
    
    protected:
        bool m_animate;
};
