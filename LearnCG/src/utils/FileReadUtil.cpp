#include "FileReadUtil.h"

FileReadUtil* FileReadUtil::instance = nullptr;

FileReadUtil * FileReadUtil::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new FileReadUtil();
	}
	return instance;
}

void FileReadUtil::readFromFilePath(string path, char * pst, int size)
{
	readStream = ifstream(path, ifstream::binary);

	if (!readStream)
	{
		cout << "��" << path << "�ļ�ʧ��" << endl;
		return;
	}

	readStream.read(pst, size);
}
