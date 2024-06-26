#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int CountDelimiters(const char* input_string, char delimiter) {
    int count = 0;
    const char* string_reference = input_string;
 
    while (*string_reference != '\0') {
        if (*string_reference == delimiter) {
            count++;
        }
        string_reference++;
    }
 
    return count;
}
char** SplitString(const char* input_string, char delimiter) {
    int count = CountDelimiters(input_string, delimiter) + 1;
    char** tokens = (char**)malloc(sizeof(char*) * (count + 2));
    int token_index = 0;
    string_reference = input_string;
    char* token = (char*)malloc(strlen(input_string) + 1);
    int tokens_index = 0;
    while (*string_reference != '\0') {
        if (*string_reference == delimiter) {
            token[tokens_index] = '\0';
            tokens[token_index++] = strdup(token);
            tokens_index = 0;
        } else {
            token[tokens_index++] = *string_reference;
        }
        string_reference++;
    }
    // Add the last token
    token[tokens_index] = '\0';
    tokens[token_index] = strdup(token);
    tokens[token_index + 1] = NULL;
    free(token);
    return tokens;
}
