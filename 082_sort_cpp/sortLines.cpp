#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
void readFromLienAndSort(std::istream& input){
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(input,line)){
        lines.push_back(line);
    }
    std::sort(lines.begin(),lines.end());
    std::vector<std::string>::iterator it = lines.begin();
    while (it!=lines.end())
    {
        std::cout<< *it <<std::endl;
        it++;
    }
}

int main(int argc,char** argv){
     if(argc == 1){
        readFromLienAndSort(std::cin);
     }else{
        for(int i = 1;i<argc;i++){
            std::ifstream file(argv[i]);
            if(file.is_open()){
                readFromLienAndSort(file);
            }else{
                std::cerr<<"can't open file"<<std::endl;
                exit(EXIT_FAILURE);
            }
        }
     }
     exit(EXIT_SUCCESS);

}

