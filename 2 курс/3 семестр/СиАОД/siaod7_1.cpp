#include <iostream>
#include <queue>
#include <clocale>
using namespace std;

struct Node {
    int value;
    bool red;
    Node* left, * right, * parent;
};

Node* root = nullptr;

Node* createNode(int x) {
    Node* n = new Node;
    n->value = x;
    n->red = true;
    n->left = n->right = n->parent = nullptr;
    return n;
}

// Левый поворот вокруг узла x
void rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Правый поворот вокруг узла x
void rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Балансировка после вставки
void fixInsert(Node* z) {
    while (z->parent && z->parent->red) {
        Node* grand = z->parent->parent;
        if (z->parent == grand->left) {
            Node* uncle = grand->right;
            if (uncle && uncle->red) {
                z->parent->red = false;
                uncle->red = false;
                grand->red = true;
                z = grand;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->red = false;
                grand->red = true;
                rotateRight(grand);
            }
        }
        else {
            Node* uncle = grand->left;
            if (uncle && uncle->red) {
                z->parent->red = false;
                uncle->red = false;
                grand->red = true;
                z = grand;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->red = false;
                grand->red = true;
                rotateLeft(grand);
            }
        }
    }
    root->red = false;
}

// Вставка элемента, false если такой уже есть
bool insert(int x) {
    Node* p = nullptr, * t = root;
    while (t) {
        p = t;
        if (x == t->value) return false;
        t = (x < t->value) ? t->left : t->right;
    }
    Node* z = createNode(x);
    z->parent = p;
    if (!p) root = z;
    else if (x < p->value) p->left = z;
    else p->right = z;
    fixInsert(z);
    return true;
}

// Вывод дерева повёрнутым на 90 градусов
void printTree(Node* n, int level) {
    if (!n) return;
    printTree(n->right, level + 1);
    for (int i = 0; i < level; i++) cout << "    ";
    cout << n->value << (n->red ? "(кр)" : "(ч)") << endl;
    printTree(n->left, level + 1);
}

void inorder(Node* n) {
    if (!n) return;
    inorder(n->left);
    cout << n->value << (n->red ? "(кр) " : "(ч) ");
    inorder(n->right);
}

void bfs() {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* n = q.front();
        q.pop();
        cout << n->value << (n->red ? "(кр) " : "(ч) ");
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

int sumLeaves(Node* n) {
    if (!n) return 0;
    if (!n->left && !n->right) return n->value;
    return sumLeaves(n->left) + sumLeaves(n->right);
}

int sumAll(Node* n) {
    if (!n) return 0;
    return n->value + sumAll(n->left) + sumAll(n->right);
}

int countNodes(Node* n) {
    if (!n) return 0;
    return 1 + countNodes(n->left) + countNodes(n->right);
}

void menuTraversals() {
    int choice;
    do {
        cout << "\n--- Обходы ---\n";
        cout << "1. Симметричный обход\n2. Обход в ширину\n0. Назад\nВыбор: ";
        cin >> choice;
        if (choice != 1 && choice != 2) continue;
        if (!root) {
            cout << "Дерево пусто\n";
        }
        else if (choice == 1) {
            inorder(root);
            cout << endl;
        }
        else {
            bfs();
            cout << endl;
        }
    } while (choice != 0);
}

void menuCalc() {
    int choice;
    do {
        cout << "\n--- Вычисления ---\n";
        cout << "1. Сумма значений листьев\n2. Среднее арифметическое всех узлов\n0. Назад\nВыбор: ";
        cin >> choice;
        if (choice != 1 && choice != 2) continue;
        if (!root) {
            cout << "Дерево пусто\n";
        }
        else if (choice == 1) {
            cout << "Сумма листьев: " << sumLeaves(root) << endl;
        }
        else {
            cout << "Среднее: " << (double)sumAll(root) / countNodes(root) << endl;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice, x, n;
    do {
        cout << "\n=== Красно-чёрное дерево ===\n";
        cout << "1. Ввести n элементов\n2. Добавить элемент\n3. Показать дерево\n";
        cout << "4. Обходы\n5. Вычисления\n0. Выход\nВыбор: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Сколько элементов: ";
            cin >> n;
            cout << "Введите элементы: ";
            for (int i = 0; i < n; i++) {
                cin >> x;
                if (!insert(x)) cout << "Элемент " << x << " уже есть\n";
            }
        }
        else if (choice == 2) {
            cout << "Элемент: ";
            cin >> x;
            if (!insert(x)) cout << "Такой элемент уже есть\n";
        }
        else if (choice == 3) {
            if (!root) cout << "Дерево пусто\n";
            else printTree(root, 0);
        }
        else if (choice == 4) {
            menuTraversals();
        }
        else if (choice == 5) {
            menuCalc();
        }
    } while (choice != 0);
    return 0;
}
