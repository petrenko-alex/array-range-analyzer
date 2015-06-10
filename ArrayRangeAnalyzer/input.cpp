#include "input.h"

Input::Input()
{

}

Input::~Input()
{

}

bool Input::readData(const QStringList &inputFileNames, QVector <Index> &vars, QVector <Array> &arrs, QStringList &expr)
{
	return true;
}

void Input::readVarInfo(const QString fileName, QVector <Index> &vars) throw(QString&)
{

}

void Input::readVarAttributes(Index &var, QXmlStreamAttributes &atrs, int i) throw(QString&)
{

}

void Input::readArrInfo(const QString fileName, QVector <Array> &arrs) throw(QString&)
{

}

void Input::readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&)
{

}

void Input::readExpression(const QString fileName, QStringList &expr, const QVector<Index> &vars, const QVector<Array> &arrs) throw(QString&)
{

}
