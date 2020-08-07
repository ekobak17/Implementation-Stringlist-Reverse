#include "stringlist.h"
#include "stdlib.h"

typedef struct sldata {        
	long capacity;
  	long size;
	char **theString;
	char *buf;	
	/* data for each instance */
    /* you must define the instance-specific fields for each StringList */
} SLData;

/* any helper functions needed by the methods */

static void sl_destroy(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;
	long i;
	for (i = 0L; i < sld->size; i++) {
		free(sld->theString[i]);
	}
	free(sld->theString);
	free(sld);
	free((char *)sl);
}

static int sl_append(const StringList *sl, char *s) {
    SLData *sld = (SLData *)sl->self;
	int status = (sld->capacity > sld->size);

	if (!status) {
		size_t nbytes = 2 *sld->capacity * sizeof(char *);
		char **tmp = (char **)realloc(sld->theString, nbytes);
		if (tmp !=NULL) {
			status = 1;
			sld->theString = tmp;
			sld->capacity *= 2;
		}
	}
	if (status) 
		sld->theString[sld->size++] = s;	
	return status;
}

static int sl_get(const StringList *sl, long index, char **sptr) {
    SLData *sld = (SLData *)sl->self;
    int status = (index >= 0L && index < sld->size);

    if (status) 
	    *sptr = sld->theString[index];
    return status;
}

static long sl_size(const StringList *sl) {
    SLData *sld = (SLData *)sl->self;
	return sld->size;
}

static StringList template = {
    NULL, sl_destroy, sl_append, sl_get, sl_size
};

const StringList *StringList_create(long capacity) {/* use default if 0L */
	StringList *sl = (StringList *)malloc(sizeof(StringList));

	if (sl != NULL) {
		SLData *sld = (SLData *)malloc(sizeof(SLData));
		if (sld != NULL) {
			long cap = (capacity <= 0) ? DEFAULT_CAPACITY : capacity;
			char **string = (char **) malloc(cap *sizeof(char *));
			if (string != NULL) {
			sld->capacity = cap;
			sld->size = 0L;
			sld->theString = string;
			*sl = template;
			sl->self = sld;
			}
		       	else {
				free(sld);
				free(sl);
				sl = NULL;
			}
		}
	}
		return sl;
}
