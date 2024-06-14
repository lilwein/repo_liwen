public class Graph {
	
	double[][] mat;
	private int nVertices;
	private int nEdges;
	
	public enum Status {UNEXPLORED, EXPLORED, EXPLORING};
	
	public Graph(int nNodi) {
		this.nVertices = nNodi;
		this.nEdges = 0;
		mat = new double[nNodi][nNodi];
		for (int i = 0; i < nNodi; ++i) {
			for (int j = 0; j < nNodi; ++j) {
				mat[i][j] = -1;
			}
		}
	}
	
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for( int i = 0; i < this.nVertices; ++i) {
			sb.append("\t" + i);
		}
		sb.append("\n");
		for( int i = 0; i < this.nVertices; ++i) {
			sb.append(i + "\t");
			for (int j = 0; j < this.nVertices; ++j) {
				sb.append(mat[i][j] + "\t");
			}
			sb.append("\n");
		}
		sb.append("The graph has " + nVertices + " nodes and " + nEdges + " edges.\n");
		return sb.toString();
	}

	public double[][] getMat() {
		return mat;
	}

	public void setMat(double[][] mat) {
		this.mat = mat;
	}

	public int getnVertices() {
		return nVertices;
	}

	public void setnVertices(int nVertices) {
		this.nVertices = nVertices;
	}

	public int getnEdges() {
		return nEdges;
	}

	public void setnEdges(int nEdges) {
		this.nEdges = nEdges;
	}
	
}
                                  