import java.util.LinkedList;

public class Driver {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("comp_graph")) {
			LinkedList<City> l1 = getCities();
			Graph g = GraphServices.getCompleteGraph(l1);
			System.out.println(g);
		}
		else if(args[0].equals("heap_edges")) {
			LinkedList<City> l1 = getCities();
			Graph g = GraphServices.getCompleteGraph(l1);
			MinHeap<GraphEdge> mh = GraphServices.getMinHeapEdges(g);
			
			while(!mh.isEmpty()) {
				System.out.println(mh.removeMin());
			}
		}
		else if(args[0].equals("mst")) {
			LinkedList<City> l1 = getCities();
			Graph g = GraphServices.getCompleteGraph(l1);
			LinkedList<GraphEdge> mst_list = GraphServices.getMST(g);
			System.out.println(mst_list);
		}
	}
	
	private static void printInfo() {
		System.out.println("Manca argomento: {comp_graph, heap_edges, mst}");
	}
	
	private static LinkedList<City> getCities(){
		LinkedList<City> to_ret = new LinkedList<>();
		
		City c1 = new City("Roma", 41.890, 12.500);
		to_ret.add(c1);
		
		City c2 = new City("Milano", 45.480, 9.190);
		to_ret.add(c2);

		City c3 = new City("Napoli", 40.850, 14.270);
		to_ret.add(c3);

		City c4 = new City("Torino", 45.080, 7.680);
		to_ret.add(c4);

		City c5 = new City("Palermo", 38.120, 13.360);
		to_ret.add(c5);

		City c6 = new City("Genova", 44.420, 8.930);
		to_ret.add(c6);

		City c7 = new City("Bologna", 44.500, 11.340);
		to_ret.add(c7);

		City c8 = new City("Firenze", 43.780, 11.240);
		to_ret.add(c8);
		
		City c9 = new City("Catania", 37.500, 15.080);
		to_ret.add(c9);
	
		City c10 = new City("Bari", 41.120, 16.870);
		to_ret.add(c10);

		return to_ret;
	}
}
