@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Задан одномерный массив, а в выражении используется несколько его измерений
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr - problem with dimensions.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"