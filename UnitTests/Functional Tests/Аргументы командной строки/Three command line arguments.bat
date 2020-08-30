@echo off
rem *************************************************************************
rem Проверка ситуации, когда заданы все три аргумента командной строки
rem корректные входные данные, считывание и анализ успешны, без выходов
rem за пределы массива
rem Результат работы программы в файле "ArrayRangeAnalyzer-Results.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"