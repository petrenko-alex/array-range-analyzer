#ifndef TEST_INPUT_H
#define TEST_INPUT_H

#include <QObject>
#include <QtTest>
#include "../ArrayRangeAnalyzer/input.h"

Q_DECLARE_METATYPE(index)
Q_DECLARE_METATYPE(Array)
Q_DECLARE_METATYPE(QVector<index>)
Q_DECLARE_METATYPE(QVector<Array>)

class test_input : public QObject
{
	Q_OBJECT

public:
	test_input(QObject *parent);
	~test_input();

private:
	
};

#endif // TEST_INPUT_H
