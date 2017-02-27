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
    p1.open("TeamY.p1", std::ios_base::out);

    std::getline(input, line);
    line += ' ';

    listing<<"Input file: "<<filename<<endl;
    debug<<"Input file: "<<filename<<endl;
    listing <<linenum<<": "<<line<<endl;
    debug<<linenum<<": "<<line<<endl;

    tokenMap = {
        {ERR_T,"ERR_T"},
        {START_T,"START_T"},
        {QUOTE_T,"QUOTE_T"},
        {LPAREN_T,"LPAREN_T"},
        {RPAREN_T,"RPAREN_T"},
        {MULT_T,"MULT_T"},
        {PLUS_T,"PLUS_T"},
        {MINUS_T,"MINUS_T"},
        {DIV_T,"DIV_T"},
        {LT_T,"LT_T"},
        {LTE_T,"LTE_T"},
        {GT_T,"GT_T"},
        {GTE_T,"GTE_T"},
        {NUMLIT_T,"NUMLIT_T"},
        {LISTOP_T,"LISTOP_T"},
        {IDENT_T,"IDENT_T"},
        {CONS_T,"CONS_T"},
        {IF_T,"IF_T"},
        {WHILE_T,"WHILE_T"},
        {AND_T,"AND_T"},
        {OR_T,"OR_T"},
        {NOT_T,"NOT_T"},
        {DEFINE_T,"DEFINE_T"},
        {NUMBERP_T,"NUMBERP_T"},
        {SYMBOLP_T,"SYMBOLP_T"},
        {LISTP_T,"LISTP_T"},
        {ZEROP_T,"ZEROP_T"},
        {NULLP_T,"NULLP_T"},
        {CHARP_T,"CHARP_T"},
        {STRINGP_T,"STRINGP_T"},
        {EOF_T,"EOF_T"},
        {EQUALTO_T,"EQUALTO_T"}, 
  };
    
}

LexicalAnalyzer::~LexicalAnalyzer()
{
  
  listing<<allErrors<<errors<<" errors found in input file"<<endl;
  debug<<errors<<" errors found in input file"<<endl;
  
  // This function will complete the execution of the lexical analyzer class
  listing.close();
  debug.close();
  input.close();
  p1.close();
}

token_type LexicalAnalyzer::GetToken()
{
    // This function will find the next lexeme int the input file and return
    // the token_type value associated with that lexeme

    if (eofFlag) return EOF_T;

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
        		linenum++;
        		debug <<linenum<<": "<<line<<endl;
        		listing<<linenum<<": "<<line<<endl;
            }

            // Otherwise, we must have reached the end of the file
            else {
            	eofFlag = true;

            	// If we reached the end of the file and we're still at START_T, then there
            	// was trailing whitespace so we can simply return EOF_T
            	if (token == START_T) return EOF_T;
            } 

            // Exit the while loop and return whatever we have for token up to this point
            if (token != START_T) break;
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

        // Cache the previous state in case we need to go back to it (i.e. GT_T vs GTE_T)
        token_type prevState = token;

        // Run the character through the DFA and get the state that we end up in
        token = LexicalAnalyzer::nextState(c, prevState);

        // If we reach an ERR_T but the previous state was final, we can return the
        // previous state.
        if (token == ERR_T) {

            // std::cout << "previous token was: " << int(line[pos - 1]) << std::endl;
            // std::cout << "current token is: " << int(c) << std::endl;

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
        	} else if (prevState == 1 || prevState == 7 || prevState == 8 || prevState == 9) {
                pos--;
                lexeme.pop_back();

                // Hack to simulate a space after characters with intermediate-final
                // states when reaching ERR_T. This is needed because of the way the
                // table is designed: we can't always assume states like PLUS_T will
                // always have either a number or a space after them, so if an error
                // is encountered while in state 1, for example, we need to check if
                // it was possibly a final state and treat it as if a space followed.
                token = static_cast<token_type>(lexicalTable[prevState][0]);
            }

        	// Exit the while loop and return the token
            break;
        }
    }

    if (token == ERR_T) {
        //Write an error report with ReportError
        std::string err = "Invalid character found: "; err+=c;
        ReportError(err);
    }
      
    debug<<"\t"<<lexeme<<"\t"<<LexicalAnalyzer::GetTokenName(token)<<endl;
    p1 << LexicalAnalyzer::GetTokenName(token) << ' ' << LexicalAnalyzer::GetLexeme() << std::endl;

    return token;
}

string LexicalAnalyzer::GetTokenName(token_type t) const
{
    // The GetTokenName function returns a string containing the name of the
    // token passed to it.
    return tokenMap.at(t);
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
  std::cout<< msg<<endl;
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

    for (int i = 0; i < 41; i++) // 62 is the last row of the table, it stores ascii equivalents of the values
    {
        if (cintval == lexicalTable[68][i])
            return i;
    }
    //string err = "Invald character found: "; err+=c;
    //ReportError(err);
    return cintval;
}

token_type LexicalAnalyzer::nextState(char c, token_type currState)
{
	int col = ConvertCharToTableCol(c);

	// If the state we've reached is outside of the bounds of our table,
	// return an ERR_T. This signals to GetToken() to check if the state
	// it was previously in was final or not.
	if (currState > 99) return ERR_T;

    return static_cast<token_type>(lexicalTable[currState][col]);
}

bool LexicalAnalyzer::isFinal(token_type s)
{
	return (s > 66);
}
