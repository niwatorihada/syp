#ifndef OPTHION_HPP
#define OPTHION_HPP

#include<string>

class Option {
public:
    // bool
    bool exist;
    // 説明文
    std::string desc;
    
    // コンストラクタ
    Option() {
        exist = false;
    }
    Option(bool exist) {
        this->exist = exist;
    }

    // 説明しよう！
    void Description();
    bool Check();
};

#endif /* OPTHION_HPP */
