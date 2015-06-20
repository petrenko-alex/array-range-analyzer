#include "operations.h"
#include "operationList.h"

Operations::Operations()
{
	/* Заполняем контейнер QMap операциями и их арностью */
	for (int i = 0; i < opsCount; ++i)
	{
		operations[QString(*ops[i])] = opsArity[i];
	}

	plus  = "+";
	minus = "-";
	dot	  = ".";
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
	int strSize = number.size();
	int dotFlag = false;
	int i = 0;

	if (strSize == 0)
		return false;

	if (number[0] == plus || number[0] == minus)
		i = 1;

	for (; i < strSize; ++i)
	{
		if (number[i] == dot)
		{
			if (!dotFlag)
				dotFlag = true;
			else
				return false;
		}
		
		if (!number[i].isDigit() && number[i] != dot)
		{
			return false;
		}
	}
	return true;
}

bool Operations::isIntNumber(const QString &number)
{
	int strSize = number.size();
	int i = 0;

	if (strSize == 0)
		return false;

	if (number[0] == plus || number[0] == minus)
		i = 1;

	for (; i < strSize; ++i)
	{
		if (!number[i].isDigit())
		{
			return false;
		}
	}
	return true;
}

bool Operations::isPositiveIntNumber(const QString &number)
{
	//QRegExp rx("^[+]?[0-9]+$");
	//return rx.exactMatch(number);
	int strSize = number.size();
	int i = 0;

	if (strSize == 0)
		return false;

	if (number[0] == plus)
		i = 1;

	for (; i < strSize; ++i)
	{
		if (!number[i].isDigit())
		{
			return false;
		}
	}
	return true;
}

bool Operations::isNumber(const QString &number)
{
	return isIntNumber(number) || isFloatNumber(number);
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

int Operations::findVar(QString var, const QVector<Index> &vars)
{
	int size = vars.size();
	for (int i = 0; i < size; ++i)
	{
		if (vars[i].name == var)
			return i;
	}
	return -1;
}

int Operations::findArr(QString arr, const QVector<Array> &arrs)
{
	int size = arrs.size();
	for (int i = 0; i < size; ++i)
	{
		if (arrs[i].name == arr)
			return i;
	}
	return -1;
}

double Operations::stringOpToDoubleOp(QString operand, const QVector<Index> &vars)
{
	int varIndex = -1;
	if (isDefiniteVariable(operand, vars))
	{
		varIndex = findVar(operand, vars);
		return vars[varIndex].curValue;
	}
	else
		return operand.toDouble();
}