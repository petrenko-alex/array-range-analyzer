@echo off
rem *************************************************************************
rem Ошибка считывания входных данных
rem Внутри файла с переменными, информация о них не задана,хотя файл корректен
rem и не пуст
rem Сообщение об ошибке в консоли и файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expression.txt" ".\Sources for tests\Arrays.xml" ".\Sources for tests\No vars data.xml"