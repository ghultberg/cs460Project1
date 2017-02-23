#include <iomanip>
#include <cstdlib>
#include <ctype.h>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T" }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
  linenum = 1;
  pos = 0;
  errors = 0;
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme

	// Reset 'lexeme' in preparation for finding the next token
	lexeme = "";

	// If for some reason we can't find a token, default to ERR_T
	token = ERR_T;

	// TODO: wrap with a while loop w/ getline()
	std::string line = "car cdr";

	char c;
	int table_map;

	while (true)
	{

		// Break when reaching the end of the line
		if (pos >= line.length()) {
			pos = 0;
			break;
		}

		// The current character being read
		c = line[pos];

		// Run the character through the DFA

		/*
			token_type result = runDFA(table_map);
			if (result == -1) {
				
				// If not in a final state already, return an error
				if (token < 100 || token > 199) {
					token = result;
					break;

				// Otherwise, return the current token type and back up one character
				} else {
					pos--;
					break;
				}
			}

		*/

		// Break from the loop when encountering whitespace of any kind
		if (isspace(c)) {
			pos++;
			break;
		}

		// Append the current character to the lexeme
		lexeme += c;

		// Increment the position before beginning the next loop
		pos++;
	}

	// For now since we don't have multiple lines to test with
	return EOF_T;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return "";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}
