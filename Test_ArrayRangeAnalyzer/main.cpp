
#include <QtCore/QCoreApplication>
#include "test_input.h"
#include "test_analyzer.h"

int main(int argc, char *argv[])
{	

	/*! Запуск тестов */
	QTest::qExec(&Test_input(), argc, argv);
	printf("\n\n\n");
	QTest::qExec(&Test_analyzer(), argc, argv);
	
	getchar();
	return 0;
}
