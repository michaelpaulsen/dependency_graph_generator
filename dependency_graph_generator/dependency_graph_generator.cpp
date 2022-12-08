// dependency_graph_generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <memory>
#include <cstring>
#include <cstdio>

constexpr size_t MAX_LINE_LENG   = 256;
constexpr size_t MAX_FOLDER_LENG = 3072; 
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
