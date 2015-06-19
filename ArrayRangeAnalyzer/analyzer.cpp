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
