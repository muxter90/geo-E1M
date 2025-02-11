#include <iostream>
#include <cmath> // Библиотека для матетматики
#include <utility> // Бибилотека для вывода 2-х и более значений из функции
#include <iomanip>
using namespace std;

// Определение цветов с помощью ANSI-кодов
const string RESET = "\033[0m";       // Сброс цвета
const string RED = "\033[31m";        // Красный
const string GREEN = "\033[32m";      // Зеленый
const string YELLOW = "\033[33m";     // Желтый
const string BLUE = "\033[34m";       // Синий
const string MAGENTA = "\033[35m";    // Фиолетовый
const string CYAN = "\033[36m";       // Голубой
const string WHITE = "\033[37m";      // Белый
const string BOLD = "\033[1m";        // Жирный текст

// Функция для расчёта прямой геодезической задачи
pair<double, double> p_geo_z(double x, double y, double d, double a){
	double dx = d * cos(a * M_PI / 180.0); // Переводим угол в радианы и вычисляем dx
	double dy = d * sin(a * M_PI / 180.0); // Переводим угол в радианы и вычисляем dy

	return make_pair(x + dx, y + dy); // Возвращаем новые координаты 
}
// Функция для расчёта обратной геодезической задачи
pair<double, double> o_geo_z(double x1, double x2, double y1, double y2){
	double dx = x2 - x1;
	double dy = y2 - y1;

	double d = sqrt(pow(dx, 2) + pow(dy, 2));
	double r = abs(atan2(dy, dx) * 180.0 / M_PI);

	int a = 0;

	if (dx > 0 && dy > 0){
		a += r;
	} else if(dx > 0 && dy < 0){
		a += 180 - r;
	} else if (dx < 0 && dy < 0){
		a += 180 + r;
	} else if(dx < 0 && dy > 0){
		a += 360 - r;
	} else if (dx == 0){
		if (dy > 0){
			a += 90;
		} else if(dy < 0){
			a += 270;
		}
	} else if(dy == 0){
		if (dx > 0){
			a += 0;
		} else if(dx < 0){
			a += 180;
		}
	}

	return make_pair(d, a); 
}
// Функция для расчёта дирекционного угла
double r_dir_y(double dir_y_1, double dir_y_2){
	double a = dir_y_1 + 180.0 - dir_y_2;
	return a;
}
// Функция для расчёта румба
double r_rumb(double a){
	if (a <= 90){
		return a;
	} else if (a > 90 && a < 180){
		return 180 - a;
	} else if (a > 180 && a < 270){
		return a - 180;
	} else if(a > 270 && a < 360){
		return 360 - a;
	}
	return -1;
}
// Функция для расчёта приложения по Х
double r_prol_x(double prol, double dir_y){
	double rad = dir_y * M_PI / 180.0; // Преобразование градусов в радианы
	double x_pr = prol * cos(rad);

	return x_pr;
}
// Функция для расчёта проложения по У
double r_prol_y(double prol, double dir_y){
	double rad = dir_y * M_PI / 180.0; // Преобразование градусов в радианы
	double y_pr = prol * sin(rad);

	return y_pr;
} 


