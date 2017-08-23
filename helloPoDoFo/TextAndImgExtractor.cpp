#include "TextAndImgExtractor.h"
#include <my/TextHelper.h>
#include <stack>
#include <iostream>
#include <cstdio>
using namespace PoDoFo;
using namespace std;

CTextAndImgExtractor::CTextAndImgExtractor()
    : m_nSuccess(0), m_nCount(0)
    , m_tmpPath(std::getenv("temp"))
{
}


CTextAndImgExtractor::~CTextAndImgExtractor()
{
}

void CTextAndImgExtractor::Init(const char* pszInput)
{
    if (!pszInput)
    {
        PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
    }
    m_pagesTxtMap.clear();
    m_imgPathMap.clear();
    m_objs.Clear();

    PdfMemDocument document(pszInput);
    m_objs = document.GetObjects();

    m_pageCount = document.GetPageCount();
    for (int i = 0; i < m_pageCount; i++)
    {
        PdfPage* pPage = document.GetPage(i);

        this->ExtractText(&document, pPage);
        this->ExtractImage(&document, pPage);
    }
}

void CTextAndImgExtractor::ExtractImage(PoDoFo::PdfMemDocument* pDocument, PoDoFo::PdfPage* pPage)
{
    try
    {
        PdfObject* pResourceOfPage = pPage->GetResources();
        if (pResourceOfPage == nullptr)
            return;

        PdfObject* pXObjs = pResourceOfPage->GetDictionary().GetKey(PoDoFo::PdfName("XObject"));
        if (pXObjs == nullptr)
            return;

        TKeyMap km = pXObjs->GetDictionary().GetKeys();
        PdfObject*  pObjItem = nullptr;
        for (const auto& pair : km)
        {
            cout << pair.first.GetName() << endl;

            pObjItem = pXObjs->GetDictionary().GetKey(PdfName(pair.first.GetName()));
            if (pObjItem == nullptr && !pObjItem->IsReference())
                continue;

            const PdfReference& ref = pObjItem->GetReference();
            cout << ref.ToString() << endl;
            PdfObject* pObjTmp = m_objs.GetObject(ref);

            PdfObject* pObjType = pObjTmp->GetDictionary().GetKey(PdfName::KeyType);
            PdfObject* pObjSubType = pObjTmp->GetDictionary().GetKey(PdfName::KeySubtype);
            if ((pObjType && pObjType->IsName() && (pObjType->GetName().GetName() == "XObject")) ||
                (pObjSubType && pObjSubType->IsName() && (pObjSubType->GetName().GetName() == "Image")))
            {
                const PdfObject*  pObj = pObjTmp->GetDictionary().GetKey(PdfName::KeyFilter);
                if (pObj && pObj->IsArray() && pObj->GetArray().GetSize() == 1 &&
                    pObj->GetArray()[0].IsName() && (pObj->GetArray()[0].GetName().GetName() == "DCTDecode"))
                    pObj = &pObj->GetArray()[0];

                if (pObj && pObj->IsName() && (pObj->GetName().GetName() == "DCTDecode"))
                {
                    // The only filter is JPEG -> create a JPEG file
                    ExportImage(pObjTmp, true, pPage->GetPageNumber());
                }
                else
                {
                    ExportImage(pObjTmp, false, pPage->GetPageNumber());
                }

                // 为什么要释放?? 
                //pDocument->FreeObjectMemory(pObjTmp);
            }
        }
    }
    catch (PdfError & e) {
        fprintf(stderr, "Error: An error %i ocurred during counting pages in the pdf file.\n", e.GetError());
        e.PrintErrorMsg();
        return;
    }
}

void CTextAndImgExtractor::ExportImage(PoDoFo::PdfObject* pObject, bool bJpeg, int pageNo)
{
    FILE*       hFile = NULL;
    const char* pszExtension = bJpeg ? "jpg" : "ppm";

    snprintf(m_szBuffer, MAX_PATH, "%s/pdfimage_%04i_%03i.%s", m_tmpPath.c_str(), m_nCount++, pageNo, pszExtension);

    hFile = fopen(m_szBuffer, "wb");
    if (!hFile)
    {
        PODOFO_RAISE_ERROR(ePdfError_InvalidHandle);
    }

    printf("-> Writing image object %s to the file: %s\n", pObject->Reference().ToString().c_str(), m_szBuffer);

    if (bJpeg)
    {
        PdfMemStream* pStream = dynamic_cast<PdfMemStream*>(pObject->GetStream());
        fwrite(pStream->Get(), pStream->GetLength(), sizeof(char), hFile);
    }
    else
    {
        //long lBitsPerComponent = pObject->GetDictionary().GetKey( PdfName("BitsPerComponent" ) )->GetNumber();
        // Create a ppm image
        const char* pszPpmHeader = "P6\n# Image extracted by PoDoFo\n%li %li\n%li\n";


        fprintf(hFile, pszPpmHeader,
            pObject->GetDictionary().GetKey(PdfName("Width"))->GetNumber(),
            pObject->GetDictionary().GetKey(PdfName("Height"))->GetNumber(),
            255);

        char*    pBuffer;
        pdf_long lLen;
        pObject->GetStream()->GetFilteredCopy(&pBuffer, &lLen);
        fwrite(pBuffer, lLen, sizeof(char), hFile);
        free(pBuffer);
    }

    fclose(hFile);
    ++m_nSuccess;

    // m_imgPathMap[pageNo] = std::string(m_szBuffer);
    // insert 比[] 效率更高
    m_imgPathMap.insert({ pageNo , std::string(m_szBuffer)});
}

