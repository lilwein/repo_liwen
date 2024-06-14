
import java.util.*; 

public class MinHeap<V> {
	
	private ArrayList<HeapEntry<V>> a; 
	
	/*
	 * Crea un nuovo heap
	 */
	public MinHeap() {
		a = new ArrayList<HeapEntry<V>>(); 
		a.add(null); // per un indirizzamento piu' naturale (radice -> a.get(1))
	}
	
	/*
	 * Restituisce il valore minore del heap mh
	 */
    public HeapEntry<V> getMin() { 
    	if(isEmpty()) return null; 
    	return a.get(1); 
    }
    
    private void upheap(HeapEntry<V> e) {
    	while(e.getIndex() != 1) {
    		int eIdx = e.getIndex(); 
    		int pIdx = eIdx / 2; 
    		HeapEntry<V> p = a.get( pIdx ); 
    		if(e.getKey() >= p.getKey()) break;  
    		a.set( pIdx, e ); 
    		a.set( eIdx, p ); 
    		e.setIndex( pIdx ); 
    		p.setIndex( eIdx ); 
    	}
    }
    
    private boolean hasChildren(HeapEntry<V> e) {
    	return 2*e.getIndex() <= size(); 
    }

    private boolean hasBothChildren(HeapEntry<V> e) {
    	return 2*e.getIndex()+1 <= size(); 
    }
    
    private void downheap(HeapEntry<V> e) {
    	while(hasChildren(e)) {
    		int eIdx = e.getIndex(); 
    		int lIdx = 2*eIdx; 
    		int rIdx = 2*eIdx + 1; 
    		HeapEntry<V> l = a.get( lIdx ); 
    		if(hasBothChildren(e)) {
	    		HeapEntry<V> r = a.get( rIdx ); 
	    		int minIdx = ( r.getKey() < l.getKey() ? rIdx : lIdx ); 
	    		HeapEntry<V> min = a.get( minIdx ); 
	    		if(e.getKey() <= min.getKey()) break; 
	    		a.set( minIdx, e ); 
	    		a.set( eIdx, min );  
	    		e.setIndex( minIdx ); 
	    		min.setIndex( eIdx ); 
    		}
    		else { // e ha solo il figlio sinistro
    			if(e.getKey() <= l.getKey()) break; 
    			a.set( lIdx, e ); 
    			a.set( eIdx, l ); 
    			e.setIndex( lIdx ); 
    			l.setIndex( eIdx ); 
    		}
    	}
    }
    
    /*
     * Inserisce nel heap, il valore value, con priorita' v 
     */
    public HeapEntry<V> insert(double v, V value) {
    	HeapEntry<V> e = new HeapEntry<V>(size()+1, v, value); 
    	a.add(e); 
    	upheap(e); 
    	return e; 
    }
	
    /*
     * Ritorna 1 se minheap e' vuoto, 0 altrimenti
     */
	public boolean isEmpty() { 
		return size()==0; 
	}
    
	/*
	 * Restituisce e rimuove il valore minore del heap
	 */
    public HeapEntry<V> removeMin() {
    	HeapEntry<V> e = getMin(); 
    	HeapEntry<V> last = a.get( size() ); // ultimo elemento
    	a.set( 1, last ); 
    	last.setIndex(1); 
    	a.remove( size() ); 
    	downheap(last); 
    	return e; 
    }
	
    /*
     * Ritorna il numero di elementi presenti nel heap mh
     */
	public int size() { 
		return a.size()-1; 
	}
    
	/*
	 * Ordina l'array che inizia all'indirizzo v, utilizzando heapsort
	 */
	public static void heapsort(double[] v) {
		MinHeap<Object> t = new MinHeap<Object>(); 
		for(int i=0; i<v.length; i++)
			t.insert(v[i], null); 
		int c = 0; 
		while(!t.isEmpty()) {
			v[c++] = t.removeMin().getKey(); 
		}
	}
    
	/*
	 * Cambia l'oggetto puntato da e con value, nel heap
	 */
    public HeapEntry<V> replaceValue(HeapEntry<V> e, V value) {
    	e.setValue(value); 
    	return e; 
    }
    
    /*
     * Cambia la priorita' dell'oggetto puntato da e in key, nel heap
     */
    public HeapEntry<V> replaceKey(HeapEntry<V> e, double key) {
    	double oldKey = e.getKey(); 
    	e.setKey(key); 
    	if(key < oldKey) upheap(e); 
    	else downheap(e); 
    	return e; 
    }
	
    /*
     * Rimuove l'oggetto e dal heap mh
     */
	public HeapEntry<V> remove(HeapEntry<V> e) {
    	HeapEntry<V> last = a.get( size() ); // ultimo elemento
    	a.set( e.getIndex(), last ); 
    	last.setIndex( e.getIndex() ); 
    	a.remove( size() ); 
    	if(last.getKey() < e.getKey()) 
    		upheap(last); 
    	else
    		downheap(last); 
    	return e; 
    }

}

