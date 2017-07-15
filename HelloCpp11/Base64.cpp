/*
* �ļ���: Base64.cpp
* ����: Base64�����
* �汾: v1.0
* ����: door
* ʱ��: 2012��08��15�� ������
* �޶�:
*/

#include <stdlib.h>

#include "Base64.h"

/** ���캯�� */
CBase64::CBase64()
{

}

/** �������� */
CBase64::~CBase64()
{

}

/**
base64����
@param btSrc: ���, ԭ�ַ���
@param nSrcLen: ���, ԭ�ַ����ĳ���(����'\0')
@param btRet: ����, �������ַ���
@param pnRetLen: ����, ������ַ����ĳ���(����'\0')
@return �����ĳ��� ������ֵ<=0, �����ʧ��
*/
int CBase64::EncodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen)
{
	int i = 0, j = 0, k = 0;   
	unsigned char EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";   

	i = (nSrcLen+2) / 3 * 4; // get EncodeBase64 buffer size
	if (btRet != NULL)   
	{   
		if (*pnRetLen < i) // less than EncodeBase64 need size
		{
			return -1;
		}   
		*pnRetLen = i; // return EncodeBase64 buffer size
	}   
	else  
	{   
		*pnRetLen = i;   
		return 0;   
	}   

	k = nSrcLen - nSrcLen % 3;   
	for (i = j = 0; i < k; i += 3)
	{   
		btRet[j++] = EncodeBase64Map[(btSrc[i]>>2) & 0x3F];   
		btRet[j++] = EncodeBase64Map[((btSrc[i]<<4) + (btSrc[i + 1]>>4)) & 0x3F];   
		btRet[j++] = EncodeBase64Map[((btSrc[i + 1]<<2) + (btSrc[ i + 2]>>6)) & 0x3F];   
		btRet[j++] = EncodeBase64Map[btSrc[i + 2] & 0x3F];   
	}   
	k = nSrcLen - k ;   
	if (1 == k)   
	{   
		btRet[j++] = EncodeBase64Map[(btSrc[i]>>2) & 0x3F];   
		btRet[j++] = EncodeBase64Map[(btSrc[i]<<4) & 0x3F];   
#if 0
		btRet[j++] = btRet[j] = '=';   
#else
		btRet[j + 1] = btRet[j] = '=';
		j++;
#endif
	}   
	else if(2 == k)   
	{   
		btRet[j++] = EncodeBase64Map[(btSrc[i]>>2) & 0x3F];   
		btRet[j++] = EncodeBase64Map[((btSrc[i]<<4) + (btSrc[i + 1]>>4)) & 0x3F];   
		btRet[j++] = EncodeBase64Map[(btSrc[i + 1]<<2) & 0x3F];   
		btRet[j] = '=';   
	}   

	return ++j; 
}

/**
base64����
@param btSrc: ���, ԭ�ַ���
@param nSrcLen: ���, ԭ�ַ����ĳ���(����'\0')
@param btRet: ����, �������ַ���
@param pnRetLen: ����, ������ַ����ĳ���(����'\0')
@return �����ĳ��� ������ֵ<=0, �����ʧ��
*/
int CBase64::DecodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen)
{
	int i = 0, j = 0;   
	unsigned char EncodeBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	unsigned char DecodeBase64Map[256] = {0};   

	for (j = nSrcLen; j > 0 && '=' == btSrc[j - 1]; --j); // ignore "="
	i = (j / 4) * 3 + (j % 4 + 1) / 2; // DecodeBase64 length

	if (btRet != NULL)   
	{   
		if (*pnRetLen < i) // Given buffer size less than decodeBase64 buffer
		{
			return -1;
		}   
		*pnRetLen = i; // return decodeBase64 buffer size
	}   
	else  
	{   
		*pnRetLen = i;
		return 0;   
	}   

	j = sizeof(EncodeBase64Map);
	for (i = 0; i < j; ++i)
	{   
		DecodeBase64Map[EncodeBase64Map[i]] = i;
	}

	for (i = j = 0; i < nSrcLen; i+=4)
	{
		btRet[j++] = DecodeBase64Map[btSrc[i    ]] << 2 | DecodeBase64Map[btSrc[i + 1]] >> 4;
		btRet[j++] = DecodeBase64Map[btSrc[i + 1]] << 4 | DecodeBase64Map[btSrc[i + 2]] >> 2;
		btRet[j++] = DecodeBase64Map[btSrc[i + 2]] << 6 | DecodeBase64Map[btSrc[i + 3]];
	}

	return *pnRetLen;
}
