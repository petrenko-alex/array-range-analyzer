/*!
 *\file
 *\brief Файл объявления класса массива.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный файл содержит в себе класс, содержащий информацию
 * о имени массива, размерах его измерений, а также элементы массива.
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <QObject>
#include <QVector>

/*!
*\brief Класс массива.
*\author Александр Петренко gafk555@gmail.com.
*
* Данный класс описывает массив и информацию о нем.
*/
class Array
{
public:
	Array();
	~Array();

public:
	QString		   name;				///< Строка с именем массива
	QVector <int>  size;				///< Целочисленный вектор с размерами массива
	QVector <int>  elements;			///< Вектор с элементами массива
	QVector <bool> isExceeding;			///< Вектор, содержащий информацию о том, произошел ли выход за пределы измерений массива

};

#endif // ARRAY_H