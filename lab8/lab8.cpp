#include <iostream>
#include <vector>
#include <string>
// Вариант 2

struct Book {
    std::string author;
    std::string title;
    int tomNumber;
    int pageCount;
    Book* nextOne;

    // Создание нового тома
    Book(std::string auth, std::string titl, int tom, int pages)
        : author(auth), title(titl), tomNumber(tom), pageCount(pages), nextOne(nullptr) {}
};

struct BookCollection {
    Book* firstTom; // Указатель на первый том в цепочке
    std::string author; // Автор сборника
    std::string title; // Название сборника

    // Создание сборника
    BookCollection (std::string auth, std::string titl)
        : author(auth), title(titl), firstTom(nullptr) {}

    // Деструктор, при удалении сборника все тома также удаляются из памяти
    ~BookCollection() {
        Book* k = firstTom;
        while (k != nullptr) {
            Book* next = k -> nextOne;
            delete k;
            k = next;
        }
    }
};

std::vector <BookCollection*> collections; // Все сборники
Book* readingLine = nullptr; // Начало очереди
Book* lineTail = nullptr; // Конец очереди

// Просмотр сборников
void viewCollection () {
    if (collections.empty()) {
        std::cout << "Нет созданных сборников" << std::endl;
        return;
    }

    std::cout << "СБОРНИКИ СОЧИНЕНИЙ" << std::endl;
    for (size_t i = 0; i < collections.size(); i++) {
        std::cout << "\nСборник номер" << i + 1 << ":\n";
        std::cout << "Автор: " << collections[i] -> author << "\n";
        std::cout << "Название: " << collections[i] -> title << "\n";
        Book* k = collections[i] -> firstTom; // Проход по цепочке томов 
        if (k == nullptr) {
            std::cout << "Томов нет" << std::endl;
        }
        else {
            std::cout << "Тома:" << std::endl;
            while (k != nullptr) {
                std::cout << "Том" << k -> tomNumber << ": " << k -> pageCount << " стр." << std::endl;
                k = k -> nextOne;
            }
        }
    }
}

void createNewCollection () {
    std::string author;
    std::string title;
    std::cout << "СОЗДАТЬ НОВЫЙ СБОРНИК" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите автора: ";
    getline(std::cin, author);
    std::cout << "Введите название сборника произведений: ";
    getline(std::cin, title);
    BookCollection* newCollection = new BookCollection(author, title);
    collections.push_back(newCollection);
    std::cout << "Сборник создан" << std::endl;
}

void addBook () {
    if (collections.empty()) {
        std::cout << "Необходимо создать сборник" << std::endl;
        return;
    }

    std::cout << "ДОБАВЛЕНИЕ КНИГ" << std::endl;
    std::cout << "Доступные сборники: " << std::endl;
    for (size_t i = 0; i < collections.size(); i++) {
        std::cout << i + 1 << ") " << collections[i] -> author << " - " << collections[i] -> title << std::endl;
    }

    int ind;
    std::cout << "Выберите номер сброника: " << std::endl;
    std::cin >> ind;

    if (ind < 1 || ind > static_cast<int> (collections.size())) {
        std::cerr << "Неверный номер сборника";
        return; 
    }

    BookCollection* collection = collections[ind - 1];

    int tomNumber;
    int pageCount;
    std::cout << "Введите номер тома: " << std::endl;
    std::cin >> tomNumber;

    Book* k = collection -> firstTom;
    while (k != nullptr) {
        if (k -> tomNumber == tomNumber) {
            std::cerr << "Ошибка. Том с таким номером уже существует в сборнике" << std::endl;
            return;
        }
        k = k -> nextOne;
    }

    std::cout << "Введите количество страниц: " << std::endl;
    std::cin >> pageCount;
    Book* newBook = new Book(collection -> author, collection -> title, tomNumber, pageCount);
    
    if (collection -> firstTom == nullptr || collection -> firstTom -> tomNumber > tomNumber) {
        newBook -> nextOne = collection -> firstTom;
        collection -> firstTom = newBook;
    }
    else {
        k = collection -> firstTom;
        while (k -> nextOne != nullptr && k -> nextOne -> tomNumber < tomNumber) {
            k = k -> nextOne;
        }
        newBook -> nextOne = k -> nextOne;
        k -> nextOne = newBook;
    }

    std::cout << "Книга добавлена в сборник" << std::endl;
}

