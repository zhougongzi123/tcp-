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

	//ʵ�ֱ����ļ��� 
	void BrowseFile(QString &strFile);

	//��ȡ���·�� 
	void GetRelativePath(QString& pFullPath, QString& pSubString);

	//����·�� 
	bool CreatedMultipleDirectory(wchar_t* direct);

	//ѹ���ӿ� 
	bool Zip_PackFiles(QString FromFilePath, QString mZipFileFullPath);

	//��ѹ���ӿ�
	bool Zip_UnPackFiles(QString mZipFileFullPath, QString mUnPackPath);

	//����ļ��д���
	bool IsFolderExist(QString strPath);

	//����ļ�����
	bool IsFileExist(QString strPath);

	//ָ��ѹ����  ��һ·�� ·������
	void PressFolder(QString strTgt, QString strSrcFolder);

	//ָ����ѹĿ��
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
