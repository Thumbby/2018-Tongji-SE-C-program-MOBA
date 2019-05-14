#include "CsvParser.h"

USING_NS_CC;

//�ַ����ָ��
void split(const std::string &str, const char *reps, std::vector<std::string> &tarVector)
{
	std::string tarString(str);
	while (!tarString.empty()) {
		int pos = tarString.find_first_of(reps);
		if (pos == std::string::npos) {
			tarVector.push_back(tarString);
			tarString.clear();
		}
		else {
			tarVector.push_back(tarString.substr(0, pos));
			tarString.erase(0, pos + strlen(reps));
		}
	}
}

LineString::LineString(const std::string &str)
{
	this->initWithString(str);
}

LineString::~LineString()
{

}

void LineString::initWithString(const std::string &str)
{
	split(str, ",", _lineStr);
}

//////////////////////////////////////////////////////////////////////////
CsvParser::CsvParser()
{

}

CsvParser::~CsvParser()
{

}

void CsvParser::parseWithFile(const std::string &csvFilename)
{
	std::string fullPth = FileUtils::getInstance()->fullPathForFilename(csvFilename);
	std::string tokenStr = FileUtils::getInstance()->getStringFromFile(fullPth);

	//��ȡ����Ϣ
	std::vector<std::string> lineInfo;
	split(tokenStr, "\n\r", lineInfo);

	//�õ�����
	split(lineInfo[0], ",", _titles);

	//��ȡ��������
	size_t rowCount = lineInfo.size();
	for (int i = 1; i < rowCount; i++) {
		LineString lineStr(lineInfo[i]);
		_dataInfo.push_back(lineStr);
	}
}