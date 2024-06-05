import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.StringTokenizer;

public class Graph<V> {

    private LinkedList<GraphNode<V>> nodes;
    private int n_nodes;
    private int n_edges;

    public Graph () {
        this.nodes = new LinkedList<GraphNode<V>>();
    }

    @SuppressWarnings("unchecked")
	public List<GraphNode<V>> getNodes() {
    	List<GraphNode<V>> ret = new LinkedList<>();
    	for(GraphNode<V> n : this.nodes) {
    		try {
				ret.add((GraphNode<V>) n.clone());
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
    	}
        return (List<GraphNode<V>>) ret;
    }

    @SuppressWarnings("unchecked")
	public List<GraphNode<V>> getNeighbors(GraphNode<V> n){
    	List<GraphNode<V>> ret = new LinkedList<>();
    	for(GraphNode<V> edge : n.outEdges) {
    		try {
				ret.add((GraphNode<V>) edge.clone());
			} catch (CloneNotSupportedException e) {
				e.printStackTrace();
			}
    	}
        return (List<GraphNode<V>>) ret;
    }

    public GraphNode<V> addNode(V value) {
        GraphNode<V> n = new GraphNode<V>();
        n.value = value;
        n.outEdges = new LinkedList<GraphNode<V>>();
        n.state = GraphNode.Status.UNEXPLORED;
        for(GraphNode<V> node : this.nodes) {
        	if(node.value.equals(value))
        		return node;
        }
        this.nodes.add(n);
        this.n_nodes++;
        return n;
    }

    public void addEdge(GraphNode<V> s, GraphNode<V> t) {
        s.outEdges.add(t);
        t.outEdges.add(s);
        this.n_edges++;
    }

    public V getNodeValue(GraphNode<V> n) {
        return n.value;
    }
    
    public void removeEdge(GraphNode<V> v1, GraphNode<V> v2){
    	removeEdgeAux(v1,v2);
    	removeEdgeAux(v2,v1);
		this.n_edges--;
    }
    
    private void removeEdgeAux(GraphNode<V> v1, GraphNode<V> v2) {
    	Iterator<GraphNode<V>> it = this.nodes.iterator();
    	while(it.hasNext()) {
    		GraphNode<V> n1 = it.next();
    		Iterator<GraphNode<V>> it2 = n1.outEdges.iterator();
    		if(n1.equals(v1)) {
	    		while(it2.hasNext()) {
	    			GraphNode<V> n2 = it2.next();
	    			if(n2.equals(v2)) { 
	    				it2.remove();
	    			}
	    		}
    		}
    	}
    }

    public void removeNode(GraphNode<V> v){
    	if(this.nodes.contains(v)) {
	    	for(GraphNode<V> e : v.outEdges) {
	    		this.removeEdgeAux(e, v);
	    		this.n_edges--;
	    	}
    	}
    	this.nodes.remove(v);
    }

    public static <V> Graph<V> readFF(File input){
    	Graph<V> toRet = new Graph<>();
    	try {
			BufferedReader br = new BufferedReader(new FileReader(input));
			String firstLine = br.readLine();
			StringTokenizer tok = new StringTokenizer(firstLine);
			int v = Integer.parseInt(tok.nextToken());
			int e = Integer.parseInt(tok.nextToken());
			for(int i = 0; i< e; i++) {
				tok = new StringTokenizer(br.readLine());
				while(tok.hasMoreTokens()) {
					GraphNode<V> v1 = toRet.addNode((V) tok.nextToken());
					GraphNode<V> v2 = toRet.addNode((V) tok.nextToken());
					toRet.addEdge(v1, v2);
				}
			}
			br.close();
			if(toRet.n_nodes < v) {
				int rem = v - toRet.n_nodes;
				int name = e + 1;
				for(int i = 0; i<rem; name++, i++) {
					toRet.addNode((V) (name + ""));
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return toRet;
    }

    public String printAdj() {
    	StringBuffer toRet = new StringBuffer();
        for(GraphNode<V> v : this.nodes) {
      	  toRet.append(v.value + ": ");
      	  for(GraphNode<V> e: v.outEdges) {
      		  toRet.append(e.value + " ");
      	  }
      	  toRet.append("\n");
        }
        return toRet.toString();
    }
    
    @Override
    public String toString(){
    	StringBuffer toRet = new StringBuffer();
    	toRet.append(this.n_nodes + " " + this.n_edges + "\n");
    	for(GraphNode<V> node : this.nodes) {
    		if(node.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(node, toRet);
    	}
    	return toRet.toString();
    }

    private void DFSprintEdges(GraphNode<V> node, StringBuffer str) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			str.append(node.value + " " + e.value + "\n");
    	}
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			DFSprintEdges(e, str);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

	public int nConComp(){
		int ret = 0;
		for(GraphNode<V> node : this.nodes) {
			if(node.state == GraphNode.Status.UNEXPLORED) {
				ret++;
				DFS(node);
			}
		}
		return ret;
    }

    private void DFS(GraphNode<V> node) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	for(GraphNode<V> e : node.outEdges) {
    		if(e.state == GraphNode.Status.UNEXPLORED)
    			DFS(e);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

	public List<Graph<V>> getConComp(){
		LinkedList<Graph<V>> toRet = new LinkedList<>();
		for(GraphNode<V> node : this.nodes) {
			if(node.state == GraphNode.Status.UNEXPLORED) {
				Graph<V> g = new Graph<>();
				toRet.add(g);
				DFSfillCC(node, g.nodes);
			}
		}
		
		return toRet;
    }

    private void DFSfillCC(GraphNode<V> node, LinkedList<GraphNode<V>> list) {
    	if(node.state != GraphNode.Status.UNEXPLORED)
    		return;
    	node.state = GraphNode.Status.EXPLORING;
    	list.add(node);
    	for(GraphNode<V> n : node.outEdges) {
    		if(n.state == GraphNode.Status.UNEXPLORED)
    			DFSfillCC(n, list);
    	}
    	node.state = GraphNode.Status.EXPLORED;
	}

	public static class GraphNode<V> implements Cloneable{

        public enum Status {UNEXPLORED, EXPLORED, EXPLORING}

        protected V value;
        protected LinkedList<GraphNode<V>> outEdges;

        // keep track status
        protected Status state;

		@Override
		public String toString() {
			return "GraphNode [value=" + value + ", state=" + state + "]";
		}

		@Override
		protected Object clone() throws CloneNotSupportedException {
			return super.clone();
		}
		
		
    }
}
