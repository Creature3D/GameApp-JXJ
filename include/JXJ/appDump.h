#pragma  once
#pragma comment( lib, "DbgHelp" )
#pragma comment( lib, "wininet.lib" )
#include <CRIOManager/crFileUtils.h>
#include <CRIOManager/crReadFile.h>
#include <CRIOManager/crWriteFile.h>
#include <crIOManager/crLoadManager.h>
#include <Windows.h>
#include <WinInet.h>
#include <Dbghelp.h>
#include <time.h>
#include <stdio.h>
#include <CRNetApp/appGlobalHandle.h>
#include <CRCore/crDisplaySettings.h>
#include <CRCore/crStreamBuf.h>
#include <crgl/glu.h>
#include <CRNet/crNetContainer.h>
#include <CRNetApp/appNetCallbacks.h>
#include <CRNet/crNetWorkUpdater.h>
#include <psapi.h>
#pragma  comment(lib,"Psapi.lib")

void getFtpInfo(std::string & ftpHost,
				std::string & ftpUserName,
				std::string & ftpPassword)
{
	std::string file = CRNetApp::crGlobalHandle::gData()->getClientCfg();//"Client.cfg";
	rcfg::ConfigScript cfg_script;
	if(!CRIOManager::crScriptLoadManager::getInstance()->loadConfigScript(cfg_script,file))
	{
		//CRCore::notify(CRCore::FATAL)<<"crInitDownloadMethod(): file open error,"<<file<<std::endl;
		char gbuf[256];
		sprintf(gbuf,"crInitDownloadMethod(): file open error,%s\n\0",file.c_str());
		gDebugInfo->debugInfo(CRCore::NOTICE,gbuf);
		return;
	}
	cfg_script.Get("FtpHost", ftpHost);
	cfg_script.Get("UserName", ftpUserName);
	cfg_script.Get("Password", ftpPassword);
//	MessageBox(NULL,ftpHost.c_str(),NULL,MB_OK);
//	MessageBox(NULL,ftpUserName.c_str(),NULL,MB_OK);
//	MessageBox(NULL,ftpPassword.c_str(),NULL,MB_OK);
	cfg_script.Close();
}
BOOL UpLoadBugFile(std::string & szfilepathName)
{
	std::string remoteDir = std::string("dump//");
	int length = szfilepathName.length();
	//int pos = szfilepathName.rfind('\\');			
	std::string dumpFile =remoteDir+szfilepathName+ std::string(TEXT(".dmp"));
	std::string textFile =remoteDir+szfilepathName+ std::string(TEXT(".txt"));
	std::string gametextFile =remoteDir+szfilepathName+ std::string(TEXT("creature3d.txt"));
	std::string bmpFile =remoteDir+szfilepathName+ std::string(TEXT(".jpg"));
	std::string localDumpFile = szfilepathName+std::string(TEXT(".dmp"));
	std::string localTextFile = szfilepathName+std::string(TEXT(".txt"));
	std::string localGameTextFile = szfilepathName+std::string(TEXT("d.txt"));
	std::string localbmpFile = szfilepathName+std::string(TEXT("d.jpg"));
	HINTERNET hInternet = InternetOpen(NULL,INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	if(hInternet != NULL)
	{
		std::string ftpAdd,ftpUserName,ftpPassword;
		getFtpInfo(ftpAdd,ftpUserName,ftpPassword);
		HINTERNET ftpInet = InternetConnect(hInternet,ftpAdd.c_str(),INTERNET_DEFAULT_FTP_PORT,ftpUserName.c_str(),\
			ftpPassword.c_str(),INTERNET_SERVICE_FTP,INTERNET_FLAG_EXISTING_CONNECT | INTERNET_NO_CALLBACK,0);
		if(ftpInet!=NULL)
		{
			//MessageBox(NULL,localDumpFile.c_str(),localDumpFile.c_str(),MB_OK);
			FtpPutFile(ftpInet,localDumpFile.c_str(),dumpFile.c_str(),FTP_TRANSFER_TYPE_BINARY,0);			
			//MessageBox(NULL,localTextFile.c_str(),localTextFile.c_str(),MB_OK);
			FtpPutFile(ftpInet,localTextFile.c_str(),textFile.c_str(),FTP_TRANSFER_TYPE_BINARY,0);
			//MessageBox(NULL,localGameTextFile.c_str(),localGameTextFile.c_str(),MB_OK);
			FtpPutFile(ftpInet,localGameTextFile.c_str(),gametextFile.c_str(),FTP_TRANSFER_TYPE_BINARY,0);
			FtpPutFile(ftpInet,localbmpFile.c_str(),bmpFile.c_str(),FTP_TRANSFER_TYPE_BINARY,0);
		}
		InternetCloseHandle(ftpInet);
	}
	InternetCloseHandle(hInternet);

	//delete file
	DeleteFile(localDumpFile.c_str());
	DeleteFile(localTextFile.c_str());
	DeleteFile(localGameTextFile.c_str());
	DeleteFile(localbmpFile.c_str());
	return TRUE;
}

BOOL SaveBitmapToFile(LPCTSTR lpszFilePath,HDC hdc ,HBITMAP hBm)
{
	//  ����λͼ�ļ���ͷ
	BITMAPFILEHEADER bmfh;
	//  ����λͼ��Ϣ��ͷ
	BITMAPINFOHEADER bmih;

	//  ��ɫ�峤��
	int nColorLen = 0;
	//  ��ɫ���С
	DWORD dwRgbQuadSize = 0;
	//  λͼ��С
	DWORD dwBmSize = 0;
	//  �����ڴ��ָ��
	HGLOBAL    hMem = NULL;
	LPBITMAPINFOHEADER     lpbi;
	BITMAP bm;
	HANDLE hFile = NULL;

	DWORD dwWritten;

	GetObject(hBm, sizeof(BITMAP), &bm);
	
	int size, wordsPerScan;
	wordsPerScan=(bm.bmWidth*3+3)/4; // rounds up to next 32 bit boundary
	size=4*bm.bmHeight*wordsPerScan; // rounded to 4bytes * number of scan lines

	bmih.biSize    = sizeof(BITMAPINFOHEADER);    // ���ṹ��ռ���ֽ�
	bmih.biWidth    = bm.bmWidth;            // λͼ��
	bmih.biHeight    = bm.bmHeight;            // λͼ��
	bmih.biPlanes    = 1;
	bmih.biBitCount        = 24;    // ÿһͼ�ص�λ��
	bmih.biCompression    = 0;            // 
	bmih.biSizeImage        = size;  //  λͼ��С
	bmih.biXPelsPerMeter    = 1000;
	bmih.biYPelsPerMeter    = 1000;
	bmih.biClrUsed        = 0;
	bmih.biClrImportant    = 0;

	//  ����λͼͼ����������С 
	dwBmSize = 4 * ((bm.bmWidth * bmih.biBitCount + 31) / 32) * bm.bmHeight;

	//  ���ͼ��λ <= 8bit�����е�ɫ��
	if (bmih.biBitCount <= 8)
	{
		nColorLen = (1 << bm.bmBitsPixel);
	}

	//  �����ɫ���С
	dwRgbQuadSize = nColorLen * sizeof(RGBQUAD);

	//  �����ڴ�
	hMem = GlobalAlloc(GHND, dwBmSize + dwRgbQuadSize + sizeof(BITMAPINFOHEADER));

	if (NULL == hMem)
	{
		return FALSE;
	}

	//  �����ڴ�
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hMem);

	//  ��bmih�е�����д�������ڴ���
	*lpbi = bmih;

	  //  ��λͼ�е�������bits����ʽ����lpData�С�
	GetDIBits(hdc, hBm, 0, (DWORD)bmih.biHeight, (LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwRgbQuadSize, (BITMAPINFO *)lpbi, (DWORD)DIB_RGB_COLORS);

	bmfh.bfType = 0x4D42;  // λͼ�ļ����ͣ�BM
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwRgbQuadSize + dwBmSize;  // λͼ��С
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits    = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwRgbQuadSize;  // λͼ�������ļ�ͷ����ƫ����

	//  �����������д���ļ���

	hFile = CreateFile(lpszFilePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		  return FALSE;
	}

	//  д��λͼ�ļ�ͷ
	WriteFile(hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER), (DWORD *)&dwWritten, NULL);
	//  д��λͼ����
	WriteFile(hFile, (LPBITMAPINFOHEADER)lpbi, bmfh.bfSize - sizeof(BITMAPFILEHEADER), (DWORD *)&dwWritten, NULL);

	GlobalFree(hMem);
	CloseHandle(hFile);

	return TRUE;
}

