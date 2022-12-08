#pragma once
#ifdef _DEBUG
#define DEBUG_P printf
#define SET_STARTLINE  auto startline = __LINE__+1
#define FUNCT_LINE_OFFSET __LINE__ - startline
#ifndef DEBUG_HEAD
#define DEBUG_HEAD  "DEBUG(%s) :\n\t"
#endif // !DEBUG_HEAD
#ifndef DEBUG_FOOT
#define DEBUG_FOOT  "\non line %llu (funct : %llu)\n"
#endif // !DEBUG_FOOT
#else
#define DEBUG_P 
#define SET_STARTLINE 
#define FUNCT_LINE_OFFSET 0
#define DEBUG_HEAD  " "
#define DEBUG_FOOT  " "
#endif // DEBUG
char* GenerateDebugMessage(const char* message) {
    const size_t len = (strlen(DEBUG_HEAD) + strlen(DEBUG_FOOT) - 2) + strlen(message);
    //bufferlen(type) inludes the null char so we don't have to add to this because it already \
    has the space for the null terminator. 
    char* buffer = (char*)malloc(len);
    if (!buffer) return NULL;

    for (size_t z = 0; z < len; z++) {
        buffer[z] = 0;
    }
    size_t i = 0;
    while (DEBUG_HEAD[i]) {
        buffer[i] = DEBUG_HEAD[i++];
    }
    size_t t = 0;
    while (message[t]) {
        buffer[i] = message[t];
        i++;
        t++;
    }
    size_t y = 0;
    while (DEBUG_FOOT[y]) {
        buffer[i] = DEBUG_FOOT[y];
        i++;
        y++;
    }
    buffer[i] = 0;
    return buffer;
}
