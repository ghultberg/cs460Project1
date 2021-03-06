#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

enum token_type {
	ERR_T 		=  -1,
	START_T   =   0,
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
	ofstream p1;
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
	string allErrors;
	bool eofFlag;
	string GetFilename(const char *);
	std::map<token_type, std::string> tokenMap;

	bool isFinal(token_type);
	int ConvertCharToTableCol(char);

	token_type nextState(char, token_type);

	int lexicalTable[69][41] = {{	START_T	,	QUOTE_T	,	LPAREN_T	,	RPAREN_T	,	MULT_T	,	1	,	9	,	2	,	DIV_T	,	3	,	7	,	EQUALTO_T	,	8	,	11	,	10	,	47	,	13	,	10	,	10	,	10	,	10	,	18	,	10	,	10	,	19	,	10	,	23	,	32	,	10	,	10	,	10	,	33	,	10	,	10	,	10	,	39	,	10	,	10	,	43	,	ERR_T	,	10	},
{	PLUS_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	2	,	ERR_T	,	3	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	5	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	NUMLIT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	4	,	ERR_T	,	5	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	NUMLIT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	4	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	NUMLIT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	4	,	ERR_T	,	5	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	LT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	LTE_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	GT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	GTE_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	MINUS_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	2	,	ERR_T	,	3	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	11	,	12	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	57	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	14	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	15	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	16	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	17	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	58	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	59	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	20	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	21	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	22	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	LISTP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	24	,	10	,	10	,	10	,	10	,	10	,	25	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	60	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	30	,	26	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	27	,	27	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	28	,	28	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	29	,	29	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	NUMBERP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	31	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	NULLP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	56	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	62	,	34	,	10	,	10	,	10	,	10	,	62	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	35	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	36	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	37	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	38	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	STRINGP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	40	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	41	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	42	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	61	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	44	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	45	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	46	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	ZEROP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	51	,	10	,	10	,	51	,	10	,	10	,	10	,	48	,	10	,	10	,	10	,	10	,	10	,	10	,	52	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	49	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	50	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	CHARP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	51	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	55	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	53	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	CONS_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	LISTOP_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	OR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	AND_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	DEFINE_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IF_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	NOT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	WHILE_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	63	,	10	,	10	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	64	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	65	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	66	,	10	,	10	,	10	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	SYMBOLP_T	,	10	},
{	IDENT_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	ERR_T	,	ERR_T	,	ERR_T	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	54	,	10	,	10	,	10	,	10	,	10	,	10	,	10	,	IDENT_T	,	10	},
{	32	,	39	,	40	,	41	,	42	,	43	,	45	,	46	,	47	,	50	,	60	,	61	,	62	,	97	,	98	,	99	,	100	,	101	,	102	,	103	,	104	,	105	,	106	,	107	,	108	,	109	,	110	,	111	,	112	,	113	,	114	,	115	,	116	,	117	,	118	,	119	,	120	,	121	,	122	,	63	,	-1	}};

};
#endif
