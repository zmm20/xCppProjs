/// ���ļ�������Ŀ����
///
/// @author zhoumanman888@126.com
/// @file common.h
/// @date 2017.07.17

#pragma once

#include <string>
#define XAB_NAMESPACE_START namespace XAB {
#define XAB_NAMESPACE_END };


XAB_NAMESPACE_START

struct CTextHelper
{
    /// ��gbk����, ת��Ϊutf8����
    ///
    /// @author zhoumanman888@126.com
    static std::string UTF2GBK(const std::string& src) noexcept;

    /// ��utf8����, ת��Ϊgbk����
    ///
    /// @author zhoumanman888@126.com
    std::string GBK2UTF(const std::string& src) noexcept;
};

XAB_NAMESPACE_END