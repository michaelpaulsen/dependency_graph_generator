#include <memory>
#include <cstring>
#include <cstdio>
#include <vector>
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
constexpr size_t MAX_LINE_LENG   = 256;
constexpr size_t MAX_FOLDER_LENG = 3072; 
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
        DEBUG_P(GenerateDebugMessage("ran out of space to write to string\n\tstrlen : %llu alocated space %llu"),  " strcpy_u", i, strlen(buffer), __LINE__, FUNCT_LINE_OFFSET);
     
        return NULL;
    }
    //msvs says possible buffer overflow but that is not possible because of 
    //above if statement
    buffer[i] = 0; 
    return buffer; 
}
char* getFolderFromFilePath(const char* filepath, const char  slashChar,  size_t leng) {
    size_t i = 0; 
    size_t lastslashPos = 0;
    char* tmp = static_cast<char*>(malloc(leng)); 
    if (!tmp) return NULL; 
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
char* getAllButFirstChar(const char *str, const size_t len) {
    char* buffer = static_cast<char*>(malloc(len)); 
    if(buffer){
        for (size_t i = 1; i < len; i++)
        {
            buffer[i-1] = str[i];
        }
    }
    return buffer; 
}
char* getFileNameFromPath(const char* path, const char slashChar, const size_t len) {
    char* tmp = strcpy_u(path);
    size_t i = 0; 
    char delim[2] = { slashChar, 0 };
    char* cntx = (char*) malloc(len); 
    char* tmpToken = strtok_s(tmp, delim, &cntx);
    char* token = strcpy_u(tmpToken);
    while (tmpToken) {
        tmpToken = strtok_s(NULL, delim, &cntx);

        if(tmpToken) token = strcpy_u(tmpToken);
    }
    return NULL; 
}
size_t getNumberOfFoldersInPath(const char *str, char slashChar) {
    size_t numberOfFolders = 0; 
    size_t i = 0; 
    
    while(str[i])
    {
        if (str[i] == slashChar) numberOfFolders++;
        i++;
    }
    return numberOfFolders; 
}
void parseFile(const char path[], std::vector<char*>& pathQue) {
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