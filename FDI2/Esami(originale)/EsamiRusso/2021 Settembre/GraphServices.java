public class GraphServices<V>{
    public static <V> boolean cycles(Graph<V> g) {
        //reset
        for(Graph.GraphNode<V> n: g.getNodes()){
            n.state = Graph.GrapNode.Status.UNEXPLORED;
            n.timestamp = 0;
        }

        for(Graph.GraphNode<V> n : g.getNodes()){
            if(n.state != Graph.GraphNode.Status.EXPLORED){
                if(BFS_dag(n) == false) return false;
            }
        }
        return true;
    }

    public static <V> boolean BFS_dag(GraphNode<V> n){
        if(n.state == Graph.GraphNode.Status.EXPLORED) return false;
        n.state = Graph.GraphNode.Status.EXPLORED;
        if(n.outEdges == null) return true;
        for(Graph.GrapNode<V> e : n.outEdges){
            return BFS_dag(e);
        }
        return result;
    }
}
    