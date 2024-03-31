#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

// Function to read the file content
std::string readFile(const std::string& fileName) {
    std::ifstream file(fileName);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to remove comments and excess spaces
std::string removeCommentsAndSpaces(const std::string& code) {
    std::string result;
    std::regex commentRegex("(#.*?\\n)|(\\//s+)");
    result = std::regex_replace(code, commentRegex, " ");
    return result;
}

// Tokenizer function
std::vector<std::pair<std::string, std::string>> tokenize(const std::string& code) {
    std::vector<std::pair<std::string, std::string>> tokens;
    std::regex tokenRegex("(def|return|print)|([a-zA-Z_][a-zA-Z0-9_]*)|(=|\\+)|([\\(\\),:])|([0-9]+)");
    auto words_begin = std::sregex_iterator(code.begin(), code.end(), tokenRegex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string matchStr = match.str();
        if (std::regex_match(matchStr, std::regex("def|return|print"))) {
            tokens.push_back({"Keyword", matchStr});
        } else if (std::regex_match(matchStr, std::regex("[a-zA-Z_][a-zA-Z0-9_]*"))) {
            tokens.push_back({"Identifier", matchStr});
        } else if (std::regex_match(matchStr, std::regex("=|/\\+*"))) {
            tokens.push_back({"Operator", matchStr});
        } else if (std::regex_match(matchStr, std::regex("[\\(\\),:]"))) {
            tokens.push_back({"Delimiter", matchStr});
        } else if (std::regex_match(matchStr, std::regex("[0-9]+"))) {
            tokens.push_back({"Literal", matchStr});
        }
    }

    return tokens;
}

// Function to print tokens in tabular form
void printTokens(const std::vector<std::pair<std::string, std::string>>& tokens) {
    std::cout << "Category\tTokens" << std::endl;
    for (const auto& token : tokens) {
        std::cout << token.first << "\t" << token.second << std::endl;
    }
}

int main() {
    std::string fileName = "input.txt";
    std::string fileContent = readFile(fileName);
    
    std::string codeWithoutComments = removeCommentsAndSpaces(fileContent);
    std::cout << "Code after removing excess space and comments:" << std::endl;
    std::cout << codeWithoutComments << std::endl << std::endl;

    auto tokens = tokenize(codeWithoutComments);
    std::cout << "Tokenized code in tabular form:" << std::endl;
    printTokens(tokens);

    return 0;
}
