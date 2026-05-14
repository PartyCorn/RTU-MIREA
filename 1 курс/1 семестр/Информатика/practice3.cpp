#include <iostream>
#include <functional>  // для 7 строки
#include <string>  // для getline()
#include <fstream>
#include <algorithm>  // для работы с контейнерами
#include <cctype>  // для работы с символами
#include <vector> // для 3.5
using namespace std;

static void run_task(const string& name, function<void()> func) {
    cout << "\n==================================================" << endl;
    cout << name << endl;
    cout << "==================================================" << endl;

    func();

    cout << endl;
}

static int task_3_1() {
    ofstream fout("file.txt");
    if (!fout.is_open()) {
        cout << "Ошибка при создании файла!";
        return 1;
    }

    fout << "Привет, мир!\n";
    fout << "Для следующего задания я подготовлю строки из букв и чисел.\n";
    // generated via Python random.sample(ascii_lowercase + ascii_uppercase + '0123456789' * 5, 100)
    fout << "Qp4717e5jJxZo942BKht8281I26v13EnFg70VmGWq2rH8Mi6R21Yl398y9kX534w74D5c3P8f103aOCT09u06b965dLz5S7A64N0\n";
    fout.close();
    cout << "Файл успешно записан!" << endl;

    ifstream fin("file.txt");
    if (!fin.is_open()) {
        cout << "Ошибка при открытии файла для чтения!";
        return 1;
    }

    cout << "\nСодержимое файла:\n";
    cout <<   "-----------------\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();

    return 0;
}

static int task_3_2() {
    ifstream fin("file.txt");
    if (!fin.is_open()) {
        cout << "Ошибка при открытии файла для чтения!";
        return 1;
    }

    cout << "\nТолько числа из записанного ранее файла:\n";
    cout <<   "----------------------------------------\n";
    char buff;
    while (fin.get(buff)) {
        if (isdigit(buff)) cout << buff;
    }
    cout << endl;
    fin.close();

    return 0;
}

static int task_3_3() {
    string line;
    cout << "Введите строку из 30 букв (обрежу, если >30, или нажмите Enter): "; getline(cin, line);;
    if (line.length()) {
        line.erase(remove_if(line.begin(), line.end(),
            [](char c) { return !isalpha(c); }), line.end());  // оставим только буквы
        line = line.substr(0, 30);
        if (line.length() < 30) {
            cout << "Вы ввели меньше 30 букв!";
            return 1;
        }
    }
    else {
        line = "shtjqkyvrzpclbnmdoeaifgwuxDBCA";
    }

    sort(line.begin(), line.end());
    cout << "Результат: " << line << endl;

    return 0;
}

static int task_3_4() {
    int a, b;
    cout << "Введите первое число: "; cin >> a;
    cout << "Введите второе число: "; cin >> b;

    int x = a, y = b;

    // Способ 1: делением НОД(a,b) = НОД(b,a % b)
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    cout << "НОД делением: " << x << endl;

    // Способ 2: вычитанием НОД(a,b) = НОД(a-b,b)
    x = a; y = b;
    while (x != y) {
        if (x > y) {
            x = x - y;
        }
        else {
            y = y - x;
        }
    }
    cout << "НОД вычитанием: " << x << endl;

    return 0;
}

static int task_3_5() {
    int n;
    cout << "Введите натуральное число: "; cin >> n;
    if (n <= 0) {
        cout << "Ошибка: число должно быть натуральным (положительным)" << endl;
        return 1;
    }

    vector<bool> arr(n + 1, true);  // +1, чтобы избежать проблему с индексацией далее
    arr[0] = arr[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (arr[i]) {
            for (int j = i * i; j <= n; j += i) {
                arr[j] = false;
            }
        }
    }
    cout << "Простые числа до " << n << ": ";
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i]) cout << i << ", ";
    }

    return 0;
}

static int task_3_6() {
    ofstream fout("file.txt");
    if (!fout.is_open()) {
        cout << "Ошибка при создании файла!";
        return 1;
    }

    for (float i = 1.0; i <= 10; i++) {
        fout << i * 7.0 / 3.0 * 17.0 / 9.1336 << endl;  // тут любую последовательность указать
    }
    cout << "Записал 10 чисел в файл" << endl;
    fout.close();

    ifstream fin("file.txt");
    if (!fin.is_open()) {
        cout << "Ошибка при открытии файла для чтения!";
        return 1;
    }

    float sum{};
    string line;
    while (getline(fin, line)) {
        cout << line << " ";
        sum += stof(line);
    }
    cout << endl << "Сумма этих чисел: " << sum;
    fin.close();

    return 0;
}

void main() {
    setlocale(LC_ALL, "RU");
    setlocale(LC_NUMERIC, "C");  // для 3.6: stof() и stod() ожидают точку как разделитель дробной части, но в локале RU используется запятая

    run_task("3.1 Копирование файла", task_3_1);
    run_task("3.2 Фильтр", task_3_2);
    run_task("3.3 Сортировка букв", task_3_3);
    run_task("3.4 Алгорим Евклида", task_3_4);
    run_task("3.5 Решето Эратосфена", task_3_5);
    run_task("3.6 Файл", task_3_6);
}