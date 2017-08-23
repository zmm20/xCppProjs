#include "stdafx.h"
#include "ChildDlg.h"

BOOL CALLBACK ShowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hParent = GetParent(hWnd);
        RECT wndRect;

        GetWindowRect(hParent, &wndRect);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);
        ShowWindow(hWnd, SW_SHOW);
        break;
    }
    default:
        return FALSE;
    }
    return TRUE;
}
