/**
 * login
 **/
// c++
#include<iostream>
#include<string>
#include<vector>
#include<map>

// c
#include<unistd.h>
#include<stdlib.h>

// 内部ライブラリ
#include"./file.cpp"
#include"./debug.cpp"
#include"./sha256.cpp"
#include"./password.cpp"

// オプション //
#include"./lib/option.hpp"
#include"./register.cpp"
#include"./list.cpp"
#include"./remove.cpp"
//

#include"./lib/data.hpp"

const std::string TO_SAVE = getenv("HOME");
const std::string FILE_NAME = "syp.txt";

std::map<char, Option>  mapInit(int argc, char*argv[]) {
    std::map<char, Option> option;
    int opt;
    opterr = 0;

    while( (opt = getopt(argc, argv, "alr") ) != -1) {
        switch(opt) {
            case 'a':
                option.insert(std::make_pair('a', Register(true)));
                break;
            case 'l':
                option.insert(std::make_pair('l', List(true)));
                break;
            case 'r':
                option.insert(std::make_pair('r', Remove(true)));
                break;
            default:
                std::cout <<
                    "Usage: "<< argv[0] << " [-a] [-l] [-r]"
                    << std::endl;
                exit(0);
        }
    }
    if(option.count('a') == 1 && option.count('r') == 1) {
        std::cout <<
            "Sorry! You can only use which option [-a] or [-r]."
            << std::endl;
        exit(0);
    }

    return option;
}

int main(int argc, char* argv[]) {
    // 宣言
    bool check = false;
    std::string y;
    Data input;
    Data inst;
    std::string service;
    std::string inst_service;
    std::vector< std::string > data;
    std::vector< std::string > alrady;
    File f;
    std::map<char, Option> option;
    const char* fn = (TO_SAVE+"/"+FILE_NAME).c_str();
    //DEBUG(fn);

    // データ保存用のmultimap：同じキーを複数使える
    //std::multimap<std::string, Data> map;
    
    option = mapInit(argc, argv);

    // file開くところ
    try {
        if(f.checkFileExist(fn)) {
            f.ifsOpen(fn);
            // read
            f.read(alrady);
        }
    } catch(int i) {
        ERROR(i,"file can't open");
        return i;
    }

    //DEBUG(alrady.back());
    if(alrady.size()%3 != 0) {
        ERROR(alrady.size()%3, "what's data?");
        return alrady.size()%3;
    }
    if(alrady.empty()) {
        if(option.count('a') == 0) {
            option.insert(std::make_pair('a', Register(true)));
            std::cout << "セーブするファイルがありません.作成します." << std::endl;
        }
        if(option.count('l') == 1 || option.count('r') == 1) {
            std::cout << "保存されているサービスは0です." << std::endl;
            return 0;
        }
    }
    else {
        if(option.count('l') == 1) {
            for(int i=0;i<alrady.size();i+=3) {
                printf("Service[%02d]: %s\n", i/3+1, alrady[i].c_str());
                printf("     ID[%02d]: %s\n", i/3+1, alrady[i+1].c_str());
            }
            return 0;
        }
    }

    // Service入力してね
    std::cout << "Service : ";
    // Service入力
    std::cin >> service;
    // dataを格納
    data.push_back(service);

    // ID入力してね
    std::cout << "ID      : ";
    // ID入力
    std::cin >> input.id;
    // dataを格納
    data.push_back(input.id);
    
    // password入力してね
    std::cout << "Password: ";
    // password入力
    input.password = secret();

    // hash化（sha256）
    input.password = sha(input.id+input.password);
    
    // dataを格納
    data.push_back(input.password);

    // password確認
    if(option.count('a') == 1) {
        try {
            f.ofsOpen(fn, 'a');
        } catch(int i) {
            ERROR(i,"file can't open");
            return i;
        }

        f.write(data);
    }
    else {
        data.clear();
        int i=0;
        while(!alrady.empty()) {
            inst.password = alrady.back();
            alrady.pop_back();

            inst.id = alrady.back();
            alrady.pop_back();

            inst_service = alrady.back();
            alrady.pop_back();

            // 確認
            if(inst_service == service
                && inst.id == input.id
                && inst.password == input.password) {
                check = true;
                std::cout << inst_service << " Access!" << std::endl;
            }
            else {
                data.push_back(inst.password);
                data.push_back(inst.id);
                data.push_back(inst_service);
            }

            i+=3;
        }
    }

    //File::read("./from.txt");

    // passwordが合ってた時

    // passwordが間違ってた時
    if(!check && option.count('a') == 0) {
        std::cout << "No matcing!" << std::endl;
    }
    if(option.count('r') == 1 && option.count('a') == 0) {
        try {
            f.ofsOpen(fn, 'w');
        } catch(int i) {
            ERROR(i,"file can't open");
            return i;
        }

        f.write(data);
    }

    return 0;
}
