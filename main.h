#ifndef TETRIS1_LIB_H
#define TETRIS1_LIB_H
const int wide = 18; //ширина
const int length = 18; //длина
const int size = 18; //размер плиток

 //массив поля

struct Point { //структура
    int x, y;
};

extern bool check(Point (&a)[4], int (&field)[wide][length]);

#endif //TETRIS1_LIB_H
