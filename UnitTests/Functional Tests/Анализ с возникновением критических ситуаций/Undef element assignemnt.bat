@echo off
rem *************************************************************************
rem Проверка ситуации обнаруженя присвоения не определенного элемента - элемента за пределами массива
rem Результат работы программы в файле "ArrayRangeAnalyzer-Results.txt"
rem Сообщение об ошибке в файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr5.txt" ".\Sources for tests\Arrs1.xml" ".\Sources for tests\Vars1.xml"