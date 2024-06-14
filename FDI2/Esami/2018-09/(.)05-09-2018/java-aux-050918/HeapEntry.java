/**
 * Entry a chiave intera e valore generico
 */
public class HeapEntry<V> {
    /**
     * indice in cui e' memorizzato il valore
     */
    private int index;

    /**
     * chiave (su cui si fa l'ordinamento)
     */
    private double key;

    /**
     * valore
     */
    private V value;

    public HeapEntry(int index, double v, V value) {
        this.index = index;
        this.key = v;
        this.value = value;
    }

    public int getIndex() {
        return index;
    }

    public double getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public void setKey(double key2) {
        this.key = key2;
    }

    public void setValue(V value) {
        this.value = value;
    }
    
    public String toString() {
    	return "[chiave: "+key+", valore: "+value+"]"; 
    }
}
