#include"./lib/option.hpp"

class List : public Option {
public:
    List() {
        exist = false;
    }
    List(bool exist) {
        this->exist = exist;
    }
    
    void Description() {
        std::cout << "syp [-l]" << std::endl;
        std::cout << "このオプションを付けて実行すると登録されてるサービス・IDの一覧が確認出来ます." << std::endl;
    }

    bool Check() {
        return exist;
    }
};
