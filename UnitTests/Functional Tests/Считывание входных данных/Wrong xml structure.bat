@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Нарушена структура xml файла
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays - wrong structure.xml" ".\Sources for tests\Variables.xml"