// testHandleWord.cpp : �������̨Ӧ�ó������ڵ㡣
//

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
    CComQIPtr<MSWord::_Application> app;
    hr = app.CoCreateInstance(OLESTR("Word.Application"), NULL, CLSCTX_SERVER); // OLESTR("Word.Application")
    if (FAILED(hr)) {
        OleUninitialize();
        cerr << "CoCreateInstance failed!" << endl;
        return 1;
    }

    MSWord::Documents* pDocs = nullptr;
    hr = app->get_Documents(&pDocs);
    if (FAILED(hr)) {
        app->Quit();
        OleUninitialize();
        cerr << "get_Documents failed!" << endl;
        return 1;
    }
    MSWord::_Document* pDoc = nullptr;
    
    cout << "test 1" << endl;
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

    cout << "test 2" << endl;
    {// ���ĵ�

         // ��������ֻ������
         hr = pDocs->Open(&CComVariant(word_file_in.data()), &vtMissing, &CComVariant(false), &vtMissing, &vtMissing
             , &vtMissing, &vtMissing, &vtMissing, &vtMissing
             , &vtMissing, &vtMissing, &CComVariant(true) // ���ò��ɼ�
             , &vtMissing, &vtMissing, &vtMissing, &vtMissing, &pDoc);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "open failed!" << endl;
            return 1;
        }

        BSTR bs;

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
        // ע��, ����Բ��ɼ���ʽ��, �� MSWord::Selection ����ʼ��δnullptr
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
        MSWord::StoryRanges* pStoryRange = nullptr;
        pDoc->get_StoryRanges(&pStoryRange);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "get_StoryRanges failed!" << endl;
            return 1;
        }
        MSWord::Range* pRange = nullptr;
        hr = pStoryRange->Item(MSWord::wdMainTextStory, &pRange);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "Item failed!" << endl;
            return 1;
        }
        hr = pRange->get_Text(&bs);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "get_Text failed!" << endl;
            return 1;
        }

        _bstr_t b = bs;
        char* wcstr = b;
        cout << wcstr << endl;
        SysFreeString(bs);

        // �滻
        bs = SysAllocString(L"hello word");
        hr = pRange->put_Text(bs);
        SysFreeString(bs);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "get_Text failed!" << endl;
            return 1;
        }
        // ���Ϊ:
        hr = pDoc->SaveAs(&CComVariant(word_file_out.data()));
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "save failed!" << endl;
            return 1;
        }
    }
    cout << endl;

    char off;
    cin >> off;



    app->Quit();
    OleUninitialize();

    return 0;
}
