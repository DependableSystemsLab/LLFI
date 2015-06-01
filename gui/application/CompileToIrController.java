package application;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import application.Controller;

public class CompileToIrController implements Initializable{
	@FXML
	private Label compileFileText;
	@FXML
	private void onClickOkHandler(ActionEvent event){
		Node  source = (Node)  event.getSource(); 
	    Stage stage  = (Stage) source.getScene().getWindow();
	    stage.close();
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		compileFileText.setText(Controller.currentProgramFolder+".ll has been created !!!");
	    // TODO
		
	}
}
