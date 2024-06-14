public class Driver {
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("nconn")) {
			Graph g = new Graph();
			GraphNode a = g.addNode("a");
			GraphNode b = g.addNode("b");
			GraphNode c = g.addNode("c");

			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(c, b);

			System.out.println("################################");
			System.out.println("Primo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_conn_comp -> " + GraphServices.connComp(g));
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");

			System.out.println("################################");
			System.out.println("Secondo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_conn_comp -> " + GraphServices.connComp(g));
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			GraphNode d = g.addNode("d");

			g.addEdge(a, b);
			g.addEdge(c, b);
			g.addEdge(d, c);

			System.out.println("################################");
			System.out.println("Terzo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_conn_comp -> " + GraphServices.connComp(g));
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			g.addNode("e");

			g.addEdge(a, b);
			g.addEdge(c, d);

			System.out.println("################################");
			System.out.println("Quarto test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_conn_comp -> " + GraphServices.connComp(g));
			System.out.println();
		}
		else if(args[0].equals("contract")) {
			Graph g = new Graph();
			GraphNode a = g.addNode("a");
			GraphNode b = g.addNode("b");
			GraphNode c = g.addNode("c");
			GraphNode d = g.addNode("d");
			GraphNode e = g.addNode("e");

			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(d, e);
			g.addEdge(a, d);

			System.out.println("################################");
			System.out.println("Primo test");
			System.out.println("################################");
			System.out.println(g);
			GraphServices.contract(g);
			System.out.println("Contracted Graph:");
			System.out.println(g);
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			e = g.addNode("e");

			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(b, c);
			g.addEdge(d, e);

			System.out.println("################################");
			System.out.println("Secondo test");
			System.out.println("################################");
			System.out.println(g);
			GraphServices.contract(g);
			System.out.println("Contracted Graph:");
			System.out.println(g);
			System.out.println();
		}
		else if(args[0].equals("count")) {
			Graph g = new Graph();
			GraphNode a = g.addNode("a");
			GraphNode b = g.addNode("b");
			GraphNode c = g.addNode("c");
			GraphNode d = g.addNode("d");
			GraphNode e = g.addNode("e");
			GraphNode f = g.addNode("f");

			g.addEdge(a, b);
			g.addEdge(a, d);
			g.addEdge(d, b);
			g.addEdge(d, e);
			g.addEdge(d, f);
			g.addEdge(b, c);

			System.out.println("################################");
			System.out.println("Primo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_k3 -> " + GraphServices.countK3(g));
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			e = g.addNode("e");

			g.addEdge(a, b);
			g.addEdge(a, c);
			g.addEdge(d, b);
			g.addEdge(d, c);
			g.addEdge(b, c);
			g.addEdge(d, e);
			g.addEdge(e, b);
			
			System.out.println("################################");
			System.out.println("Secondo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_k3 -> " + GraphServices.countK3(g));
			System.out.println();

			g = new Graph();
			a = g.addNode("a");
			b = g.addNode("b");
			c = g.addNode("c");
			d = g.addNode("d");
			e = g.addNode("e");
			f = g.addNode("f");
			
			g.addEdge(a, b);
			g.addEdge(b, c);
			g.addEdge(c, d);
			g.addEdge(d, e);
			g.addEdge(e, f);

			System.out.println("################################");
			System.out.println("Terzo test");
			System.out.println("################################");
			System.out.println(g);
			System.out.println("n_k3 -> " + GraphServices.countK3(g));
			System.out.println();
		}
	}
	
	private static void printInfo() {
		System.out.println("Manca argomento: {nconn, contract, count}");
	}
}
