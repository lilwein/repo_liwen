public class Driver {
	
	private Driver() {}
	
	public static void main(String[] args) {
		if(args.length < 1) {
			printInfo();
		}
		else if(args[0].equals("graph")) {
			Point a = new Point();
			a.x = 1.2;
			a.y = 2.5;
			Point b = new Point();
			b.x = 2.2;
			b.y = 3.7;
			Point c = new Point();
			c.x = 5;
			c.y = 1;
			Point d = new Point();
			d.x = 4.2;
			d.y = 2.2;

			Point[] points = new Point[4];
			points[0] = a;
			points[1] = b;
			points[2] = c;
			points[3] = d;

			Graph g = GraphServices.makeGraph(points);
			System.out.println(g);
		}
		else if(args[0].equals("gbc")) {
			Graph g = new Graph(4);
			g.mat[0][1] = 1.2;
			g.mat[0][2] = 3.7;
			g.mat[0][3] = 0.8;
			g.mat[1][0] = 1.2;
			g.mat[1][2] = 2.8;
			g.mat[1][3] = 5.3;
			g.mat[2][0] = 3.7;
			g.mat[2][1] = 2.8;
			g.mat[2][3] = 1.7;
			g.mat[3][0] = 0.8;
			g.mat[3][1] = 5.3;
			g.mat[3][2] = 1.7;
			g.setnEdges(6);
			System.out.println(g);
			System.out.println("");
			System.out.println("The best connections are:");
			Graph g1 = GraphServices.getBestConnections(g);
			System.out.println(g1);
		}
		else if(args[0].equals("gth")){
			Graph g = new Graph(4);
			g.mat[0][1] = 1.2;
			g.mat[0][3] = 0.8;
			g.mat[1][0] = 1.2;
			g.mat[2][3] = 1.7;
			g.mat[3][0] = 0.8;
			g.mat[3][2] = 1.7;
			g.setnEdges(3);;
			System.out.println(g);
			System.out.format("The height with root %d is: %d\n", 0, GraphServices.getTreeHeight(g, 0));
			System.out.format("The height with root %d is: %d\n", 1, GraphServices.getTreeHeight(g, 1));
			System.out.format("The height with root %d is: %d\n", 2, GraphServices.getTreeHeight(g, 2));
			System.out.format("The height with root %d is: %d\n", 3, GraphServices.getTreeHeight(g, 3));
		}
	}
	private static void printInfo() {
		System.out.println("Manca argomento: {graph, gbc, gth}");
	}
}