void findTheBiggestBook () {
    if (collections.empty()) {
        std::cout << "Нет созданных сборников" << std::endl;
        return;
    }

    std::cout << "ПОИСК САМОЙ ОБЪЕМНОЙ КНИГИ" << std::endl;

    std::cout << "Доступные сборники: " << std::endl;
    for (size_t i = 0; i < collections.size(); i++) {
        std::cout << i + 1 << ") " << collections[i] -> author << " - " << collections[i] -> title << std::endl;
    }

    int ind;
    std::cout << "Выберите номер сброника: " << std::endl;
    std::cin >> ind;

    if (ind < 1 || ind > static_cast<int> (collections.size())) {
        std::cerr << "Неверный номер сборника";
        return; 
    }

    BookCollection* collection = collections[ind - 1];

    if (collection -> firstTom == nullptr) {
        std::cout << "В этом сборнике нет томов" << std::endl;
        return;
    }

    Book* k = collection -> firstTom;
    Book* mostPages = k;

    while (k != nullptr) {
        if (k -> pageCount > mostPages -> pageCount) {
            mostPages = k;
        }
        k = k -> nextOne;
    }
    std::cout << "Самое объемное произведение в сборнике: " << std::endl;
    std::cout << "Автор: " << mostPages -> author << std::endl;
    std::cout << "Сборник: " << mostPages -> title << std::endl;
    std::cout << "Том: " << mostPages -> tomNumber << std::endl;
    std::cout << "Количество страниц: " << mostPages -> pageCount << std::endl;
}

void createReadingLine () {
    Book* k = readingLine;
    while (k != nullptr) {
        Book* next = k -> nextOne;
        delete k;
        k = next;
    }
    readingLine = nullptr;
    lineTail = nullptr;
    std::cout << "СОЗДАНИЕ ОЧЕРЕДИ ЧТЕНИЯ НА ЛЕТО" << std::endl;

    if (collections.empty()) {
        std::cout << "Нет сборников для создания очереди" << std::endl;
        return;
    }

    // Все книги из всех сборников
    std::vector<Book*> allBooks;

    for (size_t i = 0; i < collections.size(); i++) {
        Book* book = collections[i] -> firstTom;
        while (book != nullptr) {
            Book* bookCopy = new Book(book -> author, book -> title, book -> tomNumber, book -> pageCount);
            allBooks.push_back(bookCopy);
            book = book -> nextOne;
        }
    }
    if (allBooks.empty()) {
        std::cout << "В сборниках нет книг" << std::endl;
        return;
    }

    // Добавляем по одной книге в очередь
    std::cout << "Добавление книг в очередь: " << std::endl;

    for (size_t i = 0; i < allBooks.size(); i++) {
        std::cout << "\nКнига " << i + 1 << " из " << allBooks.size() << ":\n";
        std::cout << allBooks[i] -> author << " - " << allBooks[i] -> title << " (Том " << allBooks[i] -> tomNumber << ")\n";

        char choice;
        std::cout << "Добавить в очередь? (y/n): ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'n') {
            if (readingLine == nullptr) {
                readingLine = allBooks[i];
                lineTail = allBooks[i];
            }
            else {
                lineTail -> nextOne = allBooks[i];
                lineTail = allBooks[i];
            }
            lineTail -> nextOne = nullptr;
        }
        else {
            delete allBooks[i];
        }
    }

    allBooks.clear();
    std::cout << "Очередь чтения создана" << std::endl;
}

// Просмотр очереди чтения на лето
void viewReadingLine () {
    std::cout << "ОЧЕРЕДЬ ЧТЕНИЯ НА ЛЕТО" << std::endl;
    if (readingLine == nullptr) {
        std::cout << "Очередь пуста" << std::endl;
        return;
    }

    Book* k = readingLine;
    int position = 1;

    while (k != nullptr) {
        std::cout << position << ") " << k -> author << " - " << k -> title << " (Том " << k -> pageCount << " стр.)" << std::endl;
        k = k -> nextOne;
        position++;
    }
}

