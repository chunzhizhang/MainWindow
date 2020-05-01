#pragma once
#include "ui_widget.h"
#include <QtWidgets/QWidget>
#include <QLineEdit>

typedef std::map < std::string, std::map < std::string, std::vector < std::string>>> MapFile;

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(QWidget *parent = Q_NULLPTR);

private:
	enum ConfigLevel
	{
		CL_File = 0,
		CL_Section,
		CL_Key,
		CL_Count
	};
	bool readFile(const std::string& file, MapFile& mapFile);
	void readValue(const MapFile& mapFile, std::vector<std::vector<std::string>>& vecFileSectionKeyValue);
	bool saveValue(std::string& file, std::string& section, std::string& key, std::string& value);

	private slots:
	void slotEditingFinished();

private:
	Ui::Form ui;
	std::map<QLineEdit*, std::vector<std::string>> mMapLineEdit;//建立lineEdit与fileSectionKey映射关系
};
