#include <stdio.h>
#define MAX_ROW 13
#define MAX_COL 17

typedef struct {
    int row;
    int col;
} Position;

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

void find_path(int maze[MAX_ROW][MAX_COL], Position* START_POINT, Position* END_POINT);
Position* starting_point(Position* starting, int dir);
void DFS(int maze[MAX_ROW][MAX_COL], Position* starting, Position* ending);
int promising(int maze[MAX_ROW][MAX_COL], Position* starting, int dir);

// Position START_POINT = { 1, 1 };
// Position END_POINT = { 11, 15 };
void main() {
    Position* START_POINT;
    START_POINT->row = 1;
    START_POINT->col = 1;

    Position* END_POINT;
    END_POINT->row = 11;
    END_POINT->col = 15;

    void find_path(short_maze, START_POINT, END_POINT);
}

enum move{up, down, left, right};
void find_path(int maze[MAX_ROW][MAX_COL], Position* START_POINT, Position* END_POINT) {
    Position* starting = START_POINT;
    for (int dir = up; dir <= right; dir++) {
        if (promising(maze, starting, dir)) {
            maze_path[starting->row][starting->col] = dir;
            Position* starting = starting_point(starting, dir);
            DFS(maze, starting, END_POINT);
        }
    }
}

Position* starting_point(Position* starting, int dir) {
    switch (dir)
    {
    case up:
        starting->row -= 1;
        break;
    case down:
        starting->row += 1;
        break;
    case left:
        starting->col -= 1;
        break;
    default:
        starting->col += 1;
        break;
    }
    return starting;
}

void DFS(int maze[MAX_ROW][MAX_COL], Position* starting, Position* ending) {
    if (starting->row == ending->row && starting->col == ending->col) {
        print_path(maze_path);
    }
    for (int dir = up; dir <= right; dir++) {
        if (promising(maze, starting, dir)) {
            Position* starting = starting_point(starting, dir);
            DFS(maze, starting, ending);
        }
    }
}

int promising(int maze[MAX_ROW][MAX_COL], Position* starting, int dir) {
    switch (dir)
    {
    case up:
        if (starting->row - 1 < 0) {
            return 0;
        }
        else {
            int upside = starting->row - 1;
            int curCol = starting->col;
            if (maze[upside][curCol] == 1) {
                return 0;
            }
        }
        break;
    case down:
        if (starting->row - 1 >= MAX_ROW) {
            return 0;
        }
        else {
            int downside = starting->row + 1;
            int curCol = starting->col;
            if (maze[downside][curCol] == 1) {
                return 0;
            }
        }
        break;
    case left:
        if (starting->col - 1 < 0) {
            return 0;
        }
        else {
            int curRow = starting->row ;
            int leftside = starting->col - 1;
            if (maze[curRow][leftside] == 1) {
                return 0;
            }
        }
        break;
    default:
        if (starting->col - 1 < 0) {
            return 0;
        }
        else {
            int curRow = starting->row ;
            int rightside = starting->col + 1;
            if (maze[curRow][rightside] == 1) {
                return 0;
            }
        }
        break;
    }
    return 1;
}