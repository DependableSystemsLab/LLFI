package application;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import application.Controller;

@Deprecated
public class ProfilingController implements Initializable{
	
	@FXML 
	private TextField programInputText;
	@FXML
	private void onClickProfile(ActionEvent event)
	{
		try{
			ProcessBuilder p = new ProcessBuilder("/bin/tcsh","-c",Controller.llfibuildPath+"bin/profile "+Controller.currentProgramFolder+"/llfi/"+Controller.currentProgramFolder+"-profiling.exe "+programInputText.getText());
		    
		    p.redirectErrorStream(true);
		    Process pr = p.start();
			BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
		    String line1;
		    while ((line1 = in1.readLine()) != null) {
		        System.out.println(line1);
		    }
		    pr.waitFor();
		  in1.close();
		}catch(IOException e){
			 e.printStackTrace();  
			    System.out.println(e);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			 System.out.println(e.getMessage());
		}
        
		
	}
	
	@FXML
	private void onClickOkHandler(ActionEvent event){
		
		
		Node  source = (Node)  event.getSource(); 
	    Stage stage  = (Stage) source.getScene().getWindow();
	    stage.close();
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
	    // TODO

}
}
