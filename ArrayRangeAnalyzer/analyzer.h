/*!
 *\file
 *\brief Файл объявления класса проверки выражения на наличие выходов за пределы массивов.
 *\author Александр Петренко gafk555@gmail.com.
 * 
 * Данный файл содержит в себе класс проверки выражения на наличие выходов за пределы массивов.
 */

#ifndef ANALYZER_H
#define ANALYZER_H

#include <QObject>
#include "index.h"
#include "array.h"
#include "exceeding.h"
#include "operations.h"

/*!
 *\brief Класс проверки выражения на наличие выходов за пределы массива.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный класс содержит основные функции для проверки выражения на наличие выходов за пределы массивов.
 */
class Analyzer
{
public:
	/*! Конструктор по-умолчанию */
	Analyzer();
	/*! Деструктор */
	~Analyzer();

	/*!
	 *\brief Проверяет наличие выходов за пределы массивов в выражении при текущих значениях переменных
	 *\details Проходит по выражению слева на право, вычисляя его, и сравнивает индексы массивов с их размерами
	 *
	 *param[in]  vars		  вектор объектов класса \ref index – информация о переменных
	 *param[in]  arrs		  вектор объектов класса \ref Array - информация о массивах
	 *param[in]  expr		  выражение в виже списка строк
	 *param[out] exceedings   вектор объектов класса \ref exceeding - информация о выходах за пределы
	 *\exception errorString  строка с информацией о возникшем исключении
	 */
	void analyzeExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&);


	/*!
	 *\brief Проверяет наличие выходов за пределы массивов в выражении на всем диапазоне заданных переменных
	 *\details При нескольких переменных цикла, циклы считаються вложенными 
	 *
	 *param[in]  vars		  вектор объектов класса \ref index – информация о переменных
	 *param[in]  arrs		  вектор объектов класса \ref Array - информация о массивах
	 *param[in]  expr		  выражение в виже списка строк
	 *param[out] exceedings   вектор объектов класса \ref exceeding - информация о выходах за пределы
	 *\exception errorString  строка с информацией о возникшем исключении
	 */
	void checkExpression(QVector<Index> &vars, QVector<Array> &arrs, const QStringList &expr, QVector<Exceeding> &exceedings) throw(QString&);

private:
	Operations ops;							///< Объект класса вспомагательных операций
	int iteration;							///< Номер итерации "захода" в analyzeExpression из checkExpression
	QString leftOpS, rightOpS, resultS;		///< Операнды для вычислений в виде строки
	double  leftOpD, rightOpD, resultD;		///< Операнды для вычислений в виде числа
	int exprPos;							///< Позиция в выражении при обходе

};

#endif // ANALYZER_H

