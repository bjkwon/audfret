// WndDlg0.cpp: implementation of the CWndDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "audfret.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndDlg::CWndDlg()
: hDlg(NULL)
{
	hInst = GetModuleHandle(NULL);
}

CWndDlg::~CWndDlg()
{

}

BOOL CWndDlg::SetWindowText(const char *text) 
{
	return ::SetWindowText(hDlg, text);
}
BOOL CWndDlg::GetWindowRect(LPRECT lpRect) 
{
	return ::GetWindowRect (hDlg, lpRect); 
}
UINT_PTR CWndDlg::SetTimer(UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) 
{ 
	return ::SetTimer(hDlg, nIDEvent, uElapse, lpTimerFunc); 
}
BOOL CWndDlg::KillTimer(UINT_PTR nIDEvent) 	
{
	return ::KillTimer(hDlg, nIDEvent);	
}
BOOL CWndDlg::MoveWindow (int x, int y, int nWidth, int nHeight, BOOL bRepaint) 	
{ 
	return ::MoveWindow (hDlg, x, y, nWidth, nHeight, bRepaint); 
}
BOOL CWndDlg::MoveWindow (LPCRECT lpRect, BOOL bRepaint) 
{ 
	return ::MoveWindow (hDlg, lpRect->left, lpRect->top, lpRect->right-lpRect->left, lpRect->bottom-lpRect->top, bRepaint); 
}
BOOL CWndDlg::MoveWindow (HWND hCtrl, LPCRECT lpRect, BOOL bRepaint) 
{ 
	return ::MoveWindow (hCtrl, lpRect->left, lpRect->top, lpRect->right-lpRect->left, lpRect->bottom-lpRect->top, bRepaint); 
}
LONG_PTR CWndDlg::SetWindowLongPtr(int nIndex, LONG dwNewLong) 
{
	return ::SetWindowLongPtr(hDlg, nIndex, dwNewLong); 
}
LONG_PTR CWndDlg::GetWindowLongPtr(int nIndex) 
{ 
	return ::GetWindowLong(hDlg, nIndex); 
}
int CWndDlg::PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	return ::PostMessage (hDlg, Msg, wParam, lParam);
}
int CWndDlg::MessageBox (LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType)
{ 
	return ::MessageBox (hDlg, lpszText, lpszCaption, nType);
}
LRESULT CWndDlg::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage (hDlg, Msg, wParam, lParam); 
}
HWND CWndDlg::ChildWindowFromPoint(POINT Point) 
{ 
	return ::ChildWindowFromPoint(hDlg, Point); 
}

int CWndDlg::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{ 
	// hDlg may remain NULL unless other messages prior to WM_INITDIALOG has caught and set it up.
	char fullmoduleName[MAX_PATH], moduleName[MAX_PATH];
 	char drive[16], dir[256], ext[8], buffer[MAX_PATH];
 	GetModuleFileName(hInst, fullmoduleName, MAX_PATH);
 	_splitpath(fullmoduleName, drive, dir, buffer, ext);
 	sprintf (moduleName, "%s%s", buffer, ext);
 	sprintf (AppPath, "%s%s", drive, dir);
	strcpy(AppName, buffer);
	strcpy(AppRunName, moduleName);
	if (hwndFocus) hDlg = GetParent(hwndFocus);
	return 1;
}

void CWndDlg::OnClose()
{
	DestroyWindow();
}

BOOL CWndDlg::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(hDlg, nCmdShow);
}

void CWndDlg::OnCommand(int idc, HWND hwndCtl, UINT event)
{
	switch(idc)
	{
	case IDCANCEL:
		::PostQuitMessage(0);
		break;
	}
}

int CWndDlg::SetDlgItemText(int idc, LPCTSTR str) const
{
	return ::SetDlgItemText(hDlg, idc, str);
}

int CWndDlg::SetDlgItemInt(int idc, UINT uValue, BOOL bSigned) const
{
	return ::SetDlgItemInt(hDlg, idc, uValue, bSigned);
}

int CWndDlg::GetDlgItemText(int idc, char *strOut, int len) const
{
	return ::GetDlgItemText(hDlg, idc, strOut, len);
}

HWND CWndDlg::GetDlgItem(int idc)
{
	return ::GetDlgItem(hDlg,idc);
}

int CWndDlg::GetDlgItemInt(int idc, BOOL* lpTranslated, int bSigned) const
{ 
	return ::GetDlgItemInt(hDlg, idc, lpTranslated, bSigned); 
}

int CWndDlg::GetDlgItemText(int idc, CString &strOut) const
{
	int res, size=MAX_PATH;
	res = ::GetDlgItemText (hDlg, idc, strOut.GetBuffer(size), size);
	while (res>=size-1)
	{
		size *=2;
		res = ::GetDlgItemText (hDlg, idc, strOut.GetBuffer(size), size);
	}
	strOut.ReleaseBuffer();
	return res;
}


int CWndDlg::GetWindowText(CString& strOut) const
{
	int res, size=MAX_PATH;
	res = ::GetWindowText (hDlg, strOut.GetBuffer(size), size);
	while (res>=size-1)
	{
		size *=2;
		res = ::GetWindowText (hDlg, strOut.GetBuffer(size), size);
	}
	strOut.ReleaseBuffer();
	return res;
}

int CWndDlg::GetWindowText(char *strOut, int len) const
{
	return ::GetWindowText(hDlg, strOut, len);
}

LRESULT CWndDlg::SendDlgItemMessage(int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	return ::SendDlgItemMessage(hDlg, nIDDlgItem, Msg, wParam, lParam); 
}


void CWndDlg::GetLastErrorStr(CString &errstr)
{
	char  string[256];

	GetLastErrorStr(string);
		errstr = string;
	return;
}

void CWndDlg::GetLastErrorStr(char *errstr)
{
	char string[256];
	DWORD WindowsError, nchar;
	WindowsError = GetLastError();

	nchar = FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL, WindowsError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
							(LPTSTR) string, sizeof(string), NULL  );
	if (nchar == 0)	MessageBox ("Failed to translate Windows error");
	else strcpy(errstr, string);
	return;
}
BOOL CWndDlg::InvalidateRect(CONST RECT *lpRect, BOOL bErase)
{
	return ::InvalidateRect(hDlg, lpRect, bErase);
}

BOOL CWndDlg::DestroyWindow()
{
	return ::DestroyWindow(hDlg);
}