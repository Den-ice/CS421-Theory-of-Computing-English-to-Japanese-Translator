#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: **
//=====================================================

// --------- HELPER FUNCTIONS ---------------------
// Done By: Ivan Inandan
// Purpose: To simplify vowel / consanant checking

// Checks for vowel
// 'a' 'e' 'i' 'o' 'u' 'E' 'I'
// Done By: Ivan Inandan
bool vowelCheck(char input)
{
  if(input == 'a' || input == 'e' || input == 'i' || input == 'o' || input == 'u' || // Word 1
     input == 'E' || input == 'I') // Word 2
    return true;
  
  else
    return false;
}

// Checks for consonants able to start a consonant pair
// 'b' 'g' 'h' 'k' 'm' 'n' 'p' 'r'
// Done By: Ivan Inandan
bool consonantPairCheck(char input)
{
  if(input == 'b' || input == 'g' || input == 'h' || input == 'k' ||
     input == 'm' || input == 'n' || input == 'p' || input == 'r')
    return true;
  
  else
    return false;
}

// Checks for other consonants not able to start consonant pair
// 'd' 'j' 'w' 'y' 'z'
// Done By: Ivan Inandan
bool consonantCheck(char input)
{
  if(input == 'd' || input == 'j' || input == 'w' ||
     input == 'y' || input == 'z')
    return true;
  
  else
    return false;
}

// --------- STATE REFERENCE ----------------------
// State 0: q0 (starting state)
// State 1: qV (final state)
// State 2: qN (final state)
// State 3: qSA
// State 4: qY
// State 5: qS
// State 6: qC
// State 7: qT

// --------- DFAs ---------------------------------

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by: Ivan Inandan
// ** RE: (vowel | vowel n | consonant vowel | consonant vowel n |
//         consonant-pair vowel | consonant-pair vowel n) ^+

bool word(string s)
{
  int state = 0;//changed to string for parser program
  int charpos = 0;
  
  while (s[charpos] != '\0')
    {
      if(state == 0 && vowelCheck(s[charpos])) //q0 --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 0 && consonantCheck(s[charpos])) //q0 --> qSA (on consonant nonpair)
	state = 3;
      
      else if(state == 0 && consonantPairCheck(s[charpos])) //q0 --> qY (on consonant pair)
	state = 4;

      else if(state == 0 && s[charpos] == 's') //q0 --> qS (on 's')
	state = 5;
      
      else if(state == 0 && s[charpos] == 'c') //q0 --> qC (on 'c')
	state = 6;
      
      else if(state == 0 && s[charpos] == 't') //q0 --> qT (on 't')
	state = 7;
      
      else if(state == 1 && vowelCheck(s[charpos])) // qV --> qV (loop on vowel)
	state = 1; // Final State
      
      else if(state == 1 && s[charpos] == 'n') //qV --> qN (on 'n')
	state = 2; // Final state
      
      else if(state == 1 && consonantCheck(s[charpos])) //qV --> qSA (on consonant nonpair)
	state = 3;
      
      else if(state == 1 && consonantPairCheck(s[charpos])) //qV --> qY (on consonant pair)
	state = 4;

      else if(state == 1 && s[charpos] == 's') //qV --> qS (on 's')
	state = 5;
      
      else if(state == 1 && s[charpos] == 'c') //qV --> qC (on 'c')
	state = 6;
      
      else if(state == 1 && s[charpos] == 't') //qV --> qT (on 't')
	state = 7;
      
      else if(state == 2 && vowelCheck(s[charpos])) //qN --> qV (on vowel)
	state = 2; // Final State
      
      else if(state == 2 && s[charpos] == 'n') //qN --> qN (loop on 'n')
	state = 2;
      
      else if(state == 2 && consonantCheck(s[charpos])) //qN --> qSA (on consonant nonpair)
	state = 3;

      else if(state == 2 && consonantPairCheck(s[charpos])) //qN --> qY (on consonant pair)
	state = 4;
      
      else if(state == 2 && s[charpos] == 's') //qN --> qS (on 's')
	state = 5;
      
      else if(state == 2 && s[charpos] == 'c') //qN --> qC (on 'c')
	state = 6;
      
      else if(state == 2 && s[charpos] == 't') //qN --> qT (on 't')
	state = 7;

      else if(state == 3 && vowelCheck(s[charpos])) //qSA --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 4 && vowelCheck(s[charpos])) //qY --> qV (on owel)
	state = 1; // Final State

      else if(state == 4 && s[charpos] == 'y') //qY --> qSA (on 'y')
	state = 3;
      
      else if(state == 5 && vowelCheck(s[charpos])) //qS --> qV (on vowel)
	state = 1; // Final state
      
      else if(state == 5 && s[charpos] == 'h') //qS --> qSA (on 'h')
	state = 3;
      
      else if(state == 6 && vowelCheck(s[charpos])) //qC --> qV (on vowel)
	state = 1; // Final State
      
      else if(state == 6 && s[charpos] == 'h') //qC --> qSA (on 'h')
	state = 3;
      
      else if(state == 7 && vowelCheck(s[charpos])) //qT --> qV (on vowel)
	state = 1; // Final State

      else if(state == 7 && s[charpos] == 's') //qT --> qSA (on 's')
	state = 3;

      else // Stuck in a state
	return false;
      
      charpos++;
    }//end of while
  
  // where did I end up????
  if (state == 1 || state == 2) // Final States
    return(true);  // end in a final state
  
  else // Otherwise not in final state
    return(false);
}

