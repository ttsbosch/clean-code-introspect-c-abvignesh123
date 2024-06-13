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
