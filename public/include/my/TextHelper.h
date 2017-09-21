/// ���ļ�������Ŀ����
///
/// @author zhoumanman888@126.com
/// @file TextHelper.h
/// @date 2017.07.17

#pragma once

#include <string>
#define XAB_NAMESPACE_START namespace XAB {
#define XAB_NAMESPACE_END };


XAB_NAMESPACE_START

namespace TextHelper
{
    /// ��gbk����, ת��Ϊutf8����
    ///
    /// @author zhoumanman888@126.com
    std::string UTF2GBK(const std::string& src) noexcept;

    /// ��utf8����, ת��Ϊgbk����
    ///
    /// @author zhoumanman888@126.com
    std::string GBK2UTF(const std::string& src) noexcept;
	
	/// convert string to wstring
    ///
    /// @author zhoumanman888@126.com
    std::wstring to_wstring(const std::string& str, const std::locale& loc = std::locale()) noexcept;
	/// convert wstring to string with ��?�� as default character
    ///
    /// @author zhoumanman888@126.com
    std::string to_string(const std::wstring& str, const std::locale& loc = std::locale()) noexcept;
};

XAB_NAMESPACE_END