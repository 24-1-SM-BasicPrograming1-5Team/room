#include <stdio.h>

// 게임 방 정보 구조체 정의
typedef struct {
    int id;
    char roomName[50];
    char nickname[50];
    char inGame[10];
    char passwordSet[5];
} GameRoom;

void printTable(GameRoom rooms[], int size) {
    printf("+----+---------------------+----------------+--------+-------------+\n");
    printf("| 순번 |      방 이름       |    닉네임      | 게임중 | 비밀번호 |\n");
    printf("+----+---------------------+----------------+--------+-------------+\n");
    for(int i = 0; i < size; i++) {
        printf("| %-4d | %-19s | %-14s | %-6s | %-11s |\n", rooms[i].id, rooms[i].roomName, rooms[i].nickname, rooms[i].inGame, rooms[i].passwordSet);
    }
    printf("+----+---------------------+----------------+--------+-------------+\n");
}

int main() {
    GameRoom rooms[] = {
        {1, "Room1", "Player1", "Yes", "No"},
        {2, "Room2", "Player2", "No", "Yes"},
        {3, "Room3", "Player3", "Yes", "No"},
        {4, "Room4", "Player4", "No", "Yes"}
    };
    
    int size = sizeof(rooms) / sizeof(rooms[0]);
    printTable(rooms, size);
    
    return 0;
}
