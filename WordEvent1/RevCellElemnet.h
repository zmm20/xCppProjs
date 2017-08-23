#pragma once


class RevCellElemnet
{
private:
	int Row;			//单元格所在行
	int Col;			//单元格所在列
	CString Content;	//单元格内容
public:
	int getRow();
	void setRow(int row);

	int getCol();
	void setCol(int col);

	CString getContent();
	void setContent(CString content);
};

