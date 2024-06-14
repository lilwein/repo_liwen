public class Partition {
	
	private int[] links;
	private int[] sizes;
	private int[] ranks;
	private int maxindex;
	private int nsets;
	
	/*
 	 * Crea una nuova partizione di maxindex elementi
 	 */
	public Partition(int maxindex) {
		this.maxindex = maxindex;
		this.nsets = 0;
		this.links = new int[maxindex];
		this.sizes = new int[maxindex];
		this.ranks = new int[maxindex];
		
		for (int i = 0; i < maxindex; i++) this.links[i] = -2;
		for (int i = 0; i < maxindex; i++) this.sizes[i] = -1;
		for (int i = 0; i < maxindex; i++) this.ranks[i] = -1;
	}
	/*
 	 * Crea un set nella partizione p, con chiave index
 	 */
	public void makeSet(int index) {
		if (this.links[index] != -2) {
			System.err.println("makeSet called on an already made set " + index);
			System.exit(1);
		}
		this.links[index] = -1;
		this.nsets++;
		this.sizes[index] = 1;
		this.ranks[index] = 1;
	}

	/*
	 * Unisce i set denominati s1 ed s2 e ritorna la chiave del nuovo set
 	 */
	public int union(int s1, int s2) {
		if (this.links[s1] != -1) {
			System.err.println("union called on a non-root node " + s1);
			System.exit(1);
		}
		if (this.links[s2] != -1) {
			System.err.println("partition_union called on a non-root node " + s2);
			System.exit(1);
		}
		if (s1 == s2) return s1;

		this.nsets--;

		if (this.ranks[s1] < this.ranks[s2]) {
			this.links[s1] = s2;
			this.sizes[s2] += this.sizes[s1];
			return s2;
		}
		else if (this.ranks[s1] > this.ranks[s2]) {
			this.links[s2] = s1;
			this.sizes[s1] += this.sizes[s2];
			return s1;
		}
		else {
			this.links[s2] = s1;
			this.sizes[s1] += this.sizes[s2];
			this.ranks[s1]++;
			return s1;
		}
	}
	
	/*
 	 * Restituisce l'id del root del set identificato da index, nella partizione p
 	 */
	public int find(int index) {
		int id;

		if (this.links[index] == -1) return index;

		if (this.links[this.links[index]] == -1) return this.links[index];

		id = this.find(this.links[index]);
		this.links[index] = id;
		return id;
	}
}