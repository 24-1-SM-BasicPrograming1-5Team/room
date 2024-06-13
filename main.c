#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 100
#define MAX_NICKNAME_LENGTH 50
#define FILE_PATH_LENGTH 100

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
    for (int i = 0; i < size; i++) {
        printf("| %-4d | %-19s | %-14s | %-6s | %-11s |\n", rooms[i].id, rooms[i].roomName, rooms[i].nickname, rooms[i].inGame, rooms[i].passwordSet);
    }
    printf("+----+---------------------+----------------+--------+-------------+\n");
}

void saveNickFile(char *filePath, char *nickname) {
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    fprintf(file, "%s\n", nickname);
    fclose(file);
}

void loadNickFile(char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    char nickname[FILE_PATH_LENGTH];
    fscanf(file, "%s", nickname);
    printf("%s\n", nickname);
    fclose(file);
}

void loadRoomList(GameRoom rooms[], int *size) {
    FILE *file = fopen("roomlist.txt", "r");
    if (file == NULL) {
        printf("roomlist.txt 파일을 열 수 없습니다.\n");
        exit(1);
    }

    *size = 0;
    while (fscanf(file, "%d %49s %49s %9s %4s",
                  &rooms[*size].id, rooms[*size].roomName, rooms[*size].nickname,
                  rooms[*size].inGame, rooms[*size].passwordSet) != EOF) {
        (*size)++;
    }

    fclose(file);
}

int main() {
    GameRoom rooms[MAX_ROOMS];
    int roomSize = 0;

    // roomlist.txt 파일에서 데이터 로드
    loadRoomList(rooms, &roomSize);

    char nickname[MAX_NICKNAME_LENGTH];
    printf("닉네임을 입력해주세요: ");
    scanf("%s", nickname);

    char filePath[FILE_PATH_LENGTH];
    snprintf(filePath, FILE_PATH_LENGTH, "users/%s.txt", nickname);

    FILE *file = fopen(filePath, "r");
    if (file) {
        // 파일이 존재하면 파일에서 데이터를 불러옴
        fclose(file);
        loadNickFile(filePath);
        printf("파일에서 데이터를 불러왔습니다.\n");
    } else {
        // 파일이 존재하지 않으면 파일을 생성하고 기본 데이터를 저장함
        saveNickFile(filePath, nickname);
        printf("파일을 생성하고 기본 데이터를 저장했습니다.\n");
    }

    // 테이블 출력
    printTable(rooms, roomSize);

    return 0;
}