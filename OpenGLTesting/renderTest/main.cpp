#include "scenerunner.h"
#include "scenerust.h"

#include <memory>

std::map<std::string, std::string> sceneInfo = {
		{ "rust", "A rusted teapot."}
};

int main(int argc, char *argv[])
{
	std::string recipe = SceneRunner::parseCLArgs(argc, argv, sceneInfo);

	SceneRunner runner("Render Test - " + recipe);

	std::unique_ptr<Scene> scene;
    if( recipe == "rust" ) {
		scene = std::unique_ptr<Scene>( new SceneRust() );
	} else {
		printf("Unknown scene: %s\n", recipe.c_str());
		exit(EXIT_FAILURE);
	}

	return runner.run(std::move(scene));
}
