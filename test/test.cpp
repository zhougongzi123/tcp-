#include "test.h"


struct test::TestImpl
{
	TestImpl(test* parent)
	{

	}
	HZIP m_hz;				 //Zip�ļ���� 
	ZRESULT m_zr;			 //��������ֵ 
	ZIPENTRY m_ze;			 //Zip�ļ����

	int m_nZipCnt;
	int pathLength;

	QString m_FolderPath;	 //folder·�� 
	QString  m_FolderName;   //folder��Ҫ��ѹ�����ļ�����

	QVector<QString>  m_arrFileFullName;

	Ui::testClass ui;
};


test::test(QWidget *parent)
	: QMainWindow(parent)
	,impl(new TestImpl(this))
{
	impl->ui.setupUi(this);

}


void test::on_test_clicked()
{
	QString strTgt = impl->ui.filename->text();
	QString formFilename = impl->ui.formFilename->text();
	GetPathLenth(formFilename);
	PressFolder(strTgt, formFilename);

}

void test::on_UnCompress_clicked()
{
	QString strTgt = impl->ui.filename->text();
	UnPressFolder(strTgt);

}

void test::setStr(QString * str)
{
	QString Qstr = "\"12121\"";
	*str = Qstr;
	//str->remove("\"");
}


//ʵ�ֱ����ļ��� 
void test::BrowseFile(QString &strFile)
{
	QDir fromdir(strFile);
	QFileInfoList fileInfolist = fromdir.entryInfoList();
	for each (QFileInfo fileInfo in fileInfolist)
	{
		QString str = fileInfo.fileName();
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
		{
			continue;
		}
		if (fileInfo.isDir())
		{
			QString strPath = fileInfo.filePath();
			QString subPath ;
			/*.right(pFullPath.length() - qApp->applicationDirPath().length())*/;

			GetRelativePath(strPath, subPath);
			//���ļ���ӵ�ZIP�ļ� 
			ZipAddFolder(impl->m_hz, subPath.toStdWString().c_str());
			BrowseFile(strPath);
		}
		else
		{
			QString strPath = fileInfo.filePath();
			QString subPath;

			GetRelativePath(strPath, subPath);
			//���ļ���ӵ�ZIP�ļ� 
			ZipAdd(impl->m_hz, subPath.toStdWString().c_str(), strPath.toStdWString().c_str());
		}
	}

	//�ر� 
	//ff.Close();
}

//��ȡ·������
int test::GetPathLenth(QString pFullPath)
{
	QStringList pathlist = pFullPath.split("\\");
	QString filename = pathlist.at(pathlist.length() - 1);
	QString path = pFullPath.left(pFullPath.length() - filename.length());
	impl->pathLength = path.length();
	return path.length();
}
//��ȡ���·�� 
void test::GetRelativePath(QString& pFullPath, QString& pSubString)
{

	pSubString = pFullPath.right(pFullPath.length() - impl->pathLength);
	//pSubString = pFullPath.remove(qApp->applicationDirPath());
}

//����·�� 
bool test::CreatedMultipleDirectory(wchar_t* direct)
{
	std::wstring Directoryname = direct;

	if (Directoryname[Directoryname.length() - 1] != '\\')
	{
		Directoryname.append(1, '\\');
	}
	std::vector< std::wstring> vpath;
	std::wstring strtemp;
	bool  bSuccess = false;
	for (int i = 0; i < Directoryname.length(); i++)
	{
		if (Directoryname[i] != '\\')
		{
			strtemp.append(1, Directoryname[i]);
		}
		else
		{
			vpath.push_back(strtemp);
			strtemp.append(1, '\\');
		}
	}
	std::vector< std::wstring>::const_iterator vIter = vpath.begin();
	for (vIter; vIter != vpath.end(); vIter++)
	{
		bSuccess = CreateDirectory((LPCTSTR)vIter->c_str(), NULL) ? TRUE : FALSE;
	}
	return bSuccess;

}

