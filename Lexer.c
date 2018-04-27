/*
Jacob Alderink
CS 210
Dr. Michael Wilder
Lexer.c

./a.out *filename.ccx*
^
|
|
outputs the lexemes of a program to standard output


The goal of this program is to be a Lexer program. In other words the goal of the program is to split the program into the separate meaningful components, or Lexemes.

The Program is organized by taking one character at a time, and then placing that character into a function named analyze where it is sent to another function
according to the character that was inputted;

it then analyzes the character and subsequent characters and prints it out, as well as what type of lexeme it is.

It parses the lexemes of the fake language CCX
This is a sort of manual version of what the UNIX tool flex does 

Started: August 28 2017
Last Edited: September 9 2017
*/
#include <bool.h>
#include <stdio.h>
#include <string.h> //strcmp line 330

void CaseOfForwardAngle( int z, FILE *f2);
void Analyze(int z, FILE *f2);
void CaseOfOperator( int z, FILE *f2);
void CaseOfCharLiteral( int z, FILE *f2);
void CaseOfString( int z, FILE *f2);
void CaseOfUpperCaseLetter(int z, FILE *f2);
void CaseOfNumerLiteral(int z,FILE *f2);
void CaseOfLowerCaseLetter(int z, FILE *f2);


int main ( int argc, char *argv[]){		//takes an input from the command line.
	
  FILE *f1 = fopen ( argv[1] , "r");	//opens the file specified in the command line. 
  if(argc != 2){
    printf("No file was passed in command line");
    return 0;
		
  }
	
  if( f1 == NULL ){	//test to see if the File was opened correctly, if the file was not opened correctly it would be an empty file.
    //fclose(f1);
	
    printf("file is empty");
  }
  else{
    int x;
    while( ( x = fgetc( f1))!=EOF){ //takes first character and places into an integer.
      Analyze( x, f1);
			
    }
	
  }
  fclose(f1);
  return 0;
}

void Analyze(int z, FILE *f2){
		
  if( z == '/' )
    {
      CaseOfForwardAngle(z, f2);
    }
  else if(( z == '.') || (z =='<') || (z == '>') || (z== '(') || (z==')') || (z=='+') || (z=='-') || (z=='*') || (z=='|') || (z=='&') || (z==';') || (z==',') || (z==':') || (z=='[') || (z==']') || (z=='=') || (z=='!'))
    {
      CaseOfOperator(z, f2);
    }
  else if(z == '\'')
    {
      CaseOfCharLiteral(z, f2);
    }
  else if(z == '"')
    {
      CaseOfString(z,f2);
    }
  else if(z >= 'A' && z <= 'Z')
    {
      CaseOfUpperCaseLetter(z, f2);
    }
  else if ( z>= 'a' && z <= 'z')
    {
      CaseOfLowerCaseLetter(z, f2);
    }
  else if(z >= '0' && z <= '9')
    {
      CaseOfNumerLiteral(z,f2);
    }
}



void CaseOfOperator( int z, FILE *f2){
  if(z == ':')
    {
      int temp = fgetc( f2);
      
      if(temp == '='){
	printf("%c", z);
	printf("%c", temp); // if the operator inputted was := then it outputs := (operator) and ends the function
	printf(" (operator)\n");
      }
		
      else{
	printf("%c",z);
	printf(" (operator)\n"); //if the operator was just : and = wasnt the next character it prints : (operator) and then passes the next cahracter into the analyze function.
	Analyze(temp,f2);
      }
    }
  else if(z == '=')
    {
      int temp = fgetc( f2);
			
      if(temp == '>'){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }
			
      else{
	printf("%c",z);
	printf(" (operator)\n");
	Analyze(temp,f2);
      }
    }
	
  else if(z == '.')
    {
      int temp = fgetc( f2);
		
      if(temp == '.'){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }
		
      else{
	printf("%c",z);
	printf(" (operator)\n");
	Analyze(temp,f2);
      }
    }
	
  else if(z == '<')
    {
      int temp = fgetc( f2);
      
      if(temp == '<'){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }	
      
      else if(temp == '='){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }	
      else if(temp == '>'){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }	
      else{
	printf("%c",z);
	printf(" (operator)\n");
	Analyze(temp,f2);
      }
    }
  else if(z == '>')
    {
      int temp = fgetc( f2);
		
      if(temp == '>'){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }	
		
      else if(temp == '='){
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
      }	
      
      else{
	printf("%c",z);
	printf(" (operator)\n");
	Analyze(temp,f2);
      }	
    }
  
  else if(z == '!')
    {
      int temp = fgetc( f2);
      
      if(temp == '='){
	
	printf("%c", z);
	printf("%c", temp);
	printf(" (operator)\n");
		
      }
      
      else{
	printf("%c",z);
	printf(" (UNK)\n");
	Analyze(temp,f2);
      }
    }
  else{
    printf("%c",z);
    printf(" (operator)\n");
    
  }
}

