#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;

	debug.open("TeamY.dbg", std::ios_base::out);

	while ((t = lex->GetToken()) != EOF_T)
	{
		// get a token
		// write its name to the debug file
    debug << t << " : ";

		// write the corresponding lexeme to the debug file
		debug << lex->GetLexeme() << std::endl;
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	debug.close();
	delete lex;
}
