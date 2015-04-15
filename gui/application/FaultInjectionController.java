package application;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import application.Controller;
import application.InputYaml.RuntimeOption;
import javafx.scene.control.Button;

public class FaultInjectionController implements Initializable {
	@FXML
	private TextField noOfRunsText;
	@FXML
	private TextField fiRegIndex;
	@FXML
	private TextField fiBitText;
	@FXML
	private TextField randomSeed;
	@FXML
	private TextField timeOut;
	@FXML
	private Label fiIndexLabel;
	@FXML
	private Slider fiIndexSlider;
	@FXML
	private Label fiCycleLabel;
	@FXML
	private Slider fiCycleSlider;
	@FXML
	private ComboBox<String> faulInjectionTypeCombo;
	@FXML
	private Label runCountLabel;
	@FXML
	private Label runNumberLabel;
	@FXML
	private Button prevRunOption;
	@FXML
	private CheckBox saveProfileCheckBox;
	@FXML
	private TextField profileNameText;

	/**
	 * Folder name or name of the project
	 */
	private String currentFolderName;
	private int currentRun;
	/**
	 * Entered or parsed runtime options list
	 */
	private List<RuntimeOption> runtimeOptions;

	// #SFIT
	// used for making these boxes disappear if Software Injection is selected
	@FXML
	private Node faulInjectionTypeLabel;
	@FXML
	private Node faulInjectionTypeAsterisk;
	@FXML
	private Node fiRegIndexLabel;
	@FXML
	private Node fiBitLabel;

	// for batch mode even less options are available
	@FXML
	private Node faultInjectionCyclesLabel;
	@FXML
	private Node faultInjectionIndexLabel;

	@FXML
	private void onClickDeleteRun(ActionEvent event) {
		runtimeOptions.remove(currentRun);
		changeDisplayedRunOption();
	}

	@FXML
	private void onClickAddRunOption(ActionEvent event) {
		saveCurrentRunOption();
		
		if (runtimeOptions.size() == 0) {
			displayError();
			return;
		}
		
		try {
			// read in the input.yaml then dump the current configurations
			InputYaml input = new InputYaml();
			input.load(new File(currentFolderName + "/input.yaml"));
			input.setRuntimeOption(runtimeOptions);
			input.writeChanges(currentFolderName + "/input.yaml");

			// #SFIT
			// the above options generated needs to be copied over
			if (Controller.isBatchMode) {
				input.copyRunOptionsToSubfolders();
			}

			// clear error box
			Controller.errorString = new ArrayList<>();
			Node source = (Node) event.getSource();
			Stage stage = (Stage) source.getScene().getWindow();
			stage.close();

			// save the input.yaml in another location as well
			if (saveProfileCheckBox.isSelected()) {
				FileChooser fileChooser = new FileChooser();

				// Set extension filter
				FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter(
						"(*.yaml)", "*.yaml");
				fileChooser.getExtensionFilters().add(extFilter);

				// Show save file dialog
				File file = fileChooser.showSaveDialog(stage);

				// user actually selected something
				if (file != null) {
					input.writeChanges(file + ".yaml");
				}
			}
		} catch (IOException e) {
			System.err
					.println("Exception Occured in writing to the input.yaml file");
			e.printStackTrace();
		}
	}

	@FXML
	private void onChangeIndexSlider(MouseEvent e) {
		int slideValue = (int) Math.round(fiIndexSlider.getValue());
		fiIndexLabel.setText(String.valueOf(slideValue));
	}

	@FXML
	private void onChangeRegIndexSlider(MouseEvent e) {
		int slideValue1 = (int) Math.round(fiCycleSlider.getValue());
		fiCycleLabel.setText(String.valueOf(slideValue1));
	}

	@FXML
	private void checkForNumberRuns(KeyEvent event) {
		String regex = "\\d+";
		if (!randomSeed.getText().matches(regex)) {
			randomSeed.setText("");
		}
	}

	@FXML
	private void checkForNumberRegister(KeyEvent event) {
		String regex = "\\d+";
		if (!randomSeed.getText().matches(regex)) {
			randomSeed.setText("");
		}
	}

	@FXML
	private void checkForNumberBit(KeyEvent event) {
		String regex = "\\d+";
		if (!randomSeed.getText().matches(regex)) {
			randomSeed.setText("");
		}
	}

	@FXML
	private void checkForNumberSeed(KeyEvent event) {
		String regex = "\\d+";
		if (!randomSeed.getText().matches(regex)) {
			randomSeed.setText("");
		}
	}

