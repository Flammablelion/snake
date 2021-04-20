#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "Random.h"
#include <Windows.h>

using namespace sf;
using namespace std;




const int M = 500;
const int N = 350;

float w = Random(M), h = Random(N);
float x = Random(M), y = Random(N);

bool Up = false, Left = true, Right = false, Down = false;

RectangleShape* test = new RectangleShape[(M * N) / 16];
int* G_x = new int[(M * N) / 16];
int* G_y = new int[(M * N) / 16];
int ob = 0;
int testtt = M * N / 16;
bool End = false;
int FinalEnd = 1;

RectangleShape snake(Vector2f(8.f, 8.f));
RectangleShape food(Vector2f(8.f, 8.f));
RenderWindow windowtest(VideoMode(M, N), "zmeyka ebat moy huy");

void boom(int x, int y, int kol, RenderWindow win) {

    

}

bool SnakeIntersects(RectangleShape head, RectangleShape* body, int kol) {
    for (int i = 0; i < kol; i++)
    {
        if (head.getGlobalBounds().intersects(body[i].getGlobalBounds()))
        {
            return true;
        }
    }
    return false;

}
int main()
{
    srand(time(0));
    RectangleShape boom[4];
    for (int i = 0; i < 4; i++)
    {
        boom[i].setSize(Vector2f(8.f, 8.f));
        boom[i].setFillColor(Color::Yellow);
    }


    for (int i = 0; i < (M * N) / 16; i++)
    {
        test[i].setSize(Vector2f(8.f, 8.f));
        test[i].setFillColor(Color::White);
    }
    int KolSnake = 0;



    while (windowtest.isOpen())
    {
        windowtest.clear(Color::Black);
        if (End == false)
        {
            //srand(time(0));

            Event event;


            food.setFillColor(Color::Red);
            food.setPosition(x, y);
            windowtest.draw(food);



            snake.setFillColor(Color::White);


            while (windowtest.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    windowtest.close();
                }

                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Up && Down != true)
                    {
                        Up = true;
                        Left = false;
                        Right = false;
                        Down = false;
                    }
                    else if (event.key.code == Keyboard::Down && Up != true) {
                        Up = false;
                        Left = false;
                        Right = false;
                        Down = true;
                    }
                    else if (event.key.code == Keyboard::Left && Right != true) {
                        Up = false;
                        Left = true;
                        Right = false;
                        Down = false;
                    }
                    else if (event.key.code == Keyboard::Right && Left != true) {
                        Up = false;
                        Left = false;
                        Right = true;
                        Down = false;
                    }


                }
            }


            if (Up == true && Left == false && Right == false && Down == false) h -= 8;
            else if (Up == false && Left == false && Right == false && Down == true) h += 8;
            else if (Up == false && Left == true && Right == false && Down == false) w -= 8;
            else if (Up == false && Left == false && Right == true && Down == false) w += 8;

            Sleep(40);

            snake.setPosition(w, h);
            windowtest.draw(snake);

            if (snake.getGlobalBounds().intersects(food.getGlobalBounds()))
            {
                x = Random(M);
                y = Random(N);

                if (KolSnake > 10) KolSnake += 2;
                else KolSnake++;
            }
            G_x[ob] = w;
            G_y[ob] = h;

            for (int i = 0; i < KolSnake; i++)
            {
                if (ob != 0) test[i].setPosition(G_x[ob - (i + 1)], G_y[ob - (i + 1)]);
                else test[i].setPosition(G_x[M * N / 16 - (1 + i)], G_y[M * N / 16 - (1 + i)]);

                windowtest.draw(test[i]);
            }

            if (snake.getGlobalBounds().intersects(test->getGlobalBounds()))
            {
                Up = false;
                Left = false;
                Right = false;
                Down = false;
            }

            if (SnakeIntersects(snake, test, KolSnake)) End = true;

            if (h >= N) h = 0;
            else if (h <= 0) h = N;
            else if (w >= M) w = 0;
            else if (w <= 0)  w = M;

            ob++;
            if (ob >= (((M * N) / 16) - 1)) ob = 0;
        }
        else
        {
        snake.setFillColor(Color::White);
        for (int i = 0; i < KolSnake; i++)
        {
            if (ob != 0) test[i].setPosition(G_x[ob - (i + 1)], G_y[ob - (i + 1)]);
            else test[i].setPosition(G_x[M * N / 16 - (1 + i)], G_y[M * N / 16 - (1 + i)]);


            windowtest.draw(test[i]);

        }
        if(KolSnake > 0) KolSnake--;
        if (KolSnake == 0)
        {
            boom[0].setPosition(w + FinalEnd*8, h + FinalEnd*8);
            boom[1].setPosition(w + FinalEnd*8, h - FinalEnd*8);
            boom[2].setPosition(w - FinalEnd*8, h + FinalEnd*8);
            boom[3].setPosition(w - FinalEnd*8, h - FinalEnd*8);
            windowtest.draw(boom[0]);
            windowtest.draw(boom[1]);
            windowtest.draw(boom[2]);
            windowtest.draw(boom[3]);
            FinalEnd++;
            if (FinalEnd == 7) windowtest.close();
        }
        Sleep(500);

        }


        windowtest.display();
    }


    setlocale(LC_ALL, "RUS");
    return 0;
}
