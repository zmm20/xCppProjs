// CalcCtl.cpp : CCalcCtl 的实现
#include "stdafx.h"
#include "CalcCtl.h"


// CCalcCtl


STDMETHODIMP CCalcCtl::Add(DOUBLE a, DOUBLE b, DOUBLE* result)
{
    *result = a + b;

    return S_OK;
}


STDMETHODIMP CCalcCtl::AddAsync(DOUBLE a, DOUBLE b)
{
    m_a = a;
    m_b = b;

    // 下面这句起始应该放到线程中
    m_result = m_a + m_b;

    // 下面这句必须在主线程中调用, 可以通过在线程中 SendMessage, 然后在消息相应函数中调用
    // 下面这句调用, 客户的获得结果为null, 而2, 3调用可以取得返回结果.
    // 也就是说, 事件的参数应该是[in] 而不是[out, retval]. 另外如果什么前缀都不加, 则默认表示[in]
    //Fire_AddCompleted(&m_result);

    //Fire_AddCompleted2(&m_result);

    Fire_AddCompleted3(&m_result);


    return S_OK;
}