/* Andy Pat
   CSE 340
   February 11, 2013
   Project 1
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
using namespace std;

// Preprocessor Macros
// Used to access outputTypes array to print type
#define RESERVED 1
#define INTEGER 2
#define FLOAT 3
#define MATH 4
#define COMPARISON 5
#define SHIFT 6
#define GROUPING 7
#define IDENTIFIER 8
#define ERROR0 9
#define ERROR1 10


// Array with all the keywords for comparison
string keywords[27] =
{
    "begin",
    "end",
    "if",
    "then",
    "for",
    "while",
    "print",
    "int",
    "float",
    ".",
    "+",
    "-",
    "*",
    "/",
    "=",
    ">",
    "<",
    ">=",
    "<=",
    ">>",
    "<<",
    "{",
    "}",
    "{}",
    "[",
    "]",
    "[]"
};

// Array of possible output for the token types
string outputTypes[11] =
{
    "",
    "reserved word",
    "integer",
    "float",
    "math operator",
    "comparison operator",
    "shift operator",
    "grouping operator",
    "identifier",
    "ERROR CODE 0: Lexical error: invalid character found in token",
    "ERROR CODE 1: Lexical error: token not valid in language"
};

// Global Variables
string token; // Stores the token being read currently
int totype; // Stores the token type to access outputTypes array

/*
    Helper function to display ERROR CODE 0.
    Takes a character c read in from file as parameter.
*/
int e0(char c)
{
    // Check and add characters until a whitespace
    while(!feof(stdin) && !isspace(c))
    {
        token += c;
        c = getchar();
    }
    return ERROR0;
}

/*
    Helper function to check the rest of the string for invalid characters or
    read in the rest of the token until the delimiter white space. Will output
    ERROR CODE 1 or call e0. Takes a character c read in from file as parameter.
*/
int getError(char c)
{
    stringstream ss;
    string s;
    // Check and add characters until a whitespace
    while(!feof(stdin) && !isspace(c))
    {
        // Do the following for non-alpha and non-digit character
        if(!isalpha(c) && !isdigit(c))
        {
            bool value = false;
            for(int i = 0; i < 27; i++)
            {
                ss << c;
                ss >> s;
                // Compare character with everyone keyword
                if(s == keywords[i])
                {
                    // Set to true if c is a valid character
                    value = true;
                }
            }
            if(value == true)
            {
                token += c;
                c = getchar();
            }
            else
            {
                // c is an invalid character, call e0 to throw error code 0
                token += c;
                c = getchar();
                return e0(c);

            }
        }
        // character is an alpha or digit character
        else
        {
            token += c;
            c = getchar();
        }
    }
    // Reached a whitespace and did not throw error code 0
    // Print error code 1
    return ERROR1;
}

