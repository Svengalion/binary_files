#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "flareoni.h"

int getLen(FILE* ptr);

void addRecord(FILE* file) {
    struct Record newRecord;
    if (scanf("%d", &newRecord.year) != 1) {
        printf("n/a");
    }
    if (scanf("%d", &newRecord.month) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.day) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.hour) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.minute) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.second) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.status) != 1) {
        printf("n/a");
        exit(0);
    }
    if (scanf("%d", &newRecord.code) != 1) {
        printf("n/a");
        exit(0);
    }
    writeRecord(file, &newRecord);
}

int main() {
    char* filename = getPath();

    FILE* file = fopen(filename, "rb+");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("n/a");
        fclose(file);
        return 0;
    }

    switch (choice) {
        case 0:
            printFileContents(file);
            break;
        case 1:
            sortFileContents(file);
            printFileContents(file);
            break;
        case 2:
            addRecord(file);
            sortFileContents(file);
            printFileContents(file);
            break;
        default:
            printf("n/a");
    }

    fclose(file);
    return 0;
}

int getLen(FILE* ptr) {
    int i = 0;
    int num;
    fseek(ptr, 0, SEEK_SET);
    while (!feof(ptr)) {
        fread(&num, sizeof(int), 1, ptr);
        i++;
    }
    fseek(ptr, 0, SEEK_SET);
    return i - 1;
}
