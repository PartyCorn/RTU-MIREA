#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <numeric>
#include <windows.h>
#include <algorithm>
using namespace std;

static void run_task(const string& name, function<void()> func) {
    cout << "\n==================================================" << endl;
    cout << name << endl;
    cout << "==================================================" << endl;

    func();

    cout << endl;
}

static void task_5_1() {
    float A[3][4] = { 5, 2, 0, 10, 3, 5, 2, 5, 20, 0, 0, 0 };
    float B[4][2] = { 1.2, 0.5, 2.8, 0.4, 5.0, 1.0, 2.0, 1.5 };
    float C[3][2] = { {0} };

    for (int i = 0; i < sizeof(A) / sizeof(A[0]); i++) {  // строки матрицы A
        for (int j = 0; j < sizeof(B[0]) / sizeof(B[0][0]); j++) {  // столбцы матрицы B
            C[i][j] = 0;
            for (int k = 0; k < sizeof(A[0]) / sizeof(A[0][0]); k++) {  // общий размер
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "Матрица C:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << C[i][j] << "\t";
        }
        cout << endl;
    }

    // 1
    float total_sales = 0, min_sales = INFINITY, max_sales = 0;
    int min_sales_idx = 0, max_sales_idx = 0;
    for (int i = 0; i < 3; i++) {
        total_sales += C[i][0];
        if (C[i][0] < min_sales) {
            min_sales = C[i][0];
            min_sales_idx = i;
        }
        if (C[i][0] > max_sales) {
            max_sales = C[i][0];
            max_sales_idx = i;
        }
    }
    cout << endl << "Минимальные продажи: " << min_sales << " (магазин " << min_sales_idx + 1 << ")" << endl;
    cout << "Максимальные продажи: " << max_sales << " (магазин " << max_sales_idx + 1 << ")" << endl << endl;

    // 2
    float total_commission = 0, min_commission = INFINITY, max_commission = 0;
    int min_commission_idx = 0, max_commission_idx = 0;
    for (int i = 0; i < 3; i++) {
        total_commission += C[i][1];
        if (C[i][1] < min_commission) {
            min_commission = C[i][1];
            min_commission_idx = i;
        }
        if (C[i][1] > max_commission) {
            max_commission = C[i][1];
            max_commission_idx = i;
        }
    }
    cout << endl << "Минимальные комиссионные: " << min_commission << " (магазин " << min_commission_idx + 1 << ")" << endl;
    cout << "Максимальные комиссионные: " << max_commission << " (магазин " << max_commission_idx + 1 << ")" << endl << endl;

    // 3
    cout << "Общая выручка: " << total_sales << endl;
    // 4
    cout << "Всего комиссионных: " << total_commission << endl;
    // 5
    cout << "Общая выручка: " << total_sales + total_commission << endl;
}

static void task_5_2() {
    string input;
    cout << "Введите римскую запись числа: "; cin >> input;
    if (input.empty()) {
        cerr << "Ошибка: введена пустая строка!" << endl;
        return;
    }

    int sum{};
    map<char, int> values = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };

    for (char& c : input) {
        c = toupper(c);
        if (values.find(c) == values.end()) {
            cerr << "Ошибка: недопустимый символ '" << c << "'!" << endl;
            cerr << "Разрешенные символы: I, V, X, L, C, D, M" << endl;
            return;
        }
    }

    // Проверка на повторяющиеся недопустимые комбинации
    vector<string> invalidRepeats = { "VV", "LL", "DD", "IIII", "XXXX", "CCCC", "MMMM" };
    for (const auto& invalid : invalidRepeats) {
        if (input.find(invalid) != string::npos) {
            cerr << "Ошибка: недопустимое повторение символов '" << invalid << "'!" << endl;
            return;
        }
    }

    // Проверка на вычитание
    for (size_t i = 0; i < input.length(); i++) {
        if (i + 1 < input.length() && values[input[i]] < values[input[i + 1]]) {
            if ((values[input[i]] * 10 < values[input[i + 1]]) || (values[input[i + 1]] - values[input[i]] == values[input[i]])) {
                cerr << "Ошибка: недопустимое вычитание: '" << input[i] << input[i + 1] << "'!" << endl;
                return;
            }
            // Проверка на повторение (чтобы не было IIX и IXI)
            if ((i > 0 && values[input[i - 1]] <= values[input[i]]) || (i + 2 < input.length() && values[input[i + 2]] >= values[input[i]])) {
                cerr << "Ошибка: недопустимая последовательность!" << endl;
                return;
            }
            // Проверка на DCD, LXL, VIV
            if (i > 0 && i + 1 < input.length() &&
                values[input[i - 1]] == values[input[i + 1]] &&
                values[input[i]] < values[input[i - 1]]) {

                string pattern = { input[i - 1], input[i], input[i + 1] };
                if (pattern == "DCD" || pattern == "LXL" || pattern == "VIV") {
                    cerr << "Ошибка: недопустимая последовательность '" << pattern << "'!" << endl;
                    return;
                }
            }

        }
    }

    for (size_t i = 0; i < input.length(); i++) {  // беззнаковый целочисленный тип (идеально для индексов)
        if (i + 1 < input.length() && values[input[i]] < values[input[i + 1]]) {
            sum -= values[input[i]];
        }
        else {
            sum += values[input[i]];
        }
    }

    if (sum < 1e-10) {
        cerr << "Ошибка: некорректное римское число!" << endl;
        return;
    }

    cout << "Результат: " << sum;
}