// Инициализация некоторых примеров
void Examples () {
    std::cout << "ИНИЦИАЛИЗАЦИЯ ПРИМЕРАМИ" << std::endl;

    BookCollection* col1 = new BookCollection("Фёдор Михайлович Достоевский", "Братья Карамазовы");
    BookCollection* col2 = new BookCollection("Александр Сергеевич Пушкин", "Собрание сочинений");
    BookCollection* col3 = new BookCollection("Антон Павлович Чехов", "Рассказы и повести");

    collections.push_back(col1);
    collections.push_back(col2);
    collections.push_back(col3);

    Book* book1 = new Book("Фёдор Михайлович Достоевский", "Братья Карамазовы", 1, 350);
    Book* book2 = new Book("Фёдор Михайлович Достоевский", "Братья Карамазовы", 2, 350);
    Book* book3 = new Book("Фёдор Михайлович Достоевский", "Братья Карамазовы", 3, 400);

    col1 -> firstTom = book1;
    book1 -> nextOne = book2;
    book2 -> nextOne = book3;

    Book* book4 = new Book("Александр Сергеевич Пушкин", "Собрание сочинений", 1, 300);
    Book* book5 = new Book("Александр Сергеевич Пушкин", "Собрание сочинений", 4, 280);

    col2 -> firstTom = book4;
    book4 -> nextOne = book5;

    Book* book6 = new Book("Антон Павлович Чехов", "Рассказы и повести", 2, 310);
    Book* book7 = new Book("Антон Павлович Чехов", "Рассказы и повести", 4, 310);
    Book* book8 = new Book("Антон Павлович Чехов", "Рассказы и повести", 5, 290);

    col3 -> firstTom = book6;
    book6 -> nextOne = book7;
    book7 -> nextOne = book8;

}

// Очистка всех данных
void clearAllData () {
    // Очищение очереди чтения
    Book* k = readingLine;
    while (k != nullptr) {
        Book* next = k -> nextOne;
        delete k;
        k = next;
    }
    readingLine = nullptr;
    lineTail = nullptr;

    // Очищение сборников
    for (size_t i = 0; i < collections.size(); i++) {
        delete collections[i];
    }
    collections.clear();

    std::cout << "Все данные очищены" << std::endl;
}

// Меню
void Menu () {
    std::cout << "\n------ МЕНЮ УПРАВЛЕНИЯ СОБРАНИЯМИ ПРОИЗВЕДЕНИЙ ------\n" << std::endl;
    std::cout << "0) Выход" << std::endl;
    std::cout << "1) Просмотр всех сборников" << std::endl;
    std::cout << "2) Создание нового сборника" << std::endl;
    std::cout << "3) Добавить книгу в сборник" << std::endl;
    std::cout << "4) Найти самое объемное произведение" << std::endl;
    std::cout << "5) Создать очередь чтения на лето" << std::endl;
    std::cout << "6) Просмотр очереди чтения" << std::endl;
    std::cout << "7) Инициализировать примерами (3 сборника)" << std::endl;
    std::cout << "8) Очистить все данные" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "Выберите пункт меню: ";
}

int main() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        Menu();
        std::cin >> choice;

        switch (choice) {
            case 0:
            exitProgram = true;
            std::cout << "Выход из программы" << std::endl;
            break;

            case 1:
            viewCollection();
            break;

            case 2:
            createNewCollection();
            break;

            case 3:
            addBook();
            break;

            case 4:
            findTheBiggestBook();
            break;

            case 5:
            createReadingLine();
            break;

            case 6:
            viewReadingLine();
            break;

            case 7:
            Examples();
            break;

            case 8:
            clearAllData();
            break;

            default:
            std::cout << "Неверный номер команды" << std::endl;
            break;
        }
    }

    // Очистка памяти
    clearAllData();
    return 0;
}
