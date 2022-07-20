//
// Created by zhangsiyu on 7/20/2022.
//

#ifndef REVLANG_LEXER_H
#define REVLANG_LEXER_H

#include <string>
#include "Token.h"

class Lexer {
public:
    explicit Lexer(std::string input);

    char read_char();

    char next_char();

    Token* get_next_token();

    Token* get_number_token();

    std::string get_number();

    Token* get_ident_or_kw();

    bool is_digit(char c);

    bool is_letter(char c);

    void skip_whitespace();
private:
    std::string input;
    int position{};
    char ch;
};


#endif //REVLANG_LEXER_H