// Checks to see if word ends in vowel lower case                                         // Done By: Ivan Inandan                
bool checkWord1(string s)
{
  if(word(s)==true)
    {
      char lastCharacter = s[s.length() - 1];

      //char seclastCharacter = s[s.length()-2];
      
      if(lastCharacter == 'a' || lastCharacter == 'e' || lastCharacter == 'i' ||
         lastCharacter == 'o' || lastCharacter == 'u')
        return true;
      //else if (lastCharacter == 'n')
      //  if(seclastCharacter == 'a' || seclastCharacter == 'e' ||
      //   seclastCharacter == 'i' || seclastCharacter == 'o' || seclastCharacter == 'u')
      //  return true;
      else
        return false;
    }
}

// Checks to see if word ends in 'E' or 'I'                                                                      
// Done By: Ivan Inandan
bool checkWord2(string s)
{
  if(word(s)==true)
    {
      char lastCharacter = s[s.length() - 1];

      if(lastCharacter == 'E' || lastCharacter == 'I')
        return true;

      else
        return false;
    }
}

// ** Add the PERIOD DFA here
// ** Done by: Ivan Inandan
bool periodtoken(string s)
{
  if(s == ".")
    return true;
  
  else
    return false;
}

// -----  Tables -------------------------------------
//Done by: Denice Hickethier
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {VERB, 
		VERBNEG, 
		VERBPAST, 
		VERBPASTNEG,
                IS,
		WAS,
		OBJECT, 
		SUBJECT, 
		DESTINATION, 
		PRONOUN, 
		CONNECTOR, 
		WORD1, 
		WORD2,
		PERIOD, 
		EOFM, 
		ERROR};

string tokenName[30] = {"VERB", 
			"VERBNEG", 
			"VERBPAST", 
			"VERBPASTNEG",
			"IS", 
			"WAS", 
			"OBJECT", 
			"SUBJECT", 
			"DESTINATION", 
			"PRONOUN", 
			"CONNECTOR",
			"WORD1",
			"WORD2", 
			"PERIOD", 
			"EOFM", 
			"ERROR"};
//for the display names of tokens - must be in the same order as the tokentype.

// ** Need the reservedwords table to be set up here.
struct rt
{
  const char* string;
  tokentype token;
}

// ** Do not require any file input for this.
// ** a.out should work without any additional files
  
//rt = reserved table
// has strings from file and tokent types
  rt[] = {
    //Verb Markers
    {"masu", VERB},
    {"masen", VERBNEG},
    {"mashita", VERBPAST},
    {"masendshita", VERBPASTNEG},
    {"desu", IS},
    {"deshita", WAS},
    //Particles
    {"o", OBJECT},
    {"wa", SUBJECT},
    {"ni", DESTINATION},
    //Pronouns
    {"watashi", PRONOUN}, //(I/me)
    {"anata", PRONOUN}, //(you)
    {"kare", PRONOUN}, //(he/him)
    {"kanojo", PRONOUN},//(she/her)
    {"sore", PRONOUN}, //(it)
    //Connectors
    {"mata", CONNECTOR}, //(Also)
    {"soshite", CONNECTOR}, //(Ho)
    {"shikashi", CONNECTOR},//(However)
    {"dakara", CONNECTOR} //(Therefore)
  };


// ------------ Scaner and Driver -----------------------

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself

// Done by: Denice Hickethier
int scanner(tokentype& a, string& w)
{

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  fin >> w;
  /*
  2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.

  3. Then, make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.

  4. Return the token type & string  (pass by reference)
  */
  
  int rowcounter = sizeof rt/ sizeof rt[0];
  
  //call token function
  if( checkWord1(w) || w == "gohan")
    {
      a = WORD1;
    }
  
  else if(checkWord2(w))
    {
      a = WORD2;
    }
  
  //check period token
  else if( periodtoken(w))
    {
      a = PERIOD;
    }
  else //lexical error if failed both DFAs
    {
      cout << "LEXICAL ERROR: " << w << " is not a valid token \n";
      a = ERROR;
    }

  if(a == WORD1 || a == WORD2)
    {
      for(int i = 0; i < rowcounter+1; i++)
        {
          if(w == rt[i].string)
            a = rt[i].token;
	}
    }

  return 0;
}//the end of scanner
/*
// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  while (true)
    {
      scanner(thetype, theword);  // call the scanner
      if (theword == "eofm") break;  // stop now
       
      cout << "\n";
      cout << "Type is:" << tokenName[thetype] << endl;
      cout << "Word is:" << theword << endl;
      cout << "\n";
    }

  cout << "End of file is encountered." << endl;
  fin.close();

}// end
*/
/*
##########################################################################################
##########################################################################################
##########################################################################################
*/
// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp . and do
// cat scanner.cpp parser.cpp > myparser.cpp
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: 12
//=================================================

