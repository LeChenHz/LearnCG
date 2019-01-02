#include "S_Pet_Demo.h"

S_Pet_Demo::S_Pet_Demo()
{
}


S_Pet_Demo::~S_Pet_Demo()
{
}


void S_Pet_Demo::initGL()
{
	perModel = new PetMathmaticalModel();
}

void S_Pet_Demo::paintGL(float deltaTime)
{
	perModel->draw();
}

void S_Pet_Demo::freeGL()
{
}

