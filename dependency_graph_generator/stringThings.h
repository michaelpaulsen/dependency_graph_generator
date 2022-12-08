#pragma once
char* strcpy_u(const char* source) {
    SET_STARTLINE;
    DEBUG_P(GenerateDebugMessage("source: %s"), "strcpy_u", source, __LINE__, FUNCT_LINE_OFFSET);
    char* buffer = static_cast<char*>(malloc(strlen(source)));
    if (!buffer) {
        DEBUG_P(GenerateDebugMessage("failed to create buffer \n\treturned (NULL)"), "strcpy_u", __LINE__, FUNCT_LINE_OFFSET);
        return NULL;
    }
    size_t i = 0;
    while (source[i]) {
        buffer[i] = source[i];
        ++i;
    }
    if (i > strlen(source)) {
        DEBUG_P(GenerateDebugMessage("ran out of space to write to string\n\tstrlen : %llu alocated space %llu"), " strcpy_u", i, strlen(buffer), __LINE__, FUNCT_LINE_OFFSET);

        return NULL;
    }
    //msvs says possible buffer overflow but that is not possible because of 
    //above if statement
    buffer[i] = 0;
    return buffer;
}