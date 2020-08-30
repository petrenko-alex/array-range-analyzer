@echo off
rem *************************************************************************
rem Проверка ситуации обнаруженя инкрементации константы ( не l-value операнда )
rem Результат работы программы в файле "ArrayRangeAnalyzer-Results.txt"
rem Сообщение об ошибке в файле "ArrayRangeAnalyzer-Errors.txt"
rem *************************************************************************

rem Запуск программы...
"..\ArrayRangeAnalyzer.exe" ".\Sources for tests\Expr4.txt" ".\Sources for tests\Arrs1.xml" ".\Sources for tests\Vars1.xml"