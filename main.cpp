#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include "main.h"

using namespace sf;

Point a[4], b[4];//структура

int field[wide][length] = {0};

int figures[7][4] = { //массив с координатами закрашиваемых квадратов в фигуре(7 строк, 4 столбца)
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5,
};

RenderWindow window(VideoMode(wide * size, length * size), "Tetris!");


/*!
 * функция, проверяющая, приземлилась ли фигура
 */

/*! генерирование фигуры
 * @param colorNum - цвет фигуры
 * @param fig - тип фигуры
 */

auto genrandom() {
    int colorNum = 1 + rand() % 7;
    for (auto &i: b)
        field[i.y][i.x] = colorNum;
    int fig = rand() % 7;
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[fig][i] % 2;
        a[i].y = figures[fig][i] / 2;
    }
}
/*!вращение фигуры
 */
auto turn(){
    Point rotation_center = a[1]; //Задаем центр вращения
    for (int i = 0; i < 4; i++) {
        int x = a[i].y - rotation_center.y;
        int y = a[i].x - rotation_center.x;

        a[i].x = rotation_center.x - x;
        a[i].y = rotation_center.y + y;
    }
}
/*! падение фигуры
 */
auto fall(){
    for (int i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].y += 1;
    }
}


/*! обнаружение конца игры
 * @param ga - коэффициент для конца игры
 */
int ga = 0;
auto gameclose(){
    for (int i = 0; i < 4; i++) {
        if (a[i].y > 0 && a[i].y < 4) //Если фигура находиться наверху, то увеличиваем
            ga++;
        else if (a[i].y >= 4) //Иначе 0
            ga = 0;
    }
}
/*!
 * основная функция, выполняющая действия в игре
 * @param dx - начальное положение по иксу
 * @param colorNum - номер цвета фигуры
 * @param rotate - поворот
 * @param timer - таймер игры
 * @param delay - задержка
 */
int main() {
    srand(time(nullptr));

    Texture t;
    t.loadFromFile("images/tiles.png");

    Sprite tiles(t);
    tiles.setTextureRect(IntRect(0, 0, size, size));
    int dx = 0, colorNum = 1;
    bool rotate = false;
    float timer = 0, delay = 0.3;
    Clock period;
    bool position = true;

    Texture go;
    go.loadFromFile("images/gameover.png");
    Sprite gameover(go);
    gameover.setPosition(15, 30);
    gameover.setScale(1, 1);


/* Главный цикл приложения. Выполняется, пока открыто окно */

    while (window.isOpen()) {
        float time = period.getElapsedTime().asSeconds();
        period.restart();
        timer += time;
        window.display();
        Event action{};
        bool downpress = false;
        while (window.pollEvent(action)) {
            if (action.type == Event::Closed)
                window.close();

            if (action.type == Event::KeyPressed) //управление клавиатурой
                if (action.key.code == Keyboard::Up)
                    rotate = true;
                else if (action.key.code == Keyboard::Right)
                    dx = 1;
                else if (action.key.code == Keyboard::Left)
                    dx = -1;
                else if (action.key.code == Keyboard::Down)
                    downpress = true;
        }


        if (downpress)
            delay = 0.05;

//Горизонтальное перемещение
        for (int i = 0; i < 4; i++) { //движение фигуры
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check(a, field)) {
            for (int i = 0; i < 4; i++)
                a[i] = b[i];
        }

        if (rotate) {  //поворот фигуры
            turn();

            if (!check(a, field)) {
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
            }
        }

        if (timer > delay) { //падение
            fall();

            if (!check(a, field)) { //генерирование рандомной фигуры(отрисовка её)
                genrandom();
            }

            timer = 0;
        }

        if (position) {
            int n = rand() % 7;
            if (a[0].x == 0)
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            position = false;
        }

        int k = wide - 1;    //отвечает за удаление готовой строки
        for (int i = wide - 1; i > 0; i--) {
            int count = 0;
            for (int j = 0; j < length; j++) {
                if (field[i][j])
                    count++;
                field[k][j] = field[i][j];
            }
            if (count < length)
                k--;
        }

        dx = 0 ;
        rotate = false;
        delay = 0.5; //задержка движения

        window.clear(Color::White);
//отрисовка конечного положения фигуры
        for (int i = 0; i < wide; i++)
            for (int j = 0; j < length; j++) {
                if (field[i][j] == 0)
                    continue;
                tiles.setTextureRect(IntRect(field[i][j] * size, 0, size, size));
                tiles.setPosition(j * size, i * size);
                window.draw(tiles);
            }
//отрисовка следующей фигуры
        for (int i = 0; i < 4; i++) {
            tiles.setTextureRect(IntRect(colorNum * size, 0, size, size));
            tiles.setPosition(a[i].x * size, a[i].y * size);
            window.draw(tiles);
        }
//завершение игры, вывод картинки об окончании
        gameclose();
        if (ga > 10000)
            window.draw(gameover);

    }
    return 0;
}
