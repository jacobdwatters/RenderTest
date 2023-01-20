set(target renderTests)
set( renderTests_SOURCES
	noisetex.cpp
	main.cpp
		scenerust.cpp scenerust.h
)

add_executable( ${target} ${renderTests_SOURCES} )

target_compile_definitions(${target}
		PRIVATE
		GLFW_INCLUDE_NONE
)

target_link_libraries( ${target}
		PRIVATE
		ingredients
		glfw
		${OPENGL_gl_LIBRARY}
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
