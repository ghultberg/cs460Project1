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
	  //removed all writes to debug, those are done in LexicalAnalyzer
	}
}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	
	delete lex;
}
