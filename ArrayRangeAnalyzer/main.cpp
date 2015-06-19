/*!
 *\file
 *\brief Файл основной функции программы.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный файл содержит в себе функцию main - осовную функцию, вполняющую программу.
 */
#include <QtCore/QCoreApplication>
#include "input.h"
#include "analyzer.h"
#include "output.h"
#include "operations.h"
#include "index.h"
#include "array.h"
#include "exceeding.h"

int main(int argc, char *argv[])
{
	printf("********** Array Range Analyzer **********\n");
	Input input;
	Output out;
	Analyzer analyze;
	Operations ops;
	QStringList inputFileNames;
	QVector<Index> vars;
	QVector<Array> arrs;
	QVector<Exceeding> exceedings;
	QStringList expr;
	bool correctInputData = false;

	/* Проверка аргументов командной строки */
	if (argc == 1)
	{
		out.writeError(QString("Additional arguments of command line are not set.Please, set required arguments."));
		printf("\nError!!!\nAdditional arguments of command line are not set.\nPlease, set required arguments.\n");
		return 1;
	}
	else if (argc == 2)
	{
		out.writeError(QString("Not enough arguments of command line. The file with array's info is not set."));
		printf("\nError!!!\nNot enough arguments of command line.\nThe file with array's info is not set.\n");
		return 1;
	}
	else if (argc == 3)
	{
		out.writeError(QString("Not enough arguments of command line. The file with variable's info is not set."));
		printf("\nError!!!\nNot enough arguments of command line.\nThe file with variable's info is not set.\n");
		return 1;
	}
	else if (argc > 3)
	{
		printf("\nArguments of command line are set correctly...\n");
		inputFileNames << argv[3] << argv[2] << argv[1];
	}


	/* Считывание входных данных */
	correctInputData = input.readData(inputFileNames, vars, arrs, expr);

	/* Установка счетчика зацикливания по дополнительному аргументу командной строки */
	if (correctInputData && argc > 4)
	{
		QString argument(argv[4]);
		int loop = 10;
		if (ops.isNumber(argument))
		{
			loop = argument.toInt();
			for (auto &var : vars)
			{
				var.looped = loop;
			}
			printf("\nInfinite loop counter is set to %s...\n", argv[4]);
		}
	}

	/* Проверка выражения на наличие выходов за пределы массива */
	if (correctInputData)
	{
		analyze.checkExpression(vars, arrs, expr, exceedings);
	}
	else
	{
		printf("\nError!!!\nInput data reading failed.\nPlease, check \"ArrayRangeAnalyzer-Errors.txt\" file for more info.\n");
		return 1;
	}


	/* Вывод результатов работы прогаммы */
	out.makeOutputFile(exceedings, arrs, inputFileNames);

	/* Если в процессе анализа выражения ошибок не произошло */
	if (out.isErrorOccured())
	{
		printf("\nAnalyzing completed.\nSome errors were detected.\nPlease, check \"ArrayRangeAnalyzer-Errors.txt\" file for errors info\nAnd \"ArrayRangeAnalyzer-Results.txt\" file for results.\n");
	}
	/* Если в процессе анализа выражения произошли ошибки */
	else
	{
		printf("\nAnalyzing completed.\nNo errors were detected.\nPlease, check \"ArrayRangeAnalyzer-Results.txt\" file for results.\n");
	}

	getchar();
	return 0;
}
