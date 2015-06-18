/*!
 *\file
 *\brief Файл объявления класса считывания входных данных.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный файл содержит в себе класс считывания входных данных.
 */

#ifndef INPUT_H
#define INPUT_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QtXml >
#include "array.h"
#include "index.h"
#include "operations.h"


/*!
 *\brief Класс считывания входных данных.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный класс содержит необходимые функции для считывания входных данных программы.
 */
class Input
{
public:
	/*! Конструктор по-умолчанию */
	Input();
	/*! Деструктор */
	~Input();

	/*!
	 * Считывает входные данные программы
	 *\param[in]  inputFileNames	имена входных файлов
	 *\param[out] vars				вектор объектов класса \ref Index – информация о переменных
	 *\param[out] arrs				вектор объектов класса \ref Array - информация о массивах
	 *\param[out] expr				выражение в виде списка строк
	 *\return						признак успешности считывания
	 */
	bool readData(const QStringList &inputFileNames, QVector <Index> &vars, QVector <Array> &arrs, QStringList &expr);


	/*!
	 * Считывает входной файл с информацией об использующихся в выражении переменных
	 *\param[in]  fileName      имя файла входных данных с информацией о переменных
	 *\param[out] vars          вектор объектов класса \ref Index – информация о переменных
	 *\exception  errorString   строка с информацией о возникшем исключении
	 */
	void readVarInfo(const QString fileName, QVector <Index> &vars) throw(QString&);

	/*!
	 * Считывает значения аттрибутов тега variable в файле входных данных с информацией о переменных
	 *\param[out] var          объект класса \ref Index , в который происходит считывание данных
	 *\param[in]  atrs         аттрибуты тега variable
	 *\param[in]  i            номер тега variable в файле
	 *\exception  errorString  строка с информацией о возникшем исключении
	 */
	void readVarAttributes(Index &var, QXmlStreamAttributes &atrs, int i) throw(QString&);

	/*!
	 * Считывает входной файл с информацией об использующихся в выражении массивах
	 *\param[in]  fileName      имя файла входных данных с информацией о массивах
	 *\param[out] arrs          вектор объектов класса \ref Array – информация о массивах
	 *\exception  errorString   строка с информацией о возникшем исключении
	 */
	void readArrInfo(const QString fileName, QVector <Array> &arrs) throw(QString&);

	/*!
	 * Считывает значения аттрибутов тега array в файле входных данных с информацией о массивах
	 *\param[out] arr          объект класса \ref Array , в который происходит считывание данных
	 *\param[in]  atrs         аттрибуты тега array
	 *\param[in]  i            номер тега array в файле
	 *\exception  errorString  строка с информацией о возникшем исключении
	 */
	void readArrAttributes(Array &arr, QXmlStreamAttributes &atrs, int i) throw(QString&);

	/*!
	 * Считывает входной файл с выражением
	 *\param[in]  fileName      имя файла входных данных с выражением
	 *\param[out] expr          выражение в виде списка строк
	 *\param[in]  vars		    вектор объектов класса \ref index – информация о переменных
	 *\param[in]  arrs		    вектор объектов класса \ref Array - информация о массивах
	 *\exception  errorString   строка с информацией о возникшем исключении
	 */
	void readExpression(const QString fileName, QStringList  &expr, const QVector<Index> &vars, const QVector<Array> &arrs) throw(QString&);

	/*!
	 * Проверяет считанные переменные на корректность границ и шага
	 * Отсеивает случаи когда цикл выполняться не будет
	 *\param[in] vars вектор объектов класса \ref Index – информация о переменных
	 *\exception errorString строка с информацией о возникшем исключении
	 */
	void checkNonExecutableCycle(QVector<Index> &vars) throw(QString&);

	/*!
	 * Удаляет не использующиеся в выражении переменные и массивы
	 * из векторов vars и arrs соответственно
	 *\param[in|out] vars вектор объектов класса \ref Index – информация о переменных
	 *\param[in|out] arrs вектор объектов класса \ref Array - информация о массивах
	 *\param[in]     expr выражение в виде списка строк
	 */
	void removeUnusedVarsAndArrs(QVector<Array> &arrs, QVector<Index> &vars, QStringList &expr);

};

#endif // INPUT_H
