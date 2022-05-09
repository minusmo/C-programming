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

int maze_path[MAX_ROW][MAX_COL] = {0};

void finding_path(int maze[MAX_ROW][MAX_COL], Position* START_POINT, Position* END_POINT);
void updating_starting_point(Position* starting, int direction);
void DFS(int maze[MAX_ROW][MAX_COL], Position* starting, Position* ending);
int direction_is_promising(int maze[MAX_ROW][MAX_COL], Position starting, int direction);
void printing_path(int maze_path[MAX_ROW][MAX_COL], Position* starting, Position* ending);
const char* move(int direction);

int main() {
    Position START_POINT;
    START_POINT.row = 1;
    START_POINT.col = 1;

    Position END_POINT;
    END_POINT.row = 11;
    END_POINT.col = 15;

    finding_path(short_maze, &START_POINT, &END_POINT);
    return 0;
}

enum direction{ up, right_up, right, right_down, down, left_down, left, left_up };

void finding_path(int maze[MAX_ROW][MAX_COL], Position* START_POINT, Position* END_POINT) {
    Position* starting = START_POINT;
    for (int direction = up; direction <= left_up; direction++) {
        if (direction_is_promising(maze, *starting, direction)) {
            maze_path[starting->row][starting->col] = direction;
            updating_starting_point(starting, direction);
            DFS(maze, starting, END_POINT);
        }
    }
}

void updating_starting_point(Position* starting, int direction) {
    switch (direction)
    {
    case up:
        starting->row -= 1;
        break;
    case right_up:
        starting->row -= 1;
        starting->col += 1;
        break;
    case right:
        starting->col += 1;
        break;
    case right_down:
        starting->col += 1;
        starting->row += 1;
        break;
    case down:
        starting->row += 1;
        break;
    case left_down:
        starting->col -= 1;
        starting->row += 1;
        break;
    case left:
        starting->col -= 1;
        break;
    case left_up:
        starting->col -= 1;
        starting->row -= 1;
        break;
    default:
        break;
    }
}

void DFS(int maze[MAX_ROW][MAX_COL], Position* starting, Position* ending) {
    if (starting->row == ending->row && starting->col == ending->col) {
        printing_path(maze_path, starting, ending);
    }
    for (int direction = up; direction <= left_up; direction++) {
        if (direction_is_promising(maze, *starting, direction)) {
            updating_starting_point(starting, direction);
            DFS(maze, starting, ending);
        }
    }
}

int direction_is_promising(int maze[MAX_ROW][MAX_COL], Position starting, int direction) {
    switch (direction)
    {
    case up:
        if (starting.row - 1 < 0) {
            return 0;
        }
        else {
            int up_row = starting.row - 1;
            int current_col = starting.col;
            if (maze[up_row][current_col] == 1) {
                return 0;
            }
        }
        break;
    case right_up:
        if (starting.row - 1 < 0 || starting.col + 1 >= MAX_COL) {
            return 0;
        }
        else {
            int up_row = starting.row - 1;
            int right_col = starting.col + 1;
            if (maze[up_row][right_col] == 1) {
                return 0;
            }
        }
        break;
    case right:
        if (starting.col + 1 >= MAX_COL) {
            return 0;
        }
        else {
            int cur_row = starting.row;
            int right_col = starting.col + 1;
            if (maze[cur_row][right_col] == 1) {
                return 0;
            }
        }
        break;
    case right_down:
        if (starting.row + 1 >= MAX_ROW || starting.col + 1 >= MAX_COL) {
            return 0;
        }
        else {
            int down_row = starting.row + 1;
            int right_col = starting.col + 1;
            if (maze[down_row][right_col] == 1) {
                return 0;
            }
        }
        break;
    case down:
        if (starting.row + 1 >= MAX_ROW) {
            return 0;
        }
        else {
            int down_row = starting.row + 1;
            int current_col = starting.col;
            if (maze[down_row][current_col] == 1) {
                return 0;
            }
        }
        break;
    case left_down:
        if (starting.row + 1 >= MAX_ROW || starting.col - 1 < 0) {
            return 0;
        }
        else {
            int down_row = starting.row + 1;
            int left_col = starting.col - 1;
            if (maze[down_row][left_col] == 1) {
                return 0;
            }
        }
        break;
    case left:
        if (starting.col - 1 < 0) {
            return 0;
        }
        else {
            int current_row = starting.row ;
            int left_col = starting.col - 1;
            if (maze[current_row][left_col] == 1) {
                return 0;
            }
        }
        break;
    case left_up:
        if (starting.row - 1 < 0 || starting.col - 1 < 0) {
            return 0;
        }
        else {
            int up_row = starting.row - 1;
            int left_col = starting.col - 1;
            if (maze[up_row][left_col] == 1) {
                return 0;
            }
        }
        break;
    default:
        break;
    }
    return 1;
}

void printing_path(int maze_path[MAX_ROW][MAX_COL], Position* starting, Position* ending) {
    Position* temp;
    temp->row = starting->row;
    temp->col = starting->col;

    while (temp->row != ending->row && temp->col != ending->col)
    {   
        int direction = maze_path[temp->row][temp->col];
        printf("%s\n", move(direction));
        updating_starting_point(temp, direction);
    }
}

const char* move(int direction) {
    const char* move_up = "up";
    const char* move_right_up = "right_up";
    const char* move_right = "right_up";
    const char* move_right_down = "right_down";
    const char* move_down = "down";
    const char* move_left_down = "left_down";
    const char* move_left = "left";
    const char* move_left_up = "left_up";

    switch (direction)
    {
    case up:
        return move_up;
    case right_up:
        return move_right_up;
    case right:
        return move_right;
    case right_down:
        return move_right_down;
    case down:
        return move_down;
    case left_down:
        return move_left_down;
    case left:
        return move_left;
    case left_up:
        return move_left_up;
    default:
        break;
    }
}