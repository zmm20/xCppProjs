#pragma once
class RevTextElement
{
private:
	long mType;				//�޶�����
	CString content;		//�޶�������
public:
	long getMtype();
	void setMtype(long mtype);

	CString getContent();
	void setContent(CString content);
};

