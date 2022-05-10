#include <stdio.h>
#define MAX_ROW 13
#define MAX_COL 17
#define TRUE 1
#define FALSE 0
#define STAY_INDEX 30
#define VISITED 60
#define NOTVISITED 61

typedef struct {
    int x;
    int y;
} Position;

enum Directions { stay = STAY_INDEX, up, rightUp, right, rightDown, down, leftDown, left, leftUp };

const Position START_POINT = { 1, 1 };
const Position END_POINT = { 15, 11 };

const char* moveStay = "stay";
const char* moveUp = "up";
const char* moveRightUp = "rightUp";
const char* moveRight = "right";
const char* moveRightDown = "rightDown";
const char* moveDown = "down";
const char* moveLeftDown = "leftDown";
const char* moveLeft = "left";
const char* moveLeftUp = "leftUp";

int short_maze[MAX_ROW][MAX_COL] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1},
  {1,1,0,0,0,1,1,0,1,1,1,0,0,1,1,1,1},
  {1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1},
  {1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,0,1},
  {1,1,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1},
  {1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,1,1},
  {1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
  {1,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1},
  {1,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,1},
  {1,0,1,0,0,1,1,1,1,1,0,1,1,1,1,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int maze_path[MAX_ROW][MAX_COL];

void InitializeMazePath();
void FindPath();
void DFS(Position position);
void PrintPath();
void PrintMove(int direction);
const char* GetDirectionString(int direction);
int IsPromisingPosition(Position position);
int IsOutBound(Position position);
int IsBlockedPath(Position postion);
int IsNotVisited(Position position);
Position GetMovedPosition(Position position, int direction);

int main() {
    InitializeMazePath();
    FindPath();
    return 0;
}

void InitializeMazePath() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            maze_path[i][j] = NOTVISITED;
        }
    }
}

void FindPath() {
    DFS(START_POINT);
}

void DFS(Position position) {
    maze_path[position.y][position.x] = VISITED;
    if (position.y == END_POINT.y && position.x == END_POINT.x) {
        PrintPath();
    }
    for (int direction = up; direction <= leftUp; direction++) {
        Position newPosition = GetMovedPosition(position, direction);
        if (IsPromisingPosition(newPosition) && IsNotVisited(newPosition)) {
            maze_path[position.y][position.x] = direction;
            DFS(newPosition);
        }
    }
}

void PrintPath() {
    Position temp = { 0, 0 };
    temp.x = START_POINT.x;
    temp.y = START_POINT.y;

    while (!(temp.x == END_POINT.x && temp.y == END_POINT.y))
    {   
        int direction = maze_path[temp.y][temp.x];
        PrintMove(direction);
        temp = GetMovedPosition(temp, direction);
    }
}

void PrintMove(int direction) {
    printf("%s ", GetDirectionString(direction));
}

const char* GetDirectionString(int direction) {
    switch (direction)
    {
    case up:
        return moveUp;
    case rightUp:
        return moveRightUp;
    case right:
        return moveRight;
    case rightDown:
        return moveRightDown;
    case down:
        return moveDown;
    case leftDown:
        return moveLeftDown;
    case left:
        return moveLeft;
    case leftUp:
        return moveLeftUp;
    default:
        break;
    }
    return moveStay;
}

Position GetMovedPosition(Position position, int direction) {
    Position newPosition = { 0, 0 };
    newPosition.x = position.x;
    newPosition.y = position.y;

    switch (direction)
    {
    case up:
        newPosition.y -= 1;
        break;
    case rightUp:
        newPosition.y -= 1;
        newPosition.x += 1;
        break;
    case right:
        newPosition.x += 1;
        break;
    case rightDown:
        newPosition.x += 1;
        newPosition.y += 1;
        break;
    case down:
        newPosition.y += 1;
        break;
    case leftDown:
        newPosition.x -= 1;
        newPosition.y += 1;
        break;
    case left:
        newPosition.x -= 1;
        break;
    case leftUp:
        newPosition.x -= 1;
        newPosition.y -= 1;
        break;
    default:
        break;
    }
    return newPosition;
}

int IsPromisingPosition(Position position) {
    if (IsOutBound(position) || IsBlockedPath(position)){
        return FALSE;
    }
    else {
        return TRUE;
    }
}

int IsOutBound(Position position) {
    int x = position.x;
    int y = position.y;
    if (x < 0 || x >= MAX_COL || y < 0 || y >= MAX_ROW) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int IsBlockedPath(Position position) {
    int x = position.x;
    int y = position.y;
    if (short_maze[y][x] == 1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

int IsNotVisited(Position position) {
    if (maze_path[position.y][position.x] == NOTVISITED) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}