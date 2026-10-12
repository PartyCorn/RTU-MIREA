#include <chrono>
#include <cstdio>
#include <fstream>
#include <clocale>
using namespace std;

struct TaxPayer {
    long long inn;      // ИНН ключ, 10-значное число
    char surname[30];   // Фамилия
    char phone[20];     // Телефон
};

struct TableEntry {
    long long key;
    long offset;
};

long long generateKey() {
    long long key = 1 + rand() % 9;
    for (int i = 0; i < 9; i++)
        key = key * 10 + rand() % 10;
    return key;
}

bool alreadyUsed(long long* keys, int count, long long key) {
    for (int i = 0; i < count; i++)
        if (keys[i] == key) return true;
    return false;
}

// Пред.: offset — корректное смещение в файле fname.
// Пост.: возвращает прочитанную запись
TaxPayer readRecord(const char* fname, long offset) {
    ifstream f(fname, ios::binary);
    TaxPayer p;
    f.seekg(offset);
    f.read((char*)&p, sizeof(p));
    f.close();
    return p;
}

// Пред.: n > 0. Пост.: создан бинарный файл fname из n уникальных записей,
// в lastKey возвращается ключ последней записанной записи
void generateFile(const char* fname, int n, long long& lastKey) {
    long long* keys = new long long[n];
    ofstream f(fname, ios::binary);
    for (int i = 0; i < n; i++) {
        long long key;
        do { key = generateKey(); } while (alreadyUsed(keys, i, key));
        keys[i] = key;

        TaxPayer p;
        p.inn = key;
        sprintf_s(p.surname, "Surname%d", i);
        sprintf_s(p.phone, "+7900%07d", i);
        f.write((char*)&p, sizeof(p));
        lastKey = key;
    }
    f.flush(); f.close();
    delete[] keys;
}

// Пост.: заполняет table парами (ключ, смещение) из файла, сортирует по ключу
// и возвращает количество записей
int buildTable(const char* fname, TableEntry* table) {
    ifstream f(fname, ios::binary);
    TaxPayer p;
    int count = 0;
    long pos = 0;
    while (f.read((char*)&p, sizeof(p))) {
        table[count].key = p.inn;
        table[count].offset = pos;
        count++;
        pos += sizeof(p);
    }
    f.close();

    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - 1 - i; j++)
            if (table[j].key > table[j + 1].key) {
                TableEntry tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
    return count;
}

// Пред.: файл fname существует и содержит записи TaxPayer.
// Пост.: если запись с ключом key найдена, result заполнен
// и возвращается true, иначе false
bool linearSearch(const char* fname, long long key, TaxPayer& result) {
    ifstream f(fname, ios::binary);
    TaxPayer p;
    while (f.read((char*)&p, sizeof(p))) {
        if (p.inn == key) { result = p; f.close(); return true; }
    }
    f.close();
    return false;
}

// Пред.: table отсортирована по возрастанию ключа.
// Пост.: возвращает смещение записи с ключом key, либо -1, если не найдено
long interpolationSearch(TableEntry* table, int count, long long key) {
    int lo = 0, hi = count - 1;
    while (lo <= hi && key >= table[lo].key && key <= table[hi].key) {
        if (table[hi].key == table[lo].key)
            return (table[lo].key == key) ? table[lo].offset : -1;
        int pos = lo + (int)((double)(key - table[lo].key) * (hi - lo)
            / (table[hi].key - table[lo].key));
        if (table[pos].key == key) return table[pos].offset;
        if (table[pos].key < key) lo = pos + 1; else hi = pos - 1;
    }
    return -1;
}

void measureGenerate(int n, const char* fname) {
    long long lastKey = 0;

    auto start = std::chrono::high_resolution_clock::now();
    generateFile(fname, n, lastKey);
    auto end = std::chrono::high_resolution_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    printf_s("Записей: %d | %.0f мкс (%.2f мс) | %.2f мкс/запись\n",
        n, (double)us, us / 1000.0, (double)us / n);
}

void measureLinear(const char* fname, int n) {
    long long key = 0;
    generateFile(fname, n, key);

    auto t1 = std::chrono::high_resolution_clock::now();
    TaxPayer res;
    bool found = linearSearch(fname, key, res);
    auto t2 = std::chrono::high_resolution_clock::now();

    double ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

    printf("N=%d, найдено=%d, время=%.3f мс\n", n, (int)found, ms);
}

void measureInterpolation(const char* fname, int n) {
    long long key = 0;
    generateFile(fname, n, key);

    TableEntry* table = new TableEntry[n];

    auto t1 = std::chrono::high_resolution_clock::now();

    int count = buildTable(fname, table);
    long off = interpolationSearch(table, count, key);

    bool found = false;
    TaxPayer res;
    if (off != -1) { res = readRecord("taxpayers.dat", off); found = true; }

    auto t2 = std::chrono::high_resolution_clock::now();

    double us = std::chrono::duration<double, std::micro>(t2 - t1).count();
    double ms = us / 1000.0;

    delete[] table;

    printf("N=%d, найдено=%d, время=%.3f мс (%.1f мкс)\n",
        n, (int)found, ms, us);
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    // measureGenerate(100, "taxpayers.bin");
    
    int sizes[] = { 100, 1000, 10000 };
    for (int s = 0; s < 3; s++) {
        // measureLinear("taxpayers.dat", sizes[s]);
        measureInterpolation("taxpayers.dat", sizes[s]);
    }

    return 0;
}