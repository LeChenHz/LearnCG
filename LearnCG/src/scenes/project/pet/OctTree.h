#pragma once

#include <vector>
#include <map>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class OctTree 
{
	std::map<int, OctTree*> childs; // �ӽڵ�
	int acc = 0; // ��ǰ�ڵ��Ũ��
	glm::vec3 size; // ��С
	glm::vec3 center; // ����
	int depth = 0; // ��ȣ����ڵ������8��
	int max = -1; // Ҷ�ӽڵ��Ũ�����ֵ
	glm::vec3 regionVector(int region) const;

public:
	OctTree(glm::vec3 size, glm::vec3 center, int maxDepth);
	~OctTree();
	int getRegion(glm::vec3 point) const; // �ж�ĳ�������ڵ�����
	void addPoint(glm::vec3 point); // ��ӵ�
	glm::vec3 getCenter() const;
	glm::vec3 getSize() const;
	int getMax() const;
	int getAcc() const;
	// ��ȡҶ�ӽڵ㣬���С��filter_max�͹��˵�
	void getLeaves(std::vector<const OctTree*> &result, int filter_max = 0) const;
};
