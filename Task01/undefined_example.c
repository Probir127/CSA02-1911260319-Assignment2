/* Compile for diagnostics only. Do not execute undefined behaviour. */
int main(void) { int count=0; count=count++ + 1; return count; }
