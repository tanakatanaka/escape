#ifndef DEF_ModelID_H
#define DEF_ModelID_H

#include "DxLib.h"


/** ���f����delete���y�ɂ��邽�߂̃��b�p */
class ModelID
{
	int id;

public:
	ModelID() : id(-1) {}
	void operator =(int n) { id = n; }
	operator int() { return id; }
	~ModelID() { MV1DeleteModel(id); }
};

#endif
