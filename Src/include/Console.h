#ifndef _ZCONSOLE_H
#define _ZCONSOLE_H

#define __Z_CAN_CONSOLE__

#ifdef __Z_CAN_CONSOLE__


#include <stdio.h>
//#include <fstream>

class ZConsole{
public:
  HANDLE mh;
  char * ret;
  char * line;
  DWORD nWritten;

  ZConsole(){
    ret = "\r\n";
    line = "---------------------------------\r\n";
    mh = NULL;
    ::AllocConsole ();
	mh = ::GetStdHandle (STD_OUTPUT_HANDLE);

	COORD size = {100, 125};
	SetConsoleScreenBufferSize(mh,size); // 重新设置缓冲区大小
	SMALL_RECT rc = {0,0, 100-1, 25-1}; // 重置窗口位置和大小
	SetConsoleWindowInfo(mh,true ,&rc);
	
  }
	ZConsole& print_bitmapInfo(BITMAPINFO* pInfo){
		BITMAPINFOHEADER* pHeader = &pInfo->bmiHeader;
		*this<<"sizeof(BITMAPINFOHEADER):"<<sizeof(BITMAPINFOHEADER)<<"\r\n";
		*this<<"sizeof pHeader->biSize:"<<pHeader->biSize<<"\r\n";
		*this<<"width:"<<pHeader->biWidth<<"\r\n";
		*this<<"height:"<<pHeader->biHeight<<"\r\n";
		*this<<"biBitCount:"<<pHeader->biBitCount<<"\r\n";
		*this<<"biCompression:"<<pHeader->biCompression<<"\r\n";
		*this<<"biSizeImage:"<<pHeader->biSizeImage<<"\r\n";
		*this<<"bix:"<<pHeader->biXPelsPerMeter <<"\r\n";
		*this<<"biy:"<<pHeader->biYPelsPerMeter <<"\r\n";
		*this<<"bicu:"<<pHeader->biClrUsed <<"\r\n";
		*this<<"bici:"<<pHeader->biClrImportant <<"\r\n";

		return *this;
	}
  ZConsole& operator <<(const WCHAR * pStr){    
    return *this<<((WCHAR*)pStr);
  }
  ZConsole& operator <<(WCHAR * pStr){
	long len = (long)wcslen(pStr)*2 + 1;
	char *pMultiStr = new char[len];
	memset(pMultiStr, 0, len);
	WideCharToMultiByte(CP_ACP, 0, pStr, -1, pMultiStr, len, 0, 0);
    ::WriteFile(mh, pMultiStr, (DWORD)strlen(pMultiStr), &nWritten, NULL);
	delete[] pMultiStr;
    return *this;
  }
  ZConsole& operator <<(const char * pStr){    
    return *this<<((char*)pStr);
  }
  ZConsole& operator <<(char * pStr){
    if(pStr) ::WriteFile(mh, pStr,(DWORD)strlen(pStr), &nWritten, NULL);
    return *this;
  }
  ZConsole& operator <<(char c){
    return *this<<&c;
  }
  ZConsole& operator <<(short n){
    return *this<<(int)n;
  }
  ZConsole& operator <<(int n){
    char pStr[100];
    memset(pStr, 0, 100);
    ::sprintf(pStr, "%i", n);
    return *this<<pStr;
  }
// 	ZConsole& operator<<(HWND hwnd){
// 	  return *this<<(unsigned long)hwnd;
// 	}
  ZConsole& operator <<(unsigned short n){
    return *this<<(int)n;
  }
	ZConsole& operator <<(unsigned int n){
		return *this<<(int)n;
	}
//  ZConsole& operator <<(unsigned long n){
//    return *this<<(int)n;
//  }
	ZConsole& operator <<(long n){
		return *this<<(int)n;
	}
	ZConsole& operator <<(double n){
		return *this<<(float)n;
	}
  ZConsole& operator <<(float n){
    char pStr[100];
    memset(pStr, 0, 100);
    ::sprintf(pStr, "%f", n);
    return *this<<pStr;
  }
  ZConsole& operator <<(unsigned long n){
	  char pStr[11];
	  memset(pStr, 0, 11);
	  ::sprintf(pStr, "0x%08X", n);
	  return *this<<pStr;
  }	
	ZConsole& operator<<(RECT r){
		char pStr[100];
		memset(pStr, 0, 100);
		::sprintf(pStr, "l:%i, t:%i, r:%i b:%i, w:%i, h:%i\r\n", r.left, r.top, r.right, r.bottom, r.right - r.left, r.bottom - r.top);
		return *this<<pStr;
	}
	ZConsole& operator<<(POINT pt){
		char pStr[100];
		memset(pStr, 0, 100);
		::sprintf(pStr, "x:%i, y:%i\r\n", pt.x, pt.y);
		return *this<<pStr;
	}
	ZConsole& operator<<(SIZE size){
		char pStr[100];
		memset(pStr, 0, 100);
		::sprintf(pStr, "w:%i, h:%i\r\n", size.cx, size.cy);
		return *this<<pStr;
	}
#ifdef _OBJBASE_H_
	ZConsole& operator<<(GUID guid){
		WCHAR pStr[100];
		memset(pStr, 0, 100*sizeof(WCHAR));
		StringFromGUID2(guid, pStr, 100);
		return *this<<pStr;
	}
#endif
#ifdef DIRECT3D_VERSION
	ZConsole& operator<<(D3DMATRIX mat)
	{
		*this<<mat._11<<" "<<mat._12<<" "<<mat._13<<" "<<mat._14<<"\n";
		*this<<mat._21<<" "<<mat._22<<" "<<mat._23<<" "<<mat._24<<"\n";
		*this<<mat._31<<" "<<mat._32<<" "<<mat._33<<" "<<mat._34<<"\n";
		*this<<mat._41<<" "<<mat._42<<" "<<mat._43<<" "<<mat._44<<"\n\n";
		return *this;
	}
#endif
	/*
	void wf(const char* pFileName, const char* pContent){
		std::ofstream ostm(pFileName);
		ostm<<pContent;
		ostm.close();
	}
	void af(const char* pFileName, const char* pContent){
	  std::ofstream ostm(pFileName, std::ios::app);
		ostm<<pContent;
		ostm.close();
	}*/
  /*
	static CString ToStrGuid(GUID& gid){
		USES_CONVERSION;
		BSTR bstr;
		CString strGid;
		char* pStr = NULL;
		::StringFromCLSID(gid, &bstr);
		pStr = OLE2T(bstr);
		
		strGid = pStr;
		return strGid;
  }*/
  ~ZConsole()
  {
    if(mh)
	{
      ::CloseHandle (mh);
	  mh = NULL;
      ::FreeConsole ();
    }
  }
};

#endif

#ifndef __Z_CAN_CONSOLE__

class ZConsole{
public:
  ZConsole(){}
	ZConsole& print_bitmapInfo(BITMAPINFO* pInfo){return *this;}
  ZConsole& operator <<(const char * pStr){return *this;}
  ZConsole& operator <<(char * pStr){return *this;}
  ZConsole& operator <<(char c){return *this;}
  ZConsole& operator <<(short n){return *this;}
  ZConsole& operator <<(int n){return *this;}
  ZConsole& operator <<(unsigned short n){return *this;}
	ZConsole& operator <<(unsigned int n){return *this;}
  ZConsole& operator <<(unsigned long n){return *this;}
	ZConsole& operator <<(long n){return *this;}
	ZConsole& operator <<(double n){return *this;}
  ZConsole& operator <<(float n){return *this;}
	ZConsole& operator<<(RECT r){return *this;}
#ifdef DIRECT3D_VERSION
	ZConsole& operator<<(D3DMATRIX mat){return *this;}
#endif
	///void wf(const char* pFileName, const char* pContent){}
	///void af(const char* pFileName, const char* pContent){}
  ~ZConsole(){}
};

#endif


#endif