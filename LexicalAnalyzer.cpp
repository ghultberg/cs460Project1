#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T" }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
  ifstream input = "";
  ofstream listing = "";
  ofstream debug = "";
  token_type token = 0;
  string line;
  int linenum = 0;
  int pos = 0;
  string lexeme;
  int errors = 0;
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme

  while (std::getline(input, input))
    {
      static const char space[] = " \t";
    }
  if (input.length() == 0)
    {
      continue;
    }
  pos =  input.//find_first_not_of(white_space, 0);

  if ((position == std::string::npos)
      {
	continue; // Blank line.
      }
    if (std::isalpha(input_text[position]))
      {
	// First character is a letter.
	// Find the end of the identifier.
	/*
	std::string::size_type identifier_end_posn = 0;
	identifier_end_posn = input.find_first_not_of(identifier_letters, position);
	if (identifier_end_posn != std::string::npos)
	  {
	    const int identifier_length = identifier_end_posn - position + 1;
	    std::string identifier = input_text.substr(position, identifier_length);
	    cout << identifier << "\n";
	    continue;
	  }
      }
	*/
	return token;
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
