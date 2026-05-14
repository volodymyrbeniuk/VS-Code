#include "rounding.h"
#include <iostream>

using namespace std;

// Округлюємо СУМУ
void round(cina &amount) {
    if (amount.cop % 10 <= 4) { 
        amount.cop = amount.cop - (amount.cop % 10);
    }
    else {
        amount.cop = amount.cop - amount.cop % 10 + 10 ;
    }

    if (amount.cop >= 100) {
        amount.grn = amount.grn + (amount.cop / 100);
        amount.cop = amount.cop % 100;
    }
}

// Додаємо ДВІ ЦІНИ
void add(cina &price1, cina &price2, cina &result) {
    result.grn = price1.grn + price2.grn;
    result.cop = price1.cop + price2.cop;

    if (result.cop >= 100) {
        result.grn = result.grn + (result.cop / 100);
        result.cop = result.cop % 100;
    }
}

// Множимо ЦІНУ на кількість
void multiply(cina &price, int n) {
    price.grn = price.grn * n;
    price.cop = price.cop * n;

    if (price.cop >= 100) {
        price.grn = price.grn + price.cop / 100;
        price.cop = price.cop % 100;
    }
}

void read(cina &sum_c) {
    FILE *file;
    file = fopen("./price.txt", "r");

    if (file == nullptr) {
        cout << "Failed to open file" << endl;
        return;
    }

    int temp_grn, temp_cop, temp_n;
    
    while (fscanf(file, "%*s %d %d %d", &temp_grn, &temp_cop, &temp_n) == 3) {
        
        if (temp_grn < 0 || temp_cop < 0 || temp_n < 0) {
            cout << "The numbers can't be negative" << endl;
            continue; 
        }

        cina c = {0, 0};
        c.grn = temp_grn;
        c.cop = temp_cop;

        multiply(c, temp_n);
        add(c, sum_c, sum_c);
    }
    fclose(file); 
}

void show(cina c) {
    cout << c.grn << " Hrn " << c.cop << " Kop." << endl;
}

void results() {
    cina sum_c = {0, 0}; 
    
    read(sum_c);
    
    cout << "Total amount: ";
    show(sum_c);         
    cout << endl;

    cina r_sum = sum_c;  
    round(r_sum);        
    
    cout << "Amount to pay: ";
    show(r_sum);         
    cout << endl;
}