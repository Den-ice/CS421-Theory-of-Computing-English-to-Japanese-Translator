#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: ** 
//=====================================================

// --------- DFAs ---------------------------------

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:
// ** RE:
bool word (string s)
{
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0') 
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
}

// ** Add the PERIOD DFA here
// ** Done by:

// -----  Tables -------------------------------------

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, EOFM, PERIOD, WORD1, WORD2, VERB, VERBNEG, VERBPAST, VERBPASTNEG, 
		IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};

string tokenName[30] = {"PERIOD", "WORD1", "WORD2", "VERB", "VERBNEG", "VERBPAST",
			"VERBPASTNEG","IS", "WAS", "OBJECT", "SUBJECT","DESTINATION"
			"PRONOUN", "CONNECTOR" }; //for the display names oftokens - must be in the same order as the tokentype.

// ** Need the reservedwords table to be set up here. 
struct rt
{
  cont char* string;
  tokenType token;
}

// ** Do not require any file input for this.
// ** a.out should work without any additional files

//rt = reserved table
// has strings from file and tokent types
rt[] = {
  {"masi", VERB}, {"masen", VERBNEG}, {"mashita", VERBPAST}, {"mashendshita", VERBPASTNEG}
  {"desu", IS}, {"deshita", WAS}, {"o", OBJECT}, {"wa", SUBJECT}, {"ni", DESTINATION}, 
  {"watashi", PRONOUN}, {"anata", PRONOUN}, {"kare", PRONOUN}, {"kanojo", PRONOUN}, 
  {"mata", CONNECTOR}, {"soshite", CONNECTOR}, {"shikashi", CONNECTOR}, {"dakara", CONNECTOR}
};

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: 
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
  if(mytoken(w))
    {
      for (int i = 0; i < rowcounter; i++)
	{
	  if (w == rt[i].string)
	    {
	      a = rt[i].token;
	      return 0;
	    }
	}
      //find it token has a capital E or I
      char endofstring = ' '; endofstring = w[(w.length())-1];

      //checking for tokent type word1 and word2
      if(endofstring == 'I' || endofstring == 'E')
	{
	  a = WORD2;
	}
      else
	{
	  a = WORD1;
	}
    }
  //check period token
  else if (periodtoken(w))
    {
      a = PERIOD;
    }
  else if (w == "eofm")
    {}
  else //check if lexical error
    {
      cout << "LEXICAL ERROR: " << w << "is not a valid token \n";
      a = ERROR;
    }

  return 0;				   


}//the end of scanner



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

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

