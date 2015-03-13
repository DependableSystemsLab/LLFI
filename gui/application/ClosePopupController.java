package application;

import java.net.URL;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.stage.Stage;

@Deprecated
public class ClosePopupController implements Initializable {
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

