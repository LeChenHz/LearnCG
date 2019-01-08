#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#pragma pack(1) //�رսṹ�����
struct SingleCoin { //12�ֽ�
	unsigned long long nTime; //8�ֽ�
	unsigned short CrystalId; //2�ֽ�
	unsigned char BDMId; //1�ֽ�
	unsigned char DUId; //1�ֽ�
}; 
// sizeof(SingleCoin)=16�ֽ�
//�رսṹ�����֮�� sizeof(SingleCoin)=12�ֽ�
#pragma pack()

class ReadPetBigFile
{
public:
	ifstream readStream;
	string petDataFilename;
	//vector<SingleCoin> coins
	SingleCoin coins[617880];
	int coinCount = 617880; // ��2 ��
public:
	ReadPetBigFile();
	~ReadPetBigFile();
	void writeSingleCoin();
	void coutSingleCoin(SingleCoin &s);
};

