// Scrivi la soluzione qui...
#include "e1.h"
#include <string.h>
#include <stdlib.h>
int cmp(const void *ap, const void *bp){
	person_t a = *(person_t*)ap;
	person_t b = *(person_t*)bp;
	return strcmp(a.name, b.name);
}
void sort_people(person_t p[], size_t n){
	qsort(p, n, sizeof(person_t), cmp);
}
person_t *find_person(char *key, person_t sorted[], size_t n){
	person_t key_person;
	key_person.name = key;
	return bsearch( &key_person, sorted, n, sizeof(person_t), cmp);
}