LONG WINAPI JXJExceptionInfo(_EXCEPTION_POINTERS *ExceptionInfo)
{
	SYSTEMTIME sys; 
	GetLocalTime( &sys ); 
	char temp[128];
	char tempfilename[128];
	char tempgamefileName[128];
	char tempbmpfileName[128];

	sprintf_s(temp,"%4d%02d%02d%02d%02d%02d%03d\0",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wMinute,sys.wMilliseconds);
	sprintf_s(tempfilename,"%s.dmp\0",temp);
	HANDLE dumpFile = CreateFile(tempfilename,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
	char filePath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,filePath);
	char exeFilePath[2*MAX_PATH];
	//const char *exePath = "reportbugs\\reportbugs.exe";
	sprintf_s(exeFilePath,"%s\0",temp);

	MINIDUMP_EXCEPTION_INFORMATION dumpExceptioninfo;
	dumpExceptioninfo.ExceptionPointers = ExceptionInfo;
	dumpExceptioninfo.ThreadId = GetCurrentThreadId();
	dumpExceptioninfo.ClientPointers = TRUE;

	BOOL isWriteSucess = MiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),dumpFile,MiniDumpNormal,&dumpExceptioninfo,NULL,NULL);
	CloseHandle(dumpFile);
	if(CRNetApp::crGlobalHandle::isClient())
	{
		//�ر������߳�
		CRNet::crNetWorkReconnecter::getInstance()->clear();
		CRNet::crNetWorkUpdater::getInstance()->clear();
		CRNet::crNetBridge::shutdownGame();
		CRNet::crNetContainer::getInstance()->clear();

		if(CRNetApp::crGlobalHandle::getRunProtectHandle())
		{
			CloseHandle(CRNetApp::crGlobalHandle::getRunProtectHandle());
			CRNetApp::crGlobalHandle::setRunProtectHandle(NULL);
		}
		sprintf_s(tempfilename,"%s.txt\0",temp);
		CRIOManager::copyFile("glinfo.txt",tempfilename);

		char gbuf[256];
		//GLenum errorNo = glGetError();
		//sprintf(gbuf,"OpenGL error %s\n\0",gluErrorString(errorNo).c_str());
		//gDebugInfo->debugInfo(CRCore::NOTICE,gbuf);

		HANDLE handle = GetCurrentProcess();
		PROCESS_MEMORY_COUNTERS pmc;
		GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
		sprintf(gbuf, "Error:%d,�ڴ�ʹ��:%d,��ֵ�ڴ�:%d,�����ڴ�:%dKB,��ֵ�����ڴ�:%dKB\n\0", GetLastError(), pmc.WorkingSetSize / 1024, pmc.PeakWorkingSetSize / 1024, pmc.PagefileUsage / 1024, pmc.PeakPagefileUsage / 1024);
		gDebugInfo->debugInfo(CRCore::ALWAYS, gbuf);

		gDebugInfo->writeToFile();

		//WinExec(exeFilePath,SW_NORMAL);	
		//
		sprintf_s(tempgamefileName,"%sd.txt\0",temp);
		CRIOManager::copyFile("creature3d.txt",tempgamefileName);
			//����
		sprintf_s(tempbmpfileName,"%sd.bmp\0",temp);
		HDC hdc = GetDC(NULL);

		static int screenx = GetSystemMetrics(SM_CXSCREEN);
		static int screeny = GetSystemMetrics(SM_CYSCREEN);

		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, screenx, screeny);
		HDC hdcMem = CreateCompatibleDC(hdc);

		SelectObject(hdcMem, hBitmap);
		BitBlt(hdcMem, 0, 0, screenx, screeny, hdc, 0, 0, SRCCOPY);
		SaveBitmapToFile(tempbmpfileName,hdc,hBitmap);

		ReleaseDC(NULL, hdcMem);
		ReleaseDC(NULL, hdc);

		CRCore::ref_ptr<CRCore::crImage> image = CRIOManager::readImageFile(tempbmpfileName);
		if (image.valid())
		{
			std::string fileName = CRCore::crArgumentParser::getFileNameEliminateExt(tempbmpfileName) + ".jpg";
			CRIOManager::writeImageFile(*image,fileName);
		}
		DeleteFile(tempbmpfileName);

		UpLoadBugFile(std::string(exeFilePath));
		::Sleep(1000);
		WinExec(CRNetApp::crGlobalHandle::argvstr().c_str(),SW_NORMAL);
		TerminateProcess(GetCurrentProcess(),1);
	}
	else
	{
		CRNet::crNetConductor *dbServer = CRNet::crNetContainer::getInstance()->getNetConductor(CRNetApp::DBServer);
		if(dbServer)
		{
			CRNetApp::crDBServerCallback *callback = dynamic_cast<CRNetApp::crDBServerCallback *>(dbServer->getNetDataManager()->getNetCallback());
			if(callback)
			{
				callback->serverShutdown();
			}
		}
		//MessageBox(GetDesktopWindow(),CRNetApp::crGlobalHandle::argvstr().c_str(),"Creature3D",MB_OK);
		::Sleep(3000);
		WinExec(CRNetApp::crGlobalHandle::argvstr().c_str(),SW_NORMAL);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}
