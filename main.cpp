#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace sf;

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

RenderWindow window(VideoMode(wide * size, length * size), "Tetris!");



bool check() {
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

//генерирование фигуры
std::void_t<> genrandom() {
    int colorNum = 1 + rand() % 7;
    for (auto &i: b)
        field[i.y][i.x] = colorNum;
    int n = rand() % 7;
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[n][i] % 2;
        a[i].y = figures[n][i] / 2;
    }
}

auto turn(){
    Point rotation_center = a[1]; //Задаем центр вращения
    for (int i = 0; i < 4; i++) {
        int x = a[i].y - rotation_center.y;
        int y = a[i].x - rotation_center.x;

        a[i].x = rotation_center.x - x;
        a[i].y = rotation_center.y + y;
    }
}
auto fall(){
    for (int i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].y += 1;
    }
}
int ga = 0;
auto gameclose(){
    for (int i = 0; i < 4; i++) {
        if (a[i].y > 0 && a[i].y < 4) //Если фигура находиться наверху, то прибaвляем на 1
            ga++;
        else if (a[i].y >= 4) //Иначе 0
            ga = 0;
    }
}

int main() {
    srand(time(nullptr));

    Texture t;
    t.loadFromFile("images/tiles.png");

    Sprite tiles(t);
    tiles.setTextureRect(IntRect(0, 0, size, size));
    int dx = 0, colorNum = 1; //управление
    bool rotate = false; //поворот
    float timer = 0, delay = 0.3; //движение
    Clock period;
    bool position = true;

 //коэффициент для конца игры

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

//// Горизонтальное перемещение ////
        for (int i = 0; i < 4; i++) { //движение фигуры
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check()) {
            for (int i = 0; i < 4; i++)
                a[i] = b[i];
        }

        if (rotate) {  //поворот фигуры
            turn();

            if (!check()) {
                for (int i = 0; i < 4; i++)
                    a[i] = b[i];
            }
        }

        if (timer > delay) { //падение
            fall();

            if (!check()) { //генерирование рандомной фигуры(отрисовка её)
                genrandom();
            }

            timer = 0;
        }

        //Пишем новый цикл для этого коэффициента



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

        for (int i = 0; i < wide; i++)  //визуализация вставания фигур(без неё опускается и не видно)
            for (int j = 0; j < length; j++) {
                if (field[i][j] == 0)
                    continue;
                tiles.setTextureRect(IntRect(field[i][j] * size, 0, size, size));
                tiles.setPosition(j * size, i * size);
                window.draw(tiles);
            }

        for (int i = 0; i < 4; i++) {//без неё вообще ничего не видно)
            tiles.setTextureRect(IntRect(colorNum * size, 0, size, size));
            tiles.setPosition(a[i].x * size, a[i].y * size);
            window.draw(tiles);
        }

        gameclose();
        if (ga > 10000)
            window.draw(gameover);

        window.display();
    }

    return 0;
}
