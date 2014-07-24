package application;

 
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

import javafx.collections.ObservableList;
import javafx.concurrent.Task;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import application.Controller;



public class ProgressBarController implements Initializable{
	
	public int totalRunCount = 0;
	public int currentCount = 0;
	@FXML
	private ProgressBar progressBar;
	@FXML
	private ProgressIndicator indicator;
	@FXML
	private TextField runText;
	@FXML
	private void onClickOkHandler(ActionEvent event){
		
		
		Node  source = (Node)  event.getSource(); 
	    Stage stage  = (Stage) source.getScene().getWindow();
	    stage.close();
	}
	

	@Override
	public void initialize(URL url, ResourceBundle rb) {
	    // TODO
	try{
		
	FileReader inputFile = new FileReader(Controller.currentProgramFolder+"/input.yaml");
	BufferedReader bufferReader = new BufferedReader(inputFile);
    String line;
 
   while ((line = bufferReader.readLine()) != null)   {
 	if(line.contains("numOfRuns"))
 	{
 		totalRunCount = totalRunCount+Integer.parseInt(line.split(":")[1].trim());
 	}
 	}
   runText.setText(Integer.toString(totalRunCount));
	/*	//System.out.println("\ntotalRunCount ="+totalRunCount);
		File file = new File(Controller.currentProgramFolder+"/llfi/llfi_stat_output/");
		 
		if(file.isDirectory()){
	 
			if(file.list().length>0){
				currentCount = file.listFiles().length;
			}
		}*/
  	 // if(currentCount != totalRunCount)
  		 
  		  //System.out.println("currentCount = "+currentCount);
			
		//progressBar.visibleProperty().bind(event..progressProperty().lessThan(1));
		//
		//tabBottom.getSelectionModel().select(faultStatus);
		progressBar.setVisible(true);
		//indicator.setVisible(true);
		//indicator.setProgress(-1);
		//progressBar.setProgress(-1);
		Task<Void> task = new Task<Void>()
		{
			 @Override public Void call()
			 {
				 
				 int parts = 0;
				 int i = 0;
				 int listCount=0;
				 String tempName=null;
				// System.out.println("i = "+i);
				 while( i <= totalRunCount) {
			          try {
			        	  //System.out.println("i1 = "+Controller.currentProgramFolder+"/llfi/llfi_stat_output/");
			        	  File file = new File(Controller.currentProgramFolder+"/llfi/llfi_stat_output/");
			        	  listCount=0;
			      		if(file.isDirectory()){
			      			File[] listOfFiles = file.listFiles();
			      			if(listOfFiles.length>0){
			      				for(int k = 0;k<listOfFiles.length;k++)
			      				{
			      					tempName = listOfFiles[k].getName();
			      					//tempName = "he";
			      					if(tempName.contains("injectedfaults"))
						    		{
			      						//System.out.println(listOfFiles[k].getName());
			      						listCount++;
						    		}
			      					/*if(tempName.equalsIgnoreCase("llfi"));
			      					{
			      						System.out.println(listOfFiles[k].getName());
			      						listCount++;
			      					}*/
			      					
			      					
			      				}
			      		    currentCount = listCount;
			      		  //System.out.println(currentCount);
			         	 // if(currentCount != totalRunCount)
			         		 
			         		  //System.out.println("currentCount = "+currentCount);
			      			}
			      			}
			        	  
			        	 // if(currentCount != totalRunCount)
			        		  i=currentCount;
			        		  //System.out.println("currentCount = "+currentCount);
			            Thread.sleep(1000);
			          } catch (InterruptedException e) {
			            e.printStackTrace();
			          }
			          //System.out.println(i);
			          updateProgress(i, totalRunCount);
			            if(i== totalRunCount)
			          {
			        	 try {
							Thread.sleep(1000);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
			        	 // indicator.setVisible(false);
			        	 
			        	 // progressBar.setVisible(false);
			        	  //onGeneratingResultTable();
			        	 // generateFaultSummaryGraph();
			        	 // 
			        	  
			        	  Controller.errorString = new ArrayList<>();
			        	 
						 
				           
			          }
			        	  
			        }
				 return null;
			 }
		};
		
		  MyThread t1 = new MyThread();
	    
	        t1.start();
	       // Thread.sleep(2000);
	        progressBar.progressProperty().bind(task.progressProperty());
            indicator.progressProperty().bind(task.progressProperty());
	        Thread th = new Thread(task);
	        th.setDaemon(true);
	        th.start();
	        
	        
		
	    
	}catch (Exception e) {
	      System.err.println("Problem writing to the file statsTest.txt");
	   }

}
}
