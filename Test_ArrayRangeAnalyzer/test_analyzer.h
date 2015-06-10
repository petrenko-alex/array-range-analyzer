#ifndef TEST_ANALYZER_H
#define TEST_ANALYZER_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/analyzer.h"
#include "declarations.h"

class Test_analyzer : public QObject
{
	Q_OBJECT

private slots:

	/*! �������������� ������ ��� ������������ analyzeExpression */
	void analyzeExpression_data();

	/*! �������������� ������ ��� ������������ checkExpression */
	void checkExpression_data();

	/*! ��������� ������� analyzeExpression */
	void analyzeExpression();

	/*! ��������� ������� checkExpression */
	void checkExpression();

private:
	/*! ������� ���������� ����������� ������ */
	void clearData();

	QVector<Index>     vars;
	QVector<Array>	   arrs;
	QVector<Exceeding> exceedings;
	QStringList        expr;
};

#endif // TEST_ANALYZER_H
