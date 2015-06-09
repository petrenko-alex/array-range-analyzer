#include "operations.h"

operations::operations()
{
}

operations::~operations()
{
}

int operations::getArity(const QString &op)
{
	return 0;
}

bool operations::isDefiniteOperation(const QString &op)
{
	return false;
}

bool operations::isDefiniteVariable(const QString &var, const QVector<index> &vars)
{
	return false;
}

bool operations::isFloatNumber(const QString &number)
{
	return false;
}

bool operations::isIntNumber(const QString &number)
{
	return false;
}

bool operations::isPositiveIntNumber(const QString &number)
{
	return false;
}

bool operations::isOperand(const QString &operand, const QVector<index> &vars, const QVector<Array> &arrs)
{
	return false;
}

bool operations::isDefiniteArray(const QString &arr, const QVector<Array> &arrs)
{
	return false;
}

bool operations::isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<index> &vars)
{
	return false;
}
