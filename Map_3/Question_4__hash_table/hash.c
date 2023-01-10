#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


/* The main task - delete the name and the definition of an element from the hash-table */
struct nlist *undef(char *s) {
    struct nlist *np; 
    if((np = lookup(s)) != NULL)  { 
        free((void *) np->name);
        free((void *) np->defn);
        np->name = NULL;
        np->defn = NULL;
    }    
    return np;
}


/* Printing all the elements in the hash-table */
void print_hash() {
    struct nlist *np;    
    for(int i = 0; i < HASHSIZE; ++i) {
        if (hashtab[i] != NULL)
            for (np = (hashtab[i]); np != NULL; np = np->next)
                printf("the element is: %s, %s\n" , np->name, np->defn);
    }

}


/**** The given functions ****/

/* lookup: From K&R2 page 145. Look for s in hashtab. */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
}


/* install: From K&R2 page 145. Put (name, defn) in hashtab. */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	
	if((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *) np->defn);
	if((np->defn = strdup_(defn)) == NULL)
		return NULL;
	return np;
}


/* hash: From K&R2 page 144.  Form hash value for string s. */
unsigned hash(char *s)
{
	unsigned hashval;
	for(hashval = 0; *s != '\0'; ++s)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}


/* strdup: From K&R2 page 143. Makes a duplicate of s. */
char *strdup_(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}
