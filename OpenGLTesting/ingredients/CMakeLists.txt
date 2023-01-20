set(target ingredients)

set(ingredients_SOURCES
        teapotpatch.cpp
        teapot.cpp
        torus.cpp
        glutils.cpp
        objmesh.cpp
        glslprogram.cpp
        cube.cpp
        plane.cpp
        sphere.cpp
        scene.h
        teapotdata.h
        glad/src/glad.c trianglemesh.cpp trianglemesh.h aabb.h
        scenerunner.h
        texture.h texture.cpp
        random.h
        skybox.cpp skybox.h
        stbimpl.cpp)

add_library(${target} STATIC ${ingredients_SOURCES} ../Lab01/scenebasic.cpp)

target_include_directories(${target} PUBLIC glad/include)

if( UNIX AND NOT APPLE )
    target_link_libraries(${target} PUBLIC ${CMAKE_DL_LIBS})
endif()


