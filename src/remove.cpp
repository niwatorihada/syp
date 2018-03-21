#include"./lib/option.hpp"

class Remove : public Option {
public:
    Remove() {
        exist = false;
    }
    Remove(bool exist) {
        this->exist = exist;
    }

    void Description() {
        std::cout << "syp [-r]" << std::endl;
        std::cout << "このオプションを付けて実行すると指定したデータを消去出来ます." << std::endl;
    }

    bool Check() {
        return exist;
    }
};
