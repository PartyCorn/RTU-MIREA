#include <iostream>
#include <string>
#include <cstdlib>
#include <clocale>
#include <Windows.h>
using namespace std;

const int Q = 11;         // размер хеш-таблицы
struct Cell { string pat; int cnt; bool used; };
Cell tab[Q];              // хеш-таблица образцов
long long cmpCount = 0;   // число сравнений символов

// хеш строки (полином, основание 31)
int hashStr(const string& s) {
    int h = 0;
    for (char c : s) h = (h * 31 + (unsigned char)c) % Q;
    return h;
}

// вставка образца, линейное пробирование с шагом 1
int addPattern(const string& p) {
    int a = hashStr(p);
    while (tab[a].used) {
        if (tab[a].pat == p) return a; // образец уже есть
        a = (a + 1) % Q;
    }
    tab[a].pat = p; tab[a].cnt = 0; tab[a].used = true;
    return a;
}

// поиск образца в таблице, -1 если нет
int findPattern(const string& p) {
    int a = hashStr(p);
    for (int i = 0; i < Q && tab[a].used; i++) {
        if (tab[a].pat == p) return a;
        a = (a + 1) % Q;
    }
    return -1;
}

// алгоритм Хорспула, число вхождений p в t
int horspool(const string& t, const string& p) {
    int n = t.size(), m = p.size(), cnt = 0;
    if (m == 0 || m > n) return 0;
    int shift[256];
    for (int i = 0; i < 256; i++) shift[i] = m;             // сдвиг по умолчанию
    for (int i = 0; i < m - 1; i++) shift[(unsigned char)p[i]] = m - 1 - i;
    int pos = 0;
    while (pos <= n - m) {
        int j = m - 1;
        while (j >= 0) {                                    // сравнение справа налево
            cmpCount++;
            if (t[pos + j] != p[j]) break;
            j--;
        }
        if (j < 0) cnt++;
        pos += shift[(unsigned char)t[pos + m - 1]];        // сдвиг окна
    }
    return cnt;
}

// замер: случайный текст длины n, образец длины m
void measure(int n, int m, bool ok) {
    string t(n, 'a');
    for (int i = 0; i < n; i++) t[i] = 'a' + rand() % 25;   // без буквы z
    string p = ok ? t.substr(n / 2, m) : string(m, 'z');    // из текста или нет
    cmpCount = 0;
    int k = horspool(t, p);
    cout << n << "\t" << m << "\t" << (ok ? "успех" : "неуспех")
        << "\t" << k << "\t" << cmpCount << endl;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int mode;
    cout << "1 - поиск образцов, 2 - замер сложности\n> ";
    cin >> mode;
    if (mode == 2) {
        cout << "n\tm\tпоиск\tвхождений\tсравнений\n";
        int ns[] = { 1000, 10000, 100000, 1000000 };
        int ms[] = { 2, 3, 5, 10, 20, 50 };
        for (int n : ns) { measure(n, 5, true); measure(n, 5, false); }
        for (int m : ms) { measure(100000, m, true); measure(100000, m, false); }
        return 0;
    }
    string text, p;
    int k;
    cin.ignore();
    cout << "Текст: "; getline(cin, text);
    cout << "Сколько образцов (до " << Q - 1 << "): "; cin >> k;
    cin.ignore();
    for (int i = 0; i < k && i < Q - 1; i++) {
        cout << "Образец " << i + 1 << ": "; getline(cin, p);
        addPattern(p);
    }
    // поиск для каждой занятой ячейки и вывод таблицы
    cout << "\nЯчейка: образец | вхождений | сравнений\n";
    for (int i = 0; i < Q; i++) {
        cout << i << ": ";
        if (!tab[i].used) { cout << "пусто\n"; continue; }
        cmpCount = 0;
        tab[i].cnt = horspool(text, tab[i].pat);
        cout << tab[i].pat << " | " << tab[i].cnt << " | " << cmpCount << endl;
    }
    // запрос результата по образцу через хеш-таблицу
    cout << "\nОбразец для запроса (0 - выход): ";
    while (getline(cin, p) && p != "0") {
        int a = findPattern(p);
        if (a == -1) cout << "Нет в таблице\n";
        else cout << "Ячейка " << a << ", вхождений: " << tab[a].cnt << endl;
        cout << "> ";
    }
    return 0;
}
