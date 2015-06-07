#ifndef TEST_INPUT_H
#define TEST_INPUT_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/input.h"

Q_DECLARE_METATYPE(index)
Q_DECLARE_METATYPE(Array)
Q_DECLARE_METATYPE(QVector<index>)
Q_DECLARE_METATYPE(QVector<Array>)

class input;
class test_input : public QObject
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
