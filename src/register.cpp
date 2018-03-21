#include"./lib/option.hpp"

class Register : public Option {
public:
    Register() {
        exist = false;
    }
    Register(bool exist) {
        this->exist = exist;
    }

    void Description() {
        std::cout << "syp [-a]" << std::endl;
        std::cout << "このオプションを付けて実行するとデータを登録出来ます." << std::endl;
    }

    bool Check() {
        return exist;
    }
};