static long baseTo10(const string& input, int base) {
    if (base < 2 || base > 36) {
        cerr << "Основание должно быть между 2 и 36" << endl;
        return LONG_MIN;
    }

    bool isNegative = (input[0] == '-');
    long value = 0;
    for (size_t i = (isNegative ? 1 : 0); i < input.length(); i++) {
        char c = toupper(input[i]);

        // Converting char to int
        if (c >= '0' && c <= '9') {
            c -= '0';
        }
        else {
            c = c - 'A' + 10;
        }

        if (c >= base) {
            cerr << "Числовое значение " << to_string(c) << " превышает основание " << base << " или равно ему" << endl;
            return LONG_MIN;
        }

        value = value * base + c;
    }

    if (isNegative) value *= -1;

    return value;
}

static string toBase(long value, int base) {
    if (base < 2 || base > 36) {
        cerr << "Основание должно быть между 2 и 36" << endl;
        return "";
    }
    if (value == 0) return "0";

    bool isNegative = (value < 0);
    if (isNegative) value *= -1;

    string res = "";
    while (value > 0) {
        char c = value % base;

        if (c < 10) {
            c += '0';
        }
        else {
            c = c + 'A' - 10;
        }

        res = c + res;
        value /= base;
    }

    if (isNegative) res = '-' + res;

    return res;
}

static void task_5_3() {
    string number;
    int old_base, new_base;
    cout << "Исходное число: "; cin >> number;
    cout << "Старое основание: "; cin >> old_base;
    cout << "Новое основание: "; cin >> new_base;
    cout << toBase(baseTo10(number, old_base), new_base) << endl;
}

static int task_5_4() {
    /*21. Статистическая обработка текстового файла : поиск наиболее часто
        встречающейся гласной буквы.
      22. Статистическая обработка текстового файла : поиск наименее часто
        встречающейся гласной буквы.*/

    ofstream fout("file.txt");
    if (!fout.is_open()) {
        cout << "Ошибка при создании файла!";
        return 1;
    }
    fout.close();
    cout << "Запишите что-нибудь в созданный файл и нажмите Enter"; cin.get();

    ifstream fin("file.txt");
    if (!fin.is_open()) {
        cout << "Ошибка при открытии файла для чтения!";
        return 1;
    }
    map<char, int> frequency;
    char c;
    while (fin.get(c)) {
        char lower_c = tolower(c);
        frequency[lower_c]++;
    }
    fin.close();

    string vowels = "aeiouyаеёиоуыэюя";

    char most_frequent_vowel = '\0';
    char least_frequent_vowel = '\0';
    int max_count = 0;
    int min_count = INT_MAX;

    for (const auto& pair : frequency) {
        char character = pair.first;
        int count = pair.second;

        if (isalpha(character) && vowels.find(character) != string::npos) {
            if (count > max_count) {
                max_count = count;
                most_frequent_vowel = character;
            }
            if (count < min_count) {
                min_count = count;
                least_frequent_vowel = character;
            }
        }
    }

    if (most_frequent_vowel != '\0') {
        cout << "Наиболее часто встречающаяся гласная буква: '" << most_frequent_vowel
            << "' (встречается " << max_count << " раз)" << endl;
    }
    else {
        cout << "Гласные буквы не найдены в файле" << endl;
        return 0;
    }

    if (least_frequent_vowel != '\0') {
        cout << "Наименее часто встречающаяся гласная буква: '" << least_frequent_vowel
            << "' (встречается " << min_count << " раз)" << endl;
    }
    else {
        cout << "Гласные буквы не найдены в файле" << endl;
    }

    return 0;
}

