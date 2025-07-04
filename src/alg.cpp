// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>

#include "bst.h"

bool compareFrequency(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "' для чтения." << std::endl;
        return;
    }

    std::string current_word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            current_word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!current_word.empty()) {
                tree.insert(current_word);
                current_word.clear();
            }
        }
    }

    if (!current_word.empty()) {
        tree.insert(current_word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> word_frequencies;
    tree.getWordFrequencies(word_frequencies);

    std::sort(word_frequencies.begin(), word_frequencies.end(), compareFrequency);

    std::cout << "Частотный анализ слов (по убыванию встречаемости):" << std::endl;
    for (const auto& pair : word_frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::ofstream outfile("result/freq.txt");
    if (!outfile.is_open()) {
        std::cerr << "Ошибка: не получилось открыть файл 'result/freq.txt' для записи результатов." << std::endl;
        return;
    }

    outfile << "Частотный анализ слов (по убыванию встречаемости):" << std::endl;
    for (const auto& pair : word_frequencies) {
        outfile << pair.first << ": " << pair.second << std::endl;
    }

    outfile.close();
}