int main(){

	cout << GREEN <<" ██████╗ ███████╗ ██████╗     ███████╗ ██╗███╗   ███╗" << endl;                   // Вывод кастомизации в консоль
	cout << GREEN <<"██╔════╝ ██╔════╝██╔═══██╗    ██╔════╝███║████╗ ████║" << endl;                   //  
	cout << GREEN <<"██║  ███╗█████╗  ██║   ██║    █████╗  ╚██║██╔████╔██║" << endl;                   //
	cout << GREEN <<"██║   ██║██╔══╝  ██║   ██║    ██╔══╝   ██║██║╚██╔╝██║" << endl;                   //
	cout << GREEN <<"╚██████╔╝███████╗╚██████╔╝    ███████╗ ██║██║ ╚═╝ ██║" << endl;				   // 	
	cout << GREEN <<" ╚═════╝ ╚══════╝ ╚═════╝     ╚══════╝ ╚═╝╚═╝     ╚═╝" << YELLOW << "Version 0.0.3" << endl;    // Вывод кастомизации + вывод инфо. версии программы

	cout << YELLOW <<"Функционал программы: " << endl;
	cout << " " << endl;
	cout << YELLOW <<"[1] "<< "Прямая геодезическая задача" << endl;
	cout << YELLOW <<"[2] "<< "Обратная геодезическая задача" << endl;
	cout << YELLOW <<"[3] "<< "Расчёт дирекционного угла" << endl;
	cout << YELLOW <<"[4] "<< "Расчёт румбов" << endl;
	cout << YELLOW <<"[5] "<< "Расчёт проложения по Х" << endl;
	cout << YELLOW <<"[6] "<< "Расчёт проложения по Y" << endl;
	cout << " " << endl;

	int povtor;
	do{
		int vybor;
		cout << "Выберите какой расчёт вам нужен: ";
		cin >> vybor;

		char repeat;

		switch(vybor){
			case 1:
				do{
					double x, y, d, a;
					cout << "Введите координату X: ";
					cin >> x;
					cout << "Введите координату Y: ";
					cin >> y;
					cout << "Введите горизонтальное проложение: ";
					cin >> d;
					cout << "Введите дирекционный угол: ";
					cin >> a;
					cout << " " << endl;

					pair<double, double> result = p_geo_z(x, y, d, a);

					cout << fixed << setprecision(3) << "Новые координаты: (" << result.first << ", " << result.second << ")" << endl;

					cout << " " << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;

				} while (repeat == 'Y' || repeat == 'y');
				break;
			case 2:
				do{
	 				double x1, x2, y1, y2;
	 				cout << "Введите Х1: ";
	 				cin >> x1;
	 				cout << "Введите X2: ";
	 				cin >> x2;
	 				cout << "Введите Y1: ";
	 				cin >> y1;
	 				cout << "Введите Y2: ";
	 				cin >> y2;
	 				cout << " " << endl;

	 				pair<double, double> result = o_geo_z(x1, x2, y1, y2);

	 				cout << fixed << setprecision(3) << "Новые координаты: (" << result.first << ", " << result.second << ")" << endl;
	 				cout << " " << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;

				} while (repeat == 'Y' || repeat == 'y');
				break;
			case 3:
				do{

					double dir_y_1, dir_y_2;

					cout << "Введите первый дирекционный угол: ";
					cin >> dir_y_1;
					cout << "Введите второй дирекционный угол: ";
					cin >> dir_y_2;
					cout << " " << endl;

					double o = r_dir_y(dir_y_1, dir_y_2);

					cout << fixed << setprecision(3) << "Дирекционный угол равен: " << o << endl;
					cout << " " << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;
				} while (repeat == 'Y' || repeat == 'y');
				break;
			case 4:
				do{

					double a;
					cout << "Введите значение дирекционного угла: ";
					cin >> a;
					cout << " " << endl;

					double o = r_rumb(a);

					cout << fixed << setprecision(3) << "Румб равняется: " << o << endl;
					cout << " " << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;
				} while (repeat == 'Y' || repeat == 'y');
				break;
			case 5:
				do{

					double prol;
					double dir_y;
					cout << "Введите значение проложения: ";
					cin >> prol;
					cout << "Введите значение дирекционного угла: ";
					cin >> dir_y;
					cout << " " << endl;

					double o = r_prol_x(prol, dir_y);

					cout << fixed << setprecision(3) << "Проложение равно: " << o << endl;
					cout << " " << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;
				} while (repeat == 'Y' || repeat == 'y');
				break;
			case 6:
				do{

					double prol;
					double dir_y;
					cout << "Введите значение проложения: ";
					cin >> prol;
					cout << "Введите значение дирекционного угла: ";
					cin >> dir_y;
					cout << " " << endl;

					double o = r_prol_y(prol, dir_y);

					cout << fixed << setprecision(3) << "Проложение равно: " << o << endl;

					cout << YELLOW <<"Хотите продолжить? (Y/n): ";
					cin >> repeat;
				} while (repeat == 'Y' || repeat == 'y');
				break;
			default:
				cout << RED <<"Ошибка! Возможно вы ввели не правильное значение! Презепустите программу!" << endl;
		}
		cout << " " << endl;
		cout << YELLOW <<"[0] Назад: ";
		cin >> povtor;
		cout << " " << endl;
	} while (povtor == 0);

	return 0;
}