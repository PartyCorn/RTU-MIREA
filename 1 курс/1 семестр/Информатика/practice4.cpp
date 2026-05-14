#include <iostream>
#include <functional>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

static void run_task(const string& name, function<void()> func) {
    cout << "\n==================================================" << endl;
    cout << name << endl;
    cout << "==================================================" << endl;

    func();

    cout << endl;
}

static void task_4_1() {
    int x;
    cout << "Введите число: "; cin >> x;
    cout << "Сигнум равен " << (x > 0 ? 1 : (x == 0 ? 0 : -1)) << endl;
}

static double rectangleArea(double length, double width) {
    return length * width;
}

static double triangleArea(double base, double height) {
    return 0.5 * base * height;
}

static double circleArea(double radius) {
    return 3.14 * radius * radius;
}

static void task_4_2() {
    int choice;
    double a, b, r;

    cout << "Выберите фигуру для вычисления площади:" << endl;
    cout << "1 - Прямоугольник" << endl;
    cout << "2 - Треугольник" << endl;
    cout << "3 - Круг" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Введите длину и ширину прямоугольника: ";
        cin >> a >> b;
        cout << "Площадь прямоугольника: " << rectangleArea(a, b) << endl;
        break;

    case 2:
        cout << "Введите основание и высоту треугольника: ";
        cin >> a >> b;
        cout << "Площадь треугольника: " << triangleArea(a, b) << endl;
        break;

    case 3:
        cout << "Введите радиус круга: ";
        cin >> r;
        cout << "Площадь круга: " << circleArea(r) << endl;
        break;

    default:
        cout << "Неверный выбор!" << endl;
    }
}

static int task_4_3() {
    cout << endl;
    for (int i = 0; i < 13; i++) {
        if (i < 7) for (int j = 0; j < 8; j++) cout << (i < 6 ? "* " : "  ");
        int fit_line = i < 7 ? 34 : 34 + 8 * 2;
        for (int j = 0; j < fit_line; j++) cout << (!(i % 2) ? '#' : '-');
        cout << endl;
    }

    return 0;
}

static void task_4_4() {
    /* Пример для x = 40 (середина):
        x = 40
        x_val = 4.0 * π * 40 / 80 = 2π
        sin(2π) = 0
        plot_y = 10 - (0 * 10) = 10
    */
    const int width = 80, height = 20;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double x_val = 4.0 * 3.14 * x / width;
            int plot_y = height / 2 - (int)(sin(x_val) * height / 2);
            cout << (plot_y == y ? '*' : ' ');
        }
        cout << '\n';
    }
}

static void task_4_5() {
    cout << "I вариант: m=37, k=3, c=64" << endl;
    cout << "Первые 10 чисел последовательности:" << endl;

    int s = 0;
    for (int n = 1; n <= 10; n++) {
        s = (37 * s + 3) % 64;
        cout << "s" << n << " = " << s << endl;
    }

    cout << "\nII вариант: m=25173, k=13849, c=65537" << endl;
    cout << "Первые 5 чисел последовательности:" << endl;

    s = 0;
    for (int n = 1; n <= 5; n++) {
        s = (25173 * s + 13849) % 65537;
        cout << "s" << n << " = " << s << endl;
    }
}

// Сортировка вставками (как в визуализации)
static void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        // Сдвигаем элементы больше key вправо
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static void bucketSort(vector<int>& arr, int bucketCount) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    if (minVal == maxVal) return; // Все элементы одинаковые

    vector<vector<int>> buckets(bucketCount); // Корзинки

    double range = (double)(maxVal - minVal + 1) / bucketCount; // Распределяем элементы по корзинкам

    for (int num : arr) {
        int bucketIndex = (num - minVal) / range;
        if (bucketIndex >= bucketCount) bucketIndex = bucketCount - 1;
        buckets[bucketIndex].push_back(num);
    }

    // Сортируем каждую корзинку и собираем обратно
    arr.clear();
    for (auto& bucket : buckets) {
        insertionSort(bucket);
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}

static void task_4_6() {
    vector<int> arr;
    int n, bucketCount;

    cout << "Введите количество элементов: ";
    cin >> n;

    cout << "Введите " << n << " элементов через пробел: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        arr.push_back(num);
    }

    cout << "Введите количество корзинок: ";
    cin >> bucketCount;

    if (bucketCount < 1e-10) {
        cout << "Количество корзинок должно быть положительным!" << endl;
        return;
    }

    cout << "До сортировки: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    bucketSort(arr, bucketCount);

    cout << "После сортировки: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RU");

    run_task("4.1 Знак числа", task_4_1);
    run_task("4.2 Геометрические фигуры", task_4_2);
    run_task("4.3 Былая слава", task_4_3);
    run_task("4.4 Синусоида", task_4_4);
    run_task("4.5 Генератор псевдослучайных чисел", task_4_5);
    run_task("4.6 Алгоритм сортировки (блочный или \"корзиночный\")", task_4_6);
}