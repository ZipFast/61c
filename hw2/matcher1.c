#include "matcher.h"


/**
 * Your helper functions can go below this line
 */
int isEmpty(char character){
	if (character == '\0') // makes sure its a valid character
		return 1; // its empty
	else 
		return 0; // its not empty
}

int period_operator(char* partial_line){	
	if (!isEmpty(*partial_line)) // just making sure there is something for the period, if there is then its valid.
		return 1;
	else
		return 0;
}

void plus_operator(char** partial_line){
	if (**(partial_line - 1) != **partial_line) // If they don't equal each other, it means there is no more repitition.
		return;
	else
		plus_operator(partial_line++); // This means there is still repitition, so I recursively advance and check the pointer.
}


/**
 * Your helper functions can go above this line
 */


/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // You can use this recommended helper function, or not.
	
	if (*pattern == '\0')
		return 1;

	else if(*pattern == '\\') // if the pattern has a backslash \ i need to catch it before it goes on and does the other operations.
		if(*partial_line == *(pattern + 1))
			return matches_leading(partial_line + 1, pattern + 2);
		else 
			return 0;

	else if(*(pattern + 1) == '?'){ 
		if (*partial_line == *pattern) // if the characters match I advance partial line, if not then that means the character isn't there.
			partial_line++;
		return matches_leading(partial_line, pattern + 2);
	}
	else if(*pattern == '.' && period_operator(partial_line))
		return matches_leading(partial_line + 1, pattern + 1);

	else if(*pattern == '+'){
		plus_operator(&partial_line);
		return matches_leading(partial_line + 1, pattern + 1);
	}

	else if(*partial_line == *pattern){
		return matches_leading(partial_line + 1, pattern + 1); // standard matching of characters
	}

	else {
		return 0;
	}
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {

    //
    // TODO put your code here.
    //
    while(*line != '\0')
    {
    	if(matches_leading(line, pattern))
    	{
    		return 1;
    	}
    	line++;
    }

    return 0;
}
