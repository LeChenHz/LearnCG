#include "Scene.h"

Scene::Scene()
{
	windowTitle = "Computer Graphics";
	hiddenMouse = false;

	initCamera();
}

void Scene::initCamera()
{
	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

void Scene::setTwBar(TwBar * bar)
{
	this->twBar = bar;
}

