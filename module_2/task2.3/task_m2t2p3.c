#include <stdio.h>
#include <locale.h>

double sum(double, char, double);
double difference(double, char, double);
double product(double, char, double);
double relation(double, char, double);

int main() {
	//Установка локали. Вывод текста.
	setlocale(LC_ALL, "rus");
	printf("Задание 1. Калькулятор.\n");
	printf("Пример ввода: a \"знак\" b, где:\n	a и b - числа;\n	\"знак\" - математический знак: +, -, *, /;\n");

	char sign = ' ';
	double a = 0, b = 0, c = 0;

	//Создание массива указателей на функции.
	double (*action[4]) (double, char, double) = {
			sum,
			difference,
			product,
			relation
	};
	//Длинна массива указателей на функции.
	int length = (int)(sizeof(action) / sizeof(action[0]));
	printf("Длинна массива на функции: %d\n", length);

	while (1) {
		//Запрос на ввод уравнения. Проверка на ввод.
		printf("Ввод: ");
		if (scanf("%lf %c %lf", &a, &sign, &b) == 0) {
			printf("Ошибка ввода!\n");
			return 1;
		}//При ошибке ввода программа завершается.
		if (sign != '+' && sign != '-' && sign != '*' && sign != '/') {
			printf("Ошибка ввода знака! Выход из программы!\n");
			return 0;
		}//При вводе символа, который не соответствует не одному из указанных, программа завершается.

		//Вызов математического действия в зависимости от знака.
		//Условия: пока массив не закончится и пока результат равен 0.
		c = 0;
		for (int i = 0; i < length && c == 0; i++) {
			c = action[i](a, sign, b);
		}

		//Вывод результата.
		printf("\n%lf %c %lf = %lf\n", a, sign, b, c);
	}
}

double sum(double a, char sign, double b) {
	if (sign == '+') { return a + b; }
	return 0;
}
double difference(double a, char sign, double b) {
	if (sign == '-') { return a - b; }
	return 0;
}
double product(double a, char sign, double b) {
	if (sign == '*') { return a * b; }
	return 0;
}
double relation(double a, char sign, double b) {
	if (sign == '/') { return a / b; }
	return 0;
}

