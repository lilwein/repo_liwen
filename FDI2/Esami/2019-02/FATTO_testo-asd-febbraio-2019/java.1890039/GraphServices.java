import java.util.*;


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
		int n = points.length;
		double [][] matGraph = new double[n][n];
		Graph g = new Graph(n);
		
		for(int i = 0; i < n; i += 1){
			for(int j = 0; j < n ; j += 1){
				if(dist(points[i],points[j]) == 0.0 ) matGraph[i][j] = -1.0;
				else matGraph[i][j] = dist(points[i],points[j]);
			}
		}
		
		g.setMat(matGraph);
		return g;
	}
	
	
	/*
	* Dato un grafo g, la funzione ritorna un nuovo grafo g', con gli archi che rappresentano
	* un albero ricoprente che descrive la cablatura da impiegare per l'interconnesione
	* di tutti i punti, minimizzando la quantita' di cavo impiegato. 
	*/
	public static Graph getBestConnections(Graph g) {
		/*DA IMPLEMENTARE*/
		double [][] matGraph = g.getMat();
		
		LinkedList<Node<Integer>> nodi = new LinkedList<Node<Integer>>();
		
		for(int i = 0; i < g.getnVertices(); i += 1){
			Node<Integer> nd = new Node<Integer>(i);
			nd.map = i;
			nodi.add(nd);
		}
		
		int numVert = g.getnVertices();
		
		Partition vSets = new Partition(nodi);
		
		MinHeap hpEdge = new MinHeap<Integer>();
		
		for(int i = 0; i < g.getnVertices(); i += 1){
			for(int j = i + 1; j < g.getnVertices(); j += 1){
				hpEdge.insert((int)matGraph[i][j], edgeToCode(i,j));
			} 
		}
		
		Graph newGraph = new Graph(numVert);
		
		double [][] mat = new double[numVert][numVert];
		
		//Inizializzazione matrice
		for(int i = 0; i < numVert; i += 1){
			for(int j = 0; j < numVert; j += 1){
				mat[i][j] = 0;
			}
		}
		int numEdge = 0;
		while(hpEdge.size() > 0 ){
			int []edge = code_to_edge((int)hpEdge.removeMin().getValue());
			if( vSets.find(edge[0]) != vSets.find(edge[1]) ){
				vSets.union(edge[0],edge[1]);
				mat[edge[0]][edge[1]] = matGraph[edge[0]][edge[1]];
				mat[edge[1]][edge[0]] = matGraph[edge[1]][edge[0]];
				numEdge += 1;
			}
		}
		
		newGraph.setMat(mat);
		newGraph.setnEdges(numEdge);
		
		
		
		
		return newGraph;
	}
	
	
	/*
	 * Dato un grafo ed un suo nodo v, la funzione ritorna l'altezza dell'albero
	 * avente v come radice.
	*/
	public static int getTreeHeight(Graph h, int v) {
		/*DA IMPLEMENTARE*/
		LinkedList<LinkedList<Integer>> stack = new LinkedList<LinkedList<Integer>>();
		LinkedList<Integer> s0 = new LinkedList<Integer>();
		s0.add(v);
		stack.add(s0);
		
		int livello = 0;
		System.out.println(h.toString());
		
		double [][] matCopy = new double[h.getnVertices()][h.getnVertices()];
		
		for(int i = 0; i < h.getnVertices(); i += 1){
			for(int j = 0; j < h.getnVertices(); j += 1){
				
				matCopy[i][j] = h.getMat()[i][j];
			}
		}
		
		while(stack.size() > 0){
			System.out.println(stack.size());
			LinkedList<Integer> si = stack.remove();
			LinkedList<Integer> sL = new LinkedList<Integer>();
			
			while(si.size() > 0){
				int elem = si.remove();
				
				for(int i = 0; i < h.getnVertices(); i+= 1){
					
					 
					if(matCopy[elem][i] > 0 && !sL.contains(i)) { 
						matCopy[elem][i] = -1.0;
						matCopy[i][elem] = -1.0;
						sL.add(i);
						//System.out.println(mat[elem][i] +"!=" + -1.0f);}
					}
				
				}
				System.out.println(sL.size());
				if(sL.size() > 0){
					stack.add(sL);
					livello += 1;
				}
			}
			
		}
		return livello;
	}
}




