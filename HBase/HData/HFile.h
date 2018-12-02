#pragma once
#include "HObject.h"
#include <QFile>
class HFile :
	public HObject
{
	H_OBJECT(HFile);
public:
	HFile();
	~HFile();
};
