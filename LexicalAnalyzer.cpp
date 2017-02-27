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
    allErrors = "";
    eofFlag = false;
    // This function will initialize the lexical analyzer class

    input.open(filename);

    if (input.fail()) {
        std::cerr << "Failed to open file '" << filename << "'" << std::endl;
        exit(1);
    }

    listing.open("TeamY.lst", std::ios_base::out);
    debug.open("TeamY.dbg", std::ios_base::out);

    std::getline(input, line);

    listing<<"Input file: "<<filename<<endl;
    debug<<"Input file: "<<filename<<endl;
    listing <<linenum<<": "<<line<<endl;
    debug<<linenum<<": "<<line<<endl;
    
}

LexicalAnalyzer::~LexicalAnalyzer()
{
  
  listing<<allErrors<<errors<<" errors found in input file"<<endl;
  debug<<errors<<" errors found in input file"<<endl;
  
  // This function will complete the execution of the lexical analyzer class
  listing.close();
  debug.close();
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

    char c;

    // If reading a lexeme and encountering EOF, return whatever the most recent state is
    while (!eofFlag) {
        // Break when reaching the end of the line
      if (pos >= line.length()) {
	linenum ++;
	if (std::getline(input, line))
	  {
	    pos = 0;
	    debug <<linenum<<": "<<line<<endl;
	    listing<<linenum<<": "<<line<<endl;
	  }
	else eofFlag = true;
      }

        // The current character being read
        c = line[pos];

        // Increment the position before beginning the next loop
        pos++;

        // Append the current character to the lexeme
        lexeme += c;

        std::cout << "Read character: " << c << std::endl;

        token_type prevState = token;

        // Break from the loop when encountering whitespace of any kind or EOF flag is set
        if (isspace(c) || c == 0) {
        	if (prevState != START_T) token = LexicalAnalyzer::nextState(c, prevState);
            break;
        }

        // Run the character through the DFA
        token = LexicalAnalyzer::nextState(c, prevState);
        std::cout << "DFA returned: " << token << std::endl;

        // If in a final state when the next token is ERR_T, return the previous token
        if (token == ERR_T) {
        	if (LexicalAnalyzer::isFinal(prevState)) {
        		std::cout << "Need to use prevstate" << std::endl;
        		pos--;
        		lexeme.pop_back();
	            token = prevState;
        	}
            break;
        }
    }

    // If there was a space at the end of the file
    if (token != 0) {
      debug<<"\t"<<lexeme<<"\t"<<token<<endl;
    	std::cout << "Lexeme is: " << lexeme << std::endl;
	std::cout << "Token is: " << token << std::endl;

	return token;
    } else {
    	std::cout << "Found end of file." << std::endl;
    	return EOF_T;
    }

    
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
  string err = "Error at "; err+=to_string(linenum); err+=","; err+=to_string(pos);
  err += ": "+msg+"\n";
  std::cout<< msg;
  debug<<err;
  allErrors +=err;
  errors++;
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
    string err = "Invald character found: "; err+=c;
    ReportError(err);
    return cintval;
}

token_type LexicalAnalyzer::nextState(char c, token_type currState)
{
	int col = ConvertCharToTableCol(c);

	if (currState >= 100) return ERR_T;

	std::cout << "Reading table row " << currState << " col " << col << std::endl;

    return static_cast<token_type>(lexicalTable[currState][col]);
}

bool LexicalAnalyzer::isFinal(token_type s)
{
	return (s > 61);
}
