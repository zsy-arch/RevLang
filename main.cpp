#include <iostream>
#include "core/Lexer.h"

int main(int argc, const char *argv[]) {
    std::cout << "RevLang v0.0.1" << std::endl;
    Lexer lexer("let a = 10.");
    Token *token = nullptr;

    while ((token = lexer.get_next_token()) != nullptr) {
        if (*token == "END" || *token == ILLEGAL_STR) break;
        std::cout << token->get_token_string() << std::endl;
    }
    return 0;
}
