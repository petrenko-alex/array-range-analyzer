@echo off
rem *************************************************************************
rem Проверка ситуации, когда задано два аргумента командной строки - 
rem файл с выражением и файл с массивами
rem Сообщение об ошибке в консоле и в файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays.xml"