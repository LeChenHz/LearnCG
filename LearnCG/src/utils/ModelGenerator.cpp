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
		cout << "���ļ�ʧ��";
		return;
	}
	writeSteam << "�������" << length << endl;
	writeSteam << "��ĸ���" << length / 3 << endl;

	writeSteam << "# ����v" << endl;
	for (int i = 0; i < length; i++)
	{
		writeSteam << "v " << pos[i].x << " " << pos[i].y << " " << pos[i].z << endl;
	}

	writeSteam << endl << endl << endl << "# ����vn" << endl;
	for (int i = 0; i < length; i++)
	{
		writeSteam << "vn " << normal[i].x << " " << normal[i].y << " " << normal[i].z << endl;
	}

	writeSteam << endl << endl << endl << "# ��f" << endl;
	for (int i = 0; i < length / 3; i++)
	{
		writeSteam << "f " 
			<< 3 * i + 1 << "//" << 3 * i + 1 << " "
			<< 3 * i + 2 << "//" << 3 * i + 2 << " "
			<< 3 * i + 3 << "//" << 3 * i + 3 << endl;
	}
}
