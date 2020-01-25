%{
	int numChars = 0, numWords = 0, numLines = 0;
%}

%%

\n				{numLines++; numChars++;}
[^ \t\n]+		{numWords++; numChars += yyleng;}
.				{numChars++;}	

%%

#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Must provide 2 arguments\n");
		return 1;
	}
	yyin = fopen(argv[1],"r"); 
	yylex();
	freopen (argv[2],"w",stdout);
	printf("%d\t%d\t%d\n", numChars, numWords, numLines);
	fclose(stdout);
	return 0;
}