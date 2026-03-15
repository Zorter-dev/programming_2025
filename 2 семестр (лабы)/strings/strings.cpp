#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

const char vowels[] = "аеёиоуъыьэюя";
const char consonants[] = "бвгджзйклмнпрстфхцчшщ";

bool isRussianLetter(char l) {
    return (l >= 'а' && l <= 'я') || (l >= 'A' && l <= 'Я') || l == 'ё' || l == 'Ё';
}

bool isRussianVowel(char v) {
    v = std::tolower(v);
    for (int i = 0; vowels[i] != '\0'; i++) {
        if (v == vowels[i]) return true;
    }
    return false;
}
bool isRussianConsonants(char c) {
    c = std::tolower(c);
    for (int i = 0; consonants[i] != '\0'; i++) {
        if (c == consonants[i]) return true;
    }
    return false;
}

void task0() {
    std::cout << "----- ТАБЛИЦА ---=-" << std::endl;
    std::cout << "Строчные:" << std::endl;
    for (char l = 'а'; l <= 'я'; l++) {
        std::cout << l << " | " << (int)l << std::endl;
        if ((l - 'а' + 1) % 10 == 0) std::cout << "\n";
    }
    std::cout << "ё" << " | " << (int)'ё' << std::endl;
    
    std::cout << "Заглавные:" << std::endl;
    for (char l = 'А'; l <= 'Я'; l++) {
        std::cout << l << " | " << (int)l << std::endl;
        if ((l - 'А' + 1) % 10 == 0) std::cout << "\n";
    }
    std::cout << "Ё" << " | " << (int)'Ё' << std::endl;

    std::cout << "Англ. строчные:" << std::endl;
    for (char l = 'a'; l <= 'z'; l++) {
        std::cout << l << " | " << (int)l << std::endl;
        if ((l - 'a' + 1) % 10 == 0) std::cout << "\n";
    }

    std::cout << "Англ. заглавные:" << std::endl;
    for (char l = 'A'; l <= 'Z'; l++) {
        std::cout << l << " | " << (int)l << std::endl;
        if ((l - 'A' + 1) % 10 == 0) std::cout << "\n";
    }

    std::cout << "Цифры:" << std::endl;
    for (char n = '0'; n <= '9'; n++) {
        std::cout << n << " | " << (int)n << std::endl;
    }

    std::cout << "Знаки препинания:" << std::endl;
    const char punct[] = ".,!?;:-()\"'";
    for (int i = 0; punct[i] != '\0'; i++) {
        std::cout << punct[i] << " | " << (int)punct[i] << std::endl;
    }
    std::cout << "\n";
}

void task1() {
    std::cout << "Введите строку (не более 100): " << std::endl;
    char str[101];
    std::cin.ignore();
    std::cin.getline(str, 100);
    for (int i = 0; str[i] != '\0'; i++) {
        if (isRussianConsonants(str[i])) {
            str[i] = std::toupper(str[i]);
        }
    }
    std::cout << "Изм. текст: " << str << std::endl;
}

struct Word {
    char text[101];
    int length;
};

void cleanWord(const char* src, char* dst) {
    int j = 0;
    int len = std::strlen(src);
    int start = 0;
    while (start < len && !std::isalnum(src[start]) && !isRussianLetter(src[start])) {
        start++;
    }
    for (int i = start; i < len; i++) {
        if (std::isalnum(src[i]) || isRussianLetter(src[i])) {
            dst[j++] = std::tolower(src[i]);
        }
        else {
            break;
        }
    }
    dst[j] = '\0';
}

bool containsTwoLetters(const char* word, char letter1, char letter2) {
    bool has1 = false;
    bool has2 = false;
    letter1 = std::tolower(letter1);
    letter2 = std::tolower(letter2);
    for (int i = 0; word[i] != '\0'; i++) {
        char c = std::tolower(word[i]);
        if (c == letter1) has1 = true;
        if (c == letter2) has2 = true;
    }
    return has1 && has2;
}

void task2() {
    std::cout << "ЗАДАЧА №2" << std::endl;
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cout << "Файл не найден" << std::endl;
        return;
    }

    int N;
    char letter1;
    char letter2;
    inputFile >> N >> letter1 >> letter2;
    inputFile.close();

    std::cout << "Найти " << N << " самых коротких слов, в которых будут буквы '" << letter1 << "' и '" << letter2 << "'" << std::endl;
    std::ifstream textFile("text.txt");
    if (!textFile) {
        std::cout << "Файл не найден" << std::endl;
        return;
    }

    char buffer[1001];
    Word words[501];
    int wordCount = 0;
    char temp[101];
    while (textFile >> buffer) {
        cleanWord(buffer, temp);
        if (std::strlen(temp) > 0) {
            bool f = false;
            for (int i = 0; i < wordCount; i++) {
                if (std::strcmp(words[i].text, temp) == 0) {
                    f = true;
                    break;
                }
            }
            if (!f) {
                std::strcpy(words[wordCount].text, temp);
                words[wordCount].length = std::strlen(temp);
                wordCount++;
            }
        }
    }
    textFile.close();

    Word variants[500];
    int varianCount = 0;
    for (int i = 0; i < wordCount; i++) {
        if (containsTwoLetters(words[i].text, letter1, letter2)) {
            variants[varianCount++] = words[i];
        }
    }
    std::cout << "Найдено нужных слов: " << varianCount << std::endl;
    for (int i = 0; i < varianCount - 1; i++) {
        for (int j = 0; j < varianCount - i - 1; j++) {
            if (variants[j].length > variants[j + 1].length) {
                Word temp = variants[j];
                variants[j] = variants[j + 1];
                variants[j + 1] = temp;
            }
        }
    }

    std::ofstream resultFile("result.txt");
    if (!resultFile) {
        std::cout << "Не удалось создать файл" << std::endl;
        return;
    }

    int count = (N < varianCount) ? N : varianCount;
    resultFile << "Самые короткие слова, содержащие буквы '" << letter1 << "' и '" << letter2 << "'" << std::endl;
    for (int i = 0; i < count; i++) {
        resultFile << variants[i].text << " длина" << variants[i].length << std::endl;
    }
    resultFile.close();
    std::cout << "Результат записан в файл" << std::endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        std::cout << "0. Задача 0" << std::endl;
        std::cout << "1. Задача 1" << std::endl;
        std::cout << "2. Задача 2" << std::endl;
        std::cout << "3. Выход" << std::endl;
        std::cout << "Выберите пункт: " << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 0: task0(); break;
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: std::cout << "Выход :("  << std::endl; break;
            default: std::cout << "Неверный пункт -_-" << std::endl;
        }
    } while (choice != 3);
    return 0;
}