// ----- Utility and Globals -----------------------------------

tokentype saved_token;
string saved_lexeme;
bool token_here = false;

//story
void s();
void after_subject();

void after_noun();
void after_Object();
void noun();

void verb();
void be();
void tense();


// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by: 
//exit(1) is for halting

//Done by: Denice Hickethier
void syntax_error1(tokentype correct, string saved_lexeme)
{
  cout << "SYNTAX ERROR: expected " << tokenName[correct] << ", yet found " << saved_lexeme << endl;
  exit (1);
}

//Done by: Denice Hickethier
void syntax_error2(string saved_lexeme, string pfunction)
{
  cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " located in " << pfunction << endl;
  exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by: Ivan Inandan

// Next Token Function
// Done By: Ivan Inandan
tokentype next_token()
{
  // bool tokenFlag = token_here();

  if(!token_here)// If no token exists
    {
      scanner(saved_token, saved_lexeme);// Calls scanner to advance token
      cout << "Scanning: " << saved_lexeme << endl;
      token_here = true;
    }

  return saved_token;
}

//Done by: Ivan Inandan
bool match(tokentype searchToken)
{
  // tokentype nextToken = next_token();

  if(next_token() != searchToken)// Mismatch
    {
      syntax_error1(searchToken, saved_lexeme);// Syntax Error due to mismatch
    }
  else // Match
    {
      cout << "Match occured: " << tokenName[searchToken] << endl; // Display token type
      token_here = false;// Advance token
      return true; // Match occurred
    }
}


// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

/*
Grammar: <story> ::= <s>{<s>}
Done by: Denice Hickethier
*/

void story()
{
  cout << "Processing: <story> \n";
  s();
  while((true) && (saved_lexeme != "eofm"))
    {
      s();
    }
  cout << "\nStory was successfully parsed!\n";
}

/*
Grammar: <s> ::= [CONNECTOR] 
Done by: Denice Hickethier
*/

void s()
{
  next_token();
  if(saved_lexeme != "eofm")
    {
      cout << "Processing: <s> \n";

      if(next_token() == CONNECTOR)
	{
	  match(CONNECTOR);
	}
      noun();
      match(SUBJECT);
      after_subject();
    } 
  else
    {
      cout << "\nDid not get through!\n";
    }
}

/*
Grammar: <after subject> ::= <verb> <tense> PEROD | <noun> <after noun>
Done by: Denice Hickethier
*/

void after_subject()
{
  cout << "Processing: <after_subject> \n";
  switch(next_token())  // Grab next token                                        
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      after_noun();
      break;
    case PRONOUN:
      noun();
      after_noun();
      break;
    default:
      syntax_error2(saved_lexeme, "after subject");    
    }
}

/*
Grammar: <after object> ::= <verb> <tense> PERIOD |<noun> DESTINATION <verb> <tense> PERIO\
D
Done by: Denice Hickethier
*/

void after_object()
{
  cout<<"Processing: <after_object> \n";

  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    default:
      syntax_error2(saved_lexeme, "after object");
    }
}

/*
Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD| OBJECT <after object>
Done by: Denice Hickethier
*/

void after_noun()
{
  cout << "Processing: <after_noun> \n";
  
  switch(next_token())  // Grab next token       
    {
    case IS:
      be();
      match(PERIOD);
      break;

    case WAS:
      be();
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      after_object();
      break;

    default:
      syntax_error2(saved_lexeme, "after noun"); 
    }
  
}

/*
Grammar: <noun> ::= WORD1 | PRONOUN 
Done by: Denice Hickethier
*/

void noun()
{
  cout << "Processing: <noun> \n";
  switch(next_token())  // Grab next token
    {
    case  WORD1:
      match(WORD1);
      break;

    case  PRONOUN:
      match(PRONOUN);
      break;

    default:
      syntax_error2(saved_lexeme, "noun"); 
    }
}

/*
Grammar: <verb> ::= WORD2
Done by:Ivan Inandan
*/

void verb()
{
  cout << "Processing: <verb>" << endl;

  switch(next_token())// Grab next token
    {
    case WORD2:
      match(WORD2);
      break;
      
    default:
      syntax_error2(saved_lexeme, "verb");
    }
}

/*
Grammar: <be> ::= IS | WAS
Done by: Ivan Inandan
*/

void be()
{
  cout << "Processing: <be>" << endl;

  switch(next_token())// Grab Next Token
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;
      
    default:
      syntax_error2(saved_lexeme, "be");
    }
}

/*
Grammar: <tense> ::= VERB | VERBPAST | VERBNEG | VERBPASTNEG
Done by:Ivan Inandan
*/
void tense()
{
  cout << "Processing: <tense>" << endl;

  switch(next_token())// Grab Next Token
    {
    case VERB:
      match(VERB);
      break;

    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;      

    default:
      syntax_error2(saved_lexeme, "tense");
    }
}


//---------------------------------------

// The new test driver to start the parser
// Done by:  Denice Hickethier
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
   story();

  //** closes the input file 
   fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages

