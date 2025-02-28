﻿

#include <stdio.h> // стандартный ввод/вывод
#include <iostream> // потоковый ввод/вывод
using namespace std; // подключение библиотеки

int calc_cpp(int a, int b, int c)
{
	return (4 * a - b - 1) / (c / b + a);
}


// функция вычисления выражения (4*a - b - 1)/(c/b + a);
int calc(int a, int b, int c)
{
	int result = 0;
	__asm {
		mov eax, a
		mov ecx, 4
		imul ecx // <eax> 4*a сохранение данных в eax
		mov ebx, b
		sub eax, ebx // <eax> 4*a - b
		dec eax // <eax> 4*a - b - 1
		push eax // <eax> сохранение в  стек

		mov eax, c
		mov	ebx, b
		cdq
		idiv ebx // <eax> c/b в ячкйкм eax
		mov ecx, a
		add eax, ecx // <eax> c/b + a
		mov ebx, eax // <ebx> c/b + a
		pop eax // выталкивание из стека
		cdq
		idiv ebx // только eax
		mov result, eax // <result> (4*a - b - 1)/(c/b + a);
	}
	return result; // возвращаем результат вычисления выражения
}

int main()
{
	int a, b, c;
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Ассемблер. Лабораторная работа №1: Арифметические и логические команды\nВыполнил Боряков Н.С. 6102-020302D, вариант №28\n\nВычисление значения выражения (4*a - b - 1)/(c/b + a)\n\n";
	cout << "Введите a >> ";
	cin >> a;
	cout << "Введите b >> ";
	cin >> b;
	cout << "Введите c >> ";
	cin >> c;

	try
	{
		if (b == 0) // проверка 
			throw - 1;
		cout << "Вывод в С++  " << calc_cpp(a, b, c) << endl; // вывод и перевод на другую строку еа консоле
		cout << "Вывод в Assembler " << calc(a, b, c) << endl;
	}
	catch (int a)
	{
		cout << "Ошибка " << a;
	}
	
	
	system("PAUSE");
	return 0; 
}


