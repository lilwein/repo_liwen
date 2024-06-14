import java.util.*;

public class GraphServices {


	public static <V> void bfs(Graph<V> g, Node<V> source) {
		// DA IMPLEMENTARE
		LinkedList<LinkedList<Node<V>>> stack = new LinkedList<LinkedList<Node<V>>>();
		LinkedList<Node<V>> l0 = new LinkedList<Node<V>>();
		l0.add(source);
		stack.add(l0);
		
		
		int livello = 0;
		while(stack.size() >0 ){
			LinkedList<Node<V>> lvi = stack.remove();
			LinkedList<Node<V>> lvnew = new LinkedList<Node<V>>();
			Iterator<Node<V>> lit = lvi.iterator();
			
			while(lit.hasNext()){
				
				Node<V> nd = lit.next();
				
				System.out.println("Livello "+ livello + ": " + nd.getElement());
				Collection<Edge<V>> outEdge = g.getOutEdges(nd);
				Iterator<Edge<V>> edgeit = outEdge.iterator();
				
				while(edgeit.hasNext()){
					Node<V> out = edgeit.next().getTarget();
					if(out.stato != Node.Stato.EXPLORED){
						out.stato = Node.Stato.EXPLORED;
						lvnew.add(out);
					}
				} 
			}
			
			if(lvnew.size() > 0){ 
				stack.add(lvnew);
				livello ++;
			}
			
		}
	}
	
	static final int INFINITO = 10000;

	public static <V> String sssp(Graph<V> g, Node<V> source) {
		// DA IMPLEMENTARE
		Collection<Node<V>> nodi = g.getNodes();
		LinkedList<HeapEntry<Node<V>>> hpEntries = new LinkedList<HeapEntry<Node<V>>>();
		
		Iterator <Node<V>> nodiIt = nodi.iterator();
		
		MinHeap<Node<V>> hp = new MinHeap<Node<V>>();
		
		
		//Creazione Heap e memorizzazione elementi
		while(nodiIt.hasNext()){
			Node<V> nd = nodiIt.next();
			
			if(nd == source) {
				hpEntries.add(hp.insert(0,nd));
			}
			else{
				hpEntries.add(hp.insert(INFINITO,nd));
			}
		}
		
		while(hp.size() > 0 ){
			HeapEntry<Node<V>> elem = hp.removeMin();
			Node<V> ndMin = elem.getValue();
			
			Iterator<Edge<V>> outEdges = g.getOutEdges(ndMin).iterator();
			
			while(outEdges.hasNext()){
				Edge<V> edge  = outEdges.next();
				Node<V> targ = edge.getTarget();
				
				Iterator<HeapEntry<Node<V>>> it = hpEntries.iterator();
				while(it.hasNext()){
					HeapEntry<Node<V>> ent = it.next();
					if(ent.getValue() == targ ){
						if( elem.getKey() + edge.getWeight() < ent.getKey())
							hp.replaceKey(ent,elem.getKey() + edge.getWeight());
					}
				}
				
			}
		}
		
		String res  = "Distanze dal nodo " + source.getElement() + " [";
		Iterator<HeapEntry<Node<V>>> hpIt  = hpEntries.iterator();
		while(hpIt.hasNext()){
			HeapEntry<Node<V>> ent = hpIt.next();
			
			res += ent.getValue().getElement() + ":" + ent.getKey() + ", "; 
			
		}
		
		res += "]\n" ;
		 
		
			return res;
	}

	public static <V> void apsp(Graph<V> g) {
		// DA IMPLEMENTARE
		
		Iterator<Node<V>> it = g.getNodes().iterator();
		
		String risp = "";
		
		while(it.hasNext()){
			risp += sssp(g,it.next());
		}
		System.out.print(risp);
	}
}
