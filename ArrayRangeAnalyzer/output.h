/*!
 *\file
 *\brief Файл объявления класса представления результатов.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный файл содержит в себе класс представления выходных данных.
 */
#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "exceeding.h"
#include "array.h"

/*!
 *\brief Класс представления выходных данных.
 *\author Александр Петренко gafk555@gmail.com.
 *
 * Данный класс содержит необходимые функции вывода результатов работы программы:
 * результатов проверки выражения и/или возникших критических ошибок.
 */

class Output
{
public:
	/*! Конструктор по-умолчанию */
	Output();
	/*! Деструктор */
	~Output();

	/*!
	 * Генерирует файл с ошибками и заполняет его информацией об ошибках
	 *\param[in] errorString строка с информацией об ошибке
	 */
	void writeError(QString &errorString);

	/*!
	 * Генерирует выходной файл программы и заполняет его информацией о результатах
	 * работы программы - проверки выражения на выходы за пределы массива
	 *\param[in] exceedings		информация о выходах за пределы массива
	 *\param[in] arrs			вектор массивов
	 *\param[in] inputFileNames имена входных файлов
	 */
	void makeOutputFile(QVector<Exceeding> &exceedings, const QVector<Array> &arrs, const QStringList &inputFileNames);

	/*!
	 * Возвращает признак того, была ли найдена ошибка при выполнении программы
	 *\return true, если ошибка возникала или false, если нет
	 */
	bool isErrorOccured();

private:
	QString resultFileName; ///< Имя файла результатов
	QString errorFileName;  ///< Имя файла ошибок
};

#endif // OUTPUT_H