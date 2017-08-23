// MyWindow.cpp : CMyWindow µÄÊµÏÖ
#include "stdafx.h"
#include "MyWindow.h"


// CMyWindow


STDMETHODIMP CMyWindow::get_Port(USHORT* pVal)
{
    *pVal = m_Port;

    return S_OK;
}


STDMETHODIMP CMyWindow::put_Port(USHORT newVal)
{
    m_Port = newVal;

    return S_OK;
}
