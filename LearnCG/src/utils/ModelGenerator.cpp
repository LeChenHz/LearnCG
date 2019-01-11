#include "ModelGenerator.h"



ModelGenerator* ModelGenerator::instance = nullptr;

ModelGenerator * ModelGenerator::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ModelGenerator();
	}
	return instance;
}

void ModelGenerator::generateObjUsePosNormal(string path, glm::vec3 * pos, glm::vec3 * normal, int length)
{
	writeSteam = ofstream(path);
	if (!writeSteam)
	{
		cout << "打开文件失败";
		return;
	}
	writeSteam << "顶点个数" << length << endl;
	writeSteam << "面的个数" << length / 3 << endl;

	writeSteam << "# 顶点v" << endl;
	for (int i = 0; i < length; i++)
	{
		writeSteam << "v " << pos[i].x << " " << pos[i].y << " " << pos[i].z << endl;
	}

	writeSteam << endl << endl << endl << "# 法线vn" << endl;
	for (int i = 0; i < length; i++)
	{
		writeSteam << "vn " << normal[i].x << " " << normal[i].y << " " << normal[i].z << endl;
	}

	writeSteam << endl << endl << endl << "# 面f" << endl;
	for (int i = 0; i < length / 3; i++)
	{
		writeSteam << "f " 
			<< 3 * i + 1 << "//" << 3 * i + 1 << " "
			<< 3 * i + 2 << "//" << 3 * i + 2 << " "
			<< 3 * i + 3 << "//" << 3 * i + 3 << endl;
	}
}
