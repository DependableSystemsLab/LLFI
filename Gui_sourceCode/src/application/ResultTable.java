package application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;

public class ResultTable {


    SimpleIntegerProperty noOfRuns;
    SimpleStringProperty failureClass;
    SimpleStringProperty failureMode;
    SimpleStringProperty functionName;
    SimpleStringProperty FaultInjectionType;
    SimpleIntegerProperty index;
    SimpleIntegerProperty cycle;
    
    SimpleIntegerProperty bit;
    SimpleStringProperty sdc;
    SimpleStringProperty status;
    SimpleStringProperty result;



    public ResultTable(int noOfRuns,String failureClass,String failureMode,String functionName,String FaultInjectionType,int index,int cycle,int bit,
    		String sdc,String status,String result) {
        this.noOfRuns = new SimpleIntegerProperty(noOfRuns);
        this.failureClass = new SimpleStringProperty(failureClass);
        this.failureMode = new SimpleStringProperty(failureMode);
        this.functionName = new SimpleStringProperty(functionName);
        this.FaultInjectionType = new SimpleStringProperty(FaultInjectionType);
        this.index = new SimpleIntegerProperty(index);
        this.cycle = new SimpleIntegerProperty(cycle);
        
        
        this.bit = new SimpleIntegerProperty(bit);
        this.sdc = new SimpleStringProperty(sdc);
        this.status = new SimpleStringProperty(status);
        this.result = new SimpleStringProperty(result);
       
    } 

    public Integer getNoOfRuns() {
		return noOfRuns.get();
	}

	public void setNoOfRuns(Integer v) {
		this.noOfRuns.set(v);
	}
	
	public String getFailureClass() {
		return failureClass.get();
	}

	public void setFailureClass(String fc) {
		this.failureClass.set(fc);
	}
	public String getFailureMode() {
		return failureMode.get();
	}

	public void setFailureMode(String fm) {
		this.failureMode.set(fm);
	}
	public String getFunctionName() {
		return functionName.get();
	}

	public void setFunctionName(String fn) {
		this.functionName.set(fn);
	}

	public String getFaultInjectionType() {
		return FaultInjectionType.get();
	}

	public void setFaultInjectionType(String d) {
		FaultInjectionType.set(d);
	}

	public Integer getIndex() {
		return index.get();
	}

	public void setIndex(Integer n) {
		this.index.set(n);
	}

	public Integer getCycle() {
		return cycle.get();
	}

	public void setCycle(Integer c) {
		this.cycle.set(c);
	}

	

	public Integer getBit() {
		return bit.get();
	}

	public void setBit(Integer b) {
		this.bit.set(b);;
	}
	public String getSdc() {
		return sdc.get();
	}

	public void setSdc(String sd) {
		this.sdc.set(sd);
	}
	public String getStatus() {
		return status.get();
	}

	public void setStatus(String s) {
		this.status.set(s);
	}

	public String getResult() {
		return result.get();
	}

	public void setResult(String e) {
		this.result.set(e);;
	}

	

}
