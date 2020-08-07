/*
 * Author: Ellie Kobak
 * usage:
 *
 */

#include <stdio.h>
#include "stringlist.h"
#include <string.h>


int main() {
	int i = 0;
	int programError = 1;
	char input[BUFSIZ];
	int N;
	char *str;
	int line;

	
	const StringList *sl = StringList_create(0L);
	if(sl == NULL){
		fprintf(stderr, "unable to create String ADT"); 
		return programError;
	}
	while (fgets(input, BUFSIZ, stdin)!= NULL) {
		if (!sl->append (sl, strdup(input))) {
			if (sl != NULL) 
				sl->destroy(sl);
			fprintf(stderr, "unable to append");
		}
	}
	N = sl->size(sl);
	for (i = N - 1; i>= 0; i--) {
		int tmp = sl->get(sl, i, &str);
		if (tmp)
			fprintf(stdout, "%s", str);
	}
	sl->destroy(sl);
	
	return programError;		

}

