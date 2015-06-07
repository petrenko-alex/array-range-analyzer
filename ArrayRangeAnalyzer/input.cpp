#include "input.h"

input::input()
{

}

input::~input()
{

}

bool input::readData(const QStringList &inputFileNames, QVector <index> &vars, QVector <Array> &arrs, QStringList &expr)
{
	return true;
}

void input::readVarInfo(const QString fileName, QVector <index> &vars) throw(QString&)
{

}

void input::readVarAttributes(index &var, QXmlStreamAttributes &atrs, int i) throw(QString&)
{

}

void input::readArrInfo(const QString fileName, QVector <Array> &arrs) throw(QString&)
{

}

void input::readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&)
{

}

void input::readExpression(const QString fileName, QStringList &expr, const QVector<index> &vars, const QVector<Array> &arrs) throw(QString&)
{

}
