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
	/* Если операция известна */
	if (operations.contains(op))
	{
		/* Возвращаем ее арность */
		return operations.value(op);
	}
	/* Нуль как признак ошибки */
	return 0;
}

bool Operations::isDefiniteOperation(const QString &op)
{
	/* Проверяем наличие символа в контейнере определенных операций */
	return operations.contains(op);
}

bool Operations::isDefiniteVariable(const QString &var, const QVector<Index> &vars)
{
	/* Итераторы на вектор переменных */
	auto it = vars.constBegin();
	auto endIt = vars.constEnd();

	/* Проходим по вектору переменных */
	for (; it != endIt; ++it)
	{
		/* Ищем переменную с соответствующим именем*/
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

	/* Если строка пуста */
	if (strSize == 0)
		return false;

	/* На первом месте может быть + или + */
	if (number[0] == plus || number[0] == minus)
	{
		/* Не может быть только знак + или - (без цифр) */
		if (strSize < 2)
			return false;

		i = 1;
	}

	/* Проверка оставшейся части строки на содержание только цифр и 1 точки */
	for (; i < strSize; ++i)
	{
		/* Если i-ый символ строки - точка */
		if (number[i] == dot)
		{
			if (!dotFlag)
				dotFlag = true;
			else
				return false;
		}
		/* Если i-ый символ строки - не точка и не цифра */
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

	/* Если строка пуста */
	if (strSize == 0)
		return false;

	/* На первом месте может быть + или + */
	if (number[0] == plus || number[0] == minus)
	{
		/* Не может быть только знак + или - (без цифр) */
		if (strSize < 2)
			return false;

		i = 1;
	}

	/* Проверка оставшейся части строки на содержание только цифр  */
	for (; i < strSize; ++i)
	{
		/* Если i-ый символ строки - не цифра */
		if (!number[i].isDigit())
		{
			return false;
		}
	}
	return true;
}

bool Operations::isPositiveIntNumber(const QString &number)
{
	int strSize = number.size();
	int i = 0;

	/* Если строка пуста */
	if (strSize == 0)
		return false;

	/* На первом месте может быть + */
	if (number[0] == plus)
	{
		/* Не может быть только знак + или - (без цифр) */
		if (strSize < 2)
			return false;

		i = 1;
	}
	/* Проверка оставшейся части строки на содержание только цифр  */
	for (; i < strSize; ++i)
	{
		/* Если i-ый символ строки - не цифра */
		if (!number[i].isDigit())
		{
			return false;
		}
	}
	return true;
}

bool Operations::isNumber(const QString &number)
{
	/* Символ должен являться либо целым, либо вещественным числом */
	return isIntNumber(number) || isFloatNumber(number);
}

bool Operations::isOperand(const QString &operand, const QVector<Index> &vars, const QVector<Array> &arrs)
{
	/* Символ должен являться либо числом, либо переменной, либо массивом */
	return isIntNumber(operand) || isFloatNumber(operand) || isDefiniteVariable(operand, vars) || isDefiniteArray(operand, arrs);
}

bool Operations::isDefiniteArray(const QString &arr, const QVector<Array> &arrs)
{
	/* Итераторы на вектор массивов */
	auto it = arrs.constBegin();
	auto endIt = arrs.constEnd();
	/* Проходим по вектору массивов */
	for (; it != endIt; ++it)
	{
		/* Ищем массив с соответствующим именем*/
		if ((*it).name == arr)
		{
			return true;
		}
	}
	return false;
}

bool Operations::isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<Index> &vars)
{
	/* Символ должен являться либо операндом, либо операцией */
	return isOperand(element, vars, arrs) || isDefiniteOperation(element);
}

int Operations::findVar(QString var, const QVector<Index> &vars)
{
	int size = vars.size();
	/* Проходим по вектору переменных */
	for (int i = 0; i < size; ++i)
	{
		/* Ищем индекс переменной с переданным именем */
		if (vars[i].name == var)
			return i;
	}
	return -1;
}

int Operations::findArr(QString arr, const QVector<Array> &arrs)
{
	int size = arrs.size();
	/* Проходим по вектору массивов */
	for (int i = 0; i < size; ++i)
	{
		/* Ищем индекс массива с переданным именем */
		if (arrs[i].name == arr)
			return i;
	}
	return -1;
}

double Operations::stringOpToDoubleOp(QString operand, const QVector<Index> &vars)
{
	int varIndex = -1;
	/* Если переданный символ - имя переменной */
	if (isDefiniteVariable(operand, vars))
	{
		/* Находим ее и возвращаем ее значение */
		varIndex = findVar(operand, vars);
		return vars[varIndex].curValue;
	}
	/* Если переданный символ содержит число */
	else
		return operand.toDouble();
}