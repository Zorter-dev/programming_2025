#include <iostream>

const char LOWER_TO_UPPER_CASE_DIFF = 32;

char to_lower (char c) {
    if ('a' <= c && c <= 'z') {
        return c;
    }
    return c - LOWER_TO_UPPER_CASE_DIFF;
}

bool is_alpha(char c) {
    c = to_lower(c);
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
        return true;
    }
    return false;
}

int main() {
    char c; // symbolic type, integer type
    char c1 = 'a';
    char c2 = 'B';
    std::cout << c1 << std::endl;
    std::cout << (to_lower(c1) < to_lower(c2)) << std::endl;
    
    char str[100] = "Hello, world!";
    std::cout << str << std::endl;

    size_t len = strlen(str);
    for (int i = 0; i < strlen(str); i++) {
        std::cout << static_cast<int>(str[i]) << " ";
    }

    // Конкатенация 
    char str1[100] = "hello";
    char str2[100] = "world";
    strcat(str1, str2);
    std::cout << str1 << std::endl;
}