public class GraphServices<V> {

    public static <V> int max_dist(Graph<V> g, Graph.GraphNode<V> source) {
        // reset the graph
        for(Graph.GraphNode<V> n : g.getNodes()) {
            n.timestamp = 0;
            n.state = Graph.GraphNode.Status.UNEXPLORED;
        }

        int ret = 0;
        LinkedList<Graph.GraphNode<V>> queue = new LinkedList<>();
        queue.add(source);
        source.state = Graph.GraphNode.Status.EXPLORED;
        while(!queue.isEmpty()){
            Graph.GraphNode<V> n = queue.remove();
            for(Graph.GraphNode<V> adj : n.outEdges){
                if(adj.state == Graph.GraphNode.Status.UNEXPLORED){
                    adj.state = Graph.GraphNode.Status.EXPLORED;
                    adj.timestamp = n.timestamp + 1;
                    queue.add(adj);
                }
            }
            if(n.timestamp > ret) ret = n.timestamp;
        }
        return ret;
    }
}