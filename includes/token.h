#include <string>

enum TOKEN_TYPE {
    KEYWORD,
    SYMBOL,
    IDENTIFIER,
    INT_CONST,
    STRING_CONST,
    OTHERS
};

class Token {
  public:
    TOKEN_TYPE type;
    std::string value = "";
};