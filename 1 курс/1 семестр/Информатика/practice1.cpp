#include <iostream>
#include <string>
#include <cmath>
#include <functional>
using namespace std;

static void run_task(const string& name, function<void()> func) {
    // Это декоратор, который я буду использовать для красивого форматирования задач и быстрой отладки
    cout << "\n==================================================" << endl;
    cout << name << endl;
    cout << "==================================================" << endl;

    func();

    cout << endl;
}

static void task_1_1() {
    string name;
    cout << "Введите Ваше имя: ";
    cin >> name;
    cout << "Привет, " << name << endl;
}

static void task_1_2() {
    float a, b;
    cout << "Введите первое число: "; cin >> a;
    cout << "Введите второе число: "; cin >> b;

    cout << "Сумма: " << a + b << endl;
    cout << "Разность: " << a - b << endl;
    cout << "Произведение: " << a * b << endl;

    if (b == 0) {
        cout << "Деление: на ноль делить нельзя" << endl;
    }
    else {
        cout << "Деление: " << a / b << endl;
    }
}

static void solveLinearEquation(float b, float c) {
    if (b == 0 && c == 0) {
        cout << "Уравнение имеет бесконечно много решений" << endl;
    }
    else if (b == 0) {
        cout << "Корней нет" << endl;
    }
    else {
        cout << "Корень = " << -c / b << endl;
    }
}

static void task_1_3() {
    float b, c;
    cout << "Введите b: "; cin >> b;
    cout << "Введите c: "; cin >> c;
    solveLinearEquation(b, c);
}

static void task_1_4() {
    float a, b, c;
    cout << "Введите a: "; cin >> a;
    cout << "Введите b: "; cin >> b;
    cout << "Введите c: "; cin >> c;

    if (a == 0) {
        solveLinearEquation(b, c);
    }
    else {
        double D = b * b - 4 * a * c;
        if (D > 0) {
            double sqrt_D = sqrt(D);
            cout << "x1 = " << (-b + sqrt_D) / (2 * a) << endl;
            cout << "x2 = " << (-b - sqrt_D) / (2 * a) << endl;
        }
        else if (D == 0) {
            cout << "x = " << -b / (2 * a) << endl;
        }
        else {
            cout << "Действительных корней нет" << endl;
        }
    }
}

static void task_1_5() {
    bool isDay, isCurtains, isLamp;
    cout << "Сейчас день? (0/1): "; cin >> isDay;
    cout << "Шторы открыты? (0/1): "; cin >> isCurtains;
    cout << "Лампа включена? (0/1): "; cin >> isLamp;

    if ((isDay && isCurtains) || isLamp) {
        cout << "В комнате светло!" << endl;
    }
    else {
        cout << "В комнате темно!" << endl;
    }
}

static void task_1_6() {
    const double PI = 3.1415926535;
    float R, r, h;
    cout << "Укажите радиус большего основания R: "; cin >> R;
    cout << "Укажите радиус меньшего основания r: "; cin >> r;
    cout << "Укажите высоту конуса h: "; cin >> h;

    if (R <= r || r < 0 || h <= 0) {
        cout << "Некорректный ввод! Убедитесь, что R > r > 0 и h > 0" << endl;
    }
    else {
        float l = sqrt(h * h + (R - r) * (R - r));
        double V = (1.0 / 3.0) * PI * h * (R * R + R * r + r * r);
        double S = PI * (R * R + l * (R + r) + r * r);

        cout << "Образующая l = " << l << endl;
        cout << "Объем V = " << V << endl;
        cout << "Площадь поверхности S = " << S << endl;
    }
}

void main()
{
    setlocale(LC_ALL, "RU");

    run_task("1.1 Имя", task_1_1);
    run_task("1.2 Арифметика", task_1_2);
    run_task("1.3 Уравнение", task_1_3);
    run_task("1.4 Еще уравнение", task_1_4);
    run_task("1.5 Лампа со шторой", task_1_5);
    run_task("1.6 Конус", task_1_6);
}