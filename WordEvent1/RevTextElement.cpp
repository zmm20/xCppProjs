#include "StdAfx.h"
#include "RevTextElement.h"

long RevTextElement::getMtype()
{
	return this->mType;
}
void RevTextElement::setMtype(long mtype)
{
	this->mType=mtype;
}

CString RevTextElement::getContent()
{
	return this->content;
}
void RevTextElement::setContent(CString content)
{
	this->content=content;
}