/*!
*\file
*\brief Файл объявления класса вспомогательных операций.
*\author Александр Петренко gafk555@gmail.com.
*
* Данный файл содержит в себе класс вспомогательных операций.
*/

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "index.h"
#include "array.h"
#include <QRegExp>

/*!
*\brief Класс вспомогательных операций.
*\author Александр Петренко gafk555@gmail.com.
*
* Данный класс содержит вспомогательные функции, позволяющие:
* - Получить арность операции
* - Определить, являеться ли символ поддерживаемой операцией;
* - Определить, являеться ли символ известной переменной;
* - Определить, являеться ли символ вещественным числом;
* - Определить, являеться ли символ целым числом;
* - Определить, являеться ли символ положительным целым числом;
* - Определить, являеться ли символ вещественным цислом;
* - Определить, являеться ли символ операндом;
* - Определить, являеться ли символ известным массивом;
* - Определить, являеться ли символ известным элементом(операция, переменная, константа или массив).
*/
class Operations
{
public:
	Operations();
	~Operations();

	/*!
	 * Возвращает арность операции
	 *\param[in] op символ операции
	 *\return       арность операции
	 */
	int getArity(const QString &op);

	/*!
	 * Определяет, является ли элемент поддерживаемой операцией
	 *\param[in] op проверяемый элемент
	 *\retrun       логическое значение true - если является, false - если нет 
	 */
	bool isDefiniteOperation(const QString &op);

	/*!
	 * Определяет, является ли элемент заданной переменной
	 *\param[in] var  проверяемый элемент
	 *\param[in] vars вектор заданных переменных
	 *\retrun         логическое значение true - если является, false - если нет
	 */
	bool isDefiniteVariable(const QString &var, const QVector<Index> &vars);

	/*!
	 * Определяет, является ли символ вещественным числом
	 *\param[in] number проверяемый элемент
	 *\retrun           логическое значение true - если является, false - если нет
	 */
	bool isFloatNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент целым числом
	 *\param[in] number проверяемый элемент
	 *\retrun           логическое значение true - если является, false - если нет
	 */
	bool isIntNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент положительным целым числом
	 *\param[in] number проверяемый элемент
	 *\retrun           логическое значение true - если является, false - если нет
	 */
	bool isPositiveIntNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент операндом(числом, переменной или массивом)
	 *\param[in] number проверяемый элемент
	 *\param[in] vars   вектор заданных переменных
	 *\param[in] arrs   вектор заданных массивов
	 *\retrun           логическое значение true - если является, false - если нет
	 */
	bool isOperand(const QString &operand, const QVector<Index> &vars, const QVector<Array> &arrs);

	/*!
	 * Определяет, является ли элемент заданным массивом
	 *\param[in] arr  проверяемый элемент
	 *\param[in] arrs вектор заданных массивов
	 *\retrun         логическое значение true - если является, false - если нет
	 */
	bool isDefiniteArray(const QString &arr, const QVector<Array> &arrs);

	/*!
	 * Определяет, является ли символ элементом (операцией, переменной, константой или массивом)
	 *\param[in] element проверяемый символ
	 *\param[in] arrs    вектор заданных массивов
	 *\param[in] vars    вектор заданных переменных
	 *\retrun            логическое значение true - если является, false - если нет
	 */
	bool isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<Index> &vars);

private:
	QMap<QString, int> operations;			///< Поддерживаемые в программе операции и их арность

};

#endif // OPERATIONS_H