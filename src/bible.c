#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flareoni.h"

int compareRecords(const void* a, const void* b) {
    struct Record* recordA = (struct Record*)a;
    struct Record* recordB = (struct Record*)b;

    if (recordA->year != recordB->year) return recordA->year - recordB->year;

    if (recordA->month != recordB->month) return recordA->month - recordB->month;

    if (recordA->day != recordB->day) return recordA->day - recordB->day;

    if (recordA->hour != recordB->hour) return recordA->hour - recordB->hour;

    if (recordA->minute != recordB->minute) return recordA->minute - recordB->minute;

    if (recordA->second != recordB->second) return recordA->second - recordB->second;

    return 0;
}

void readRecord(FILE* file, struct Record* record) {
    fread(&record->year, sizeof(int), 1, file);
    fread(&record->month, sizeof(int), 1, file);
    fread(&record->day, sizeof(int), 1, file);
    fread(&record->hour, sizeof(int), 1, file);
    fread(&record->minute, sizeof(int), 1, file);
    fread(&record->second, sizeof(int), 1, file);
    fread(&record->status, sizeof(int), 1, file);
    fread(&record->code, sizeof(int), 1, file);
}

void writeRecord(FILE* file, struct Record* record) {
    fwrite(&record->year, sizeof(int), 1, file);
    fwrite(&record->month, sizeof(int), 1, file);
    fwrite(&record->day, sizeof(int), 1, file);
    fwrite(&record->hour, sizeof(int), 1, file);
    fwrite(&record->minute, sizeof(int), 1, file);
    fwrite(&record->second, sizeof(int), 1, file);
    fwrite(&record->status, sizeof(int), 1, file);
    fwrite(&record->code, sizeof(int), 1, file);
}

void sortRecords(struct Record* records, int numRecords) {
    qsort(records, numRecords, sizeof(struct Record), compareRecords);
}

int getNumRecords(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    return size / sizeof(struct Record);
}

void printFileContents(FILE* ptr) {
    fseek(ptr, 0, SEEK_SET);
    int num = 5;
    int size = getLen(ptr);

    fread(&num, sizeof(int), 1, ptr);
    printf("%d", num);
    for (int i = 1; i < size; i++) {
        if (i % 8 == 0)
            printf("\n");
        else
            printf(" ");
        fread(&num, sizeof(int), 1, ptr);
        printf("%d", num);
    }
}

void sortFileContents(FILE* file) {
    int numRecords = getNumRecords(file);

    if (numRecords > 0) {
        rewind(file);
        struct Record* records = (struct Record*)malloc(numRecords * sizeof(struct Record));

        for (int i = 0; i < numRecords; i++) {
            readRecord(file, &records[i]);
        }

        sortRecords(records, numRecords);
        rewind(file);

        for (int i = 0; i < numRecords; i++) {
            writeRecord(file, &records[i]);
        }

        free(records);
    } else {
        printf("n/a\n");
    }
}

// int isWithinDateRange(struct Record* record, char* startDate, char* endDate) {
//     char dateString[11];
//     sprintf(dateString, "%02d.%02d.%04d", record->day, record->month, record->year);
//
//     if (strcmp(dateString, startDate) >= 0 && strcmp(dateString, endDate) <= 0) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

char* getStr() {
    char* str = (char*)malloc(sizeof(char) * 10);
    int size = 0, k = 1;
    char c = ' ';
    scanf("%c", &c);
    if (c == '\n') scanf("%c", &c);
    while (c != '\n') {
        if (size > k * 10) {
            k++;
            char* tmp = (char*)realloc(str, sizeof(char) * 10 * k);
            if (tmp != NULL)
                str = tmp;
            else
                return NULL;
        }
        str[size++] = c;
        scanf("%c", &c);
    }
    str[size] = '\0';
    return str;
}

char* s21_strcat(char* str1, char* str2) {
    while (*str1 != '\0') str1++;
    while (*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return str1;
}

char* getPath() {
    char* str = getStr();
    char* tmp = (char*)malloc(sizeof(char) * (strlen(str) + 3));
    tmp[0] = '.';
    tmp[1] = '.';
    tmp[2] = '/';
    tmp[3] = '\0';
    s21_strcat(tmp, str);
    free(str);
    return tmp;
}

int getDate(int* date) {
    int is_error = 0;
    char* str = getStr();
    int len = strlen(str);
    date[0] = 0;
    date[1] = 0;
    date[2] = 0;
    for (int i = 2; i >= 0; i--) {
        while (*str) {
            if (((*str >= '0') && (*str <= '9')) || (*str == '.')) {
                if (*str == '.') {
                    str++;
                    break;
                }
                date[i] *= 10;
                date[i] += *str - '0';
            } else {
                is_error = 1;
            }
            str++;
        }
    }
    free(str - len);
    return is_error;
}
