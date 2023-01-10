#define HASHSIZE 101

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

struct nlist *undef(char *s);
void print_hash(); 
char *strdup_(char *s);
unsigned hash(char *s);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);




