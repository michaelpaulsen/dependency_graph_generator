// dependency_graph_generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <cstring>
#include <cstdio>
#include <vector>

constexpr size_t MAX_LINE_LENG   = 256;
constexpr size_t MAX_FOLDER_LENG = 3072; 
char* strcpy_u(const char* source) {
    char* buffer = static_cast<char*>(malloc(strlen(source)));
    size_t i = 0;
    size_t len = 1;
    if (!buffer) return NULL; 
    while (source[i]) {
        buffer[i] = source[i];
        ++i;
        ++len;
    }
    if (len > strlen(source)) return NULL; 
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
