#ifndef __PARTITION_H__
#define __PARTITION_H__

typedef struct {
	int *links;
	int *sizes;
	int *ranks;
	int maxindex;
	int nsets;
} partition;

/*
 * Crea una nuova partizione di maxindex elementi
 */
partition *partition_new(int maxindex);

/*
 * Elimina la partizione p
 */
void partition_delete(partition *p);

/*
 * Crea un set nella partizione p, con chiave index
 */
void partition_makeset(partition *p, int index);

/*
 * Unisce i set denominati s1 ed s2 e ritorna la chiave del nuovo set
 */
int partition_union(partition *p, int s1, int s2);

/*
 * Restituisce l'id del root del set identificato da index, nella partizione p
 */
int partition_find(partition *p, int index);

#endif /* __PARTITION_H__ */