//ѹ���ӿ� 
bool test::Zip_PackFiles(QString FromFileFullPath, QString mZipFileFullPath)
{
	QDir fromdir(FromFileFullPath);
	QList<QFileInfo> fileInfolist = fromdir.entryInfoList();
	int count = fileInfolist.count();
	impl->m_hz = CreateZip(mZipFileFullPath.toStdWString().c_str(), 0);
	if (impl->m_hz == 0)
	{
		//����Zip�ļ�ʧ�� 
		return false;
	}

	BrowseFile(FromFileFullPath);
	//�ر�ZIP�ļ� 
	
	CloseZip(impl->m_hz);
	

	/************************************************************************/

	//׷��ѹ��֮���ļ��Ƿ����
	//CFileFind tFFind;
	//if (!tFFind.FindFile(mZipFileFullPath))
	//{
	//	//ѹ��ʧ��(δ����ѹ������ļ�) 
	//	return FALSE;
	//}

	return true;
}

//��ѹ���ӿ�
bool test::Zip_UnPackFiles(QString mZipFileFullPath, QString mUnPackPath)
{
	impl->m_hz = OpenZip(mZipFileFullPath.toStdWString().c_str(), 0);
	if (impl->m_hz == 0)
	{
		//��Zip�ļ�ʧ�� 
		return false;
	}

	impl->m_zr = SetUnzipBaseDir(impl->m_hz, mUnPackPath.toStdWString().c_str());
	if (impl->m_zr != ZR_OK)
	{
		//��Zip�ļ�ʧ�� 
		CloseZip(impl->m_hz);
		return false;
	}

	impl->m_zr = GetZipItem(impl->m_hz, -1, &impl->m_ze);
	if (impl->m_zr != ZR_OK)
	{
		//��ȡZip�ļ�����ʧ�� 
		CloseZip(impl->m_hz);
		return false;
	}

	int numitems = impl->m_ze.index;
	for (int i = 0; i < numitems; i++)
	{
		impl->m_zr = GetZipItem(impl->m_hz, i, &impl->m_ze);
		impl->m_zr = UnzipItem(impl->m_hz, i, impl->m_ze.name);

		if (i == 100)
		{
			int x = 1;
		}
		if (impl->m_zr != ZR_OK)
		{
			//��ȡZip�ļ�����ʧ�� 
			CloseZip(impl->m_hz);
			return false;
		}
	}

	impl->m_nZipCnt = 0;
	CloseZip(impl->m_hz);
	return true;
}

//����ļ��д���
bool test::IsFolderExist(QString strPath)
{
	QDir FolderPath(strPath);
	if (!FolderPath.exists())
	{
		return false;
	}
	return true;
}

//����ļ�����
bool test::IsFileExist(QString strPath)
{
	if (strPath.isEmpty())
	{
		return false;
	}
	QDir *dir = new QDir(strPath);
	QStringList filter;
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
	int count = fileInfo->count();
	int row = 0;
	//bool hasFile = false;//�Ƿ������ļ�
	for (int i = 0; i<count; i++)
	{
		QString str = fileInfo->at(i).fileName();

		if (str == "." || str == "..")
		{
		}
		else
		{
			QStringList strList = str.split(".");
			if (strList.at(0).contains(strPath))
			{
				//hasFile = true;
				return true;
			}
		}
	}
	return false;

}

//ָ��ѹ����  ��һ·�� ·������
void test::PressFolder(QString strTgt, QString strSrcFolder)
{

	//Ŀ���ļ���
	QString patm_hzipFile = strTgt;
	Zip_PackFiles(strSrcFolder, patm_hzipFile);
}

// ָ����ѹĿ��
void test::UnPressFolder(QString strTgt)
{
	if (strTgt.isEmpty())
		return;

	QString patm_hzipFile = strTgt;
	QString mUnPackPath = impl->ui.formFilename->text();

	Zip_UnPackFiles(patm_hzipFile, mUnPackPath);
}