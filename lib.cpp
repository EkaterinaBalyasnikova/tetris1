#include "main.h"

/*!
 * функция, проверяющая, приземлилась ли фигура
 */
bool check(Point (&a)[4], int (&field)[wide][length]) {
    for (auto &i: a) {
        if (i.x < 0) {
            return false;
        } else {
            if (i.x >= length) {
                return false;
            } else {
                if (i.y < length) {
                    if (field[i.y][i.x] == false)
                        continue;
                    return false;
                } else
                    return false;
            }
        }
    }
    return true;
}