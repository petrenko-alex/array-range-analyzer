#include "operations.h"
#include "operationList.h"

operations::operations()
{

	/*! Заполняем контейнер QMap операциями и их арностью */
	for (int i = 0; i < opsCount; ++i)
	{
		Operations[QString(*ops[i])] = opsArity[i];
	}
}

operations::~operations()
{
}

int operations::getArity(const QString &op)
{
	if (Operations.contains(op))
	{
		return Operations.value(op);
	}
	return 0;
}

bool operations::isDefiniteOperation(const QString &op)
{
	return Operations.contains(op);
}

bool operations::isDefiniteVariable(const QString &var, const QVector<index> &vars)
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

bool operations::isFloatNumber(const QString &number)
{
	// ^[-+]?[0-9]*\.?[0-9]+$ - problems with b2 #2 +-2, 2,21 , but 2b is OK
	QRegExp match("^[-+]?[0-9]*\.?[0-9]+$");
	return match.exactMatch(number);
}

bool operations::isIntNumber(const QString &number)
{
	QRegExp match("^[+-]?[0-9]+$");
	return match.exactMatch(number);
}

bool operations::isPositiveIntNumber(const QString &number)
{
	QRegExp match("^[+]?[0-9]+$");
	return match.exactMatch(number);
}

bool operations::isOperand(const QString &operand, const QVector<index> &vars, const QVector<Array> &arrs)
{
	// Добавить целые числа??????????????????????????????????????????????????????????

	return isFloatNumber(operand) || isDefiniteVariable(operand, vars) || isDefiniteArray(operand, arrs);
}

bool operations::isDefiniteArray(const QString &arr, const QVector<Array> &arrs)
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

bool operations::isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<index> &vars)
{
	return isOperand(element, vars, arrs) || isDefiniteOperation(element);
}
