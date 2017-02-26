#include "LexicalAnalyzer.h"
#include <cstdlib>
#include <ctype.h>
#include <iomanip>

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(char* filename)
{
    linenum = 1;
    pos = 0;
    errors = 0;
    eofFlag = false;
    // This function will initialize the lexical analyzer class

    input.open(filename);

    if (input.fail()) {
        std::cerr << "Failed to open file '" << filename << "'" << std::endl;
        exit(1);
    }
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    // This function will complete the execution of the lexical analyzer class

    input.close();
}

token_type LexicalAnalyzer::GetToken()
{
    // This function will find the next lexeme int the input file and return
    // the token_type value associated with that lexeme

    if (eofFlag) return EOF_T;

    std::cout << std::endl
              << "Getting a new token" << std::endl;

    // Reset 'lexeme' in preparation for finding the next token
    lexeme = "";

    token = START_T;

    std::getline(input, line);

    char c;

    // If reading a lexeme and encountering EOF, return whatever the most recent state is
    while (!eofFlag) {
        // Break when reaching the end of the line
        if (pos >= line.length()) {
            if (std::getline(input, line)) pos = 0;
            else eofFlag = true;
        }

        // The current character being read
        c = line[pos];

        // Break from the loop when encountering whitespace of any kind or EOF flag is set
        if (isspace(c)) {
            pos++;
            break;
        }

        // Append the current character to the lexeme
        lexeme += c;

        std::cout << "Read character: " << c << std::endl;

        token_type prevState = token;

        // Run the character through the DFA
        token = LexicalAnalyzer::nextState(c, prevState);

        std::cout << "DFA returned: " << token << std::endl;

        // If in a final state when the next token is ERR_T, return the previous token
        if (token == ERR_T && (token >= 100 || token <= 199)) {
            pos--;
            token = prevState;
            break;
        }

        // Increment the position before beginning the next loop
        pos++;
    }

    std::cout << "Lexeme is: " << lexeme << std::endl;
    std::cout << "Token is: " << token << std::endl;

    return token;
}

string LexicalAnalyzer::GetTokenName(token_type t) const
{
    // The GetTokenName function returns a string containing the name of the
    // token passed to it.
    return "";
}

string LexicalAnalyzer::GetLexeme() const
{
    // This function will return the lexeme found by the most recent call to
    // the get_token function
    return lexeme.c_str();
}

void LexicalAnalyzer::ReportError(const string& msg)
{
    // This function will be called to write an error message to a file
    std::cout << msg << std::endl;
}

int LexicalAnalyzer::ConvertCharToTableCol(char c)
{
    int cintval;

    if (c >= 97 || c <= 122)
        cintval = c - 32;
    else if (isdigit(c))
        cintval = 50; // all digits are represented on the table as the same value
    // of 50, since all digits behave the same way lexically
    else
        cintval = (int)c;
    for (int i = 0; i < 41; i++) // 61 is the last row of the table, it stores ascii equivalents of the values
    {
        if (cintval == lexicalTable[61][i])
            return i;
    }
    string err = "Error: unexpected character ";
    err.push_back(c);
    ReportError(err);
    return cintval;
}

token_type LexicalAnalyzer::nextState(char c, token_type currState)
{
	int col = ConvertCharToTableCol(c);
    return static_cast<token_type>(lexicalTable[currState][col]);
}
