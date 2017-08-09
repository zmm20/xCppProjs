#pragma once
class RevTextElement
{
private:
	long mType;				//修订类型
	CString content;		//修订的内容
public:
	long getMtype();
	void setMtype(long mtype);

	CString getContent();
	void setContent(CString content);
};

