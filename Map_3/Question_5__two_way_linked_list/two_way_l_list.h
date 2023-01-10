typedef struct cell *CellPtr;

typedef struct cell {
    int contents;
    CellPtr next;
    CellPtr prev;
} Cell;

void print_list (CellPtr list);
void print_rev(CellPtr list);
CellPtr insert_first (CellPtr list, int input);
CellPtr remove_first (CellPtr list, int *output);