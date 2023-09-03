#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 定义常量
#define MAX_ROWS 30
#define MAX_COLS 30
#define MAX_MINES 99

// 定义格子的状态
typedef struct
{
    // 是否有雷
    int isMine;
    // 是否已经被打开
    int isOpened;
    // 是否被标记为雷
    int isMarked;
    // 是否被标记为问题
    int isQuestion;
    // 周围雷的个数
    int numMines;
} Cell;

// 定义全局变量

// 棋盘
Cell board[MAX_ROWS][MAX_COLS];
// 行和列
int rows, cols;
// 地雷的总数
int numMines;
// 已打开的格子数量
int numOpenedCells;
// 已标记地雷的格子数量
int numMarkedCells;
// 已进行的操作数量
int numAction;
// 偏移量
int dx[] = {1, -1, 0, 0, -1, 1, -1, 1};
int dy[] = {0, 0, -1, 1, 1, -1, -1, 1};

// 函数声明

void initializeBoard();
void placeMines();
void printBoard();
void openCell(int row, int col, int *loseFlag);
void markCell(int row, int col);
void questionCell(int row, int col);
void unmarkCell(int row, int col);
void checkDoubleClick(int row, int col, int *flag);
int countAdjacentMines(int row, int col);
int isValidCell(int row, int col);
int isGameOver();

