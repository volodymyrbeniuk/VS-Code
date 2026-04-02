#include "price.h"
#include <iostream>
#include <fstream>
#include <string>

// Заокруглення копійок
void roundPrice(Price &p) {
    int remainder = p.kopiyka % 10;
    if (remainder < 5) {
        p.kopiyka -= remainder; 
    } else {
        p.kopiyka += (10 - remainder);
    }
    
    // Переведення зайвих копійок у гривні
    if (p.kopiyka >= 100) {
        p.hryvnia += p.kopiyka / 100;
        p.kopiyka %= 100;
    }
}

// Додавання двох цін
void addPrice(Price &result, const Price &p1, const Price &p2) {
    result.hryvnia = p1.hryvnia + p2.hryvnia;
    result.kopiyka = p1.kopiyka + p2.kopiyka;

    if (result.kopiyka >= 100) {
        result.hryvnia += result.kopiyka / 100;
        result.kopiyka %= 100;
    }
}

// Множення ціни на кількість
void multiplyPrice(Price &p, int amount) {
    p.hryvnia *= amount;
    p.kopiyka *= amount;

    if (p.kopiyka >= 100) {
        p.hryvnia += p.kopiyka / 100;
        p.kopiyka %= 100;
    }
}

// Вивід на екран
void printPrice(const Price &p) {
    std::cout << p.hryvnia << " грн " << p.kopiyka << " коп." << std::endl;
}

// Читання чеку з файлу та підрахунок загальної суми
void processReceipt(Price &total) {
    std::ifstream file("receipt.txt");
    
    if (!file.is_open()) {
        std::cerr << "Помилка відкриття файлу receipt.txt" << std::endl;
        return;
    }

    std::string itemName;
    int hrv, kop, qty;
    
    // Захист від помилок
    while (file >> itemName >> hrv >> kop >> qty) {
        if (hrv < 0 || kop < 0 || qty < 0) {
            std::cerr << "Увага: знайдено від'ємні значення у файлі!" << std::endl;
            continue;
        }
        
        Price currentItem = {hrv, kop};
        multiplyPrice(currentItem, qty);
        addPrice(total, total, currentItem);
    }
    
    file.close();
}