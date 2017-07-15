/*
* 文件名: Base64.h
* 功能: Base64编解码
* 版本: v1.0
* 作者: door
* 时间: 2012年08月15日 星期三
* 修订:
*/

#ifndef BASE64_H
#define BASE64_H

class CBase64
{
public:
	/** 构造函数 */
	CBase64();

	/** 析构函数 */
	virtual ~CBase64();

	/**
	base64编码
	@param btSrc: 入参, 原字符串
	@param nSrcLen: 入参, 原字符串的长度(包含'\0')
	@param btRet: 出参, 编码后的字符串
	@param pnRetLen: 出参, 编码后字符串的长度(包含'\0')
	@return 编码后的长度 若返回值<=0, 则编码失败
	*/
	int EncodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen);

	/**
	base64解码
	@param btSrc: 入参, 原字符串
	@param nSrcLen: 入参, 原字符串的长度(包含'\0')
	@param btRet: 出参, 解码后的字符串
	@param pnRetLen: 出参, 解码后字符串的长度(包含'\0')
	@return 解码后的长度 若返回值<=0, 则解码失败
	*/
	int DecodeBase64(unsigned char *btSrc, int nSrcLen, unsigned char *btRet, int *pnRetLen);
};

#endif  ///> BASE64_H