#pragma once


class RevCellElemnet
{
private:
	int Row;			//��Ԫ��������
	int Col;			//��Ԫ��������
	CString Content;	//��Ԫ������
public:
	int getRow();
	void setRow(int row);

	int getCol();
	void setCol(int col);

	CString getContent();
	void setContent(CString content);
};

