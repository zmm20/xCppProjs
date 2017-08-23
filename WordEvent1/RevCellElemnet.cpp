#include "StdAfx.h"
#include "RevCellElemnet.h"

int RevCellElemnet::getRow()
{
		return this->Row;	   
}
void RevCellElemnet::setRow(int row)
{
	this->Row=row;
}
int RevCellElemnet::getCol()
{
	return this->Col;
}
void RevCellElemnet::setCol(int col)
{
	this->Col=col;
}

CString RevCellElemnet::getContent()
{
	return this->Content;
}
void RevCellElemnet::setContent(CString content)
{
	this->Content=content;
}