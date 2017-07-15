/*
* 文件名: Base64.cpp
* 功能: Base64编解码
* 版本: v1.0
* 作者: door
* 时间: 2012年08月15日 星期三
* 修订:
*/

#include <stdlib.h>

#include "Base64.h"

/** 构造函数 */
CBase64::CBase64()
{

}

/** 析构函数 */
CBase64::~CBase64()
{

}

/**
base64编码
@param btSrc: 入参, 原字符串
@param nSrcLen: 入参, 原字符串的长度(包含'\0')
@param btRet: 出参, 编码后的字符串
@param pnRetLen: 出参, 编码后字符串的长度(包含'\0')
@return 编码后的长度 若返回值<=0, 则编码失败
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
base64解码
@param btSrc: 入参, 原字符串
@param nSrcLen: 入参, 原字符串的长度(包含'\0')
@param btRet: 出参, 解码后的字符串
@param pnRetLen: 出参, 解码后字符串的长度(包含'\0')
@return 解码后的长度 若返回值<=0, 则解码失败
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
