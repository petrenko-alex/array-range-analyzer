@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Неизвестная переменная в выражении
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr with undef var.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\Variables.xml"