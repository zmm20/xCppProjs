// testHandleWord.cpp : 定义控制台应用程序的入口点。
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


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int main()
{
    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule == nullptr)
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        return 1;
    }

    // 初始化 MFC 并在失败时显示错误
    if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: MFC 初始化失败\n");
        return 1;
    }

    cout << "hello world" << endl;

    HRESULT hr = OleInitialize(nullptr);
    if (FAILED(hr))
    {
        cerr << "初始化 com 失败" << endl;
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
    {// 新增及保存
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
    {// 打开文档

         // 可能遇到只读错误
         hr = pDocs->Open(&CComVariant(word_file_in.data()), &vtMissing, &CComVariant(false), &vtMissing, &vtMissing
             , &vtMissing, &vtMissing, &vtMissing, &vtMissing
             , &vtMissing, &vtMissing, &CComVariant(true) // 设置不可见
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
        // 注意, 如果以不可见方式打开, 则 MSWord::Selection 对象始终未nullptr
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

        // 替换
        bs = SysAllocString(L"hello word");
        hr = pRange->put_Text(bs);
        SysFreeString(bs);
        if (FAILED(hr)) {
            app->Quit();
            OleUninitialize();
            cerr << "get_Text failed!" << endl;
            return 1;
        }
        // 另存为:
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
