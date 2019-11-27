#pragma once

//#include <Windows.h>
#include <Winuser.h>
#include <string.h>
#include <string>
#include <afxwin.h>

class dataCopy {
public:
	dataCopy(std::string windowName);
	void sendMessage(std::string message);
	BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* cds);

private:
	HWND windowHandle;
};