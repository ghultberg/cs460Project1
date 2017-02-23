#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	while ((t = lex->GetToken()) != EOF_T)
	{
		// get a token
		// write its name to the debug file
	  ofstream debug(
			 "TeamY.dbg", std::ios_base::out | std::ios_base::app );
	                   debug << t;
		// write the corresponding lexeme to the debug file
			   debug << lex <<endl;
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
