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
 * - Определить, является ли символ поддерживаемой операцией;
 * - Определить, является ли символ известной переменной;
 * - Определить, является ли символ вещественным числом;
 * - Определить, является ли символ целым числом;
 * - Определить, является ли символ положительным целым числом;
 * - Определить, является ли символ числом;
 * - Определить, является ли символ вещественным числом;
 * - Определить, является ли символ операндом;
 * - Определить, является ли символ известным массивом;
 * - Определить, является ли символ известным элементом(операция, переменная, константа или массив)
 * - Найти индекс переменной в векторе переменных по ее имени
 * - Найти индекс массива в векторе массивов по его имени
 * - Получить вещественное значение переменной или строки с числом.
 */
class Operations
{
public:
	/*! Конструктор по-умолчанию */
	Operations();
	/*! Деструктор */
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
	 *\return       логическое значение true - если является, false - если нет 
	 */
	bool isDefiniteOperation(const QString &op);

	/*!
	 * Определяет, является ли элемент заданной переменной
	 *\param[in] var  проверяемый элемент
	 *\param[in] vars вектор заданных переменных
	 *\return         логическое значение true - если является, false - если нет
	 */
	bool isDefiniteVariable(const QString &var, const QVector<Index> &vars);

	/*!
	 * Определяет, является ли символ вещественным числом
	 *\param[in] number проверяемый элемент
	 *\return           логическое значение true - если является, false - если нет
	 */
	bool isFloatNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент целым числом
	 *\param[in] number проверяемый элемент
	 *\return           логическое значение true - если является, false - если нет
	 */
	bool isIntNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент положительным целым числом
	 *\param[in] number проверяемый элемент
	 *\return           логическое значение true - если является, false - если нет
	 */
	bool isPositiveIntNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент числом
	 *\param[in] number проверяемый элемент
	 *\return           логическое значение true - если является, false - если нет
	 */
	bool isNumber(const QString &number);

	/*!
	 * Определяет, является ли элемент операндом(числом, переменной или массивом)
	 *\param[in] operand проверяемый элемент
	 *\param[in] vars    вектор заданных переменных
	 *\param[in] arrs    вектор заданных массивов
	 *\return            логическое значение true - если является, false - если нет
	 */
	bool isOperand(const QString &operand, const QVector<Index> &vars, const QVector<Array> &arrs);

	/*!
	 * Определяет, является ли элемент заданным массивом
	 *\param[in] arr  проверяемый элемент
	 *\param[in] arrs вектор заданных массивов
	 *\return         логическое значение true - если является, false - если нет
	 */
	bool isDefiniteArray(const QString &arr, const QVector<Array> &arrs);

	/*!
	 * Определяет, является ли символ элементом (операцией, переменной, константой или массивом)
	 *\param[in] element проверяемый символ
	 *\param[in] arrs    вектор заданных массивов
	 *\param[in] vars    вектор заданных переменных
	 *\return            логическое значение true - если является, false - если нет
	 */
	bool isDefiniteElement(const QString &element, const QVector <Array> &arrs, const QVector<Index> &vars);

	/*!
	 * Находит индекс переменной в векторе vars по ее имени
	 *\param[in] var  имя переменной
	 *\param[in] vars вектор переменных
	 *\return         индекс переменной в векторе,или -1, если не найдена
	 */
	int findVar(QString var, const QVector<Index> &vars);

	/*!
	 * Находит индекс массива в векторе arrs по его имени
	 *\param[in] arr  имя массива
	 *\param[in] arrs вектор массивов
	 *\return         индекс массива в векторе,или -1, если не найден
	 */
	int findArr(QString arr, const QVector<Array> &arrs);

	/*!
	 * Возвращает вещественное значение строковой константы
	 * Обрабатывает имена переменных
	 *\param[in] operand имя переменной или число в виде строки
	 *\param[in] vars    вектор переменных
	 *\return			 вещественное значение 
	 */
	double stringOpToDoubleOp(QString operand, const QVector<Index> &vars);

private:
	QMap<QString, int> operations;			///< Поддерживаемые в программе операции и их арность
	QString plus;
	QString minus;
	QString dot;
};

#endif // OPERATIONS_H