int main()
{
    // freopen("input-3.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // 游戏难度
    int level;
    // 行和列
    int row, col;
    // 操作类型
    int action;
    scanf("%d", &level);
    switch (level)
    {
    case 1:
        rows = 9;
        cols = 9;
        numMines = 10;
        break;
    case 2:
        rows = 16;
        cols = 16;
        numMines = 40;
        break;
    case 3:
        rows = 16;
        cols = 30;
        numMines = 99;
        break;
    case 4:
        // 自定义输入行、列、雷数
        scanf("%d%d%d", &rows, &cols, &numMines);
        break;
    default:
        printf("无效的选项。\n");
        return 0;
    }

    initializeBoard();
    placeMines();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j].numMines = countAdjacentMines(i, j);
        }
    }
    // 游戏循环
    while (!isGameOver())
    {
        // 输入操作类型和坐标(x, y):
        scanf("%d%d%d", &action, &row, &col);
        if (!isValidCell(row - 1, col - 1))
        {
            // printf("无效的坐标。\n");
            continue;
        }
        // 操作数加一
        numAction++;
        switch (action)
        {
        case 1:
        {
            int loseFlag = 0;
            // 注意openCell方法传入的参数是不真实的行和列
            openCell(row, col, &loseFlag);
            // 输了，点击了地雷
            if (loseFlag)
            {
                printf("Hit mine, you lose\n");
                // 输出结束状态的棋盘

                printf("%d ", numAction);
                printf("%d\n", numMines - numMarkedCells);
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        if (board[i][j].isMine)
                        {
                            printf("*");
                        }
                        else if (board[i][j].isOpened)
                        {
                            printf("%d", board[i][j].numMines);
                        }
                        else if (board[i][j].isMarked)
                        {
                            printf("!");
                        }
                        else if (board[i][j].isQuestion)
                        {
                            printf("?");
                        }
                        else
                        {
                            printf(".");
                        }
                    }
                    printf("\n");
                }
                // system("pause");
                return 0;
            }

            break;
        }
        case 2:
            markCell(row, col);
            break;
        case 3:
            questionCell(row, col);
            break;
        case 4:
        {
            if (board[row - 1][col - 1].isOpened)
            {
                break;
            }
            if (board[row - 1][col - 1].isMarked)
            {
                numMarkedCells--;
            }
            if (!board[row - 1][col - 1].isMarked && !board[row - 1][col - 1].isQuestion)
            {
                break;
            }
            board[row - 1][col - 1].isMarked = 0;
            board[row - 1][col - 1].isQuestion = 0;
            // unmarkCell(row, col);
            break;
        }
        case 9:
        {
            int flag = 0;
            checkDoubleClick(row, col, &flag);
            if (flag)
            {
                printf("Hit mine, you lose\n");
                // 输出结束状态的棋盘

                printf("%d ", numAction);
                printf("%d\n", numMines - numMarkedCells);
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        if (board[i][j].isMine)
                        {
                            printf("*");
                        }
                        else if (board[i][j].isOpened)
                        {
                            printf("%d", board[i][j].numMines);
                        }
                        else if (board[i][j].isMarked)
                        {
                            printf("!");
                        }
                        else if (board[i][j].isQuestion)
                        {
                            printf("?");
                        }
                        else
                        {
                            printf(".");
                        }
                    }
                    printf("\n");
                }
                // system("pause");
                return 0;
            }
            break;
        }

        default:
            // printf("无效的操作类型。\n");
            break;
        }
        if (!isGameOver())
        {
            printBoard();
        }
    }
    // 输出胜利信息
    printf("Game over, you win\n");
    int i, j;
    // 已进行的操作次数
    printf("%d ", numAction);
    // 总数减去已标记的即为剩余地雷数量
    printf("%d\n", numMines - numMarkedCells);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (board[i][j].isMine)
            {
                printf("*");
            }
            else
            {
                printf("%d", board[i][j].numMines);
            }
        }
        printf("\n");
    }

    // system("pause");
    return 0;
}
// 该函数用于初始化游戏棋盘。它通过遍历整个棋盘，将每个格子的状态重置为初始状态
void initializeBoard()
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            board[i][j].isMine = 0;
            board[i][j].isOpened = 0;
            board[i][j].isMarked = 0;
            board[i][j].isQuestion = 0;
            board[i][j].numMines = 0;
        }
    }

    numOpenedCells = 0;
}
// 该函数用于随机放置地雷。它使用一个循环来生成随机的行和列坐标，
// 直到放置了指定数量的地雷为止。要确保每个地雷的位置不重复，
// 我们需要检查当前位置是否已经有地雷。
// 上面说的都是错误滴
// 你爱咋放咋放，不管你
void placeMines()
{
    // int count = 0;
    // int row, col;

    // while (count < numMines) {
    //     row = rand() % rows;
    //     col = rand() % cols;

    //     if (!board[row][col].isMine) {
    //         board[row][col].isMine = 1;
    //         count++;
    //     }
    // }
    char cellType;
    getchar();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%c", &cellType);
            if (cellType == '*')
            {
                board[i][j].isMine = 1;
            }
        }
        // 吞回车
        getchar();
    }
}
// 该函数用于打印当前的游戏棋盘。它通过遍历棋盘中的每个格子，
// 并根据格子的状态输出相应的字符。已打开的格子会显示雷的个数或空白，
// 未打开的格子则显示标记或问号。
void printBoard()
{
    printf("Game in progress\n");
    int i, j;
    // 已进行的操作次数
    printf("%d ", numAction);
    // 总数减去已标记的即为剩余地雷数量
    printf("%d\n", numMines - numMarkedCells);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (board[i][j].isOpened)
            {
                printf("%d", board[i][j].numMines);
            }
            else if (board[i][j].isMarked)
            {
                printf("!");
            }
            else if (board[i][j].isQuestion)
            {
                printf("?");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
}
// 该函数用于打开一个格子。如果该格子已经被打开，函数会给出相应的提示。
// 如果该格子是地雷，游戏结束。否则，该格子将被标记为已打开，
// 如果周围没有地雷，则递归地打开周围的空白格子。
void openCell(int row, int col, int *loseFlag)
{
    if (board[row - 1][col - 1].isOpened || board[row - 1][col - 1].isMarked)
        return;
    // 判断第一次点击的是否为雷
    if (board[row - 1][col - 1].isMine)
    {
        *loseFlag = 1;
        return;
    }
    // 标记为翻开
    board[row - 1][col - 1].isOpened = 1;
    numOpenedCells++;
    // 如果周围有地雷的话
    if (board[row - 1][col - 1].numMines)
    {
        return;
    }

    // 对周围的方格进行查看
    for (int i = 0; i < 8; i++)
    {
        int next_x = row - 1 + dx[i];
        int next_y = col - 1 + dy[i];
        // 如果坐标不合法
        if (!isValidCell(next_x, next_y))
        {
            continue;
        }
        // 如果是一个地雷
        if (board[next_x][next_y].isMine)
        {
            continue;
        }
        // 如果格子已经打开过了
        if (board[next_x][next_y].isOpened)
        {
            continue;
        }
        if (board[next_x][next_y].isMarked)
        {
            continue;
        }
        // 如果格子周围有地雷，标记为打开，但不进入递归
        if (board[next_x][next_y].numMines != 0)
        {
            board[next_x][next_y].isOpened = 1;
            numOpenedCells++;
        }
        else
        {
            // 如果是空白格子，则进入递归
            int uselessFlag = 0; // 没用的东西，单纯占个位置
            openCell(next_x + 1, next_y + 1, &uselessFlag);
        }
    }
}
// 该函数用于将格子标记为雷。如果该格子已经被打开
// 函数会给出相应的提示。否则，该格子将被标记为雷。
void markCell(int row, int col)
{
    if (board[row - 1][col - 1].isOpened || board[row - 1][col - 1].isMarked == 1)
    {
        // printf("该格子已经被打开。\n");
        return;
    }
    if (board[row - 1][col - 1].isQuestion)
    {
        board[row - 1][col - 1].isQuestion = 0;
    }

    board[row - 1][col - 1].isMarked = 1;
    numMarkedCells++;
}
// 该函数用于将格子标记为问题。如果该格子已经被打开，
// 函数会给出相应的提示。否则，该格子将被标记为问题。
void questionCell(int row, int col)
{
    if (board[row - 1][col - 1].isOpened)
    {
        return;
    }

    // if (board[row - 1][col - 1].isMarked || board[row - 1][col - 1].isQuestion) {
    //     printf("该格子已经被标记。\n");
    //     return;
    // }
    if (board[row - 1][col - 1].isMarked)
    {
        board[row - 1][col - 1].isMarked = 0;
        numMarkedCells--;
    }

    board[row - 1][col - 1].isQuestion = 1;
}
// 该函数用于取消标记一个格子。如果该格子已经被打开或未被标记为雷或问题标记，
// 函数会给出相应的提示。否则，该格子的标记将被取消。
void unmarkCell(int row, int col)
{
    if (board[row - 1][col - 1].isOpened)
    {
        return;
    }
    if (board[row - 1][col - 1].isMarked)
    {
        numMarkedCells--;
    }
    if (!board[row - 1][col - 1].isMarked && !board[row - 1][col - 1].isQuestion)
    {
        return;
    }
    board[row - 1][col - 1].isMarked = 0;
    board[row - 1][col - 1].isQuestion = 0;
}
// 该函数用于执行双击操作。当双击位置周围已标记雷数等于该位置数字时，
// 操作有效。函数首先检查该格子是否已经被打开，然后计算周围已标记的雷数。
// 如果已标记雷数与数字相等，将打开周围未被标记为地雷且未打开的格子。
void checkDoubleClick(int row, int col, int *flag)
{
    if (!board[row - 1][col - 1].isOpened || board[row - 1][col - 1].numMines == 0)
    {
        // printf("该格子未被打开。\n");
        return;
    }
    // 周围有的地雷数
    // int adjacentMines = countAdjacentMines(row - 1, col - 1);
    int adjacentMines = board[row - 1][col - 1].numMines;
    // 周围被标记的地雷数
    int markedMines = 0;
    int i, j;

    for (i = row - 2; i <= row; i++)
    {
        for (j = col - 2; j <= col; j++)
        {
            if (isValidCell(i, j) && !board[i][j].isOpened && board[i][j].isMarked)
            {
                markedMines++;
            }
        }
    }
    // 如果两者相等的话，要打开周围未被标记为地雷且未打开的格子，调用递归打开方法
    if (markedMines == adjacentMines)
    {
        // 得先看周围一圈有没有雷
        // 如果有雷的话，需要输出当前棋盘未操作的状态
        for (i = row - 2; i <= row; i++)
        {
            for (j = col - 2; j <= col; j++)
            {
                // 如果是未被标记为地雷且未打开的格子
                if (isValidCell(i, j) && !board[i][j].isOpened && !board[i][j].isMarked)
                {
                    // 如果是地雷的话
                    if (board[i][j].isMine)
                    {
                        *flag = 1;
                        return;
                    }
                }
            }
        }
        // 如果没有雷的话，则调用递归方法打开格子
        for (i = row - 2; i <= row; i++)
        {
            for (j = col - 2; j <= col; j++)
            {
                if (isValidCell(i, j) && !board[i][j].isOpened && !board[i][j].isMarked)
                {
                    // 加一是因为openCell方法对应的行列是假的行列
                    int uselessFlag = 0;
                    openCell(i + 1, j + 1, &uselessFlag);
                }
            }
        }
    }
}
// 该函数用于计算给定位置周围的地雷数量。它通过遍历给定位置周围的格子，并计算地雷的个数。
int countAdjacentMines(int row, int col)
{
    int count = 0;
    int i, j;

    for (i = row - 1; i <= row + 1; i++)
    {
        for (j = col - 1; j <= col + 1; j++)
        {
            if (isValidCell(i, j) && board[i][j].isMine)
            {
                count++;
            }
        }
    }

    return count;
}
// 该函数用于检查给定的行和列坐标是否在有效的范围内，防止越界访问棋盘。
int isValidCell(int row, int col)
{
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
// 该函数用于检查游戏是否结束。如果已经打开的格子数等于除地雷外的格子总数，则游戏结束。
int isGameOver()
{
    return numOpenedCells == rows * cols - numMines;
}