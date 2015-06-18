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

/*!
*\brief Класс проверки выражения на наличие выходов за пределы массива.
*\author Александр Петренко gafk555@gmail.com.
*
* Данный класс содержит основные функции для проверки выражения на наличие выходов за пределы массивов.
*/
class Analyzer
{
public:
	Analyzer();
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


};

#endif // ANALYZER_H

