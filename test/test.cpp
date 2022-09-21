#include "test.h"


struct test::TestImpl
{
	TestImpl(test* parent)
	{

	}
	HZIP m_hz;				 //Zip文件句柄 
	ZRESULT m_zr;			 //操作返回值 
	ZIPENTRY m_ze;			 //Zip文件入口

	int m_nZipCnt;
	int pathLength;

	QString m_FolderPath;	 //folder路径 
	QString  m_FolderName;   //folder将要被压缩的文件夹名

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


//实现遍历文件夹 
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
			//将文件添加到ZIP文件 
			ZipAddFolder(impl->m_hz, subPath.toStdWString().c_str());
			BrowseFile(strPath);
		}
		else
		{
			QString strPath = fileInfo.filePath();
			QString subPath;

			GetRelativePath(strPath, subPath);
			//将文件添加到ZIP文件 
			ZipAdd(impl->m_hz, subPath.toStdWString().c_str(), strPath.toStdWString().c_str());
		}
	}

	//关闭 
	//ff.Close();
}

//获取路径长度
int test::GetPathLenth(QString pFullPath)
{
	QStringList pathlist = pFullPath.split("\\");
	QString filename = pathlist.at(pathlist.length() - 1);
	QString path = pFullPath.left(pFullPath.length() - filename.length());
	impl->pathLength = path.length();
	return path.length();
}
//获取相对路径 
void test::GetRelativePath(QString& pFullPath, QString& pSubString)
{

	pSubString = pFullPath.right(pFullPath.length() - impl->pathLength);
	//pSubString = pFullPath.remove(qApp->applicationDirPath());
}

//创建路径 
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

//压缩接口 
bool test::Zip_PackFiles(QString FromFileFullPath, QString mZipFileFullPath)
{
	QDir fromdir(FromFileFullPath);
	QList<QFileInfo> fileInfolist = fromdir.entryInfoList();
	int count = fileInfolist.count();
	impl->m_hz = CreateZip(mZipFileFullPath.toStdWString().c_str(), 0);
	if (impl->m_hz == 0)
	{
		//创建Zip文件失败 
		return false;
	}

	BrowseFile(FromFileFullPath);
	//关闭ZIP文件 
	
	CloseZip(impl->m_hz);
	

	/************************************************************************/

	//追踪压缩之后文件是否存在
	//CFileFind tFFind;
	//if (!tFFind.FindFile(mZipFileFullPath))
	//{
	//	//压缩失败(未发现压缩后的文件) 
	//	return FALSE;
	//}

	return true;
}

//解压缩接口
bool test::Zip_UnPackFiles(QString mZipFileFullPath, QString mUnPackPath)
{
	impl->m_hz = OpenZip(mZipFileFullPath.toStdWString().c_str(), 0);
	if (impl->m_hz == 0)
	{
		//打开Zip文件失败 
		return false;
	}

	impl->m_zr = SetUnzipBaseDir(impl->m_hz, mUnPackPath.toStdWString().c_str());
	if (impl->m_zr != ZR_OK)
	{
		//打开Zip文件失败 
		CloseZip(impl->m_hz);
		return false;
	}

	impl->m_zr = GetZipItem(impl->m_hz, -1, &impl->m_ze);
	if (impl->m_zr != ZR_OK)
	{
		//获取Zip文件内容失败 
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
			//获取Zip文件内容失败 
			CloseZip(impl->m_hz);
			return false;
		}
	}

	impl->m_nZipCnt = 0;
	CloseZip(impl->m_hz);
	return true;
}

//检查文件夹存在
bool test::IsFolderExist(QString strPath)
{
	QDir FolderPath(strPath);
	if (!FolderPath.exists())
	{
		return false;
	}
	return true;
}

//检查文件存在
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
	//bool hasFile = false;//是否已有文件
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

//指定压缩包  单一路径 路径集合
void test::PressFolder(QString strTgt, QString strSrcFolder)
{

	//目的文件夹
	QString patm_hzipFile = strTgt;
	Zip_PackFiles(strSrcFolder, patm_hzipFile);
}

// 指定解压目标
void test::UnPressFolder(QString strTgt)
{
	if (strTgt.isEmpty())
		return;

	QString patm_hzipFile = strTgt;
	QString mUnPackPath = impl->ui.formFilename->text();

	Zip_UnPackFiles(patm_hzipFile, mUnPackPath);
}