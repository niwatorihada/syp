/**
 * passwordの入力を隠す
 * [VC++ 標準入力に入力されたパスワードを隠す方法]
 * http://kwikwi.cocolog-nifty.com/blog/2014/01/vc-dddc.html
 * [コンソール入出力関数]
 * https://www.grapecity.com/tools/support/powernews/column/clang/047/page01.htm
 * [コンソール制御]
 * https://www.mm2d.net/main/prog/c/console-05.html
 **/

#include<iostream>
#include<string>
//#include<conio.h> // コンソール入出力関数, windowsだけ搭載
#include<termios.h>
#include<stdio.h>
#include<unistd.h>

#include"./debug.cpp"

std::string secret() {
    std::string password;
    char ch;
    const char BACKSPACE = 127;
    const char ENTER = '\n';

    struct termios term;
    struct termios save;
    
    // terminalの設定を取ってきてる
    tcgetattr(STDIN_FILENO, &term);
    // 後で設定を戻すために保存しておく
    save = term;
    // 非カノニカルモード
    term.c_lflag &= ~ICANON;
    // エコーを切る
    term.c_lflag &= ~ECHO;
    // 変更を反映
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    fgetc(stdin);

    while( (ch = fgetc(stdin)) != ENTER) {
        if(ch == BACKSPACE) {
            if(password.size() > 0) {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    //DEBUG(password);
    tcsetattr(STDIN_FILENO, TCSANOW, &save);
    return password;
}
