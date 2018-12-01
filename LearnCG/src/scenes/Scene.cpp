#include "Scene.h"

Scene::Scene()
{
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	windowTitle = "Computer Graphics";
}
