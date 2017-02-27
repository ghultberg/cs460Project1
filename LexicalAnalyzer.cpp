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

    std::getline(input, line);
    line += ' ';
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

    // std::cout << std::endl
    //           << "Getting a new token" << std::endl;

    // Reset 'lexeme' in preparation for finding the next token
    lexeme = "";

    token = START_T;

    char c;

    // If reading a lexeme and encountering EOF, return whatever the most recent state is
    while (!eofFlag) {

        // Return the current state when reaching the end of the line,
        // and prepare the next line when GetToken() is called.
        if (pos >= line.length()) {

        	// If there's a new line available, reset the position
            if (std::getline(input, line)) {
            	line += ' ';
            	pos = 0;
            }

            // Otherwise, we must have reached the end of the file
            else {
            	eofFlag = true;

            	// If we reached the end of the file and we're still at START_T, then there
            	// was trailing whitespace so we can simply return EOF_T
            	if (token == START_T) return EOF_T;
            } 

            // Exit the while loop and return whatever we have for token up to this point
            break;
        }

        // Shortcut to the current character to be evaluated
        c = line[pos];

        // Handle whitespace: if we're still at the starting state, then we can simply
        // loop through the whitespace until reaching a character.
        if (isspace(c) && token == START_T) {
    		pos++;
    		continue;
        }

        // Increment the position before beginning the next loop
        pos++;

        // Append the current character to the lexeme
        lexeme += c;

        // std::cout << "Read character: " << c << std::endl;

        // Cache the previous state in case we need to go back to it (i.e. GT_T vs GTE_T)
        token_type prevState = token;

        // Run the character through the DFA and get the state that we end up in
        token = LexicalAnalyzer::nextState(c, prevState);

        // std::cout << "DFA returned: " << token << std::endl;

        // If we reach an ERR_T but the previous state was final, we can return the
        // previous state.
        if (token == ERR_T) {

        	// If the state is final, return the previous state (otherwise, do nothing
        	// and return the ERR_T)
        	if (LexicalAnalyzer::isFinal(prevState)) {
        		
        		// Step the position counter backwards because this character we read
        		// is part of the next lexeme
        		pos--;

        		// Remove the character we appended to the lexeme for the same reason
        		// as above
        		lexeme.pop_back();

        		// Set the token to the previous state which was actually the end of
        		// the state
	            token = prevState;
        	}

        	// Exit the while loop and return the token
            break;
        }
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

    if (c >= 65 && c <= 90)
        cintval = c + 32;
    else if (isdigit(c))
        cintval = 50; // all digits are represented on the table as the same value
    // of 50, since all digits behave the same way lexically
    else
        cintval = (int)c;

    // std::cout << "Reading char " << cintval << std::endl;

    for (int i = 0; i < 41; i++) // 62 is the last row of the table, it stores ascii equivalents of the values
    {
        if (cintval == lexicalTable[62][i])
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

	// If the state we've reached is outside of the bounds of our table,
	// return an ERR_T. This signals to GetToken() to check if the state
	// it was previously in was final or not.
	if (currState > 61) return ERR_T;

	// std::cout << "Reading table row " << currState << " col " << col << std::endl;

    return static_cast<token_type>(lexicalTable[currState][col]);
}

bool LexicalAnalyzer::isFinal(token_type s)
{
	if (s > 61) return true;

	// int final[100] = {1, 3, 4, 5, 6, 7, 8, 9, 54, 55, 56, 57, 58, 59, 60, 61};

	// for (int i=0; i < 100; i++) {
	// 	if (s == final[i]) return true;
	// }

	return false;
}
