import java.util.LinkedList;
import java.util.List;

public class GraphServices<V>{

	public static <V> void sweep(Graph<V> g) {
		// Reset node's status
		g.resetStatus();
		
		int loctime = 0;
		for(Graph.GraphNode<V> node : g.getNodes()) {
			System.out.println("Root " + g.getNodeValue(node));
			loctime += sweep_aux(node, loctime);
		}
	}

	private static <V> int sweep_aux(Graph.GraphNode<V> node, int time) {
		if(node.state != Graph.GraphNode.Status.UNEXPLORED)
			return 0;
		int loctime = 1;
		node.state = Graph.GraphNode.Status.EXPLORING;
		node.timestamp = time;
		
		for(Graph.GraphNode<V> cur : node.outEdges) {
			System.out.print("\t" + node.value + "(" + node.timestamp + ")->" + cur.value + "(" + cur.timestamp + ")");
			if (cur.state == Graph.GraphNode.Status.EXPLORED) {
				if (node.timestamp < cur.timestamp)
					System.out.println("FORWARD");
				else
					System.out.println("CROSS");
			}
			else if (cur.state == Graph.GraphNode.Status.EXPLORING) {
				System.out.println("BACK");
			}
			else {
				System.out.println("TREE");
				loctime += sweep_aux(cur, time + 1);
			}
		}
		node.state = Graph.GraphNode.Status.EXPLORED;
		return loctime;
	}

	private static<V> int DDFS(Graph.GraphNode<V> nd, LinkedList<Graph.GraphNode<V>> ts) {
		if(nd.state == Graph.GraphNode.Status.EXPLORING)
			return 1;
		if(nd.state == Graph.GraphNode.Status.EXPLORED)
			return 0;
		nd.state = Graph.GraphNode.Status.EXPLORING;
		int ret = 0;
		for(Graph.GraphNode<V> cur : nd.outEdges) {
			ret += DDFS(cur, ts);
		}
		nd.state = Graph.GraphNode.Status.EXPLORED;
		ts.addFirst(nd);
		return ret;
	}

	private static<V> void transposedDFS(Graph.GraphNode<V> nd, LinkedList<Graph.GraphNode<V>> ret) {
		if(nd.state == Graph.GraphNode.Status.EXPLORING)
			return;
		if(nd.state == Graph.GraphNode.Status.EXPLORED)
			return;
		nd.state = Graph.GraphNode.Status.EXPLORING;
		for(Graph.GraphNode<V> cur : nd.inEdges) {
			transposedDFS(cur, ret);
		}
		ret.addLast(nd);
		nd.state = Graph.GraphNode.Status.EXPLORED;
	}

	/* SOLUTION ONLY WITH OUT EDGES
	private static<V> void transposedDFS(Graph<V> g, Graph.GraphNode<V> n, LinkedList<Graph.GraphNode<V>> ret) {
		if(n.state != Graph.GraphNode.Status.UNEXPLORED)
			return;
		n.state = Graph.GraphNode.Status.EXPLORING;
		for(Graph.GraphNode<V> to : g.getNodes()) {
			for(Graph.GraphNode<V> frm : to.outEdges) {
				if(frm == n)
					transposedDFS(g, to, ret);
			}
		}
		ret.addLast(n);
		n.state = Graph.GraphNode.Status.EXPLORED;
	}
	*/

	public static <V> void strongConnectedComponents(Graph<V> g) {
		// Reset node's status
		g.resetStatus();

		// First DFS
		LinkedList<Graph.GraphNode<V>> stack = new LinkedList<>();
		for(Graph.GraphNode<V> n : g.getNodes()) {
			if(n.state == Graph.GraphNode.Status.UNEXPLORED)
				DDFS(n, stack);
		}

		// Reset node's status
		g.resetStatus();

		// Second DFS on the transposed graph
		for(Graph.GraphNode<V> n : stack) {
			if(n.state == Graph.GraphNode.Status.UNEXPLORED) {
				LinkedList<Graph.GraphNode<V>> ret = new LinkedList<>();
				transposedDFS(n, ret);
				System.out.println("Strong connected component:");
				for(Graph.GraphNode<V> cur : ret) {
					System.out.print(cur.value + " ");
				}
				System.out.println("");
			}
		}
	}


	public static <V> void topologicalSort(Graph<V> g) {
		// Reset node's status
		g.resetStatus();

		LinkedList<Graph.GraphNode<V>> ts = new LinkedList<Graph.GraphNode<V>>();
		
		for(Graph.GraphNode<V> nd : g.getNodes()) {
			if(nd.state == Graph.GraphNode.Status.UNEXPLORED) {
				if(DDFS(nd, ts) > 0) {
					System.out.println("Impossibile ottenere ordine topologico, il grafo non è un DAG");
					return;
				}
			}
		}
		for(Graph.GraphNode<V> nd : ts) {
			System.out.print(nd.value + " ");
		}
		System.out.println("");
	}
	
}
