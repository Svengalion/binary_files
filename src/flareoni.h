struct Record {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};

void readRecord(FILE* file, struct Record* record);
void writeRecord(FILE* file, struct Record* record);
int isWithinDateRange(struct Record* record, char* startDate, char* endDate);
void clearFileContents(char* filename, char* startDate, char* endDate);
void printRecord(struct Record record);
int compareRecords(const void* a, const void* b);
void sortFileContents(FILE* file);
void printFileContents(FILE* file);
int getNumRecords(FILE* file);
void sortRecords(struct Record* records, int numRecords);
int getDate(int* date);
int getChoice();
char* getPath();
char* s21_strcat(char* str1, char* str2);
char* getStr();
int getLen(FILE* ptr);
