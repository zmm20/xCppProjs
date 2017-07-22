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

#ifndef _IMAGE_EXTRACTOR_H_
#define _IMAGE_EXTRACTOR_H_

#include <podofo/podofo.h>
#include <string>
#include <vector>
#include <map>

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH

/** This class uses the PoDoFo lib to parse 
 *  a PDF file and to write all images it finds
 *  in this PDF document to a given directory.
 *
 *  modified by zhoumanman@126.com
 */
class CImageExtractor {
 public:
    CImageExtractor();
    virtual ~CImageExtractor();

    /**
     * \param pnNum pointer to an integer were 
     *        the number of processed images can be stored
     *        or null if you do not want this information.
     */
    void Init( const char* pszInput);

    /**
     * \returns the number of succesfully extracted images
     */
    inline int GetNumImagesExtracted() const;

    /// 获得图片路径列表
    std::vector<std::string> getImages();
 private:
    /** Extracts the image form the given PdfObject
     *  which has to be an XObject with Subtype "Image"
     *  \param pObject a handle to a PDF object
     *  \param bJpeg if true extract as a jpeg, otherwise create a ppm
     *  \returns ErrOk on success
     */
    void ExtractImage( PoDoFo::PdfObject* pObject, bool bJpeg );

    /** This function checks wether a file with the 
     *  given filename does exist.
     *  \returns true if the file exists otherwise false
     */
    bool    FileExists( const char* pszFilename );

 private:
    unsigned int m_nSuccess;
    unsigned int m_nCount;

    char         m_szBuffer[MAX_PATH];
    std::string m_tmpPath;
    std::vector<std::string> m_imgPathList; ///< 图片路径, 暂时无法确定图片是属于那一页, 所以先用第几张图片来区别
    //std::map<int, std::vector<std::string>> m_pageImgPathList; // 页码---图片路径
};

inline int CImageExtractor::GetNumImagesExtracted() const
{
    return m_nSuccess;
}

#endif // _IMAGE_EXTRACTOR_H_
