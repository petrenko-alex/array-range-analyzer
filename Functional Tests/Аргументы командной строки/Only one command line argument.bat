@echo off
rem *************************************************************************
rem Проверка ситуации, когда задан только один аргумент командной строки - 
rem файл с выражением
rem Сообщение об ошибке в консоле и в файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt"