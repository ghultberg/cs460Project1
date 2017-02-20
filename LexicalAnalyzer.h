#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {
	ERR_T 		=  -1,
	QUOTE_T		= 101,
	LPAREN_T	= 102,
	RPAREN_T	= 103,
	MULT_T		= 104,
	PLUS_T		= 105,
	MINUS_T		= 106,
	DIV_T			= 107,
	LT_T			= 108,
	LTE_T			= 109,
	GT_T			= 110,
	GTE_T			= 111,
	NUMLIT_T	= 112,
	LISTOP_T	= 113,
	IDENT_T		= 114,
	CONS_T		= 115,
	IF_T			= 116,
	WHILE_T		= 117,
	AND_T			= 118,
	OR_T			= 119,
	NOT_T			= 120,
	DEFINE_T	= 121,
	NUMBERP_T	= 122,
	SYMBOLP_T	= 123,
	LISTP_T		= 124,
	ZEROP_T		= 125,
	NULLP_T		= 126,
	CHARP_T		= 127,
	STRINGP_T	= 128,
	EOF_T			= 129,
	EQUALTO_T	= 130
};

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
    private:
	ifstream input;
	ofstream listing;
	ofstream debug;
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
};
	
#endif
