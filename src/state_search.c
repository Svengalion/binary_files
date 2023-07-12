#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flareoni.h"

int getLen(FILE* ptr);

int searchRecordByDate(FILE* file, char* searchDate) {
    rewind(file);
    struct Record record;
    int found = 0;

    while (!feof(file)) {
        if (fread(&record, sizeof(struct Record), 1, file) == 1) {
            char dateString[11];
            sprintf(dateString, "%02d.%02d.%04d", record.day, record.month, record.year);

            if (strcmp(dateString, searchDate) == 0) {
                found = 1;
                break;
            }
        }
    }

    if (found) {
        return record.code;
    } else {
        return -1;
    }
}

int main() {
    char searchDate[11];

    char* filename = getPath();

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("n/a");
        return 1;
    }

    scanf("%10s", searchDate);

    int code = searchRecordByDate(file, searchDate);

    if (code != -1) {
        printf("%d", code);
    } else {
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
