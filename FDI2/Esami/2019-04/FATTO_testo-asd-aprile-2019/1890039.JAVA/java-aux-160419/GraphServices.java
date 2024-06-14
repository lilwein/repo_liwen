import java.util.*;

public class GraphServices {

	/**
 	* Dato un grafo g, la funziona ritorna il numero delle sue componenti connesse.
	*/
	public static int connComp(Graph g){
		/*DA IMPLEMENTARE*/
		Iterator<GraphNode> itNodes = g.getNodes().iterator();
		LinkedList<GraphNode> stack = new LinkedList<GraphNode>();
		int comCons = 0;  
		
		while(itNodes.hasNext()){
			GraphNode nd = itNodes.next();
			if(nd.getNodeTag() == Graph.UNEXPLORED ){
				nd.setNodeTag(Graph.EXCLUDED);
				stack.add(nd);
				comCons ++;
				while(stack.size() > 0){
					GraphNode node = stack.remove();
					Iterator<GraphEdge> outEdge = g.getIncidentEdges(node).iterator();
					while( outEdge.hasNext()){
						GraphNode elem = outEdge.next().getEdgeOpposite(node);
						if( elem.getNodeTag() == Graph.UNEXPLORED ){
							elem.setNodeTag(Graph.EXCLUDED);
							stack.add(elem);
						}
					}
					
				}
			}
			
		}
		
		return comCons;
	}

	/**
	 * Dato un grafo g, la funzione modifica il grafo contraendone tutti i vertici di grado 2.
	 */ 
	public static void contract(Graph g){
		/*DA IMPLEMENTARE*/
		
		List<GraphNode> l = g.getNodes();
		LinkedList<GraphNode> node = new LinkedList<GraphNode>();
		for(GraphNode gn : l){
			node.add(gn);
		}
		
		Iterator<GraphNode> nodi = node.iterator();
		while(nodi.hasNext()){
			GraphNode nd = nodi.next();
			List<GraphEdge> outEdge = g.getIncidentEdges(nd);
			if(outEdge.size() == 2 ){
				Iterator<GraphEdge> oeIt = outEdge.iterator();
					GraphEdge e1 = oeIt.next();
					GraphEdge e2 = oeIt.next();
					GraphNode n1 = e1.getEdgeOpposite(nd);
					GraphNode n2 = e2.getEdgeOpposite(nd);
					g.removeEdge(nd,n1);
					g.removeEdge(nd,n2);
					g.removeNode(nd);
					g.addEdge(n1,n2);
			}
			
		}
	}

	/**
	 * Dato un grafo g, ritorna il numero di sottografi completi di 3 nodi contenuti in g
	 */
	public static int countK3(Graph g){
		/*DA IMPLEMENTARE*/
		int coutn = 0;
		
		List<GraphNode> nodes = g.getNodes();
		for( GraphNode n1 : nodes){
			List<GraphEdge> n1Edges = g.getIncidentEdges(n1);
			for( GraphEdge e1 : n1Edges){
				GraphNode n2 = e1.getEdgeOpposite(n1);
				List<GraphEdge> n2Edges = g.getIncidentEdges(n2);
				for(GraphEdge e2 : n2Edges){
					if( e2 != e1){
						GraphNode n3 = e2.getEdgeOpposite(n2);
						List<GraphEdge> n3Edges = g.getIncidentEdges(n3);
						for( GraphEdge e3 : n3Edges){
							if(e3 != e2){
								GraphNode n4 = e3.getEdgeOpposite(n3);
								System.out.println(n1.getNodeLabel() + " == " + n4.getNodeLabel());
								if(n4 == n1) coutn ++;
							}
						}
					}
				}
			}
		}
		
		
		return coutn/6;
	}
}
