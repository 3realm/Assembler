﻿using namespace std;
#include <stdio.h> // стандартный ввод/вывод
#include <iostream> // потоковый ввод/вывод

int calc_cpp(int a, int b)
{
	if (a > b)
	{
		return b / a - 5;
	}
	else if (a == b)
	{
		return 25;
	}
	else
	{
		return (3 * a - 5) / b;
	}
}

pair<int, int> calc_asm(int a, int b)
{
	int result = 0;
	int err = 0;
	__asm {
		mov ecx, a; < eсx >= a
		mov	ebx, b; < ebx >= b
		cmp	ecx, ebx; сравнение a и b
		jg l_bigger; переход если a > b
		jl l_smaller; переход если a < b
		mov	eax, 25; < eax >= 25
		jmp	exit_l; переход на конец программы
		l_bigger :
		or ecx, ecx; сравнение a и 0
			je	error; ошибка деление на ноль
			mov	eax, ebx; < eax >= b
			cdq; подготовка деления <edx:eax> = a
			idiv ecx; <eax> = b / a
			add	eax, -5; <eax> = b / a - 5
			jmp	exit_l; переход на конец программы
			l_smaller :
		or ebx, ebx; сравнение b и 0
			je    error; ошибка деление на ноль
			imul ecx, 3; <edx:ecx> = 3 * a
			jo    error; ошибка переполнение
			mov eax, ecx; < eax >= a
			add eax, -5; < eax >= 3 * a - 5
			adc	edx, -1; коррекция старшей части
			cdq; подготовка деления <edx:eax> = a
			; <edx:eax> = 3 * a – 5
			idiv ebx; <eax> = (3 * a – 5) / b
			jmp	exit_l; переход на конец программы
			error :
		mov err, 1
			exit_l :
			mov result, eax
	}
	return pair<int, int>(result, err); // возвращаем результат вычисления выражения
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Ассемблер. Лабораторная работа № 2. Арифметические команды и команды переходов.\n";
	cout << "Выполнил: Боряков Н.С., группа 6102-020302D\n";
	cout << "Вариант 28: \nx=b/a-5, если a>b \nx=25, если a=b\nx=(3*a-5)/b, если a<b" << endl;
	int a, b;
	cout << "a = "; // потоковый вывод
	cin >> a; // потоковый ввод
	printf("b = "); // стандартный вывод
	scanf_s("%d", &b); // стандартный ввод
	auto f = calc_asm(a, b);
	if (f.second == 1)
	{
		cout << "Попытка деления на ноль\n";
	}
	else
	{
		cout << "Результат на ассемблере= " << f.first << endl;
		cout << "Результат на c++= " << calc_cpp(a, b) << endl;
	}
	system("PAUSE");
	return 0;
}