static void task_5_5_1() {
    /* 13) Дано натуральное число т < 27. Получить все трехзначные целые числа,
сумма цифр которых равна т (указание: использовать полный перебор). */
    int m; cout << "Введите сумму цифр m: "; cin >> m;
    if (m < 1 || m > 26) {
        cout << "Нет результатов" << endl;
        return;
    }

    int c = 0;
    for (int i = 100; i < 1000; i++) {
        if (i / 100 + i / 10 % 10 + i % 10 == m) {
            cout << i << ", "; c++;
        }
    }
    cout << endl << "Отображено " << c << " результатов" << endl << endl;
}

static void task_5_5_2() {
    /* 14) Получить все четырехзначные целые числа, в записи которых нет двух
    одинаковых цифр(указание: использовать полный перебор). */

    int c = 0;
    for (int i = 1000; i < 10000; i++) {
        int n = i;
        bool digits[10] = { false };
        bool valid = true;

        for (int j = 0; j < 4; j++) {
            int digit = n % 10;
            if (digits[digit]) {
                valid = false;
                break;
            }
            digits[digit] = true;
            n /= 10;
        }

        if (valid) {
            std::cout << i << ", "; c++;
        }
    }
    cout << endl << "Отображено " << c << " результатов" << endl << endl;
}

static void task_5_5_3() {
    /* 18) Написать программу, которая определяет количество учеников в
    классе, чей рост превышает средний. */

    cout << "*** Анализ роста учеников ***" << endl;
    cout << "Введите рост (см) и нажмите <Enter>." << endl;
    cout << "Для завершения введите 0 и нажмите <Enter>" << endl << "-> ";
    vector<float> heights;
    float height;
    while (cin >> height && height != 0) {
        cout << "-> ";
        heights.push_back(height);
    }
    float sum = accumulate(heights.begin(), heights.end(), 0.0f);
    float mean = sum / heights.size();

    int count = 0;
    for (float h : heights) {
        if (h > mean) {
            count++;
        }
    }

    cout << "Средний рост: " << mean << " (см)" << endl;
    cout << "У " << count << "-х человек рост превышает средний" << endl;
}

struct Book {
    string author;
    string title;
    int year{};
};

