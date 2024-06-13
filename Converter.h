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
