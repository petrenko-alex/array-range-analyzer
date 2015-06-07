#ifndef TEST_INPUT_H
#define TEST_INPUT_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/input.h"
#include "declarations.h"

class input;
class Test_input : public QObject
{
	Q_OBJECT

private slots:
	/*! �������������� ������ ��� ������������ readVarInfo */
	void readVarInfo_data();

	/*! �������������� ������ ��� ������������ readArrInfo */
	//void readArrInfo_data();

	/*! �������������� ������ ��� ������������ readExpression */
	//void readExpression_data();

	/*! �������������� ������ ��� ������������ readData */
	//void readData_data();

	/*! ��������� ������� readVarInfo */
	void readVarInfo();

	/*! ��������� ������� readArrInfo*/
	//void readArrInfo();

	/*! ��������� ������� readExpression*/
	//void readExpression();

	/*! ��������� ������� readData*/
 	//void readData();
};

#endif // TEST_INPUT_H
