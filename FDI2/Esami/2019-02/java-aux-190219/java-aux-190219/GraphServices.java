/*
 * Classe Punto, con coordinate x e y.
*/
class Point{
	double x;
	double y;
	
	public double getX() {
		return x;
	}
	public void setX(double x) {
		this.x = x;
	}
	public double getY() {
		return y;
	}
	public void setY(double y) {
		this.y = y;
	}	
}

public class GraphServices {
	
	/*
	* Funzione ausiliara che dati due noti x ed y collegati da un arco,
	* restituisce un codice univoco assegnato all'arco.
	*/
	public static int edgeToCode(int x, int y) {
		if(y < x){
			int z = y;
			y = x;
			x = z;
		}
	    return (int)((x*100) + y);
	}
	
	/*
	 * Funzione ausiliara che dato un codice, restituisce in un array
	 * di 2 elementi, i nodi collegati dall'arco associato al codice.
	*/
	public static int[] code_to_edge(int x){
	    int[] ret = new int[2];
	    double tmp = x/100.;
	    ret[0] = (int)(tmp);
	    ret[1] = (int)((tmp - ret[0])*100);
	    return ret;
	}
	
	public static double dist(Point p1, Point p2){
		double dx = p1.x - p2.x;
		double dy = p1.y - p2.y;
		return Math.sqrt((dx*dx) + (dy*dy));
	}
	
	
	/*
	 * Dato un array di n punti, con coordinate x ed y, la funzione ritorna
	 * un puntatore al grafo rappresentato dai potenziali collegamenti
	 * di tutti i punti, rappresentato con matrice di adiacenze. Il peso
	 * di ciascun arco x <-> y e' rappresentato dalla distanza euclidea dei nodi
	 * x ed y.
	*/
	public static Graph makeGraph(Point[] points){
		/*DA IMPLEMENTARE*/
		return null;
	}
	
	
	/*
	* Dato un grafo g, la funzione ritorna un nuovo grafo g', con gli archi che rappresentano
	* un albero ricoprente che descrive la cablatura da impiegare per l'interconnesione
	* di tutti i punti, minimizzando la quantita' di cavo impiegato. 
	*/
	public static Graph getBestConnections(Graph g) {
		/*DA IMPLEMENTARE*/
		return null;
	}
	
	
	/*
	 * Dato un grafo ed un suo nodo v, la funzione ritorna l'altezza dell'albero
	 * avente v come radice.
	*/
	public static int getTreeHeight(Graph h, int v) {
		/*DA IMPLEMENTARE*/
		return 0;
	}
}




