// dependency_graph_generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <cstring>
#include <cstdio>
#include <vector>
const char* DEBUG_HEAD = "DEBUG(%s) :\n\t";
const char* DEBUG_FOOT = "\non line %llu (funct : %llu)\n";
#ifdef _DEBUG
#define DEBUG_P printf
#define SET_STARTLINE  auto startline = __LINE__+1
#define FUNCT_LINE_OFFSET __LINE__ - startline
#else
#define DEBUG_P 
#define SET_STARTLINE 
#define FUNCT_LINE_OFFSET 0
#endif // DEBUG

constexpr size_t MAX_LINE_LENG   = 256;
constexpr size_t MAX_FOLDER_LENG = 3072; 
char* GenerateDebugMessage(const char* DEBUG_HEAD, const char* DEBUG_FOOT, const char* type) {
    const size_t len = (strlen(DEBUG_HEAD) + strlen(DEBUG_FOOT) - 2) + strlen(type);
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
    while (type[t]) {
        buffer[i] = type[t];
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
char* strcpy_u(const char* source) {
    SET_STARTLINE; 
    DEBUG_P(GenerateDebugMessage(DEBUG_HEAD, DEBUG_FOOT, "source: %s"), "strcpy_u", source, startline+FUNCT_LINE_OFFSET, FUNCT_LINE_OFFSET);

    char* buffer = static_cast<char*>(malloc(strlen(source)));
    if (!buffer) {
        DEBUG_P(GenerateDebugMessage(DEBUG_HEAD, DEBUG_FOOT, "failed to create buffer \n\treturned (NULL)"), "strcpy_u", FUNCT_LINE_OFFSET, startline + FUNCT_LINE_OFFSET);
        return NULL;
    }
    size_t i = 0;
    size_t len = 1;
    while (source[i]) {
        buffer[i] = source[i];
        ++i;
        ++len;
    }
    if (i > strlen(source)) {
        DEBUG_P(DEBUG_HEAD, "strcpy_u");
        DEBUG_P("length is greater than allocated space\n\treturning (NULL)");
        DEBUG_P("len %llu\n\tspace %llu", i, strlen(source));
        DEBUG_P(DEBUG_FOOT, FUNCT_LINE_OFFSET - 3, startline+FUNCT_LINE_OFFSET);
        return NULL;
    }
    //msvs says possible buffer overflow but that is not possible because of 
    //above if statement
    buffer[len] = 0; 
    return buffer; 
}
char* getFolderFromFilePath(const char* filepath, const char  slashChar,  size_t leng) {
    size_t i = 0; 
    size_t lastslashPos = 0;
    char* tmp = static_cast<char*>(malloc(leng)); 
    if (!tmp) return NULL; 
    //char* buffer = static_cast<char*>(malloc(leng)); 
    while (filepath[i]) {
        if (filepath[i] == slashChar) {
            lastslashPos = i; 
        }
        i++;
    }
    if(lastslashPos+1 < leng){  
        for (size_t i = 0; i <= lastslashPos; i++)
        {
            tmp[i] = filepath[i]; 
        }
        tmp[lastslashPos + 1] = 0; //this should be unnessisary... 
    }
    char* buffer =static_cast<char*>(calloc(strlen(tmp),1));
    if (buffer) {
        for (size_t i = 0; i <= strlen(tmp); i++)
        {
            
            buffer[i] = tmp[i]; 
        }
    }
    free(tmp);
    return buffer; 
}



char* getAllButFirstChar(const char str[], size_t len) {
    char* buffer = static_cast<char*>(malloc(len)); 
    if(buffer){
        for (size_t i = 1; i < len; i++)
        {
            buffer[i-1] = str[i];
        }
    }
    return buffer; 
}
void parseFile(char* path, std::vector<char*>& pathQue) {
    FILE* file;
    size_t lineNumber = 1;
    fopen_s(&file, path, "r");
    if (file) {
        const char* ROOT_FOLDER = getFolderFromFilePath(path, '\\', MAX_FOLDER_LENG);
        char line[MAX_LINE_LENG];

        while (fgets(line, MAX_LINE_LENG, file)) {
            char* cntx = static_cast<char*>(malloc(MAX_LINE_LENG));
            if (line[0] == '#') { // this filters out all of the non pre-prosser directivs
                char* tmp = strtok_s(line, " ", &cntx);
                char* directive = getAllButFirstChar(tmp, MAX_LINE_LENG);
                char* param = strtok_s(NULL, " ", &cntx);

                if (directive) {
                    if (param[0] != '<') {
                        printf("%llu : %s -> %s", lineNumber, directive, param);

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
    printf("opening %s for reading", argv[1]);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
