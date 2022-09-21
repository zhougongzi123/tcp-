#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test.h"
#include <zip.h>
#include <unzip.h>
#include <QVector>
#include <QFile>
#include <QFileInfoList>
#include <QScopedPointer>
#include <QDir>
class test : public QMainWindow
{
	Q_OBJECT

public:
	test(QWidget *parent = Q_NULLPTR);
public:
	void setStr(QString * str);

	//实现遍历文件夹 
	void BrowseFile(QString &strFile);

	//获取相对路径 
	void GetRelativePath(QString& pFullPath, QString& pSubString);

	//创建路径 
	bool CreatedMultipleDirectory(wchar_t* direct);

	//压缩接口 
	bool Zip_PackFiles(QString FromFilePath, QString mZipFileFullPath);

	//解压缩接口
	bool Zip_UnPackFiles(QString mZipFileFullPath, QString mUnPackPath);

	//检查文件夹存在
	bool IsFolderExist(QString strPath);

	//检查文件存在
	bool IsFileExist(QString strPath);

	//指定压缩包  单一路径 路径集合
	void PressFolder(QString strTgt, QString strSrcFolder);

	//指定解压目标
	void UnPressFolder(QString strTgt);

	int GetPathLenth(QString pFullPath);

	public slots:
	void on_test_clicked();
	void on_UnCompress_clicked();


private:
	
	struct TestImpl;
	TestImpl* impl;
	//QScopedPointer<TestImpl> impl;
};
