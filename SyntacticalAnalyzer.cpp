#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{

  //creates the LexicalAnalyzer
  lex = new LexicalAnalyzer (filename);

}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{	
  delete lex;
}
