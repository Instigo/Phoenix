#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <fstream>


void tail(std::ifstream &stream, int numLines){

    std::string line;
    std::queue<std::string> Q;

    while( getline(stream, line) ){
        if(Q.size() > numLines) 
            Q.pop();
        Q.push(line);
    }

    while(!Q.empty()){
        std::cout << Q.front() << std::endl;
        Q.pop();
    }
    stream.close();
}

int main(int argc, char * argv[]){

    int numLines = 0;
    std::stringstream ss;

    if(argc < 1){
        // display application usage
        printf("Usage ptail -n 10 <filename>\n");
        printf("\t-n\n");
        printf("\t\t\toutput the last N lines\n");
        return 0;
    }
    if( argc > 2 ){
        std::string numFlag(argv[1]);
        if( numFlag.compare("-n") == 0){
            ss << argv[2];
            ss >> numLines;
        }
   
        std::ifstream file(argv[3]);
        
        if(file.is_open()){
            tail(file, numLines);
            file.close();    
        }
                        
    }

    return EXIT_SUCCESS;
}
