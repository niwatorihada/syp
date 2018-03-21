/**
 * login
 **/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<unistd.h>

#include"./file.cpp"
#include"./debug.cpp"
#include"./sha256.cpp"
#include"./password.cpp"
#include"./lib/option.hpp"
#include"./register.cpp"

#include"./lib/data.hpp"

std::map<char, Option>  mapInit(int argc, char*argv[]) {
    std::map<char, Option> option;
    int opt;
    opterr = 0;

    while( (opt = getopt(argc, argv, "af") ) != -1) {
        switch(opt) {
            case 'a':
                option.insert(std::make_pair('a', Register(true)));
                break;
            default:
                std::cout <<
                    "Usage: "<< argv[0] << " [-a]"
                    << std::endl;
                break;
        }
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

    // データ保存用のmultimap：同じキーを複数使える
    //std::multimap<std::string, Data> map;
    
    option = mapInit(argc, argv);

    // file開くところ
    try {
        f.ofsOpen("test.txt");
        f.ifsOpen("test.txt");
        // read
        f.read(alrady);
    } catch(int i) {
        ERROR(i,"file can't open");
        return i;
    }

    //DEBUG(alrady.back());
    if(alrady.size()%3 != 0) {
        ERROR(alrady.size()%3, "what's data?");
        return alrady.size()%3;
    }
    if(alrady.empty() && option.count('a') == 0) {
        option.insert(std::make_pair('a', Register(true)));
    }


    // Service入力してね
    std::cout << "Service : ";
    // Service入力
    std::cin >> service;
    //dataを格納
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
    if(option.count('a') == 1) f.write(data);
    else {
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
        }
    }

    //File::read("./from.txt");

    // passwordが合ってた時

    // passwordが間違ってた時
    if(!check && option.count('a') == 0) {
        std::cout << "No matcing!" << std::endl;
    }

    return 0;
}
