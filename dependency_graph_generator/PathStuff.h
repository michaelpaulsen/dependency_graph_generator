#pragma once
#include <memory>
#include "DEBUG.h" 
#include "stringThings.h"
#ifndef NULL
#define NULL 0
#endif // !NULL
#ifndef MAX_FOLDER_LENG 
#define MAX_FOLDER_LENG 3072
#endif
char* getNthParentFolderFromPath(const char* path, size_t n, bool useForwardSlash = true) {
    SET_STARTLINE;
    char* buffer = (char*)malloc(strlen(path));
    if (buffer == NULL) {
        DEBUG_P(GenerateDebugMessage("Unable to create buffer"), "getNthParentFolderFromPath", __LINE__, FUNCT_LINE_OFFSET);
        return NULL;
    }
    size_t ptrindex = 0, numberOfFolders = 0;
    while (path[ptrindex] && numberOfFolders <= n) {
        buffer[ptrindex] = path[ptrindex];
        ptrindex++;
        if ((useForwardSlash && path[ptrindex] == '/') || (!useForwardSlash && path[ptrindex] == '\\')) {
            numberOfFolders++;
        }
    }
    return buffer;
}
char* getFolderFromFilePath(const char* filepath, size_t leng, bool useForwardSlash = true) {
    size_t i = 0;
    size_t lastslashPos = 0;
    char* tmp = static_cast<char*>(malloc(leng));
    if (!tmp) return NULL;
    while (filepath[i]) {
        if ((useForwardSlash && filepath[i] == '/') || (!useForwardSlash && filepath[i] == '\\')) {
            lastslashPos = i;
        }
        i++;
    }
    if (lastslashPos + 1 < leng) {
        for (size_t i = 0; i <= lastslashPos; i++)
        {
            tmp[i] = filepath[i];
        }
        tmp[lastslashPos + 1] = 0; //this should be unnessisary... 
    }
    char* buffer = static_cast<char*>(calloc(strlen(tmp), 1));
    if (buffer) {
        for (size_t i = 0; i <= strlen(tmp); i++)
        {
            buffer[i] = tmp[i];
        }
    }
    free(tmp);
    return buffer;
}
char* getFileNameFromPath(const char* path, const size_t len, bool useforwardSlash = true) {
    char* tmp = strcpy_u(path);
    size_t i = 0;
    const char* delim = useforwardSlash ? "/" : "\\";
    char* cntx = (char*)malloc(len);
    char* tmpToken = strtok_s(tmp, delim, &cntx);
    char* token = strcpy_u(tmpToken);
    while (tmpToken) {
        tmpToken = strtok_s(NULL, delim, &cntx);

        if (tmpToken) token = strcpy_u(tmpToken);
    }
    return NULL;
}
size_t getNumberOfFoldersInPath(const char* filepath, bool useForwardSlash = true) {
    size_t numberOfFolders = 0;
    size_t i = 0;

    while (filepath[i])
    {
        if ((useForwardSlash && filepath[i] == '/') || (!useForwardSlash && filepath[i] == '\\')) numberOfFolders++;
        i++;
    }
    return numberOfFolders;
}