	@FXML
	private void checkForNumberTimeOut(KeyEvent event) {
		String regex = "\\d+";
		if (!timeOut.getText().matches(regex)) {
			timeOut.setText("null");
		}
	}
	
	/**
	 * Displays an error window when the user tries to leave a
	 * run option blank
	 */
	private void displayError() {
		Parent root;
		try {
			root = FXMLLoader.load(getClass().getClassLoader().getResource(
					"application/NextRunOptionPopup.fxml"));
			Stage stage = new Stage();
			stage.setTitle("Error");
			stage.setScene(new Scene(root, 400, 100));
			stage.show();
		} catch (IOException e) {
			System.err.println("ERROR: error displaying error!");
			e.printStackTrace();
		}
	}

	@FXML
	private void onClickNextRunOption(ActionEvent event) {
		// display error if user leaves 'numbers of runs' blank or
		// when fi_type is invalid during hardware fault injection
		if (!isRunOptionValid()) {
			displayError();
		} else {
			// sets the run options
			saveCurrentRunOption();
			// increase the state
			currentRun++;
			// reflect the change in state
			changeDisplayedRunOption();
		}
	}

	@FXML
	private void onClickPrevRunOption(ActionEvent event) {
		// saves current option
		saveCurrentRunOption();
		// decrease the state
		currentRun--;
		// reflect the change in state
		changeDisplayedRunOption();
	}
	
	private boolean isRunOptionValid() {
		return !noOfRunsBlank() && isValidFiType();
	}
	
	private boolean noOfRunsBlank() {
		return noOfRunsText.getText().contentEquals("");
	}
	
