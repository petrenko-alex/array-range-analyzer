#include "analyzer.h"

Analyzer::Analyzer()
{

}

Analyzer::~Analyzer()
{

}

void Analyzer::analyzeExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{

}

void Analyzer::checkExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&)
{

}

void Analyzer::addition(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = leftOpD + rightOpD;
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::substraction(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = leftOpD - rightOpD;
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::division(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� �������� ������� �� ����*/
		if (rightOpD == 0)
		{ 
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = leftOpD / rightOpD;
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::multiplication(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = leftOpD * rightOpD;
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::modulo(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� �������� ������� �� ���� */
		if (rightOpD == 0)
		{
			QString errorString = "Division by zero is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
			throw errorString;
		}
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = (int)leftOpD % (int)rightOpD;
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::subscript(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QVector<Exceeding> &exceedings)
{
	int varsSize = vars.size();
	/*! ��������� ������ �������� ������� - ������� �� �����*/
	stackElement rightElement = operands.pop();
	rightOpS = rightElement.element;
	rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
	unaryMinusOrTypeConversion(rightElement, rightOpD);
	/*! �������� ������� ������ ��� ������� */
	int arr = ops.findArr(curArr.name, arrs);
	int exceedingsSize = arrs[arr].isExceeding.size();
	/*! ���� ��� �������� ��������� ������� ��� ��� ������ */
	if (!arrs[arr].isExceeding[curArr.dimension])
	{ 
		/*! ���� ���������� ����� - ������ ������ ������� ��� ������ 0 */
		if (rightOpD >= arrs[arr].size[curArr.dimension] || rightOpD < 0)
		{
			/*! ������� ���������� */
			QStringList indexNames;
			QVector<double> indexValues;
			/*! ���������� �������� indexNames � indexValues */
			for (int i = 0; i < varsSize; ++i)
			{
				if (vars[i].usedInExpression)
				{
					indexNames << vars[i].name;
					indexValues << vars[i].curValue;
					vars[i].usedInExpression = false;
				}
			}
			exceedings << Exceeding(curArr.name, indexNames, indexValues, rightOpD, (curArr.dimension + 1));
			arrs[arr].isExceeding[curArr.dimension] = true;
			/*! � ���� �������� �������������� ������� */
			stackElement element(undefined);
			operands.push(element);
		}
		/*! ���� ������ �� ����������*/
		else
		{ 
			/*! ���������� � �������� ������� �� ������� � �������� ������ � ���� */
			int index = 0;
			if (arrs[arr].elements.size() - 1 < (int)rightOpD)
			{ 
				/*! ���������� ������� */
				for (int i = 0; i < (int)rightOpD; ++i)
				{
					if (++index == arrs[arr].elements.size())
					{
						index = 0;
					}
				}
				resultD = arrs[arr].elements[index];
			}
			else
				resultD = arrs[arr].elements[rightOpD];

			/*! � ���� �������� ������� ������� */
			stackElement element(arrayElement, QString::number(resultD, 'f'), arr, index);
			operands.push(element);
			/*! ��������� ������������� ������/������ */
			postIncDec(rightElement, vars, arrs);
		}
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
	disableUsedInExpressionFlags(vars);
	++curArr.dimension;
}

void Analyzer::incL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();
	/*! ���� ������� - ���������� */
	if (rightElement.type == variable)
	{ 
		/*! �������������� �������� ���������� */
		rightOpS = rightElement.element;
		int var = ops.findVar(rightOpS, vars);
		rightOpD = vars[var].curValue;
		++rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		vars[var].curValue = rightOpD;
		/*! ��������� � ���� */
		stackElement element(variable, QString::number(vars[var].curValue, 'f'));
		operands.push(element);
	}
	/*! ���� ������� - ������� ������� */
	else if (rightElement.type == arrayElement)
	{ 
		/*! �������������� ������� ������� */
		rightOpD = arrs[rightElement.arrayIndex].elements[rightElement.elementIndex];
		++rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		arrs[rightElement.arrayIndex].elements[rightElement.elementIndex] = rightOpD;
		/*! ��������� � ���� */
		stackElement element(arrayElement, QString::number(resultD, 'f'), rightElement.arrayIndex, rightElement.elementIndex);
		operands.push(element);
	}
	/*! ���� ������� - �������������� ������� */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/*! ���� ������� - �� ������������� �������� */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"++\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::decL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();
	/*! ���� ������� - ���������� */
	if (rightElement.type == variable)
	{ 
		/*! �������������� �������� ���������� */
		rightOpS = rightElement.element;
		int var = ops.findVar(rightOpS, vars);
		rightOpD = vars[var].curValue;
		--rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD, 2);
		vars[var].curValue = rightOpD;
		/*! ��������� � ���� */
		stackElement element(variable, QString::number(vars[var].curValue, 'f'));
		operands.push(element);
	}
	/*! ���� ������� - ������� ������� */
	else if (rightElement.type == arrayElement)
	{ 
		/*! �������������� ������� ������� */
		rightOpD = arrs[rightElement.arrayIndex].elements[rightElement.elementIndex];
		--rightOpD;
		unaryMinusOrTypeConversion(rightElement, rightOpD, 2);
		arrs[rightElement.arrayIndex].elements[rightElement.elementIndex] = rightOpD;
		/*! ��������� � ���� */
		stackElement element(arrayElement, QString::number(resultD, 'f'), rightElement.arrayIndex, rightElement.elementIndex);
		operands.push(element);
	}
	/*! ���� ������� - �������������� ������� */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/*! ���� ������� - �� ������������� �������� */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"--\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::incR(QStack<stackElement> &operands) throw(QString&)
{
	/*! ����� ������� �� ����� */
	stackElement rightElement = operands.pop();
	/*! ���� ������� - ���������� ��� ������� ������� */
	if (rightElement.type == variable || rightElement.type == arrayElement)
	{
		/*! ������������� ���� ���������� */
		rightElement.incNeeded = true;
		/*! ��������� � ���� */
		operands.push(rightElement);
	}
	/*! ���� ������� - �������������� ������� */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/*! ���� ������� - ��������� */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"++\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::decR(QStack<stackElement> &operands) throw(QString&)
{
	/*! ����� ������� �� ����� */
	stackElement rightElement = operands.pop();
	/*! ���� ������� - ���������� ��� ������� ������� */
	if (rightElement.type == variable || rightElement.type == arrayElement)
	{
		/*! ������������� ���� ���������� */
		rightElement.decNeeded = true;
		/*! ��������� � ���� */
		operands.push(rightElement);
	}
	/*! ���� ������� - �������������� ������� */
	else if (rightElement.type == undefined)
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
	/*! ���� ������� - ��������� */
	else if (rightElement.type == constant)
	{
		QString errorString = "L-value is required for \"--\" operation on the " + QString::number(exprPos + 1) + " position";
		throw errorString;
	}
}

void Analyzer::unaryMinus(QStack<stackElement> &operands)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();
	/*! ���� ������� - �������������� ������� */
	if (rightElement.type == undefined)
	{
		stackElement element(undefined);
		operands.push(element);
	}
	/*! ���� ������� - ����������, ��������� ��� ������� ������� */
	else
	{
		/*! ������������� ������ �������������� �������� */
		rightElement.negative = true;
		/*! ��������� � ���� */
		operands.push(rightElement);
	}
}

void Analyzer::absF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();

	/*! ���� �� �� �������� �������������� ��������� */
	if (rightElement.type != undefined)
	{
		/*! �������� ��������� �������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! ���������� ������ */
		resultD = abs(rightOpD);
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::ceilF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();

	/*! ���� �� �� �������� �������������� ��������� */
	if (rightElement.type != undefined)
	{
		/*! �������� ��������� �������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! ���������� ������ */
		resultD = ceil(rightOpD);
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::fabsF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();
	/*! ���� �� �� �������� �������������� ��������� */
	if (rightElement.type != undefined)
	{
		/*! �������� ��������� �������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! ���������� ������ */
		resultD = fabs(rightOpD);
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::floorF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();
	/*! ���� �� �� �������� �������������� ��������� */
	if (rightElement.type != undefined)
	{
		/*! �������� ��������� �������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! ���������� ������ */
		resultD = floor(rightOpD);
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::powF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! �������� ��������� �������� ������ �������� */
		leftOpS = leftElement.element;
		leftOpD = ops.stringOpToDoubleOp(leftOpS, vars);
		unaryMinusOrTypeConversion(leftElement, leftOpD);
		/*! ���������� ������ */
		resultD = pow(leftOpD, rightOpD);
		/*! ��������� � ���� */
		stackElement element(constant, QString::number(resultD, 'f'));
		operands.push(element);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	else
	{
		stackElement element(undefined);
		operands.push(element);
	}
}

void Analyzer::assignment(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QString &type) throw(QString&)
{
	/*! ����� �������� �� ����� */
	stackElement rightElement = operands.pop();
	stackElement leftElement = operands.pop();

	/*! ���� ��� �� �������� ��������������� ���������� */
	if (rightElement.type != undefined && leftElement.type != undefined)
	{
		/*! �������� ��������� �������� ������� �������� */
		rightOpS = rightElement.element;
		rightOpD = ops.stringOpToDoubleOp(rightOpS, vars);
		unaryMinusOrTypeConversion(rightElement, rightOpD);
		/*! ���� ������� - ���������� - ���������� ���������� */
		if (leftElement.type == variable)
		{ 
			/*! �������� ��������� �������� ������ �������� */
			leftOpS = leftElement.element;
			int var = ops.findVar(leftOpS, vars);

			/*! ��������� ������������ ���������� � ����������� �� �������� type */
			if (type == "=")
				vars[var].curValue = rightOpD;
			else if (type == "+=")
				vars[var].curValue += rightOpD;
			else if (type == "-=")
				vars[var].curValue -= rightOpD;
			else if (type == "*=")
				vars[var].curValue *= rightOpD;
			else if (type == "/=")
				vars[var].curValue /= rightOpD;

			/*! ��������� � ���� */
			stackElement element(variable, vars[var].name);
			operands.push(element);
		}
		else if (leftElement.type == arrayElement)
		{
			/*! ��������� ������������ �������� ������� � ����������� �� �������� type */
			if (type == "=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] = rightOpD;
			else if (type == "+=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] += rightOpD;
			else if (type == "-=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] -= rightOpD;
			else if (type == "*=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] *= rightOpD;
			else if (type == "/=")
				arrs[leftElement.arrayIndex].elements[leftElement.elementIndex] /= rightOpD;

			/*! ��������� � ���� */
			stackElement element(arrayElement, QString::number(rightOpD, 'f'), leftElement.arrayIndex, leftElement.elementIndex);
			operands.push(element);
		}
		/*! ���� ������� - ��������� */
		else if (leftElement.type == constant)
		{
			QString errorString = "L-value is required for \"" + type + "\" operation on the " + QString::number(exprPos + 1) + " position";
			throw errorString;
		}
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
		postIncDec(leftElement, vars, arrs);
	}
	/*! ���� ������� - �������������� ������� */
	else
	{
		QString errorString = "Critical operation with undefined element is detected on the " + QString::number(exprPos + 1) + " position during the " + QString::number(iteration) + " iteration";
		throw errorString;
	}
}

void Analyzer::typeConversionToInt(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)
{
	/*! ����� ������ ������� */
	stackElement rightElement = operands.pop();

	/*! ���� ������� - �������������� ������� */
	if (rightElement.type == undefined)
	{

		stackElement element(undefined);
		operands.push(element);
	}
	/*! ���� �� �� �������� �������������� ��������� */
	else
	{
		/*! ������������� ���� intNeeded */
		rightElement.intNeeded = true;
		/*! ��������� � ���� */
		operands.push(rightElement);
		/*! ��������� ������������� ������/������ */
		postIncDec(rightElement, vars, arrs);
	}
}

void Analyzer::postIncDec(stackElement &element, QVector<Index> &vars, QVector<Array> &arrs)
{

}

void Analyzer::disableUsedInExpressionFlags(QVector<Index> &vars)
{

}

void Analyzer::unaryMinusOrTypeConversion(stackElement &element, double &value, int op /*= 0*/)
{

}
