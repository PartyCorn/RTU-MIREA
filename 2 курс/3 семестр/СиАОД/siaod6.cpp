#include <iostream>
#include <vector>
#include <string>
#include <clocale>
#include <Windows.h>
using namespace std;

struct Account {
    int number;
    string fio, address;
};

struct Cell {
    int key, idx, state; // 0 пусто, 1 занято, 2 удалено
};

class HashTable {
    vector<Account> data; // массив полезных данных
    vector<Cell> t;       // хеш-таблица
    int m = 8, n = 0, c = 3; // размер, занятые+удалённые, шаг

    // поиск ячейки с ключом, p - число проб
    int findCell(int k, int& p) {
        int h = k % m;
        for (p = 1; p <= m; p++) {
            int a = (h + c * (p - 1)) % m;
            if (t[a].state == 0) return -1;
            if (t[a].state == 1 && t[a].key == k) return a;
        }
        return -1;
    }
    // запись в таблицу, возвращает адрес ячейки
    int put(int k, int idx) {
        int h = k % m;
        for (int i = 0; i < m; i++) {
            int a = (h + c * i) % m;
            if (t[a].state != 1) {
                if (t[a].state == 0) n++;
                t[a] = Cell{ k, idx, 1 };
                return a;
            }
        }
        return -1;
    }
    // увеличение вдвое и рехеширование
    void rehash() {
        vector<Cell> old = t;
        m *= 2; n = 0;
        t.assign(m, Cell{ 0, 0, 0 });
        for (Cell x : old)
            if (x.state == 1) put(x.key, x.idx);
        cout << "Рехеширование, новый размер: " << m << endl;
    }
public:
    HashTable() { t.assign(m, Cell{ 0, 0, 0 }); }

    void insert(Account a) {
        int p;
        if (findCell(a.number, p) != -1) { cout << "Такой ключ уже есть\n"; return; }
        if ((n + 1.0) / m >= 0.75) rehash(); // коэффициент нагрузки
        data.push_back(a);
        int addr = put(a.number, data.size() - 1);
        cout << "Вставлено: h=" << a.number % m << ", адрес=" << addr;
        if (addr != a.number % m) cout << " (коллизия)";
        cout << endl;
    }
    void remove(int k) {
        int p, a = findCell(k, p);
        if (a == -1) { cout << "Не найден\n"; return; }
        int idx = t[a].idx, last = data.size() - 1;
        t[a].state = 2; // метка "удалено"
        if (idx != last) { // последнюю запись ставим на место удалённой
            data[idx] = data[last];
            t[findCell(data[idx].number, p)].idx = idx;
        }
        data.pop_back();
        cout << "Удалено\n";
    }
    void find(int k) {
        int p, a = findCell(k, p);
        if (a == -1) { cout << "Не найден\n"; return; }
        Account& r = data[t[a].idx];
        cout << "Найден в ячейке " << a << ", проб: " << p << ": "
            << r.fio << ", " << r.address << endl;
    }
    void print() {
        cout << "m=" << m << ", n=" << n << endl;
        for (int i = 0; i < m; i++) {
            cout << i << ": ";
            if (t[i].state == 0) cout << "пусто";
            else if (t[i].state == 2) cout << "удалено";
            else {
                Account& a = data[t[i].idx];
                cout << a.number << " | " << a.fio << " | " << a.address
                    << " (idx " << t[i].idx << ")";
            }
            cout << endl;
        }
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    HashTable h;
    // автозаполнение 5 записями, три с коллизией (h=1)
    h.insert({ 1000001, "Иванов И.И.", "Москва, ул. Мира, 1" });
    h.insert({ 1000009, "Петров П.П.", "Тверь, ул. Ленина, 5" });
    h.insert({ 1000017, "Сидоров С.С.", "Казань, ул. Кирова, 7" });
    h.insert({ 2000003, "Козлов К.К.", "Омск, ул. Мая, 3" });
    h.insert({ 3000005, "Орлов О.О.", "Тула, ул. Речная, 9" });

    int cmd = -1, k;
    while (cmd != 0) {
        cout << "\n1-вставить 2-удалить 3-найти 4-вывести 0-выход\n> ";
        cin >> cmd;
        if (cmd >= 1 && cmd <= 3) {
            cout << "Номер счёта (7 цифр): ";
            cin >> k;
            if (k < 1000000 || k > 9999999) { cout << "Неверный номер\n"; continue; }
        }
        if (cmd == 1) {
            Account a; a.number = k;
            cin.ignore();
            cout << "ФИО: "; getline(cin, a.fio);
            cout << "Адрес: "; getline(cin, a.address);
            h.insert(a);
        }
        else if (cmd == 2) h.remove(k);
        else if (cmd == 3) h.find(k);
        else if (cmd == 4) h.print();
    }
    return 0;
}
