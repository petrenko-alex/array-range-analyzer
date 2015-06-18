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
	
	enum stackElementType { constant, variable, arrayElement, undefined };	///< Тип элемента стека

	struct stackElement						///< Структура элемента стека
	{
		stackElementType type;				///< Тип элемента
		QString			 element;			///< Элемент в виде строки
		int				 arrayIndex;		///< Индекс массива в в векторе массивов, если type == arrayElement
		int				 elementIndex;		///< Индекс элемента в массиве, если type == arrayElement
		bool			 negative;			///< Флаг унарного минуса
		bool             incNeeded;			///< Флаг правого инкремента
		bool			 decNeeded;			///< Флаг правого декремента
		bool			 intNeeded;			///< Флаг приведения к int


		/*! Конструктор по-умолчанию */
		stackElement()
		{
			this->type = undefined;
			this->element = "";
			this->arrayIndex = -1;
			this->elementIndex = -1;
			this->negative = 0;
			this->incNeeded = 0;
			this->decNeeded = 0;
			this->intNeeded = 0;
		}

		/*! Конструктор с параметрами */
		stackElement(stackElementType type, QString element = "", int arrayIndex = -1, int elementIndex = -1, bool neg = 0, bool inc = 0, bool dec = 0, int intNed = 0)
		{
			this->type = type;
			this->element = element;
			this->arrayIndex = arrayIndex;
			this->elementIndex = elementIndex;
			this->negative = neg;
			this->incNeeded = inc;
			this->decNeeded = dec;
			this->intNeeded = intNed;
		}

		/*! Оператор присваивания */
		stackElement &operator=(const stackElement &other)
		{
			type = other.type;
			element = other.element;
			arrayIndex = other.arrayIndex;
			elementIndex = other.elementIndex;
			negative = other.negative;
			incNeeded = other.incNeeded;
			decNeeded = other.decNeeded;
			intNeeded = other.intNeeded;
			return *this;
		}
	};

	struct curentArray						///< Структура описывающая текущий массив при обходе выражения
	{
		unsigned int dimension;
		QString name;
	}curArr;

	/*!
	 * Функция сложения двух операндов
	 * Выполняется, когда в выражении встречается знак операции сложения "+"
	 *\param[in|out] operands стек
	 *\param[in]     vars     вектор переменных
	 *\param[in]     arrs     вектор массивов
	 */
	void addition(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция вычитания двух операндов
	 * Выполняется, когда в выражении встречается знак операции вычитания "-"
	 *\param[in|out] operands стек
	 *\param[in]     vars     вектор переменных
	 *\param[in]     arrs     вектор массивов
	 */
	void substraction(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция деления двух операндов
	 * Выполняется, когда в выражении встречается знак операции деления "/"
	 *\param[in|out] operands		стек
	 *\param[in]     vars			вектор переменных
	 *\param[in]     arrs			вектор массивов
	 *\exception     errorString		строка с информацией о возникшем исключении(деление на нуль)
	 */
	void division(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)  throw(QString&);

	/*!
	 * Функция умножения двух операндов
	 * Выполняется, когда в выражении встречается знак операции умножения "*"
	 *\param[in|out] operands		стек
	 *\param[in]     vars			вектор переменных
	 *\param[in]     arrs			вектор массивов
	 */
	void multiplication(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция операции остаток от деления
	 * Выполняется, когда в выражении встречается знак операции остаток от деления "%"
	 *\param[in|out] operands		стек
	 *\param[in]     vars			вектор переменных
	 *\param[in]     arrs			вектор массивов
	 *\exception     errorString		строка с информацией о возникшем исключении(деление на нуль)
	 */
	void modulo(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs)  throw(QString&);

	/*!
	 * Функция операции обращения к элементу массива
	 * Выполняется, когда в выражении встречается знак операции обращения к элементу массива "[]"
	 *\param[in|out] operands		стек
	 *\param[in]     vars			вектор переменных
	 *\param[in]     arrs			вектор массивов
	 *\param[in|out] exceedings		вектор выходов за пределы массива
	 */
	void subscript(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QVector<Exceeding> &exceedings);

	/*!
	 * Функция операции префиксной инкрементации
	 * Выполняется, когда в выражении встречается знак операции префиксной инкрементации "+\"
	 *\param[in|out] operands		стек
	 *\param[in|out] vars			вектор переменных
	 *\param[in|out] arrs			вектор массивов
	 *\exception     errorString	строка с информацией о возникшем исключении(инкрементация не l-value,операция с неопределенным элементом)
	 */
	void incL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&);

	/*!
	 * Функция операции префиксной декрементации
	 * Выполняется, когда в выражении встречается знак операции префиксной декрементации "-\"
	 *\param[in|out] operands		стек
	 *\param[in|out] vars			вектор переменных
	 *\param[in|out] arrs			вектор массивов
	 *\exception     errorString	строка с информацией о возникшем исключении(декрементация не l-value,операция с неопределенным элементом)
	 */
	void decL(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs) throw(QString&);

	/*!
	 * Функция операции постфиксной инкрементации
	 * Выполняется, когда в выражении встречается знак операции постфиксной инкрементации "\+"
	 *\param[in|out] operands стек
	 *\exception     errorString	строка с информацией о возникшем исключении(инкрементация не l-value,операция с неопределенным элементом)
	 */
	void incR(QStack<stackElement> &operands) throw(QString&);

	/*!
	 * Функция операции постфиксной декрементации
	 * Выполняется, когда в выражении встречается знак операции постфиксной декрементации "\-"
	 *\param[in|out] operands		стек
	 *\exception     errorString	строка с информацией о возникшем исключении(декрементация не l-value,операция с неопределенным элементом)
	 */
	void decR(QStack<stackElement> &operands) throw(QString&);

	/*!
	 * Функция операции унарный минус
	 * Выполняется, когда в выражении встречается знак операции унарный минус "/-"
	 *\param[in|out] operands		стек
	 */
	void unaryMinus(QStack<stackElement> &operands);

	/*!
	 * Функция, выполняющаяся, когда в выражении встречается "abs()"
	 *\param[in|out] operands	стек
	 *\param[in]	 vars		вектор переменных
	 *\param[in]	 arrs		вектор массивов
	 */
	void absF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция, выполняющаяся, когда в выражении встречается "ceil()"
	 *\param[in|out] operands	стек
	 *\param[in]	 vars		вектор переменных
	 *\param[in]	 arrs		вектор массивов
	 */
	void ceilF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция, выполняющаяся, когда в выражении встречается "fabs()"
	 *\param[in|out] operands	стек
	 *\param[in]	 vars		вектор переменных
	 *\param[in]	 arrs		вектор массивов
	 */
	void fabsF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция, выполняющаяся, когда в выражении встречается "floor()"
	 *\param[in|out] operands	стек
	 *\param[in]	 vars		вектор переменных
	 *\param[in]	 arrs		вектор массивов
	 */
	void floorF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция, выполняющаяся, когда в выражении встречается "pow()"
	 *\param[in|out] operands	стек
	 *\param[in]	 vars		вектор переменных
	 *\param[in]	 arrs		вектор массивов
	 */
	void powF(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);

	/*!
	 * Функция операции присваивания
	 * Выполняется, когда в выражении встречается знак операции присваивания "="
	 *\param[in|out] operands		стек
	 *\param[in|out] vars			вектор переменных
	 *\param[in|out] arrs			вектор массивов
	 *\param[in]     type			тип присваивания: "=","+=","-=","*=","/=",
	 *\exception     errorString	строка с информацией о возникшем исключении(присваивание не l-value,операция с неопределенным элементом)
	 */
	void assignment(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs, QString &type) throw(QString&);

	/*!
	 * Функция операции приведения типа к int
	 * Выполняется, когда в выражении встречается знак операции приведения типа к int "(int)"
	 *\param[in|out] operands	стек
	 *\param[in] vars			вектор переменных
	 *\param[in] arrs			вектор массивов
	 */
	void typeConversionToInt(QStack<stackElement> &operands, QVector<Index> &vars, QVector<Array> &arrs);
};

#endif // ANALYZER_H

