// CalcCtl.cpp : CCalcCtl ��ʵ��
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

    // ���������ʼӦ�÷ŵ��߳���
    m_result = m_a + m_b;

    // ���������������߳��е���, ����ͨ�����߳��� SendMessage, Ȼ������Ϣ��Ӧ�����е���
    // ����������, �ͻ��Ļ�ý��Ϊnull, ��2, 3���ÿ���ȡ�÷��ؽ��.
    // Ҳ����˵, �¼��Ĳ���Ӧ����[in] ������[out, retval]. �������ʲôǰ׺������, ��Ĭ�ϱ�ʾ[in]
    //Fire_AddCompleted(&m_result);

    //Fire_AddCompleted2(&m_result);

    Fire_AddCompleted3(&m_result);


    return S_OK;
}