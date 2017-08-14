/***************************************************************************
 *   Copyright (C) 2005 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "ImageExtractor.h"

#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#ifdef _MSC_VER
#define snprintf _snprintf
#endif

using namespace PoDoFo;
using namespace std;

CImageExtractor::CImageExtractor()
    : m_nSuccess( 0 ), m_nCount( 0 )
    , m_tmpPath(std::getenv("temp"))
{
}

CImageExtractor::~CImageExtractor()
{
}

void CImageExtractor::Init( const char* pszInput)
{
    if( !pszInput)
        return;

    try
    {
        PdfMemDocument document( pszInput );
        m_imgPathMap.clear();

        // 我修改后的代码, 增加了定位图片是那一页的功能
        PdfVecObjects objs = document.GetObjects();
        int nCount = document.GetPageCount();
        for (int i = 0; i<nCount; i++)
        {
            PdfPage* pPage = document.GetPage(i);
            PdfObject* pResourceOfPage = pPage->GetResources();
            if (pResourceOfPage == nullptr)
                continue;

            PdfObject* pXObjs = pResourceOfPage->GetDictionary().GetKey(PoDoFo::PdfName("XObject"));
            if (pXObjs == nullptr)
                continue;

            TKeyMap km = pXObjs->GetDictionary().GetKeys();
            cout << "page no: " << i + 1 << " all key: " << endl;
            PdfObject*  pObjItem = nullptr;
            for (const auto& pair : km)
            {
                cout << pair.first.GetName() << endl;

                pObjItem = pXObjs->GetDictionary().GetKey(PdfName(pair.first.GetName()));
                if (pObjItem == nullptr && !pObjItem->IsReference())
                    continue;

                const PdfReference& ref = pObjItem->GetReference();
                cout << ref.ToString() << endl;
                PdfObject* pObjTmp = objs.GetObject(ref);

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
                        ExtractImage(pObjTmp, true, i + 1);
                    }
                    else
                    {
                        ExtractImage(pObjTmp, false, i + 1);
                    }

                    // 为什么要释放?? 
                    document.FreeObjectMemory(pObjTmp);
                }
            }
        }
    }
    catch (PdfError & e) {
        fprintf(stderr, "Error: An error %i ocurred during counting pages in the pdf file.\n", e.GetError());
        e.PrintErrorMsg();
        return;
    }
}

void CImageExtractor::ExtractImage( PdfObject* pObject, bool bJpeg, int pageNo)
{
    FILE*       hFile        = NULL;
    const char* pszExtension = bJpeg ? "jpg" : "ppm"; 

    snprintf(m_szBuffer, MAX_PATH, "%s/pdfimage_%04i_%03i.%s", m_tmpPath.c_str(), m_nCount++, pageNo, pszExtension);
    
    hFile = fopen( m_szBuffer, "wb" );
    if( !hFile )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    printf("-> Writing image object %s to the file: %s\n", pObject->Reference().ToString().c_str(), m_szBuffer);

    if( bJpeg )
    {
        PdfMemStream* pStream = dynamic_cast<PdfMemStream*>(pObject->GetStream());
        fwrite( pStream->Get(), pStream->GetLength(), sizeof(char), hFile );
    }
    else
    {
        //long lBitsPerComponent = pObject->GetDictionary().GetKey( PdfName("BitsPerComponent" ) )->GetNumber();
        // Create a ppm image
        const char* pszPpmHeader = "P6\n# Image extracted by PoDoFo\n%li %li\n%li\n";
        
        
        fprintf( hFile, pszPpmHeader, 
                 pObject->GetDictionary().GetKey( PdfName("Width" ) )->GetNumber(),
                 pObject->GetDictionary().GetKey( PdfName("Height" ) )->GetNumber(),
                 255 );
                 
        char*    pBuffer;
        pdf_long lLen;
        pObject->GetStream()->GetFilteredCopy( &pBuffer, &lLen );
        fwrite( pBuffer, lLen, sizeof(char), hFile );
        free( pBuffer );
    }

    fclose( hFile );
    ++m_nSuccess;

    m_imgPathMap[pageNo] = std::string(m_szBuffer);
}

bool CImageExtractor::FileExists( const char* pszFilename )
{
    bool result = true;
    
    // if there is an error, it's probably because the file doesn't yet exist
    struct stat	stBuf;
    if ( stat( pszFilename, &stBuf ) == -1 )	result = false;

    return result;
}