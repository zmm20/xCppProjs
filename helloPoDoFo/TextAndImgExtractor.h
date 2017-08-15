#pragma once
#include <podofo/podofo.h>
#include <unordered_map>
#include <string>
#include <vector>

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH


/// ��pdf ����ȡ�ı���ͼƬ
///
/// @author zhoumanman888@126.com
/// @date 2017.8.12
class CTextAndImgExtractor
{
public:
    typedef std::unordered_map<int, std::string> PageText_t;
    typedef std::unordered_multimap<int, std::string> PageImagePa_t; // һҳ���ܰ�������ͼƬ
    typedef struct
    {
        std::string strText;
        std::vector<std::string> imgURIs;
    } PageNode_t;
public:
    CTextAndImgExtractor();
    ~CTextAndImgExtractor();

    void Init(const char* pszInput);
    inline int getPagesCount() noexcept;
    /// ȡ�õڼ�ҳ������, ��Ŵ� 1 ��ʼ
    PageNode_t getPage(int pageNo) noexcept;

    /**
    * \returns the number of succesfully extracted images
    */
    inline int GetNumImagesExtracted() const;
    inline const PageText_t& getPageTxts() const;
    inline const PageImagePa_t& getImages() const;
private:
    void ExtractImage(PoDoFo::PdfMemDocument* pDocument, PoDoFo::PdfPage* pPage);
    void ExportImage(PoDoFo::PdfObject* pObject, bool bJpeg, int pageNo = -1);

    void ExtractText(PoDoFo::PdfMemDocument* pDocument, PoDoFo::PdfPage* pPage);

    /** Adds a text string to a list which can be sorted by
    *  position on the page later, so that the whole structure
    *  of the text including formatting can be reconstructed.
    *
    *  \param dCurPosX x position of the text
    *  \param dCurPosY y position of the text
    *  \param pCurFont font of the text
    *  \param rString the actual string
    */
    void AddTextElement(double dCurPosX, double dCurPosY, PoDoFo::PdfFont* pCurFont, const PoDoFo::PdfString & rString, int nPage);
private:
    unsigned int m_nSuccess;
    unsigned int m_nCount;
    int m_pageCount;
    PoDoFo::PdfVecObjects m_objs;

    char m_szBuffer[MAX_PATH];
    std::string m_tmpPath;
    PageText_t m_pagesTxtMap; ///< ҳ��---����
    PageImagePa_t m_imgPathMap; ///< ͼƬ·��, ��ʱ�޷�ȷ��ͼƬ��������һҳ, �������õڼ���ͼƬ������
};

inline int CTextAndImgExtractor::getPagesCount() noexcept
{
    return m_pageCount;
}

inline int CTextAndImgExtractor::GetNumImagesExtracted() const
{
    return m_nSuccess;
}

inline const CTextAndImgExtractor::PageText_t& CTextAndImgExtractor::getPageTxts() const
{
    return m_pagesTxtMap;
}
inline const CTextAndImgExtractor::PageImagePa_t& CTextAndImgExtractor::getImages() const
{
    return m_imgPathMap;
}
