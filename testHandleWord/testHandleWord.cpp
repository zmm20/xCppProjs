/// ����word �ĵ�
///
/// @author zhoumanman888@126.com
/// @date 2017.7.20

#include "stdafx.h"
#include "testHandleWord.h"
#include <string>
#include <iostream>
#include <memory>
#ifdef _DEBUG
#include "Debug\MSO.tlh"
#include "Debug\MSWORD.tlh"
#define new DEBUG_NEW
#endif


const CLSID CLSID_Application = { 0x000209FF,0x0000,0x0000,{ 0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 } };
const IID IID_IApplication = { 0x00020905,0x0000,0x0000,{ 0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 } };

const CLSID CLSID_Global = { 0x000209F0,0x0000,0x0000,{ 0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 } };


// Ψһ��Ӧ�ó������
CWinApp theApp;

using namespace std;

int main()
{
    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule == nullptr)
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: GetModuleHandle ʧ��\n");
        return 1;
    }

    // ��ʼ�� MFC ����ʧ��ʱ��ʾ����
    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
    {
        // TODO: ���Ĵ�������Է���������Ҫ
        wprintf(L"����: MFC ��ʼ��ʧ��\n");
        return 1;
    }

    cout << "hello world" << endl;

    HRESULT hr = OleInitialize(nullptr);
    if (FAILED(hr))
    {
        cerr << "��ʼ�� com ʧ��" << endl;
        return 1;
    }

    wstring word_file_in = LR"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\testHandleWord\test\test.docx)";
    wstring word_file_out = LR"(C:\Users\zmm\Documents\Visual Studio 2015\Projects\xCppProjs\testHandleWord\test\test_out.docx)";
    /*
        http://www.eefocus.com/wang312/blog/13-05/294401_16a48.html
        hr = CoCreateInstance ( CLSID_ShellLink,         // coclass ��CLSID
        NULL,                    // �����þۺ�
        CLSCTX_INPROC_SERVER,    // ����������
        IID_IShellLink,          // �ӿڵ�IID
        (void**) &pISL );        // ָ��ӿڵ�ָ��
    */
    CComQIPtr<MSWord::_Application> app;
    // method 1:
    hr = app.CoCreateInstance(CLSID_Application, NULL, CLSCTX_SERVER);
    // method 2:
    //hr = app.CoCreateInstance(OLESTR("Word.Application"), NULL, CLSCTX_SERVER);
    if (FAILED(hr)) {
        app.Release();
        OleUninitialize();
        cerr << "CoCreateInstance failed!" << endl;
        return 1;
    }
    // ������ʾ
    app->put_Visible(VARIANT_TRUE);

    MSWord::Documents* pDocs = nullptr;
    hr = app->get_Documents(&pDocs);
    if (FAILED(hr)) {
        app->Quit();
        app.Release();
        OleUninitialize();
        cerr << "get_Documents failed!" << endl;
        return 1;
    }
    
    MSWord::_Document* pDoc = nullptr;
    // ���ĵ�
    // ��������ֻ������
    hr = pDocs->Open(&CComVariant(word_file_in.data()), &vtMissing, &CComVariant(false), &vtMissing, &vtMissing
        , &vtMissing, &vtMissing, &vtMissing, &vtMissing
        , &vtMissing, &vtMissing, &CComVariant(true)
        , &vtMissing, &vtMissing, &vtMissing, &vtMissing, &pDoc);
    if (FAILED(hr)) {
        app->Quit();
        app.Release();
        OleUninitialize();
        cerr << "open failed!" << endl;
        return 1;
    }
    
    cout << "test 1, �����½������Ϊ" << endl;
    {// ����������
        //hr = pDocs->Add(&CComVariant(L""), &CComVariant(false), &CComVariant(MSWord::wdNewBlankDocument), &CComVariant(true), &pDoc);
        //if (FAILED(hr)) {
        //    OleUninitialize();
        //    cerr << "save failed!" << endl;
        //    return 1;
        //}

        //hr = pDoc->SaveAs(&CComVariant(word_file_out.data()));
        //if (FAILED(hr)) {
        //    OleUninitialize();
        //    cerr << "save failed!" << endl;
        //    return 1;
        //}
    }

    cout << "test 2, �����ı��滻" << endl;
    {
        //BSTR bs;

        // method 1:
        //MSWord::Range* pRange = nullptr;
        //hr = pDoc->Range(&CComVariant(0), &CComVariant(20), &pRange);
        //if (FAILED(hr)) {
        //    OleUninitialize();
        //    cerr << "Range failed!" << endl;
        //    return 1;
        //}
        //hr = pRange->get_Text(&bs);
        //if (FAILED(hr)) {
        //    OleUninitialize();
        //    cerr << "get_Text failed!" << endl;
        //    return 1;
        //}

        // method 2:
        //MSWord::Selection* pSel = nullptr;
        //hr = app->get_Selection(&pSel);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "get_Selection failed!" << endl;
        //    return 1;
        //}
        //if (pSel == nullptr)
        //{
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "pSel equal null!" << endl;
        //    return 1;
        //}            
        //hr = pSel->WholeStory();
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "WholeStory failed!" << endl;
        //    return 1;
        //}
        //hr = pSel->get_Text(&bs);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "get_Text failed!" << endl;
        //    return 1;
        //}

        // method 3:
        //MSWord::StoryRanges* pStoryRange = nullptr;
        //pDoc->get_StoryRanges(&pStoryRange);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "get_StoryRanges failed!" << endl;
        //    return 1;
        //}
        //MSWord::Range* pRange = nullptr;
        //hr = pStoryRange->Item(MSWord::wdMainTextStory, &pRange);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "Item failed!" << endl;
        //    return 1;
        //}
        //hr = pRange->get_Text(&bs);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "get_Text failed!" << endl;
        //    return 1;
        //}

        //_bstr_t b = bs;
        //char* wcstr = b;
        //cout << wcstr << endl;
        //SysFreeString(bs);

        //// �滻
        //bs = SysAllocString(L"hello word");
        //hr = pRange->put_Text(bs);
        //SysFreeString(bs);
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "get_Text failed!" << endl;
        //    return 1;
        //}
        //// ���Ϊ:
        //hr = pDoc->SaveAs(&CComVariant(word_file_out.data()));
        //if (FAILED(hr)) {
        //    app->Quit();
        //    OleUninitialize();
        //    cerr << "save failed!" << endl;
        //    return 1;
        //}
    }
    cout << endl;

    cout << "test 3, ����и�" << endl;
    {// �иߵļ��������word �ĵ��ɼ�, ����ѡ�����ݲ��ٵ�ǰ����, ��߶�Ϊ-1;
        //MSWord::Paragraphs* pParas = nullptr;
        //hr = pDoc->get_Paragraphs(&pParas);
        //assert(SUCCEEDED(hr), "paras get failed"); // ����ʱ����, ע����static_assert ������

        //BSTR tmp;
        //long moveUnit = -1;
        //while (moveUnit)
        //{
        //    // �и�
        //    // 1> ���Ȼ�õ�ǰ��������
        //    MSWord::SelectionPtr pSel = nullptr;
        //    app->get_Selection(&pSel);
        //    MSWord::RangePtr pRange = nullptr;
        //    pSel->get_Range(&pRange);
        //    MSWord::WindowPtr pWin = nullptr;
        //    pDoc->get_ActiveWindow(&pWin);
        //    LONG x1, y1, w1, h1;
        //    pWin->GetPoint(&x1, &y1, &w1, &h1, pRange);

        //    VARIANT pageNumber;
        //    pSel->get_Information(wdActiveEndPageNumber, &pageNumber);
        //    VARIANT lineNumber;
        //    pSel->get_Information(wdFirstCharacterLineNumber, &lineNumber);
        //    VARIANT pos;
        //    pSel->get_Information(wdVerticalPositionRelativeToPage, &pos);
        //    cout << "page numer: " << pageNumber.lVal << ", line number: " << lineNumber.lVal << ", ����page��ʼ�Ĵ�ֱλ��(��): " << pos.fltVal<< endl;

        //    // �ƶ�һ��
        //    hr = pSel->MoveDown(&CComVariant(wdLine), &CComVariant(1), &vtMissing, &moveUnit);
        //    assert(SUCCEEDED(hr), "text get failed");
        //    cout << "move unit: " << moveUnit << endl;
        //    pSel->get_Range(&pRange);
        //    pDoc->get_ActiveWindow(&pWin);
        //    LONG x2, y2, w2, h2;
        //    pWin->GetPoint(&x2, &y2, &w2, &h2, pRange);
        //    cout << "�и�: " << y2 - y1 << endl;
        //}
        
    }
    cout << endl;

    cout << "test 4, ���_Global ����" << endl;
    {
        //CComQIPtr<MSWord::_Global> pGb;
        //hr = pGb.CoCreateInstance(CLSID_Global, NULL, CLSCTX_SERVER);
        //if (FAILED(hr)) {
        //    OleUninitialize();
        //    cerr << "_Global CoCreateInstance failed!" << endl;
        //    return 1;
        //}

        //float ff;
        //hr = pGb->PointsToPixels(100, &CComVariant(true), &ff); // ת����ֱ�����, ��==>����
        //if (SUCCEEDED(hr))
        //    cout << "��ֱ����: 100(��) = " << ff << "(����)"<< endl;
        //else
        //    cerr << "error PointsToPixels" << endl;

        //hr = pGb->PointsToPixels(100, &CComVariant(false), &ff); // ת��ˮƽ�����, ��==>����
        //if (SUCCEEDED(hr))
        //    cout << "ˮƽ����: 100(��) = " << ff << "(����)" << endl;
        //else
        //    cerr << "error PointsToPixels" << endl;
    }
    cout << endl;

    cout << "test 5" << endl;
    {
        // 1> ���Ȼ�õ�ǰ��������
        MSWord::TablesPtr pTbls = nullptr;
        pDoc->get_Tables(&pTbls);
        if (pTbls == nullptr)
        {
            cout << "get tables failed" << endl;
            return S_OK;
        }
        
        MSWord::TablePtr pTbl = nullptr;
        pTbls->Item(1, &pTbl);
        MSWord::RangePtr pRange = nullptr;
        long nCol = 2;
        long nRow = 3;
        for (int r = 1; r <= nRow; ++r)
        {
            for (int c = 1; c <= nCol; ++c)
            {
                // ��λ����Ԫ��
                MSWord::CellPtr pCell = nullptr;
                pTbl->Cell(r, c, &pCell);

                //pRange = pCell->Range;
                hr = pCell->get_Range(&pRange);
                if (SUCCEEDED(hr))
                {
                    pRange->put_Text(CComBSTR("test"));
                }
            }
        }
    }
    cout << endl;

    cout << "please enter 'exit' to quit program!" << endl;
    std::string off = "";
    while (off != "exit")
        cin >> off;

    app->Quit();
    app.Release();
    OleUninitialize();

    return 0;
}