	private boolean isValidFiType() {
		if (faulInjectionTypeCombo.getSelectionModel().isEmpty() // means nothing is selected
				&& Controller.isHardwareInjection) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Saves the current run options into a list.
	 */
	private void saveCurrentRunOption() {
		// check if the current run option is valid, otherwise do not save
		if (isRunOptionValid()) {
			RuntimeOption r = new RuntimeOption();

			// options below are required
			r.numOfRuns = Integer.parseInt(noOfRunsText.getText());
			if (Controller.isHardwareInjection) {
				// only exists in hardware injection
				r.fi_type = faulInjectionTypeCombo.getValue();
			} else {
				// #SFIT always autoinjection for software injection
				r.fi_type = "AutoInjection";
			}
			
			// options below are not required
			
			if (!"".equals(fiRegIndex.getText())) {
				r.fi_reg_index = Integer.parseInt(fiRegIndex.getText());
			}
			// if fi_cycle is zero we ignore it
			if (!"0".equals(fiCycleLabel.getText())) {
				r.fi_cycle = Integer.parseInt(fiCycleLabel.getText());
			}
			if (!"".equals(fiBitText.getText())) {
				r.fi_bit = Integer.parseInt(fiBitText.getText());
			}
			// if fi_index is zero we ignore it
			if (!"0".equals(fiIndexLabel.getText())) {
				r.fi_index = Integer.parseInt(fiIndexLabel.getText());
			}
			if (!"".equals(randomSeed.getText())) {
				r.randomSeed = Integer.parseInt(randomSeed.getText());
			}

			if (!"".equals(timeOut.getText())) {
				r.timeOut = Integer.parseInt(timeOut.getText());
			}

			// are we replacing some run option or are we creating a new one?
			if (currentRun >= runtimeOptions.size()) {
				runtimeOptions.add(r);
			} else {
				runtimeOptions.set(currentRun, r);
			}
		}
	}

	/**
	 * When 'currentRun' changes, reflect the change in the GUI
	 */
	private void changeDisplayedRunOption() {
		// set label
		runNumberLabel.setText("run" + currentRun);

		// are we loading some run option or are we displaying a blank one
		if (currentRun < runtimeOptions.size()) {
			// get first run settings
			RuntimeOption run = runtimeOptions.get(currentRun);

			noOfRunsText.setText(String.valueOf(run.numOfRuns));

			if (run.fi_type != null) {
				faulInjectionTypeCombo.setValue(run.fi_type);
			}
			if (run.fi_reg_index != null) {
				fiRegIndex.setText(run.fi_reg_index.toString());
			}
			if (run.fi_cycle != null) {
				fiCycleLabel.setText(run.fi_cycle.toString());
				fiCycleSlider.setValue(run.fi_cycle);
			}
			if (run.fi_bit != null) {
				fiBitText.setText(run.fi_bit.toString());
			}
			if (run.fi_index != null) {
				fiIndexLabel.setText(run.fi_index.toString());
				fiIndexSlider.setValue(run.fi_index);
			} else {
				fiIndexSlider.setValue(0);
				fiIndexLabel.setText("0");
			}
			if (run.randomSeed != null) {
				randomSeed.setText(run.randomSeed.toString());
			}
			if (run.timeOut != null) {
				timeOut.setText(run.timeOut.toString());
			}
		} else {
			// blank run options
			noOfRunsText.setText("");
			faulInjectionTypeCombo.setPromptText("--Select--");
			fiRegIndex.setText("");
			fiRegIndex.setPromptText("null");
			fiBitText.setText("");
			fiBitText.setPromptText("null");
			randomSeed.setText("");
			randomSeed.setPromptText("null");
			timeOut.setText("");
			timeOut.setPromptText("null");
			fiCycleLabel.setText("0");
			fiIndexLabel.setText("0");
			fiIndexSlider.setValue(0);
			fiCycleSlider.setValue(0);
		}

		// user cannot click on 'back' if we are already on the
		// very first run
		if (currentRun == 0) {
			prevRunOption.setDisable(true);
		} else {
			prevRunOption.setDisable(false);
		}
	}

	@Override
	public void initialize(URL url, ResourceBundle rb) {
		// set path variables
		currentFolderName = Controller.currentProgramFolder;

		// #SFIT
		// no need to set these fields in batch mode as they are not
		// displayed or used
		if (!Controller.isBatchMode) {
			try {
				FileReader inputFile;
				String line;

				// get max fi_index
				inputFile = new FileReader(Controller.currentProgramFolder
						+ "/llfi.stat.totalindex.txt");
				BufferedReader bufferReader = new BufferedReader(inputFile);

				String indexBound = "";
				while ((line = bufferReader.readLine()) != null) {
					indexBound = line.split("=")[1];
				}
				bufferReader.close();

				fiIndexSlider.setMax(Double.parseDouble(indexBound));
				fiIndexSlider.setMajorTickUnit(Double.parseDouble(indexBound));

				// get max fi_cycle
				inputFile = new FileReader(Controller.currentProgramFolder
						+ "/llfi.stat.prof.txt");
				bufferReader = new BufferedReader(inputFile);

				while ((line = bufferReader.readLine()) != null) {
					if (line.contains("=")) {
						indexBound = line.split("=")[1];
					}
				}
				bufferReader.close();

				if (indexBound.equalsIgnoreCase("0")) {
					indexBound = "-1";
					fiCycleSlider.setDisable(true);
				}

				fiCycleSlider.setMax(Double.parseDouble(indexBound));
				fiCycleSlider.setMajorTickUnit(Double.parseDouble(indexBound));
			} catch (IOException e) {
				System.err
						.println("ERROR: files (llfi.stat.totalindex.txt or llfi.stat.prof.txt) not found!");
				e.printStackTrace();
			}
		}

		// set possible fault injection types
		faulInjectionTypeCombo.setItems(FXCollections
				.observableArrayList(Controller.configReader.getFaultType()));
		faulInjectionTypeCombo.setPromptText("-- Select --");

		// load current profile
		File input = new File(currentFolderName + "/input.yaml");
		InputYaml parser = new InputYaml();
		parser.load(input);

		// get all runtime options from the file
		runtimeOptions = parser.getRuntimeOptions();

		// show the first run option
		currentRun = 0;
		changeDisplayedRunOption();

		// #SFIT
		// makes these boxes disappear if Software Injection is selected
		if (!Controller.isHardwareInjection) {
			faulInjectionTypeCombo.setVisible(false);
			faulInjectionTypeLabel.setVisible(false);
			faulInjectionTypeAsterisk.setVisible(false);

			fiRegIndex.setVisible(false);
			fiRegIndexLabel.setVisible(false);

			fiBitText.setVisible(false);
			fiBitLabel.setVisible(false);
		}
		// make more boxes disappear if we are doing batch software injection
		if (Controller.isBatchMode) {
			faultInjectionCyclesLabel.setVisible(false);
			fiCycleSlider.setVisible(false);
			fiCycleLabel.setVisible(false);

			faultInjectionIndexLabel.setVisible(false);
			fiIndexSlider.setVisible(false);
			fiIndexLabel.setVisible(false);
		}
	}
}
