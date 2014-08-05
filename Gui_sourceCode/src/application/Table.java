package application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;


public class Table {

    SimpleIntegerProperty noIndex;
    SimpleIntegerProperty noCycles;

    public Table(int noIndex, int noCycles) {
        this.noIndex = new SimpleIntegerProperty(noIndex);
        this.noCycles = new SimpleIntegerProperty(noCycles);
        
    } 

    public Integer getNoIndex() {
		return noIndex.get();
	}

	public void setNoIndex(Integer v) {
		this.noIndex.set(v);
	}

	public Integer getNoCycles() {
		return noCycles.get();
	}

	public void setNoCycles(Integer d) {
		this.noCycles.set(d);;
	}

	
}