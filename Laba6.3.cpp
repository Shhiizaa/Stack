// Laba6.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>

using namespace std;

struct Node {
    char symbol;
    Node* next;
    Node(char value) : symbol(value), next(0) {}
};

class Stack {
private:
    Node* top;

public:
    Stack() : top(0) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() {
        return top == 0;
    }

    void push(char value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Записи не найдены" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    char getTop() {
        if (isEmpty()) {
            cout << "Стек пуст" << endl;
            return '\0';
        }
        return top->symbol;
    }
};

bool checkParentheses(const char* ch) {
    Stack parenthesesStack;
    for (int i = 0; i < strlen(ch); i++) {
        if (ch[i] == '(' || ch[i] == '[' || ch[i] == '{') {
            parenthesesStack.push(ch[i]);
        }
        else if (ch[i] == ')' || ch[i] == ']' || ch[i] == '}') {
            if (parenthesesStack.isEmpty()) {
                return false;
            }

            char top = parenthesesStack.getTop();
            if ((ch[i] == ')' && top == '(') || (ch[i] == ']' && top == '[') || (ch[i] == '}' && top == '{')) {
                parenthesesStack.pop();
            }
            else {
                return false;
            }
        }
    }

    return parenthesesStack.isEmpty();
}

void look(int n, char** arr) {
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ") " << arr[i] << endl;
    }
}

void check(int n, char** arr) {
    for (int i = 0; i < n; i++) {
        if (checkParentheses(arr[i]))
            cout << "Скобки в выражении расставлены верно" << endl;
        else
            cout << "Скобки расставлены неверно" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    char* buffer = nullptr;
    int n;
    try {
        buffer = new char[30];
    }
    catch (const std::bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
        return 1;
    }

    ofstream f;
    f.exceptions(ofstream::failbit | ofstream::badbit); 

    try {
        f.open("parentheses.txt", ios::app);
        cout << "Введите кол-во записей: ";
        cin >> n;
        cin.ignore();

        for (int i = 0; i < n; i++) {
            cout << "Введите выражение: ";
            cin.getline(buffer, 30);
            f << buffer << "\n";
            cout << endl;
        }
        f.close();
    }
    catch (const std::ofstream::failure& e) {
        cerr << "Ошибка записи в файл: " << e.what() << endl;
        delete[] buffer;
        return 1;
    }

    char** arr = nullptr;
    try {
        arr = new char* [30];
    }
    catch (const std::bad_alloc& e) {
        cerr << "Ошибка выделения памяти: " << e.what() << endl;
        delete[] buffer;
        return 1;
    }

    ifstream F;
    try {
        F.open("parentheses.txt", ios::in);
        if (!F.is_open()) {
            cerr << "Ошибка открытия файла" << endl;
            delete[] buffer;
            delete[] arr;
            return 1;
        }
        n = 0;
        while (1) {
            arr[n] = new char[30];
            F.getline(arr[n], 30, '\n');
            if (F.eof()) {
                break;
            }
            n++;
        }
        F.close();
    }
    catch (const std::ifstream::failure& e) {
        cerr << "Ошибка чтения из файла: " << e.what() << endl;
        delete[] buffer;
        for (int i = 0; i < n; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        return 1;
    }

    int a = 1;
    while (a) {
        cout << endl;
        cout << "1) Просмотреть введенные выражение" << endl;
        cout << "2) Проверить все введенные выражения" << endl;
        cout << "0) Выход" << endl;
        cin >> a;
        switch (a) {
        case 0:
            break;
        case 1:
            look(n, arr);
            break;
        case 2:
            check(n, arr);
            break;
        }
    }

    delete[] buffer;
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
