#include <iostream>
#include <conio.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define MAXSNAKESIZE 100

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

class Point
{

private:
    int x;
    int y;

public:
    Point()
    {
        x = y = 10;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    void SetPoint(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int GetX()
    {
        return x;
    }
    int GetY()
    {
        return y;
    }
    void MoveUp()
    {
        y--;
    }
    void MoveDown()
    {
        y++;
    }
    void MoveLeft()
    {
        x--;
    }
    void MoveRight()
    {
        x++;
    }
    void Draw()
    {
        gotoxy(x, y);
        cout << "*";
    }
    void Erase()
    {
        gotoxy(x, y);
        cout << " ";
    }
    void CopyPosition(Point *p)
    {
        p->x = x;
        p->y = y;
    }
    void Debug()
    {
        cout << "(" << x << "," << y << ") ";
    }
};

class Snake
{

private:
    Point *cell[MAXSNAKESIZE]; // array of points representing snake
    int size;                  // current snake size
    char dir;                  // current snake direction
    Point fruit;

public:
    Snake()
    {
        size = 1;                    // default size
        cell[0] = new Point(20, 20); // default position
        for (int i = 1; i < MAXSNAKESIZE; i++)
        {
            cell[i] = NULL;
        }
        fruit.SetPoint(rand() % 50, rand() % 25);
    }
    void AddCell(int x, int y)
    {
        cell[size++] = new Point(x, y);
    }
    void TurnUp()
    {
        dir = 'w'; // w key to turn upwards
    }
    void TurnLeft()
    {
        dir = 'a'; // a key to turn left
    }
    void TurnDown()
    {
        dir = 's'; // s key to turn downwards
    }
    void TurnRight()
    {
        dir = 'd'; // d key to turn right
    }
    void Move()
    {
        // clear screen
        system("cls");

        // for snake body to follow head
        for (int i = size - 1; i > 0; i--)
        {
            cell[i - 1]->CopyPosition(cell[i]);
        }

        // for turning snake head
        switch (dir)
        {
        case 'w':
            cell[0]->MoveUp();
            break;
        case 'a':
            cell[0]->MoveLeft();
            break;
        case 's':
            cell[0]->MoveDown();
            break;
        case 'd':
            cell[0]->MoveRight();
            break;
        }

        // eating fruits
        if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY())
        {
            AddCell(0, 0);
            fruit.SetPoint(rand() % 50, rand() % 25);
        }

        // drawing snake
        for (int i = 0; i < size; i++)

            cell[i]->Draw();
        fruit.Draw();

        Sleep(100);
    }
    void Debug()
    {
        for (int i = 0; i < size; i++)
        {
            cell[i]->Debug();
        }
    }
};

int main()
{
    // random number generator
    srand((unsigned)time(NULL));

    // testing snake
    Snake snake;
    char op = '1';
    do
    {
        if (kbhit())
        {
            op = getch();
        }
        switch (op)
        {
        case 'w':
        case 'W':
            snake.TurnUp();
            break;
        case 'a':
        case 'A':
            snake.TurnLeft();
            break;
        case 's':
        case 'S':
            snake.TurnDown();
            break;
        case 'd':
        case 'D':
            snake.TurnRight();
            break;
        }
        snake.Move();

    } while (op != 'q');

    return 0;
}