
#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

unsigned int that_getTotalStrings(void);
void         that_addString(const char* txt, ...);
char*        that_getString(unsigned int strNumber);
void         that_printAllStrings(void);
void         that_removeString(unsigned int strNumber);
void         that_cleanupStrings(void);

#endif // STRING_MANAGER_H
