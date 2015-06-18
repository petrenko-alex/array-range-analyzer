#include "operations.h"
#include "operationList.h"

Operations::Operations()
{
	/*! Заполняем контейнер QMap операциями и их арностью */
	for (int i = 0; i < opsCount; ++i)
	{
		operations[QString(*ops[i])] = opsArity[i];
	}
}

Operations::~Operations()
{
}

int Operations::getArity(const QString &op)
{
	if (operations.contains(op))
	{
		return operations.value(op);
	}
	return 0;
}

bool Operations::isDefiniteOperation(const QString &op)
{
	return operations.contains(op);
}

bool Operations::isDefiniteVariable(const QString &var, const QVector<Index> &vars)
{
	auto it = vars.constBegin();
	auto endIt = vars.constEnd();

	for (; it != endIt; ++it)
	{
		if ((*it).name == var)
		{
			return true;
		}
	}
	return false;
}

bool Operations::isFloatNumber(const QString &number)
{
	// ^[-+]?[0-9]*\.?[0-9]+$ - problems with b2 #2 +-2, 2,21 , but 2b is OK
	QRegExp match("^[-+]?[0-9]*\.?[0-9]+$");
	return match.exactMatch(number);
}

bool Operations::isIntNumber(const QString &number)
{
	QRegExp match("^[+-]?[0-9]+$");
	return match.exactMatch(number);
}

bool Operations::isPositiveIntNumber(const QString &number)
{
	QRegExp match("^[+]?[0-9]+$");
	return match.exactMatch(number);
}

bool Operations::isOperand(const QString &operand, const QVector<Index> &vars, const QVector<Array> &arrs)
{
	return isIntNumber(operand) || isFloatNumber(operand) || isDefiniteVariable(operand, vars) || isDefiniteArray(operand, arrs);
}

bool Operations::isDefiniteArray(const QString &arr, const QVector<Array> &arrs)
{
	auto it = arrs.constBegin();
	auto endIt = arrs.constEnd();

	for (; it != endIt; ++it)
	{
		if ((*it).name == arr)
		{
			return true;
		}
	}
	return false;
}

bool Operations::isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<Index> &vars)
{
	return isOperand(element, vars, arrs) || isDefiniteOperation(element);
}
