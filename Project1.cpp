#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"

/*
  CS 460 Project 1
  Team Y
  Daniel Hartman, Eric Mantooth, Greg Hultberg
  This program uses a lexical analyzer to parse a .ss file into strings. These strings are then
  (without delimiting whitespace) converted into token types, denoted in the LexicalAnalyzer.h
  file.
 */
int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
	SetLimits ();
	//creates a Syntactical Analyzer. This is not the same as a Lexical Analyzer,
	//and it is used to create the Lexical Analyzer.
	SyntacticalAnalyzer parser (argv[1]);

	return 0;
}
