#ifndef ROUNDING
#define ROUNDING

struct cina {
    int grn;
    short int cop;
};

void round(cina &amount);                               
void add(cina &price1, cina &price2, cina &result);      
void multiply(cina &price, int n);                       
void read(cina &sum_c);
void show(cina c);
void results();
void showResults();

#endif