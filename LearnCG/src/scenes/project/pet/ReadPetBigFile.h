#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct SingleCoin { //12字节
	unsigned long long nTime; //8字节
	unsigned short CrystalId; //2字节
	unsigned char BDMId; //1字节
	unsigned char DUId; //1字节
}; //sizeof(SingleCoin)=16字节

class ReadPetBigFile
{
public:
	ifstream readStream;
	string petDataFilename;
	vector<SingleCoin> coins;
	int coinCount = 300; // ÷2 对
public:
	ReadPetBigFile();
	~ReadPetBigFile();
	void writeSingleCoin(SingleCoin &s);
	void coutSingleCoin(SingleCoin &s);
};

