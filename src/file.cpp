/**
 * fileから読み込んだり,書き込んだりするクラス
 * headerはfile.h
 **/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#include"./lib/file.hpp"
#include"./debug.cpp"

/**
 * 読み込み
 **/
std::ofstream File::ofs;
std::ifstream File::ifs;

bool File::checkFileExist(const char* const file) {
    bool isOpen;
    File::ifs.open(file);
    isOpen = ifs.is_open();
    if(isOpen) {
        File::ifs.close();
    }
    return isOpen;
}
    

void File::ofsOpen(const char* const file) throw(int) {
    File::ofs.open(file, std::ios::app);
    if(ofs.fail()) {
        throw 0;
    }
}
void File::ofsOpen(const char* const file, char mode) throw(int) {
    if(mode == 'a') File::ofs.open(file, std::ios::app);
    else if(mode == 'w')  File::ofs.open(file);
    else File::ofs.open(file, std::ios::app);
    if(ofs.fail()) {
        throw 1;
    }
}
void File::ofsClose() throw(int) {
    File::ofs.close();
    if(ofs.fail()) {
        throw 4;
    }
}
void File::ifsOpen(const char* const file) throw(int) {
    File::ifs.open(file);
    if(ifs.fail()) {
        throw 2;
    }
}
void File::ifsClose() throw(int){
    File::ifs.close();
    if(ifs.fail()) {
        throw 3;
    }
}

/*std::vector<std::string> File::read() {
    std::string str;
    std::vector<std::string> in;
    while(getline(ifs,str)) {
        in.push_back(str);
    }
    return in;
}*/

void File::read(std::vector<std::string> &r) {
    std::string str;
    while(std::getline(ifs,str)) {
        r.push_back(str);
    }
}

/**
 * 書き込み
 **/
void File::write(std::vector<std::string> in) {
    //DEBUG("in!");
    for(int i=0;i<in.size();i++) {
        ofs << in[i] << std::endl;
        //DEBUG(in[i]);
    }
}
void File::write( const char* const text) {
    ofs << text << std::endl;
}
