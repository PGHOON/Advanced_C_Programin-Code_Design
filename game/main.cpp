#include "ui.hpp"
#include "maze.hpp"

int main() {
    UI ui;
    ui.initialize();    //ncurses 생성

    int width, height;
    getmaxyx(stdscr, height, width);

    Maze maze(width/2 - 2, height); //Maze construct
    maze.generateMaze();    //미로생성

    int playerX = 1, playerY = 1;   //초기 Player 좌표
    int menu = 0;   //게임 메뉴 옵션
    int cursor = 0; //커서 위치
    int ch;
    ui.drawBorder(0, width, height, " Main  menu ");    //초기 화면 UI 출력

    while ((ch = getch()) != 'q') {
        if (menu == 0){
            clear();
            curs_set(1);    //커서 활성화
            ui.drawBorder(0, width, height, " Main  menu ");    //초기 화면 UI 출력
            ui.menuSelect(cursor, menu, width, height, ui, ch); //메뉴 선택 키보드 입력 제어
        }
        if (menu == 1){
            int next_PlayerX = playerX;
            int next_PlayerY = playerY;
            
            maze.keyControl(playerX, playerY, next_PlayerX, next_PlayerY, maze, ch);    //게임 키보드 입력 제어, 미로 출력
            ui.drawWall(height);    //Player, Pc 구획 구분선
            ui.drawBorder(1, width, height, " Maze  game ");    //게임 화면 UI 출력
            //maze.agent_BFS(maze); //BFS탐색 알고리즘 에이전트
            maze.agent_DFS(maze);   //DFS탐색 알고리즘 에이전트
        }
        if (menu == 2){
            ui.drawBorder(1, width, height, " How to Play ");   //게임설명 UI 출력
            menu = 0;
        }
    }

    ui.cleanup();
    return 0;
}