package application;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
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
public class SaveProfileController implements Initializable{
	
	@FXML 
	private TextField profileNameText;
	
	
	@FXML
	private void onClickOkHandler(ActionEvent event){
		
		 String profileName;
		 String fileContent = "";
		 FileReader actualFile;
		 String line;
		try {
			actualFile = new FileReader(Controller.currentProgramFolder+"/input.yaml");
		
		 BufferedReader bufferReader1 = new BufferedReader(actualFile);
		 //profileName = checkFileName(profileCount);
		 profileName = profileNameText.getText();
	    	

		    File profileFile = new File(Controller.currentProgramFolder+"/"+profileName+".yaml");
	        FileOutputStream is1 = new FileOutputStream(profileFile);
	        OutputStreamWriter osw1 = new OutputStreamWriter(is1); 
	        Writer w1 = new BufferedWriter(osw1);
		    
				while ((line = bufferReader1.readLine()) != null)   {
					fileContent = line+"\n";		        
				    w1.write(fileContent);
				
				}
			 
		    w1.close();
		
		Node  source = (Node)  event.getSource(); 
	    Stage stage  = (Stage) source.getScene().getWindow();
	    stage.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Node  source = (Node)  event.getSource(); 
	    Stage stage  = (Stage) source.getScene().getWindow();
	    stage.close();
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
	    // TODO

}
}
