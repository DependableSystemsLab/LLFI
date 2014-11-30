package application;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.SimpleBooleanProperty;

import javafx.event.ActionEvent;
import javafx.beans.value.ChangeListener;

public class ResultTable {


    SimpleIntegerProperty noOfRuns;
    
    SimpleStringProperty FaultInjectionType;
    SimpleIntegerProperty index;
    SimpleIntegerProperty cycle;
    
    SimpleIntegerProperty bit;
    SimpleStringProperty sdc;
    SimpleStringProperty status;
    SimpleStringProperty result;
    SimpleBooleanProperty trace;




    public ResultTable(int noOfRuns,String FaultInjectionType,int index,int cycle,int bit,
    		String sdc,String status,String result,Boolean trace) {
        this.noOfRuns = new SimpleIntegerProperty(noOfRuns);
        
        this.FaultInjectionType = new SimpleStringProperty(FaultInjectionType);
        this.index = new SimpleIntegerProperty(index);
        this.cycle = new SimpleIntegerProperty(cycle);
        
        
        this.bit = new SimpleIntegerProperty(bit);
        this.sdc = new SimpleStringProperty(sdc);
        this.status = new SimpleStringProperty(status);
        this.result = new SimpleStringProperty(result);
        this.trace = new SimpleBooleanProperty(trace);

//         this.trace.addListener(new ChangeListener<Boolean>() {

//            @Override
//            public void changed(ObservableValue<? extends Boolean> ov, Boolean oldval, Boolean newval) {
//                System.out.println("The check Box is: " + newval);
//            }
//        });

    }
    

    public Integer getNoOfRuns() {
		return noOfRuns.get();
	}

	public void setNoOfRuns(Integer v) {
		this.noOfRuns.set(v);
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
		this.result.set(e);
	}
	public SimpleBooleanProperty traceProperty() 
	{
	return trace;
	}

	public Boolean getTrace() {
		return trace.get();
	}

	public void setTrace(Boolean e) {
		this.trace.set(e);
	}

	

}
