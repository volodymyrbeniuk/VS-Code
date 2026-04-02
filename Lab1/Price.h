#ifndef PRICE_H
#define PRICE_H

struct Price {
    int hryvnia;
    int kopiyka;
};

void roundPrice(Price &p);
void addPrice(Price &result, const Price &p1, const Price &p2);
void multiplyPrice(Price &p, int amount);
void printPrice(const Price &p);
void processReceipt(Price &total);

#endif