#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>
using namespace std;

static void run_task(const string& name, function<void()> func) {
    cout << "\n==================================================" << endl;
    cout << name << endl;
    cout <<   "==================================================" << endl;

    func();

    cout << endl;
}

static void task_2_1() {
    float x, a;
    cout << "Введите x: "; cin >> x;
    cout << "Введите a: "; cin >> a;
    if (abs(x) < 1) {
        if (abs(x) > 1e-10) {
            cout << "w = " << a * log(abs(x)) << endl;
        }
        else {
            cout << "неопределенность" << endl;
        }
    }
    else {
        if (x * x <= a) {
            cout << "w = " << sqrt(a - x * x) << endl;
        }
        else {
            cout << "неопределенность" << endl;
        }
    }
}

static void task_2_2() {
    float x, y, b;
    cout << "Введите x: "; cin >> x;
    cout << "Введите y: "; cin >> y;
    cout << "Введите b: "; cin >> b;
    if (y < b && x <= b) {
        cout << "z = " << log(b - y) * sqrt(b - x);
    }
    else {
        cout << "неопределенность" << endl;
    }
}

static void task_2_3() {
    float N;
    cout << "Введите N: "; cin >> N;

    for (int i = ceil(N); i < N + 10; i++) cout << i << " ";
}

static void task_2_4() {
    cout << setw(5) << "x" << setw(16) << "y" << endl;
    cout << setw(5) << "----" << setw(16) << "---------" << endl;
    for (double x = -4.0; x <= 4.0; x += 0.5) {
        if (abs(x - 1.0) < 1e-10) { // Если x отличается от 1 меньше чем на 10^(-10), считаем что x = 1
            cout << setw(5) << fixed << setprecision(1) << x;
            cout << setw(16) << "не определена" << endl;
            continue;
        }
        double y = (x * x - 2 * x + 2) / (x - 1);
        cout << setw(5) << fixed << setprecision(1) << x;
        cout << setw(16) << fixed << setprecision(6) << y << endl;
    }
}

static void task_2_5() {
    float S, p, n;
    cout << "Сумма займа (руб): "; cin >> S;
    cout << "Процент займа (%): "; cin >> p;
    cout << "Срок займа (лет): "; cin >> n;
    if (S < 1e-10 || n < 1e-10 || p < 1e-10) {
        cout << "Некорректный ввод";
    }
    else {
        double r = p / 100;
        double pow_term = pow(1 + r, n);
        double m = (S * r * pow_term) / (12 * (pow_term - 1));
        cout << "Месячная выплата m = " << fixed << setprecision(2) << m << " руб" << endl;
    }
}

static void task_2_6() {
    float S, m, n;
    cout << "Величина ссуды (руб): "; cin >> S;
    cout << "Месячная выплата (руб): "; cin >> m;
    cout << "Нужно погасить в течение (лет): "; cin >> n;
    if (S < 1e-10 || n < 1e-10 || m < 1e-10) {
        cout << "Некорректный ввод";
        return;
    }

    if (m * 12 * n < S) {
        cout << "Нереалистичные данные: сумма выплат (" << m * 12 * n
            << " руб) меньше суммы ссуды (" << S << " руб)" << endl;
        return;
    }
    
    double r = 0.01;
    double prev_r;

    do {
        prev_r = r;
        double pow_term = pow(1 + r, n);
        // делим обе части на (1+r)^n, умножаем крест-накрест, делим еще на S*(1+r)^n, чтобы слева осталась только r
        r = (12 * m * (pow_term - 1)) / (S * pow_term);
    } while (abs(r - prev_r) > 1e-6);

    cout << "Ссуда выдана под " << fixed << setprecision(2) << r * 100 << "%" << endl;
}

void main() {
    setlocale(LC_ALL, "RU");

    //run_task("2.1 Разветвление", task_2_1);
    //run_task("2.2 Функция", task_2_2);
    //run_task("2.3 Порядок", task_2_3);
    run_task("2.4 Табуляция", task_2_4);
    //run_task("2.5 Заем", task_2_5);
    //run_task("2.6 Ссуда", task_2_6);
}