static void task_5_6_1() {
    /* 2) Создать файл, содержащий сведения в библиотеке о книгах : ФИО автора,
    название, год издания.Данные вводить с клавиатуры.
        1. найти название книги, автор и год издания которой вводятся вручную;
        2. определить имеется ли книга, в названии которой есть слово «Паскаль».Если
           «да», то сообщить автора и год издания. */
    ofstream file("library.txt");
    Book book;
    cout << "Введите данные о книгах (для завершения введите пустую строку):" << endl;
    while (true) {
        cout << "Автор: "; getline(cin, book.author);
        if (book.author.empty()) break;
        cout << "Название: "; getline(cin, book.title);
        cout << "Год: "; cin >> book.year; cin.ignore();

        file << book.author << "|" << book.title << "|" << book.year << endl;
        cout << "Книга добавлена!" << endl;
    }
    file.close();

    // Поиск книги
    cout << "\n=== Поиск книги ===" << endl;
    string searchAuthor, searchTitle;
    int searchYear;
    char choice;

    cout << "Введите автора (или оставьте пустым): "; getline(cin, searchAuthor);

    cout << "Введите название (или оставьте пустым): "; getline(cin, searchTitle);

    cout << "Искать по году? (y/n): "; cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        cout << "Введите год: ";
        cin >> searchYear;
    } else {
        searchYear = -1; // год не указан
    }
    cin.ignore();

    ifstream in("library.txt");
    string line;
    bool found = false;

    cout << "\nРезультаты поиска:\n";

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string author = line.substr(0, pos1);
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int year = stoi(line.substr(pos2 + 1));

            bool authorMatch = searchAuthor.empty() || author.find(searchAuthor) != string::npos;
            bool titleMatch = searchTitle.empty() || title.find(searchTitle) != string::npos;
            bool yearMatch = (searchYear == -1) || (year == searchYear);

            if (authorMatch && titleMatch && yearMatch) {
                cout << "Найдена: " << author << " - \"" << title << "\" (" << year << " год)" << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "Книги не найдены.\n";
    }

    // Проверка на ключевое слово
    cout << "\n=== Поиск книг о Паскале ===" << endl;
    ifstream in2("library.txt");
    bool pascalFound = false;

    while (getline(in2, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string author = line.substr(0, pos1);
            string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int year = stoi(line.substr(pos2 + 1));

            if (title.find("Паскаль") != string::npos ||
                title.find("Pascal") != string::npos ||
                title.find("паскаль") != string::npos) {
                cout << "Книга о Паскале: " << author << " - \"" << title << "\" (" << year << " год)" << endl;
                pascalFound = true;
            }
        }
    }

    if (!pascalFound) {
        cout << "Книг о Паскале не найдено.\n";
    }
    in2.close();
}

struct Contact {
    string surname;
    string name;
    string phone;
};

static void task_5_6_2() {
    /* 18) Написать программу, которая создаст файл phone.txt с информацией:
    фамилия и номер телефона нескольких ваших товарищей. Программа должна
    запрашивать фамилию человека и выводить его телефон. Если в справочнике есть
    одинаковые фамилии, то программа должна вывести список всех людей, имеющих
    эти фамилии. В другом файле организовать отсортированные по фамилиям данные
    исходного файла. */
    ofstream file("phone.txt");
    Contact contact;
    cout << "Введите данные контактов (для завершения введите пустую строку):" << endl;
    while (true) {
        cout << "Фамилия: "; getline(cin, contact.surname);
        if (contact.surname.empty()) break;
        cout << "Имя: "; getline(cin, contact.name);
        cout << "Телефон: "; getline(cin, contact.phone);

        file << contact.surname << "|" << contact.name << "|" << contact.phone << endl;
        cout << "Контакт добавлен!" << endl;
    }
    file.close();

    // Поиск по фамилии
    cout << "\n=== Поиск по фамилии ===" << endl;
    string searchSurname;
    cout << "Введите фамилию для поиска: "; getline(cin, searchSurname);

    ifstream in("phone.txt");
    string line;
    bool found = false;
    vector<Contact> foundContacts;
    vector<Contact> allContacts;

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 != string::npos && pos2 != string::npos) {
            string surname = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string phone = line.substr(pos2 + 1);

            Contact contact;
            contact.surname = surname;
            contact.name = name;
            contact.phone = phone;

            allContacts.push_back(contact);

            if (surname == searchSurname) {
                foundContacts.push_back(contact);
                found = true;
            }
        }
    }
    in.close();

    if (found) {
        cout << "\nНайдено " << foundContacts.size() << " контакт(ов):" << endl;
        for (const auto& contact : foundContacts) {
            cout << contact.surname << " " << contact.name << " - " << contact.phone << endl;
        }
    }
    else {
        cout << "Контакты с фамилией '" << searchSurname << "' не найдены." << endl;
    }

    // Сортировка по фамилии в отдельный файл
    sort(allContacts.begin(), allContacts.end(), [](const Contact& a, const Contact& b) {
        return a.surname < b.surname;
    });

    ofstream sortedFile("phone_sorted.txt");
    for (const auto& contact : allContacts) {
        sortedFile << contact.surname << " " << contact.name << " - " << contact.phone << endl;
    }

    cout << "Отсортированный список сохранен в файл 'phone_sorted.txt'" << endl;

    cout << "\n=== Отсортированный список контактов ===" << endl;
    for (const auto& contact : allContacts) {
        cout << contact.surname << " " << contact.name << " - " << contact.phone << endl;
    }
}

