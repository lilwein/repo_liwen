public class GraphServices<V> {
    
    public static <V> void bfs(Graph<V> g, Node<V> source) {
        //reset
        for(Node<V> n : g.getNodes()) {
            n.state = Node.Status.UNEXPLORED;
            n.timestamp = 0;
        }

        LinkedList<Node<V>> queue = new LinkedList<Node<V>>();
        queue.add(source);
        source.state = Node.Status.EXPLORED;
        source.timestamp = 0;
        while(!queue.isEmpty()){
            Node<V> n = queue.remove();
            System.out.println(n.getElement());
            for(Edge<V> e : n.getOutEdges()) {
                Node<V> w = e.getTarget();
                if(w.state == Node.Status.UNEXPLORED) {
                    w.state = Node.Status.EXPLORED;
                    w.timestamp = n.timestamp + 1;
                    queue.add(w);
                }
            }
        }
    }
}