void CaseOfForwardAngle( int z , FILE *f2 ) // if it is a forward angle then it is either the divide operation, or it is the start of a comment
{	
  int tempy = fgetc( f2) ; //grabs next character
	
  if(tempy == '*'){ //if the next character is a * then it is a comment
	
    printf("%c",  z);
    printf("%c",  tempy); //prints out /* for start fo the comment
			
    do{
				
      z = fgetc(f2); 
					
      if(  z == '*'){ //test if z is a * whihc might reflect the end of a comment if paired with a /
			
	tempy = fgetc( f2);
					
	printf("%c",  z);
	printf("%c",  tempy);
      }
      else{
	printf("%c",  z);
				
      }
    }
    while( tempy != '/'); // test if the next char is / signalling the end of the comment which will end the loop
			
    printf(" (comment)\n");
  }

  else{
    printf("%c",  z);
    printf (" (operator)\n"); // if * wasnt the next character then it was just the operator /
    Analyze(tempy, f2); //analyzed second character grabbed
  }

}

void CaseOfCharLiteral(int z, FILE *f2){
	
  int t = fgetc(f2); // grabs the character
  int c = fgetc(f2); // grabs the '
  printf("%c",  z);  // prints out first '
  printf("%c",  t);  // prints out the character
  printf("%c",  c);  // prints out the last '
  printf (" (character literal)\n");
}

void CaseOfString( int z, FILE *f2){
  printf("%c", z );
  int t;
  while( (t = fgetc(f2)) != '"'){
    printf("%c", t);
		
  }
	
  printf("%c", t);
  printf(" (string)\n" );
	
}

void CaseOfUpperCaseLetter(int z, FILE *f2){
  int t;
  t = fgetc(f2);
  printf("%c",z);
  if((t >= '0' && t <= '9') || ( t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') || t == '_'){
    CaseOfUpperCaseLetter(t, f2);
  }
  else{
    printf(" (identifier)\n");
    Analyze(t,f2);
  }
}


void CaseOfNumerLiteral(int z,FILE* f2){
  int t;
  t = fgetc(f2);
  printf("%c",z);
  if((t >= '0' && t <= '9') || ( t >= 'a' && t <= 'f') || (t >= 'A' && t <= 'F') || t == '.' || t == '_' || t == '#'){ //tests to see if the character continues to follow the paramaters of a numerical litteral
    CaseOfNumerLiteral(t, f2);
  }
  else{
    printf(" (numeric literal)\n");
    Analyze(t,f2);
  }
}

void CaseOfLowerCaseLetter(int z, FILE *f2){
 

  char keyword[][20] = {"accessor","and","array","begin","bool","case","character","constant","else","elsif","end","exit","function","if","in","integer","interface","is","loop","module","mutator","natural","null","of","or","others","out","positive","procedure","range","return","struct","subtype","then","type","when","while"}; //places all keywords in an array to be compared
  
  char str[60]; //string pulled from input file
  int x; //temp char varaiable
  int i; //counter
  
  str[0] = z;   //sets first character equal to the first character in the string
  bool b = false; // sets b equal to false later to test to se 

  for(i = 1; i < 60; i++){
    x = getc(f2);
    if((x >= 'a' && x <= 'z') || (x >='A' && x<='Z') || (x == '_') || (x >= '0' && x<='9')) //tests to see if character still follows paramaters of an identifier
      {
	str[i] = x; //adds the character to the string if it follows paramters
      }
    else
      {
	str[i] = '\0'; //terminates string once character that isnt part of identifier is reached
	b = true; // sets b == to true to be later used so the character that was pulled can be analyzed in case it was an operator or other lexeme
	break;
      }
  }

  bool a = false;
  int testv = 1;
  printf("%s", str);
  
  for(i = 0; i < 38; i++){
    testv = strcmp(str,keyword[i]); // tests to see if str is ever equal to any of the keywords, sets ret = 0 if it is
    if(testv == 0){
      a = true; //sets a = to true if str is a keyword
      break;
    }
  }
  
  
  if(a == true)
    printf( " (keyword)\n");
  else{
    printf( " (identifier)\n");
  }
  if(b==true)
    Analyze(x, f2); //analyzes last character retrieved because it wasnt apart of the identifier/keyword.
}
