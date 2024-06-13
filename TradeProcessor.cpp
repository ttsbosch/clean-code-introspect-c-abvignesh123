#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    char SC[256]; // SourceCurrency
    char DC[256]; // DestibationCurrency
    float Lots;
    double Price;
} TradeRecord;


char** SplitString(const char* str, char delimiter) {
    int count = 0;
    const char* strPtr = str;
    
    // Count the number of delimiters in the string
    while (*strPtr != '\0') {
        if (*strPtr++ == delimiter) {
            count++;
        }
    }

    // Allocate memory for the tokens array
    char** tokens = (char**)malloc(sizeof(char*) * (count + 2));
    int tokenIndex = 0;
    strPtr = str;
    
    // Allocate memory for the current token
    char* token = (char*)malloc(strlen(str) + 1);
    int tokenLength = 0;
    
    // Split the string into tokens
    while (*strPtr != '\0') {
        if (*strPtr == delimiter) {
            token[tokenLength] = '\0';
            tokens[tokenIndex++] = strdup(token);
            tokenLength = 0;
        } else {
            token[tokenLength++] = *strPtr;
        }
        strPtr++;
    }
    
    // Add the last token to the tokens array
    token[tokenLength] = '\0';
    tokens[tokenIndex++] = strdup(token);
    tokens[tokenIndex] = NULL;
    
    // Free the memory allocated for the current token
    free(token);
    
    return tokens;
}


int GetIntegerFromString(const char* str, int* value) {
    char* endptr;
    *value = strtol(str, &endptr, 10);
    if (endptr == str) {
        return True;
    }
    return False;
}

int toDouble(const char* str, double* value) {
    char* endptr;
    *value = strtod(str, &endptr);
    if (endptr == str) {
        return True;
    }
    return False;
}

void Process(FILE* stream) {
    char line[1024];
    TradeRecord objects[1024];
    int lineCount = 0;
    int objectCount = 0;

    while (fgets(line, sizeof(line), stream)) {
        char* fields[3];
        int fieldCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        if (fieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, fieldCount);
            continue;
        }

        if (strlen(fields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, fields[0]);
            continue;
        }

        int tradeAmount;
        if (!GetIntegerFromString(fields[1], &tradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, fields[1]);
        }

        double tradePrice;
        if (!toDouble(fields[2], &tradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, fields[2]);
        }

        strncpy(objects[objectCount].SC, fields[0], 3);
        strncpy(objects[objectCount].DC, fields[0] + 3, 3);
        objects[objectCount].Lots = tradeAmount / LotSize;
        objects[objectCount].Price = tradePrice;
        objectCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int index = 0; index < objectCount; index++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", objects[index].SC);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", objects[index].DC);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", objects[index].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", objects[index].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", objectCount);
}
