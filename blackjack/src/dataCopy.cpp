#include "dataCopy.h"
#include <iostream>

dataCopy::dataCopy(std::string windowName) {
	LPCTSTR windowTag = (LPCTSTR) windowName.c_str();
	windowHandle = FindWindow(NULL, windowTag);

	if (!windowHandle)
		throw std::invalid_argument("The window name does not exist");
}

void dataCopy::sendMessage(std::string message) {
	LPWSTR data = (LPWSTR) message.c_str();
	COPYDATASTRUCT dataToSend; // = {0};

	dataToSend.dwData = 498; // TODO: Replace with const
	dataToSend.cbData = sizeof(TCHAR) * (_tcslen(data) + 1);
	dataToSend.lpData = data;

	SendMessage(windowHandle, WM_COPYDATA, 0, (LPARAM)&dataToSend);
}

BOOL dataCopy::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* cds) {
		std::cout << "Recieved: " << cds->lpData;
	if (cds->dwData == 498) {
		std::cout << "Recieved Data: " << cds->lpData;
	}
}