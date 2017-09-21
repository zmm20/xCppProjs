#include "TextHelper.h"
#include <codecvt> //wstring_convert
#include <iostream>
#include <boost/locale/encoding.hpp>
#include <vector>

XAB_NAMESPACE_START


std::string TextHelper::GBK2UTF(const std::string& src) noexcept
{
	/*
#ifdef _MSC_VER
    const std::string localeName = "CHS"; // ".936";
#else
    const string localeName = "zh_CN.GBK";
#endif
    try
    {
        std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cv1(new std::codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        const std::wstring ws = cv1.from_bytes(src);

        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        return myconv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        std::cerr<<"GBK2UTF: " << e.what();
        return src;
    }
	*/
	
	// 上面的方法有时候会转换失败, 但是boost 转换却成功
	try
    {
        return boost::locale::conv::to_utf<char>(src, "GBK");
    }
    catch (std::exception& e)
    {
		std::cerr<<"GBK2UTF: " << e.what();
        return src;
    }
}

std::string TextHelper::UTF2GBK(const std::string& src) noexcept
{
	/*
#ifdef _MSC_VER
    const std::string localeName = "CHS"; //".936";
#else
    const std::string localeName = "zh_CN.GBK";
#endif
    try
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
        const std::wstring ws = myconv.from_bytes(src);

        std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> cv(new std::codecvt_byname<wchar_t, char, mbstate_t>(localeName));
        return cv.to_bytes(ws);
    }
    catch (std::exception& e)
    {
        std::cerr << "UTF2GBK: " << e.what();
        return src;
    }*/
	
	// 上面的方法有时候会转换失败, 但是boost 转换却成功
	try
    {
        return boost::locale::conv::from_utf<char>(src, "GBK");
    }
    catch (std::exception& e)
    {
		std::cerr<<"UTF2GBK: " << e.what();
        return src;
    }
}


std::wstring TextHelper::to_wstring(const std::string& str, const std::locale& loc) noexcept
{
    std::vector<wchar_t> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());
    return std::wstring(buf.data(), buf.size());
}

std::string TextHelper::to_string(const std::wstring& str, const std::locale& loc) noexcept
{
    std::vector<char> buf(str.size());
    std::use_facet<std::ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '?', buf.data());
    return std::string(buf.data(), buf.size());
}


XAB_NAMESPACE_END