/*
    Skips whitespace until a character is read. Uses switch case to determine
    the token type based on the first character read.
*/
int getToken()
{
    char c;
    c = getchar();
    // While it is a white space, continue reading until no white space
    while(!feof(stdin) && isspace(c))
    {
        c = getchar();
    }

    switch(c)
    {
        case '.':
            // Add . to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            // Check for if it is whitespace or end of file (we do not want EOF to append to token)
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the . and its math operator type
                return MATH;
            }

            while(!isspace(c))
            {
                if(isdigit(c))
                {
                    // Add the digit to the token string
                    token += c;
                    // Read next character
                    c = getchar();
                }
                else if(c == EOF)
                {
                    // Since it passed the first if statement, then the token cannot be just .
                    // To reach this point, at least one digit must follow, since if it was
                    // a letter or symbol, getError would be called. We can assume that it's a FLOAT.
                    return FLOAT;
                }
                else if(isalpha(c))
                {
                    // An alpha character comes after the .
                    // Call getError
                    return getError(c);
                }
                else
                {
                    // There is either a symbol or invalid character following the .
                    // Call getError
                    return getError(c);
                }

            }
            // Did not return any of the other token types, so token must be FLOAT
            return FLOAT;
        case '+':
            // Add + to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the + and it's math operator type
                return MATH;
            }
            // if did not return, then call getError function
            return getError(c);
        case '-':
            // Add - to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the - and it's math operator type
                return MATH;
            }
            // if did not return, then call getError function
            return getError(c);
        case '*':
            // Add * to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the * and it's math operator type
                return MATH;
            }
            // if did not return, then call getError function
            return getError(c);
        case '/':
            // Add / to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the / and it's math operator type
                return MATH;
            }
            // if did not return, then call getError function
            return getError(c);
        case '=':
            // Add = to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the = and it's math operator type
                return MATH;
            }
            // if did not return, then call getError function
            return getError(c);
        case '>':
            // Add > to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the > and it's comparison operator type
                return COMPARISON;
            }
            else if(c == '=')
            {
                // Add = to token string to form >=
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the >= and it's comparison operator type
                    return COMPARISON;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            else if(c == '>')
            {
                // Add > to token string to for >>
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the >> and it's shift operator type
                    return SHIFT;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            // if did not return, then call getError function
            return getError(c);
        case '<':
            // Add < to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the < and it's comparison operator type
                return COMPARISON;
            }
            else if(c == '=')
            {
                // Add = to token string to form <=
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the <= and it's comparison operator type
                    return COMPARISON;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            else if(c == '<')
            {
                // Add < to token string to for <<
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the << and it's shift operator type
                    return SHIFT;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            // if did not return, then call getError function
            return getError(c);
        case '{':
            // Add { to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the { and it's grouping operator type
                return GROUPING;
            }
            else if(c == '}')
            {
                // Add } to token string to form {}
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the {} and it's grouping operator type
                    return GROUPING;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            // if did not return, then call getError function
            return getError(c);
        case '}':
            // Add } to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the } and it's grouping operator type
                return GROUPING;
            }
            // if did not return, then call getError function
            return getError(c);
        case '[':
            // Add [ to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the [ and it's grouping operator type
                return GROUPING;
            }
            else if(c == ']')
            {
                // Add ] to token string to form []
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();
                if(c == EOF || isspace(c))
                {
                    // If the character is a whitespace, then return the [] and it's grouping operator type
                    return GROUPING;
                }
                // if did not return, then call getError function
                return getError(c);
            }
            // if did not return, then call getError function
            return getError(c);
        case ']':
            // Add ] to token string
            token += c;
            // Get next character until a whitespace is encountered
            c = getchar();
            if(c == EOF || isspace(c))
            {
                // If the character is a whitespace, then return the ] and it's grouping operator type
                return GROUPING;
            }
            // if did not return, then call getError function
            return getError(c);
        default :
            // Starts with a digit, could be an INTEGER or FLOAT
            if (isdigit(c))
            {
                // Add the digit to token string
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();

                if(isspace(c))
                {
                    // If the character is a whitespace, then return the digit and it's integer type
                    return INTEGER;
                }

                while(!isspace(c))
                {
                    if(isdigit(c))
                    {
                        // Add the digit to the token string
                        token += c;
                        // Read next character
                        c = getchar();
                    }
                    else if(c == EOF)
                    {
                        // End file reached. Token string must be of form [0-9]*
                        return INTEGER;
                    }
                    else if(c == '.')
                    {
                        // A . comes after the digit
                        // Check if possible FLOAT
                        // Add . to the token string
                        token += c;
                        // Read next character
                        c = getchar();

                        if(isspace(c))
                        {
                            // If the character is a whitespace, then the token is [digit]*.
                            // which is not valid token, so call getError
                            return getError(c);
                        }

                        while(!isspace(c))
                        {
                            if(isdigit(c))
                            {
                                // Add the digit to the token string
                                token += c;
                                // Read next character
                                c = getchar();
                            }
                            else if(c == EOF)
                            {
                                // End file reached. Token string must be of form [0-9]*.[0-9]*
                                return FLOAT;
                            }
                            else
                            {
                                // There is either a symbol, invalid character, letter,
                                // or another . following [digit]*. Call getError.
                                return getError(c);
                            }
                        }
                        // No Error returned, so token must be of form
                        // [digit]*.[digit]* which is a FLOAT
                        return FLOAT;
                    }
                    else
                    {
                        // There is either a symbol, invalid character, or letter following digit.
                        // Call getError
                        return getError(c);
                    }

                }
                // No Error returned, so token must be of form
                // [digit]* which is an INTEGER
                return INTEGER;
            }
            // Starts with a letter, could be a RESERVED or IDENTIFIER
            else if (isalpha(c))
            {
                // Add the letter to token string
                token += c;
                // Get next character until a whitespace is encountered
                c = getchar();

                if(isspace(c))
                {
                    // If the character is a whitespace, then return the letter and it's identifier type
                    return IDENTIFIER;
                }

                while(!isspace(c))
                {
                    if(isalpha(c) || isdigit(c))
                    {
                        // Add the letter or digit to the token string
                        token += c;
                        // Read next character
                        c = getchar();
                    }
                    else if(c == EOF)
                    {
                        // No Error returned, so token must be of form
                        // [A-Za-z][A-Za-z0-9]* or a reserved word
                        for(int i = 0; i < 9; i++)
                        {
                            if(token == keywords[i])
                            {
                                return RESERVED;
                            }
                        }
                    // Did not return RESERVED, so token must be an indentifier
                    return IDENTIFIER;
                    }
                    else
                    {
                        // There is either a symbol or invalid character following the letter or digit
                        // Call getError
                        return getError(c);
                    }
                }
                // No Error returned, so token must be of form
                // [A-Za-z][A-Za-z0-9]* or a reserved word
                for(int i = 0; i < 9; i++)
                {
                    if(token == keywords[i])
                    {
                        return RESERVED;
                    }
                }
                // Did not return RESERVED, so token must be an indentifier
                return IDENTIFIER;
            }
            // Reached end of file
            else if (c == EOF)
                return EOF;
            // Must be a symbol, either valid or invalid; will return an error code
            else
                return getError(c);
    }
}

/*
    Main. Gets tokens and token type and writes it to output file.
*/
int main()
{
    int totype = 0;
    // Get the token type from getToken function
    totype = getToken();
    // Write to output as long as token type is not end of file
    while(totype != EOF)
    {
        // Outputs token and its type to the output file
        cout << token + " " + outputTypes[totype] << endl;
        // Reset token to nothing
        token = "";
        // Get next token and its type
        totype = getToken();
    }
}
