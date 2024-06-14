import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class GraphServices {
	
	public static double dist(City c1, City c2){
		double dx = c1.x - c2.x;
		double dy = c1.y - c2.y;
		return Math.sqrt((dx*dx) + (dy*dy));
	}
	
	/*
	 * Data una lista contenente un elenco di citta', ritorna un puntatore al grafo completo avente:
	 * - un nodo per ogni citta'
	 * - un arco per ogni coppia di citta' (x,y) avente come peso la distanza euclidea tra x ed y
	 */
	public static Graph getCompleteGraph(LinkedList<City> l1) {
		Graph g = new Graph();
		HashMap< String, City > map = new HashMap< String, City >();

		for( City c1 : l1 ){
			GraphNode nc1 = g.addNode(c1.name);
			map.put(c1.name, c1);
		}
		List<GraphNode> nodes = g.getNodes();
		for( GraphNode c1 : nodes ){
			for( GraphNode c2 : nodes ){
				if( c1.equals(c2) ) continue;
				double d = GraphServices.dist(map.get(c1.name), map.get(c2.name));
				g.addEdge(c2, c1, d);
				g.addEdge(c1, c2, d);
			}
		}
		return g;
	}

	/*
	 * Dato un grafo, ritorna un puntatore al minheap costituito dagli archi del grafo, usando il peso degli archi come priorita'.
	 */
	public static MinHeap<GraphEdge> getMinHeapEdges(Graph g) {
		MinHeap<GraphEdge> h = new MinHeap<GraphEdge>();
		LinkedList<String> inserted = new LinkedList<String>();
		for( GraphNode n : g.getNodes() ){
			for( GraphEdge e : g.getIncidentEdges(n) ){
				if( inserted.contains(e.n1.name) || inserted.contains(e.n2.name) ) continue;
				h.insert(e.weight, e);
			}
			inserted.add(n.name);
		}
		return h;
	}

	/*
	 * Dato un grafo, ritorna una lista degli archi che rappresentano un Minimum Spanning Tree del grafo.
	 */
	public static LinkedList<GraphEdge> getMST(Graph g) {
		Partition p = new Partition(g.nNodes);
		HashMap< GraphNode, Integer > nodeToP = new HashMap< GraphNode, Integer >();
		HashMap< Integer, LinkedList<GraphNode> > pToNode = new HashMap< Integer, LinkedList<GraphNode> >();
		MinHeap<GraphEdge> h = GraphServices.getMinHeapEdges(g);
		LinkedList<GraphEdge> toReturn = new LinkedList<GraphEdge>();

		int i = 0;
		for( GraphNode n : g.getNodes() ){
			LinkedList<GraphNode> l = new LinkedList<GraphNode>();
			l.add(n);
			nodeToP.put(n, i);
			pToNode.put(i, l);
			p.makeSet(i);
			i++;
		}
		
		while( !h.isEmpty() ){
			HeapEntry<GraphEdge> entry = h.removeMin();
			GraphEdge edge = entry.getValue();
			int p1 = nodeToP.get(edge.n1);
			int p2 = nodeToP.get(edge.n2);

			if( p1 != p2 ){
				int newIndex = p.union(p1, p2);

				if( newIndex == p2 ){
					LinkedList<GraphNode> nodesp1 = pToNode.get(p1);
					LinkedList<GraphNode> nodesp2 = pToNode.get(p2);
					for( GraphNode n : nodesp1 ) {
						nodesp2.add(n);
						nodeToP.put(n, newIndex);
					}
				} else {
					LinkedList<GraphNode> nodesp2 = pToNode.get(p2);
					LinkedList<GraphNode> nodesp1 = pToNode.get(p1);
					for( GraphNode n : nodesp2 ) {
						nodeToP.put(n, newIndex);
						nodesp1.add(n);
					}
				}
				
				toReturn.addLast(edge);
			}
		}

		return toReturn;
	}
}

class City {
	String name;
	double x;
	double y;
	
	public City(String name, double x, double y) {
		super();
		this.name = name;
		this.x = x;
		this.y = y;
	}

	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
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
	
	@Override
	public String toString() {
		return "City [name=" + name + ", x=" + x + ", y=" + y + "]";
	}
}
