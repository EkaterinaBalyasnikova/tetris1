

#ifndef TETRIS1_MAIN_H
#define TETRIS1_MAIN_H

const int wide = 18; //ширина
const int length = 18; //длина
const int size = 18; //размер плиток

int field[wide][length] = {0}; //массив поля

struct Point { //структура
    int x, y;
} a[4], b[4];

int figures[7][4] = { //массив с координатами закрашиваемых квадратов в фигуре(7 строк, 4 столбца)
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5,
};

extern auto check() -> bool;



#endif //TETRIS1_MAIN_H
