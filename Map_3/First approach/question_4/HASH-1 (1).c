/***************************************************************************
 *                              From K&R2                                  *
 ***************************************************************************/

#define HASHSIZE 101

/* nlist:  From K&R2 page 144.  Points to a search text and
 * a replacement text */
struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

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
	if((np->defn = strdup(defn)) == NULL)
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
char *strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}