void CTextAndImgExtractor::ExtractText(PoDoFo::PdfMemDocument* pDocument, PoDoFo::PdfPage* pPage)
{
    const char*      pszToken = NULL;
    PdfVariant       var;
    EPdfContentsType eType;

    PdfContentsTokenizer tokenizer(pPage);

    double dCurPosX = 0.0;
    double dCurPosY = 0.0;
    bool   bTextBlock = false;
    PdfFont* pCurFont = NULL;

    std::stack<PdfVariant> stack;


    while (tokenizer.ReadNext(eType, pszToken, var))
    {
        if (eType == ePdfContentsType_Keyword)
        {
            // support 'l' and 'm' tokens
            if (strcmp(pszToken, "l") == 0 ||
                strcmp(pszToken, "m") == 0)
            {
                dCurPosX = stack.top().GetReal();
                stack.pop();
                dCurPosY = stack.top().GetReal();
                stack.pop();
            }
            else if (strcmp(pszToken, "BT") == 0)
            {
                bTextBlock = true;
                // BT does not reset font
                // pCurFont     = NULL;
            }
            else if (strcmp(pszToken, "ET") == 0)
            {
                if (!bTextBlock)
                    fprintf(stderr, "WARNING: Found ET without BT!\n");
            }

            if (bTextBlock)
            {
                if (strcmp(pszToken, "Tf") == 0)
                {
                    stack.pop();
                    PdfName fontName = stack.top().GetName();
                    PdfObject* pFont = pPage->GetFromResources(PdfName("Font"), fontName);
                    if (!pFont)
                    {
                        PODOFO_RAISE_ERROR_INFO(ePdfError_InvalidHandle, "Cannot create font!");
                    }

                    pCurFont = pDocument->GetFont(pFont);
                    if (!pCurFont)
                    {
                        fprintf(stderr, "WARNING: Unable to create font for object %i %i R\n",
                            pFont->Reference().ObjectNumber(),
                            pFont->Reference().GenerationNumber());
                    }
                }
                else if (strcmp(pszToken, "Tj") == 0 ||
                    strcmp(pszToken, "'") == 0)
                {
                    AddTextElement(dCurPosX, dCurPosY, pCurFont, stack.top().GetString(), pPage->GetPageNumber());
                    stack.pop();
                }
                else if (strcmp(pszToken, "\"") == 0)
                {
                    AddTextElement(dCurPosX, dCurPosY, pCurFont, stack.top().GetString(), pPage->GetPageNumber());
                    stack.pop();
                    stack.pop(); // remove char spacing from stack
                    stack.pop(); // remove word spacing from stack
                }
                else if (strcmp(pszToken, "TJ") == 0)
                {
                    PdfArray array = stack.top().GetArray();
                    stack.pop();

                    for (int i = 0; i<static_cast<int>(array.GetSize()); i++)
                    {
                        if (array[i].IsString() || array[i].IsHexString())
                            AddTextElement(dCurPosX, dCurPosY, pCurFont, array[i].GetString(), pPage->GetPageNumber());
                    }
                }
            }
        }
        else if (eType == ePdfContentsType_Variant)
        {
            stack.push(var);
        }
        else
        {
            // Impossible; type must be keyword or variant
            PODOFO_RAISE_ERROR(ePdfError_InternalLogic);
        }
    }
}

void CTextAndImgExtractor::AddTextElement(double dCurPosX, double dCurPosY, PoDoFo::PdfFont* pCurFont, const PoDoFo::PdfString & rString, int nPage)
{
    if (!pCurFont)
    {
        fprintf(stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString());
        return;
    }

    if (!pCurFont->GetEncoding())
    {
        fprintf(stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString());
        return;
    }

    // For now just write to console
    PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode(rString, pCurFont);
    const std::string u8Str(unicode.GetStringUtf8());

    m_pagesTxtMap[nPage] += XAB::CTextHelper::UTF2GBK(u8Str);
}

CTextAndImgExtractor::PageNode_t CTextAndImgExtractor::getPage(int pageNo) noexcept
{
    PageNode_t pn;
    auto itFindTxt =m_pagesTxtMap.find(pageNo);
    if (itFindTxt == m_pagesTxtMap.end())
        pn.strText = "";
    else
        pn.strText = itFindTxt->second;


    auto ImgE = m_imgPathMap.equal_range(pageNo);
    for (auto it = ImgE.first; it != ImgE.second; ++it)
        pn.imgURIs.push_back(it->second);
    return pn;
}