#include <memory>
#include <cstring>
#include <cstdio>
#include <vector>
#include "DEBUG.h"
#include "stringThings.h"
constexpr size_t MAX_LINE_LENG   = 256;
constexpr size_t MAX_FOLDER_LENG = 3072; 
char* getAllButFirstChar(const char* str, const size_t len) {
    char* buffer = static_cast<char*>(malloc(len));
    if (buffer) {
        for (size_t i = 1; i < len; i++)
        {
            buffer[i-1] = str[i];
        }
    }
    return buffer; 
}

void parseFile(const char path[], std::vector<char*>& pathQue, bool useForwardSlash = true) {
    FILE* file;
    size_t lineNumber = 1;
    fopen_s(&file, path, "r");
    if (file) {
        const char* ROOT_FOLDER = getFolderFromFilePath(path, MAX_FOLDER_LENG, useForwardSlash);
        char line[MAX_LINE_LENG];

        while (fgets(line, MAX_LINE_LENG, file)) {
            char* cntx = static_cast<char*>(malloc(MAX_LINE_LENG));
            if (line[0] == '#') { // this filters out all of the non pre-prosser directivs
                char* tmp = strtok_s(line, " ", &cntx);
                char* directive = getAllButFirstChar(tmp, MAX_LINE_LENG);
                char* param = strtok_s(NULL, " ", &cntx);

                if (directive && param) {
                    if (param[0] != '<') {
                        printf("%llu : %s -> %s\n", lineNumber, directive, param);
                    }
                }
                else {
                    fprintf(stderr, "unable to parse line %llu\n", lineNumber);
                }
            }
            lineNumber++;
        }
        fclose(file);
    }
}
int main(int argc, char* argv[])
{
    if (argc < 2) {
        perror("please pass in a entry point to begin in");
        return -1;
    }
    printf("\n\n\n");
    std::vector<char*> filePathQue;
    const char* path = argv[1];
    parseFile(path, filePathQue); 
}