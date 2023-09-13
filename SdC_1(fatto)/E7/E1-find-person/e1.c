#include "e1.h"
#include <string.h>
#include <stdlib.h>

int cmp_people(const void* p1, const void* p2){
	person_t n1 = *(person_t*) p1;
	person_t n2 = *(person_t*) p2;
	return strcmp(n1.name, n2.name);
}

void sort_people(person_t p[], size_t nel){
	qsort( p, nel, sizeof(person_t), cmp_people );
	
}

person_t *find_person(char *key, person_t sorted[], size_t nel){
	person_t p;
	p.name = key;
	person_t* ret = (person_t*) bsearch( &p, sorted, nel, sizeof(person_t), cmp_people );
	return ret;
}