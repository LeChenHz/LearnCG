#include "ReadPetBigFile.h"

ReadPetBigFile::ReadPetBigFile()
{
	petDataFilename = "C:/coin.dat";
	readStream = ifstream(petDataFilename, ifstream::binary);

	if (!readStream)
	{
		cout << "打开" << petDataFilename << "文件失败" << endl;
		return;
	}

	SingleCoin s;
	//cout << sizeof(s) << sizeof(s.nTime) << sizeof(s.CrystalId) << sizeof(s.BDMId) << sizeof(s.DUId);
	for (int i = 0; i < coinCount; i++)
	{
		writeSingleCoin(s);
		//coutSingleCoin(s);
		coins.push_back(s);
	}
}



ReadPetBigFile::~ReadPetBigFile()
{
}

void ReadPetBigFile::writeSingleCoin(SingleCoin & s)
{
	readStream.read((char *)&s.nTime, sizeof(s.nTime));
	readStream.read((char *)&s.CrystalId, sizeof(s.CrystalId));
	readStream.read((char *)&s.BDMId, sizeof(s.BDMId));
	readStream.read((char *)&s.DUId, sizeof(s.DUId));
}

void ReadPetBigFile::coutSingleCoin(SingleCoin & s)
{
	//cout << s.BDMId << endl;
	cout << s.nTime << "  " << s.CrystalId << "  " << (int)s.BDMId << "  " << (int)s.DUId << endl;
}
