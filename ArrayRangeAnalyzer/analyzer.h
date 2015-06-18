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

};

#endif // ANALYZER_H

