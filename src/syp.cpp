/**
 * login
 **/
#include<iostream>
#include<string>
#include<vector>
#include<map>

#include"./file.cpp"
#include"./debug.cpp"
#include"./sha256.cpp"
#include"./password.cpp"

#include"./lib/data.hpp"

int main() {
    // 宣言
    bool regi = false;
    bool check = false;
    std::string y;
    Data input;
    Data inst;
    std::string service;
    std::string inst_service;
    std::vector< std::string > data;
    std::vector< std::string > alrady;
    File f;
    
    // データ保存用のmultimap：同じキーを複数使える
    //std::multimap<std::string, Data> map;

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
    if(alrady.empty()) {
        regi = true;
    }
    else {
        // registor?
        std::cout << "registration?(y/n): ";
        std::cin >> y;

        if(y == "y") {
            regi = true;
        }
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
    if(regi) f.write(data);
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
    if(!check && !regi) {
        std::cout << "No matcing!" << std::endl;
    }

    return 0;
}
