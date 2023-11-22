#include "maze.hpp"

using namespace std;

Maze::Maze(int width, int height) {
    width_ = (width);
    height_ = (height);
    goal = make_pair(width - 2, height - 2);
    cell.resize(width_, vector<bool>(height_, true));
}

void Maze::generateMaze() {
    random_device rd;
    mt19937 gen(rd());
    stack<pair<int, int>> stack;
    vector<pair<int, int>> directions = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
    vector<pair<int, int>> neighbors;

    int x = 1, y = 1;
    cell[x][y] = false;
    cell[width_ - 2][height_ - 2] = false;
    stack.push({x, y});

    while (!stack.empty()) {
        tie(x, y) = stack.top();
        neighbors.clear();

        for (const auto& dir : directions) {
            int nx = x + dir.first, ny = y + dir.second;
            if (nx >= 1 && nx < width_ - 1 && ny >= 1 && ny < height_ - 1 && cell[nx][ny]) {
                neighbors.push_back({nx, ny});
            }
        }

        if (!neighbors.empty()) {
            shuffle(neighbors.begin(), neighbors.end(), gen);
            pair<int, int> next = neighbors.front();

            cell[(x + next.first) / 2][(y + next.second) / 2] = false;
            cell[next.first][next.second] = false;
            stack.push(next);
        } else {
            stack.pop();
        }
    }
}


void Maze::agent_BFS(Maze &maze) {
    pair<int, int> start = {1, 1};
    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, int>> parent;
    vector<pair<int, int>> path;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    q.push(start);
    parent[start] = {-1, -1};

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        if (maze.isGoal(current.first, current.second)) {
            for (pair<int, int> at = current; at != make_pair(-1, -1); at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            break;
        }

        for (const auto &dir : directions) {
            pair<int, int> next = {current.first + dir.first, current.second + dir.second};
            if (!maze.isWall(next.first, next.second) && parent.find(next) == parent.end()) {
                parent[next] = current;
                q.push(next);
            }
        }
    }
    thread displayThread(&Maze::agent_display, this, path);
    displayThread.detach();
}

void Maze::agent_DFS(Maze &maze) {
    pair<int, int> start = {1, 1};
    stack<pair<int, int>> s;
    map<pair<int, int>, pair<int, int>> parent;
    vector<pair<int, int>> path;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    s.push(start);
    parent[start] = {-1, -1};

    while (!s.empty()) {
        pair<int, int> current = s.top();
        s.pop();

        if (maze.isGoal(current.first, current.second)) {
            for (pair<int, int> at = current; at != make_pair(-1, -1); at = parent[at]) {
                path.push_back(at);
            }
            reverse(path.begin(), path.end());
            break;
        }

        for (const auto &dir : directions) {
            pair<int, int> next = {current.first + dir.first, current.second + dir.second};
            if (!maze.isWall(next.first, next.second) && parent.find(next) == parent.end()) {
                parent[next] = current;
                s.push(next);
            }
        }
    }
    thread displayThread(&Maze::agent_display, this, path);
    displayThread.detach();
}

void Maze::display() {
    for (int y = 1; y < height_ - 1; ++y) {
        for (int x = 1; x < width_ - 1; ++x) {
            if (cell[x][y]) {
                attron(COLOR_PAIR(3));
                mvaddch(y, x, ACS_CKBOARD);
                mvaddch(y, x+93, ACS_CKBOARD);
                attroff(COLOR_PAIR(3));
            }
        }
    }
}

void Maze::agent_display(const vector<pair<int, int>>& path) {
    for (const auto& p : path) {
        int x = p.first;
        int y = p.second;

        mt.lock();
        attron(COLOR_PAIR(2));
        mvaddch(y, x+93, ' ');
        attroff(COLOR_PAIR(2));
        refresh();
        mt.unlock();
        this_thread::sleep_for(chrono::milliseconds(100));  // 경로 출력 속도 조절
    }
}

bool Maze::isWall(int x, int y) {
    return cell[x][y];
}

bool Maze::isGoal(int x, int y) {
    return make_pair(x, y) == goal;
}

void Maze::movePlayer(int& playerX, int& playerY, int next_PlayerX, int next_PlayerY, Maze& maze) {
    if (!maze.isWall(next_PlayerX, next_PlayerY)) {
        mvaddch(playerY, playerX, ' ');
        playerX = next_PlayerX;
        playerY = next_PlayerY;
    }
    if (maze.isGoal(playerX, playerY)) {
        /*
        클리어시 화면에 대한 부분 추가 필요
        */
        mvprintw(playerY, playerX, "game clear");
    }
    attron(COLOR_PAIR(1));
    mvaddch(playerY, playerX, '@');
    attroff(COLOR_PAIR(1));
    refresh();
}

void Maze::keyControl(int &playerX, int &playerY, int &next_PlayerX, int &next_PlayerY, Maze &maze, int ch) {
    maze.display();
    attron(COLOR_PAIR(1));
    mvaddch(playerY, playerX, '@');
    attroff(COLOR_PAIR(1));
    switch (ch) {
        case KEY_UP:
        case 'w':
            maze.display();
            next_PlayerY--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_DOWN:
        case 's':
            maze.display();
            next_PlayerY++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_LEFT:
        case 'a':
            maze.display();
            next_PlayerX--;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
        case KEY_RIGHT:
        case 'd':
            maze.display();
            next_PlayerX++;
            maze.movePlayer(playerX, playerY, next_PlayerX, next_PlayerY, maze);
            break;
    }
}