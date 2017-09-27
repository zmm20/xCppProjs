/*
* �ļ���: Base64.h
* ����: Base64�����
* �汾: v1.0
* ����: door
* ʱ��: 2012��08��15�� ������
* �޶�:
*/

#ifndef BASE64_H
#define BASE64_H

class CBase64
{
public:
	/** ���캯�� */
	CBase64();

	/** �������� */
	virtual ~CBase64();

	/**
	base64����
	@param btSrc: ���, ԭ�ַ���
	@param nSrcLen: ���, ԭ�ַ����ĳ���(����'\0')
	@param btRet: ����, �������ַ���
	@param pnRetLen: ����, ������ַ����ĳ���(����'\0')
	@return �����ĳ��� ������ֵ<=0, �����ʧ��
	*/
	int EncodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen);

	/**
	base64����
	@param btSrc: ���, ԭ�ַ���
	@param nSrcLen: ���, ԭ�ַ����ĳ���(����'\0')
	@param btRet: ����, �������ַ���
	@param pnRetLen: ����, ������ַ����ĳ���(����'\0')
	@return �����ĳ��� ������ֵ<=0, �����ʧ��
	*/
	int DecodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen);
};

#endif  ///> BASE64_H