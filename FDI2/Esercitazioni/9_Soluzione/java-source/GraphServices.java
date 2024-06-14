import java.util.*;

public class GraphServices {

    public static <V> void bfs(Graph<V> g) {
        for(Node<V> n : g.getNodes()) {
            if(n.state == Node.Status.UNEXPLORED)
                bfsFromNode(g, n);
        }
    }

    private static <V> void bfsFromNode(Graph<V> g, Node<V> source) {
        if(!(source.state == Node.Status.UNEXPLORED))
            return;

        Queue<Node<V>> queue = new ArrayDeque<Node<V>>();
        source.state = Node.Status.EXPLORED;
        queue.add(source);
        
        while(!queue.isEmpty()) {
            Node<V> u = queue.remove();
            System.out.println(u.getValue());
            
            for(Edge<V> e : g.getOutEdges(u)) {
                Node<V> v = e.getTarget();
                if(v.state == Node.Status.UNEXPLORED){
                    v.state = Node.Status.EXPLORED;
                    queue.add(v);
                }
            }
        }
    }

    public static <V> void sssp(Graph<V> g, Node<V> source) {
        MinHeap<Node<V>> pqueue = new MinHeap<Node<V>>();
        HashMap<Node<V>, HeapEntry<Node<V>>> dist = new HashMap<Node<V>, HeapEntry<Node<V>>>();

        final int INFINITY = 100000;
        // (NB.: deve essere maggiore della somma di tutti i pesi del grafo)

        // Inizializzazione
        for(Node<V> u : g.getNodes()) {
            HeapEntry<Node<V>> hu = pqueue.insert(u == source ? 0 : INFINITY, u);
            dist.put(u, hu);
        }

        // Ciclo principale
        while (!pqueue.isEmpty()) {
            HeapEntry<Node<V>> hu = pqueue.removeMin();
            Node<V> u = hu.getValue();

            for(Edge<V> e : g.getOutEdges(u)) {
                Node<V> v = e.getTarget();
                if (dist.get(u).getKey() + e.getWeight() < dist.get(v).getKey())
                    pqueue.replaceKey(dist.get(v), dist.get(u).getKey() + e.getWeight());
            }
        }

        for(Node<V> u : g.getNodes())
            System.out.println(u + " " + dist.get(u).getKey());
    }

    public static <V> void mst(Graph<V> G) {
        Partition<V> P;
        MinHeap<Edge<V>> Q;

        int i = 0;
        for(Node<V> n : G.getNodes())
            n.map = i++;

        P = new Partition<V>(G.getNodes());
        Q = new MinHeap<Edge<V>>();
        for(Edge<V> e : G.getEdges())
            Q.insert(e.getWeight(), e);

        while(!Q.isEmpty())	{
            Edge<V> e = Q.removeMin().getValue();
            Node<V> u = e.getSource(), v = e.getTarget();
            
            if(P.find(u.map) != P.find(v.map)) {
                System.out.println(u.getValue() + " " + v.getValue());
                P.union(u.map, v.map);
            }
        }
    }
}