static void task_5_6_3() {
    /* 9) Создать два файла А и В.Компонентами файлов являются ЦЕЛЫЕ числа,
    которые следует упорядочить по возрастанию. Объединить содержимое файлов в
    новый файл С с сохранением сортировки всех элементов. */
    ofstream a("A.txt"), b("B.txt");
    a << "3\n1\n4\n2\n";
    b << "6\n5\n8\n7\n";
    a.close(); b.close();

    vector<int> numbers;
    int num;

    ifstream inA("A.txt"), inB("B.txt");
    while (inA >> num) numbers.push_back(num);
    while (inB >> num) numbers.push_back(num);
    inA.close(); inB.close();

    sort(numbers.begin(), numbers.end());

    ofstream c("C.txt");
    for (int n : numbers) c << n << endl;
    c.close();

    cout << "Файлы объединены и отсортированы в C.txt" << endl;

    cout << "Содержимое файла C.txt:" << endl;
    ifstream inC("C.txt");
    string line;
    while (getline(inC, line)) {
        cout << line << endl;
    }
    inC.close();
}

static vector<vector<int>> permutations(vector<int> arr) {
    vector<vector<int>> res;

    if (arr.empty()) return res;

    if (arr.size() == 1) {
        res.push_back(arr);
        return res;
    }

    for (int i = 0; i < arr.size(); i++) {
        vector<int> remaining; // массив без текущего элемента
        for (int j = 0; j < arr.size(); j++) {
            if (j != i) {
                remaining.push_back(arr[j]);
            }
        }

        vector<vector<int>> perms = permutations(remaining); // оставшиеся перестановки элементов
        for (auto& perm : perms) {
            perm.insert(perm.begin(), arr[i]);
            res.push_back(perm);
        }
    }

    return res;
}

static int factorial(int n, int res = 1) {
    return (n > 1) ? factorial(n - 1, res * n) : res;
}

static long long subfactorial(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    //return (long long)n * subfactorial(n - 1) + (n % 2 == 0 ? 1 : -1);
    return round(factorial(n) / exp(1.0));
}

static long long countSituations(int n, vector<bool>& used, int pos, bool hasMatch) {
    if (pos > n) {
        return hasMatch ? 1 : 0;
    }

    long long total = 0;

    for (int num = 1; num <= n; num++) {
        if (!used[num]) {
            bool newMatch = hasMatch || (num == pos);

            if (newMatch && !hasMatch) {
                int remaining = n - pos;
                long long ways = 1;
                for (int i = 1; i <= remaining; i++) ways *= i;
                total += ways;
                continue;
            }

            used[num] = true;
            total += countSituations(n, used, pos + 1, newMatch);
            used[num] = false;
        }
    }

    return total;
}

static void task_5_7() {
    int n = 10;
    cout << "Математическое решение: " << factorial(n) - subfactorial(n) << " ситуаций" << endl;
    
    vector<bool> used(n + 1, false); // индексы 1..n
    long long result = countSituations(n, used, 1, false);
    cout << "Найдено " << result << " ситуаций" << endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //run_task("5.1 Умножение матриц", task_5_1);
    //run_task("5.2 Автоматный распознаватель", task_5_2);
    //run_task("5.3 Системы счисления", task_5_3);

    //run_task("5.4 Обработка текстовых файлов (21 и 22 задачи)", task_5_4);
    
    //run_task("5.5 Ряды (13 задача)", task_5_5_1);
    //run_task("5.5 Ряды (14 задача)", task_5_5_2);
    //run_task("5.5 Ряды (18 задача)", task_5_5_3);

    //run_task("5.6 Файлы (2 задача)", task_5_6_1);
    //run_task("5.6 Файлы (18 задача)", task_5_6_2);
    //run_task("5.6 Файлы (9 задача)", task_5_6_3);

    run_task("5.7 Шарики", task_5_7);
}