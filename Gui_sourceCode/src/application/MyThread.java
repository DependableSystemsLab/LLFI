package application;

import java.io.BufferedReader;
import java.io.Console;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

import com.sun.glass.ui.Platform;

import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class MyThread extends Thread
{
	
   private int startIdx, nThreads, maxIdx;
   private boolean errorFlag;
   public MyThread()
   {
   }
   //
   @Override
   public void run()
   {
	   
	  
	   Parent root;
	   try{
		   Controller.console = new ArrayList<String>(); 
		   
		   ProcessBuilder p = new ProcessBuilder("/bin/tcsh","-c",Controller.llfibuildPath+"bin/injectfault "+Controller.currentProgramFolder+"/llfi/"+Controller.currentProgramFolder+"-faultinjection.exe "+Controller.inputString);
		   Controller.console.add("$ "+Controller.llfibuildPath+"bin/injectfault "+Controller.currentProgramFolder+"/llfi/"+Controller.currentProgramFolder+"-faultinjection.exe"+Controller.inputString+"\n");
		    p.redirectErrorStream(true);
		    Process pr = p.start();
		    
			BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
		    String line1;
		    while ((line1 = in1.readLine()) != null) {
		    	 Controller.console.add(line1+"\n");
		    	Controller.errorString.add(line1+"\n");
		    	if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
		    		errorFlag= true;
		    	
		        
		    }
		    pr.waitFor();
		   in1.close();
		   pr.destroy(); 
		   javafx.application.Platform.runLater(new Runnable() {
			   @Override
		        public void run() {
				   try{
				   if(errorFlag == true)
					  {
					   //progressBar.visibleProperty().unbind();
					   //progressBar.setVisible(false);
					   //indicator.setVisible(false);
						  errorFlag = false;
						 
						  
						    Parent root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ErrorDisplay.fxml"));
						    Stage stage = new Stage();
					        stage.setTitle("Error");
					        stage.setScene(new Scene(root, 450, 100));
					        stage.show();
					        
					  }
					  else
					  {
						  //progressBar.visibleProperty().unbind();
						  //progressBar.setVisible(false);
						  //indicator.setVisible(false);
						 // onGeneratingResultTable();
						 // generateFaultSummaryGraph();
						  
						  //tabBottom.getSelectionModel().select(faultStatus);
						 // Node  source = (Node)  event.getSource(); 
						  //Stage stage  = (Stage) source.getScene().getWindow();
						  //stage.close();
					  }
		        }catch (IOException e) {
		 	       System.err.println("Problem writing to the file statsTest.txt");
			    }
			   }
		   });  
		    Thread.sleep(1000);
		  
	   
	  
	   }catch (IOException e) {
	       System.err.println("Problem writing to the file statsTest.txt");
	    }
		catch (InterruptedException e) {
	    	System.out.println(e);
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	   
   
   }
   
   
}
