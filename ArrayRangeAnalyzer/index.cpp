#include "index.h"

Index::Index()
{
	this->name		= "";
	this->from      = 0;
	this->to        = 0;
	this->curValue  = 0;
	this->prevValue = 1.23456789;
	this->step		= 0;
	this->looped	= 10;
	this->usedInExpression = false;
}

Index::Index(QString name, int from, int to, int step, int looped /*= 10*/)
{
	this->name		= name;
	this->from		= from;
	this->to		= to;
	this->curValue	= from;
	this->prevValue = 1.23456789;
	this->step		= step;
	this->looped	= looped;
}

bool Index::operator==(const Index &other)
{
	return this->name	   == other.name
		&& this->from	   == other.from
		&& this->to		   == other.to
		&& this->step	   == other.step
		&& this->curValue  == other.curValue
		&& this->prevValue == other.prevValue
		&& this->looped	   == other.looped;
}

Index::~Index()
{

}
