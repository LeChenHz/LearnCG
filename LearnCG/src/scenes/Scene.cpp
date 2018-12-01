#include "Scene.h"

Scene::Scene()
{
	windowTitle = "Computer Graphics";
	hiddenMouse = false;

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}
