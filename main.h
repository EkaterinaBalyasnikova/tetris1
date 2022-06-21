//
// Created by novik on 21.06.2022.
//
struct Point { //структура
    int x, y;
} a[4], b[4];
const int wide = 18; //ширина
const int length = 18; //длина
const int size = 18; //размер плиток

int field[wide][length] = {0};
#ifndef TETRIS1_MAIN_H
#define TETRIS1_MAIN_H
extern auto check(Point (&a)[4], int (&field)[wide][length]) -> bool;
#endif //TETRIS1_MAIN_H
