import java.util.*;

public class BSTServices {
	
	public void inOrder(Node nd , LinkedList<Integer> l ){
		if(nd == null) return ;
		
		inOrder(nd.left , l);
		l.add(nd.key);
		inOrder(nd.right , l);
	}

	public LinkedList ordina(BST t) {
		LinkedList<Integer> l = new LinkedList<Integer>();
		inOrder(t.root(),l);
		// DA IMPLEMENTARE
		return l;
	}
		
	public void inOrderK1K2(Node nd , LinkedList<Integer> l , int k1 , int k2){
		if(nd == null) return ;
		
		inOrderK1K2(nd.left , l,k1,k2);
		if( nd.key < k1 || nd.key > k2) l.add(nd.key);
		inOrderK1K2(nd.right , l,k1,k2);
	}	
		
	public LinkedList outer_range(BST t, int k1, int k2) {
		LinkedList<Integer> l = new LinkedList<Integer>();
		inOrderK1K2(t.root(),l,k1,k2);
		// DA IMPLEMENTARE
		
		return l;
	}
	
	public int inOrderH(Node nd ,int h ){
		int sum = h;
		if(nd == null) return sum;
		sum += 1;
		int h1 = inOrderH(nd.left , sum);
		int h2 = inOrderH(nd.right , sum);
		
		return (h1 >= h2) ? h1 : h2;
	}
	
	public int altezza(BST t) {
		
		// DA IMPLEMENTARE
		
		return inOrderH(t.root(),-1);
	}
		
}
