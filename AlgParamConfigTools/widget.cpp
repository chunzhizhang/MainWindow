#include "widget.h"
//3rd_party
#include "iniparser/iniparser.h"
#include "stringExpansion/stringExpansion.h"
//windows
#include <tchar.h>
//C++
#include <fstream>
#include <iostream>
//Qt
#include <QLabel> 
#include <QString>
#include <QKeyEvent>
#include <QBoxLayout>

Widget::Widget(QWidget *parent /*= Q_NULLPTR*/)
	:QWidget(parent)
{
	ui.setupUi(this);

	MapFile mapFile;
	std::vector<std::vector<std::string>> vecFileSectionKeyValue;//vector<vector{file,section,key,value};
	readFile("./AlgParamConfig.ini", mapFile);
	readValue(mapFile, vecFileSectionKeyValue);

	QGridLayout* gLayout = new QGridLayout(this);
	int row = 0;
	for (auto fileSectionKeyValue : vecFileSectionKeyValue)
	{
		QLabel* label = new QLabel(QString(fileSectionKeyValue[2].c_str()), this);
		QLineEdit* lineEdit = new QLineEdit(QString(fileSectionKeyValue[3].c_str()), this);
		gLayout->addWidget(label, row, 0);
		gLayout->addWidget(lineEdit, row, 1);
		row++;
		connect(lineEdit, &QLineEdit::editingFinished, this, &Widget::slotEditingFinished);
		mMapLineEdit[lineEdit] = fileSectionKeyValue;
	}
	setLayout(gLayout);
}

//读取文件中算子配置文件，节点和键
bool Widget::readFile(const std::string& file, MapFile& mapFile)
{
	std::ifstream infile;
	infile.open(file.data()); 
	if (!infile.is_open())
	{
		return false;
	}
	
	std::string s;
	std::vector<std::string> vecStr;
	while (getline(infile, s))
	{
		std::cout << s << std::endl;
		vecStr = split(s, ",");
		if (vecStr.size() != CL_Count) //简单过滤，只保留3个string（file/section/key）的情况
		{
			continue;
		}

		mapFile[vecStr[CL_File]][vecStr[CL_Section]].push_back(vecStr[CL_Key]);
	}
	infile.close();   
	return true;
}

void Widget::readValue(const MapFile& mapFile, std::vector<std::vector<std::string>>& vecFileSectionKeyValue)
{
	INI::File iniFile;
	for (auto itr = mapFile.cbegin(); itr != mapFile.cend(); itr++)
	{
		std::string strPath = itr->first;
		if (!iniFile.Load(strPath.c_str()))
		{
			continue;
		}

		std::map < std::string, std::vector < std::string>> mapSection = itr->second;
		for (auto itr2 = mapSection.cbegin(); itr2 != mapSection.cend(); itr2++)
		{
			std::string strSection = itr2->first;
			std::vector<std::string> vecKeys = itr2->second;
			for (auto key : vecKeys)
			{
				std::string strValue = iniFile.GetSection(strSection.c_str())->GetValue(key.c_str(), "").AsString();
				vecFileSectionKeyValue.push_back({ strPath, strSection, key, strValue });
			}
		}
		iniFile.Unload();
	}
}

bool Widget::saveValue(std::string& file, std::string& section, std::string& key, std::string& value)
{
	INI::File iniFile;
	if (!iniFile.Load(file.c_str()))
	{
		return false;
	}

	iniFile.GetSection(section.c_str())->SetValue(key.c_str(), value);
	iniFile.Save(file);
	iniFile.Unload();
	return true;
}

//界面数据被修改时，同步修改配置文件数据
void Widget::slotEditingFinished()
{
	QLineEdit* p = (QLineEdit*)sender(); //获取发送信号对象
	if (!p)
	{
		return;
	}

	std::string strValue = p->text().toStdString();
	std::vector<std::string> vec = mMapLineEdit[p];
	saveValue(vec[0], vec[1], vec[2], strValue);
}