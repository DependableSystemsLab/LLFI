package application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;


public class Table {

	SimpleStringProperty failureType;
    SimpleIntegerProperty noIndex;
    SimpleIntegerProperty noCycles;

    public Table(String failureType, int noIndex, int noCycles) {
        this.noIndex = new SimpleIntegerProperty(noIndex);
        this.noCycles = new SimpleIntegerProperty(noCycles);
        this.failureType = new SimpleStringProperty(failureType);
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
		this.noCycles.set(d);
	}
	
	public void setFailureType(String failureType) {
		this.failureType.set(failureType);
	}

	public String getFailureType() {
		return this.failureType.get();
	}
}