#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct SingleCoin { //12�ֽ�
	unsigned long long nTime; //8�ֽ�
	unsigned short CrystalId; //2�ֽ�
	unsigned char BDMId; //1�ֽ�
	unsigned char DUId; //1�ֽ�
}; //sizeof(SingleCoin)=16�ֽ�

class ReadPetBigFile
{
public:
	ifstream readStream;
	string petDataFilename;
	vector<SingleCoin> coins;
	int coinCount = 300; // ��2 ��
public:
	ReadPetBigFile();
	~ReadPetBigFile();
	void writeSingleCoin(SingleCoin &s);
	void coutSingleCoin(SingleCoin &s);
};

