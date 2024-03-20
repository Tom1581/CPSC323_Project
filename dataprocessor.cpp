#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

// Function to read the file content
string readFile(const string& fileName) {
    ifstream file(fileName);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to remove comments and excess spaces
string removeCommentsAndSpaces(const string& code) {
    string result;
    regex commentRegex("(#.*?\\n)|(\\s+)");
    result = regex_replace(code, commentRegex, " ");
    return result;
}

// Tokenizer function
vector<pair<string, string>> tokenize(const string& code) {
    vector<pair<string, string>> tokens;
    regex tokenRegex("(def|return|print)|([a-zA-Z_][a-zA-Z0-9_]*)|(=|\\+)|([\\(\\),:])|([0-9]+)");
    auto words_begin = sregex_iterator(code.begin(), code.end(), tokenRegex);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        string matchStr = match.str();
        if (regex_match(matchStr, regex("def|return|print"))) {
            tokens.push_back({"Keyword", matchStr});
        } else if (regex_match(matchStr, regex("[a-zA-Z_][a-zA-Z0-9_]*"))) {
            tokens.push_back({"Identifier", matchStr});
        } else if (regex_match(matchStr, regex("=|\\+"))) {
            tokens.push_back({"Operator", matchStr});
        } else if (regex_match(matchStr, regex("[\\(\\),:]"))) {
            tokens.push_back({"Delimiter", matchStr});
        } else if (regex_match(matchStr, regex("[0-9]+"))) {
            tokens.push_back({"Literal", matchStr});
        }
    }

    return tokens;
}

// Function to print tokens in tabular form
void printTokens(const vector<pair<string, string>>& tokens) {
    cout << "Category\tTokens" << endl;
    for (const auto& token : tokens) {
        cout << token.first << "\t" << token.second << endl;
    }
}

int main() {
    string fileName = "input.txt";
    string fileContent = readFile(fileName);
    
    string codeWithoutComments = removeCommentsAndSpaces(fileContent);
    cout << "Code after removing excess space and comments:" << endl;
    cout << codeWithoutComments << endl << endl;

    auto tokens = tokenize(codeWithoutComments);
    cout << "Tokenized code in tabular form:" << endl;
    printTokens(tokens);

    return 0;
}
