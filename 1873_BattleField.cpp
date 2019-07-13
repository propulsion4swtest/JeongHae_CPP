#include<stdio.h>
 
#define RIGHT   0
#define DOWN    1
#define LEFT    2
#define UP      3
 
using namespace std;
 
int H, W;
 
char orgBoard[25][25];
char str[150];
 
int tankX, tankY;
int tankDir;
 
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
 
int cmdLen;
 
void PrintBoard(char board[][25])
{
    for (int row = 0; row < H; row++)
    {
        for (int cul = 0; cul < W; cul++)
        {
            if (row == tankY && cul == tankX)
            {
                switch (tankDir)
                {
                case RIGHT:
                    printf(" >");
                    break;
 
                case DOWN:
                    printf(" v");
                    break;
 
                case LEFT:
                    printf(" <");
                    break;
 
                case UP:
                    printf(" ^");
                    break;
 
                }
 
            }
            else
                printf("%2c", board[row][cul]);
        }
        printf("\n");
    }
    printf("\n\n");
}
 
void PrintAnswer(char board[][25])
{
    for (int row = 0; row < H; row++)
    {
        for (int cul = 0; cul < W; cul++)
        {
            if (row == tankY && cul == tankX)
            {
                switch (tankDir)
                {
                case RIGHT:
                    printf(">");
                    break;
 
                case DOWN:
                    printf("v");
                    break;
 
                case LEFT:
                    printf("<");
                    break;
 
                case UP:
                    printf("^");
                    break;
 
                }
 
            }
            else
                printf("%c", board[row][cul]);
        }
        printf("\n");
    }
}
 
void TankMove(char board[][25], int dir)
{
    int nextX = tankX + moveX[dir];
    int nextY = tankY + moveY[dir];
     
    tankDir = dir;
 
    if (nextX < 0 || nextX >= W || nextY < 0 || nextY >= H)
        return;
 
    if (board[nextY][nextX] == '.')
    {
        tankX = nextX;
        tankY = nextY;
    }
}
 
 
void TankFire(char board[25][25])
{
    int bulletX = tankX;
    int bulletY = tankY;
 
    bool isBlock = false;
 
    while (1)
    {
        bulletX += moveX[tankDir];
        bulletY += moveY[tankDir];
 
        if (bulletX < 0 || bulletX >= W || bulletY < 0 || bulletY >= H)
            return;
 
        switch (board[bulletY][bulletX])
        {
        case '*':
            board[bulletY][bulletX] = '.';
            isBlock = true;
            break;
 
        case '#':
            isBlock = true;
            break;
 
        default:
            isBlock = false;
            break;
        }
 
        if (isBlock == true)
            break;
    }
 
}
 
 
void Input()
{
    scanf("%d %d", &H, &W);
 
    for (int row = 0; row < H; row++)
    {
        scanf("%s", str);
 
        for (int cul = 0; cul < W; cul++)
        {
            if (str[cul] == '<' || str[cul] == '>' || str[cul] == '^' || str[cul] == 'v')
            {
                orgBoard[row][cul] = '.';
                tankX = cul;
                tankY = row;
 
                switch (str[cul])
                {
                case '>':
                    tankDir = RIGHT;
                    break;
 
                case 'v':
                    tankDir = DOWN;
                    break;
 
                case '<':
                    tankDir = LEFT;
                    break;
 
                case '^':
                    tankDir = UP;
                    break;
                }
            }
            else
                orgBoard[row][cul] = str[cul];
        }
    }
 
    scanf("%d", &cmdLen);
    scanf("%s", str);
}
 
 
void Simulation()
{
    for (int i = 0; i < cmdLen; i++)
    {
        switch (str[i])
        {
        case 'U':
            TankMove(orgBoard, UP);
            break;
 
        case 'D':
            TankMove(orgBoard, DOWN);
            break;
 
        case 'L':
            TankMove(orgBoard, LEFT);
            break;
 
        case 'R':
            TankMove(orgBoard, RIGHT);
            break;
 
        case 'S':
            TankFire(orgBoard);
            break;
        }
    }
 
 
}
 
 
int main(void)
{
    int T;
    scanf("%d", &T);
    for (int testCase = 0; testCase < T; testCase++)
    {
 
        Input();
 
        Simulation();
 
         
        printf("#%d ", testCase + 1);
 
        PrintAnswer(orgBoard);
 
        /*
        char key;
        while (1)
        {
            scanf(" %c", &key);
 
            switch (key)
            {
            case 'd':
                TankMove(orgBoard, RIGHT);
                break;
 
            case 's':
                TankMove(orgBoard, DOWN);
                break;
 
            case 'a':
                TankMove(orgBoard, LEFT);
                break;
 
            case 'w':
                TankMove(orgBoard, UP);
                break;
 
            case 'f':
                TankFire(orgBoard);
                break;
 
            }
 
            PrintBoard(orgBoard);
        }
        */
    }
 
 
    return 0;
}
