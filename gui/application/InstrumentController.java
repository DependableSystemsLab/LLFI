package application;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.RadioButton;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TextField;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import application.Controller;
import application.Controller.State;
import application.InputYaml.InstrumentOption;
import application.InputYaml.RuntimeOption;
public class InstrumentController implements Initializable {

	@FXML
	private ListView<String> instExcludeListView;
	@FXML
	private ListView<String> instIncludeListView;
	@FXML
	private RadioButton instTypeRadio;
	@FXML
	private RadioButton customInstTypeRadio;
	@FXML
	private ComboBox<String> regCombo;
	@FXML
	private RadioButton regTypeRadio;
	@FXML
	private RadioButton customRegTypeRadio;
	@FXML
	private RadioButton noTraceRadio;
	@FXML
	private RadioButton fullTraceRadio;
	@FXML
	private RadioButton limitTraceRadio;
	@FXML
	private Label includeLabel;
	@FXML
	private Button instIncludeButton;
	@FXML
	private Button instExcludeButton;
	@FXML
	private Button regIncludeButton;
	@FXML
	private Button regExcludeButton;
	@FXML
	private CheckBox forwardCheckbox;
	@FXML
	private CheckBox backwardCheckbox;
	@FXML
	private Label regIncludeLabel;
	@FXML
	private TextField traceCountText;
	@FXML
	private Node traceCountLabel;
	@FXML
	private ComboBox<String> customInstCombo;
	@FXML
	private ComboBox<String> customRegCombo;
	@FXML
	private Button createNewProfileButton;
	@FXML
	private CheckBox allCheckBox;
	

	private List<String> fileContent;
	private List<String> includeInstList;
	private List<String> excludeInstList;
	private List<String> removeList;
	private List<String> registerList;
	private List<String> customInstList;
	private List<String> customRegList;
	
	@FXML
	ObservableList<String> items;
	@FXML
	ObservableList<String> includeItems;
	@FXML
	ObservableList<String> tempItems=FXCollections.observableArrayList();
	@FXML
	ObservableList<String> tempItems1=FXCollections.observableArrayList();
	
	private boolean errorFlag;
	public String folderName;
	public String fileName;
	File theDirectory;
	
	// #SFIT
	// used for selection software injection
	@FXML
	private RadioButton software;
	@FXML
	private RadioButton hardware;
	
	@FXML
	private Node registerSelectionMethodLabel;
	@FXML
	private Node separator;
	
	// for determining if the previous runtime option should be kept
	private InstrumentOption previousInstrumentOption;
	private List<RuntimeOption> previousRuntimeOption;
	
	// fiResultDisplay from Controller
	private ComboBox<String> fiResultDisplay;
	
	@FXML
	private void onClickGenerateYamlFile(ActionEvent event) {
		Parent root;
		Controller.console = new ArrayList<String>();
		
		try {
			// delete old folders and files from last fault injection excluding llfi.applicable.software.failures.txt
			String cmd1 = "rm -rf `find ./" + Controller.currentProgramFolder + " -name 'llfi*' ! -name 'llfi.applicable.software.failures.txt'`";
			ProcessBuilder p1 = new ProcessBuilder("/bin/tcsh", "-c", cmd1);
			p1.start().waitFor();
			
			InstrumentOption option = new InstrumentOption();

			// see what type of injection we're doing
			if (Controller.isHardwareInjection) {
				option.isHardwareFault = true;
				
				// set regloc_OR_customRegSelector
				// does not matter for software injection
				if (regTypeRadio.isSelected()) {
					option.regloc_OR_customRegSelector = regCombo.getValue().toString().split("-")[0];
					option.customRegister = false;
				} else {
					option.regloc_OR_customRegSelector = customRegCombo.getValue().toString();
					option.customRegister = true;
				}
			} else {
				option.isHardwareFault = false;
			}

			// see if we are doing custom injection
			if (instTypeRadio.isSelected()) {
				option.customInstruction = false;
				
				ArrayList<String> formattedList = new ArrayList<String>();
				for (String s: instIncludeListView.getItems()) {
					formattedList.add(s.split("-")[0]);
				}
				
				option.includedInstruction = formattedList;
			} else {
				option.customInstruction = true;
				option.includedInstruction = new ArrayList<String>();
				option.includedInstruction.add(customInstCombo.getValue().toString().split("-")[0]);
			}

			// set tracing options
			if (fullTraceRadio.isSelected() || limitTraceRadio.isSelected()) {
				option.tracingEnabled = true;
				option.forwardTrace = forwardCheckbox.isSelected();
				option.backwardTrace = backwardCheckbox.isSelected();
			} else {
				option.tracingEnabled = false;
			}
			if (limitTraceRadio.isSelected()) {
				option.maxTrace = Integer.parseInt(traceCountText.getText());
			} else {
				option.maxTrace = null;
			}
			
			// #SFIT
			// calls the correct script if the user selected more than 1 software fault
			String scriptToCall;
			ObservableList<String> numFaultTypes = instIncludeListView.getItems();
			if (instTypeRadio.isSelected()) {
				numFaultTypes = instIncludeListView.getItems();
			} else {
				// custom instruction is selected
				numFaultTypes = FXCollections.observableArrayList(customInstCombo.getValue().toString());
			}
			Controller.selectedSoftwareFailures = numFaultTypes;
			
			if (Controller.isHardwareInjection || numFaultTypes.size() == 1) {
				scriptToCall = "bin/instrument -lpthread --readable ";
				Controller.isBatchMode = false;
			} else {
				// run batch instrument instead
				scriptToCall = "bin/batchInstrument --readable ";
				Controller.isBatchMode = true;
			}
			
			InputYaml input = new InputYaml();
			
			// if injection mode did not change, keep the same runtime option
			if (!injectionModeChanged() && previousRuntimeOption.size() != 0) {
				input.setRuntimeOption(previousRuntimeOption);
			}
			
			input.setInstrumentOption(option);
			input.writeChanges(Controller.currentProgramFolder + "/input.yaml");
			
			// sets the ComboBox so that the user can select which result to display
			// when fault injection has completed
			if (Controller.isBatchMode) {
				ObservableList<String> displayedFaultResult = FXCollections.observableArrayList(numFaultTypes);
				displayedFaultResult.add(0, "All");
				fiResultDisplay.setItems(displayedFaultResult);
			}
			
			String cmd = Controller.llfibuildPath
					+ scriptToCall + folderName + "/"
					+ folderName + ".ll";
			
			ProcessBuilder p = new ProcessBuilder("/bin/tcsh", "-c", cmd);
			Controller.console.add("$ " + cmd + "\n");

			p.redirectErrorStream(true);
			Process pr = p.start();
			BufferedReader in1 = new BufferedReader(new InputStreamReader(
					pr.getInputStream()));

			Controller.errorString = new ArrayList<>();
			String line1;
			boolean success = false;
			
			while ((line1 = in1.readLine()) != null) {
				/*
				 * if(line1.contains("Sucess")) Controller.errorString = new
				 * ArrayList<>(); else
				 */
				Controller.console.add(line1);
				Controller.errorString.add(line1);

				if (line1.contains("error") || line1.contains("Error")
						|| line1.contains("ERROR"))
					errorFlag = true;
				
				// c++ program is compiled with clang++, but the script will try clang
				// first, which would output some error(s)
				if (line1.contains("Success") || line1.contains("success") ) {
					success = true;
				}

			}
			pr.waitFor();
			in1.close();

			if (errorFlag && !success) {
				errorFlag = false;
				Node source = (Node) event.getSource();
				Stage stage = (Stage) source.getScene().getWindow();
				stage.close();

				root = FXMLLoader.load(getClass().getClassLoader().getResource(
						"application/ErrorDisplay.fxml"));
				stage = new Stage();
				stage.setTitle("Error");
				stage.setScene(new Scene(root, 450, 100));
				stage.show();

			} else {
				// Generate the LLFI .ll file with index labelled.
				// use for the indexed injection
				
				// #SFIT
				// if batch mode, we need to go into one of the generated folder
				// to generated the indexed .ll file
				fileContent = new ArrayList<>();
				String line;
				FileReader inputIndexFile;
				File outputIndexFile = new File(
						Controller.currentProgramFolder + "/"
						+ Controller.currentProgramFolder
						+ "-llfi_displayIndex.ll");
				if (!Controller.isBatchMode) {
					inputIndexFile = new FileReader(
							Controller.currentProgramFolder + "/llfi/"
									+ Controller.currentProgramFolder
									+ "-llfi_index.ll");
				} else {
					// if we are in software batch more, the location of the
					// files changes, so we need to copy files and move the location
					// of some files
					inputIndexFile = new FileReader(
							Controller.currentProgramFolder + "/llfi-"
									+ numFaultTypes.get(0) + "/llfi/"
									+ Controller.currentProgramFolder
									+ "-llfi_index.ll");
					// also copy the llfi.stat.totalindex.txt file out of (one of) the inner folder
					Files.copy(
							Paths.get(Controller.currentProgramFolder + "/llfi-" + numFaultTypes.get(0) + "/llfi.stat.totalindex.txt"),
							Paths.get(Controller.currentProgramFolder + "/llfi.stat.totalindex.txt"));
					// also the dot file for batch trace graph
					Files.copy(
							Paths.get(Controller.currentProgramFolder + "/llfi-" + numFaultTypes.get(0) + "/llfi.stat.graph.dot"),
							Paths.get(Controller.currentProgramFolder + "/llfi.stat.graph.dot"));
				}
				
				// reads llfi/<program>-llfi_index.ll
				BufferedReader bufferReader = new BufferedReader(inputIndexFile);
				while ((line = bufferReader.readLine()) != null) {
					fileContent.add(line + "\n");
				}
				bufferReader.close();
		
				// writes a modified, easily readable file (<program>-llfi_displayIndex.ll)
				BufferedWriter outputFile = new BufferedWriter(new FileWriter(outputIndexFile));
				long index = 0;
				for (int i = 0; i < fileContent.size(); i++) {
					String l = fileContent.get(i);

					if (l.contains("!llfi_index !")) {
						outputFile.write(index++ + "\t\t" + l.substring(0, l.indexOf("!llfi_index !")) + "\n");
					} else if (!l.contains("= metadata !")) {
						outputFile.write("\t\t" + l);
					}
				}
				outputFile.close();
				
				Controller.cs.changeStateTo(State.INSTRUMENT_COMPLETED);
				Controller.errorString.clear();
				
				Node source = (Node) event.getSource();
				Stage stage = (Stage) source.getScene().getWindow();
				stage.close();
			}
		} catch (IOException e) {
			System.err.println("ERROR: instrumentation failed!");
			e.printStackTrace();
		} catch (InterruptedException e) {
			System.err.println("ERROR: instrumentation failed!");
			e.printStackTrace();

		}
	}
	
	private static enum InjectionType {
		HARDWARE, SOFTWARE, SOFTWARE_BATCH;
	}

	private boolean injectionModeChanged() {
		InjectionType current, previous;
		
		// first time doing instrument
		if (previousInstrumentOption == null) {
			return true;
		}
		
		// compute current mode
		if (Controller.isHardwareInjection) {
			current = InjectionType.HARDWARE;
		} else if (Controller.isBatchMode) {
			current = InjectionType.SOFTWARE_BATCH;
		} else {
			current = InjectionType.SOFTWARE;
		}
		
		// compute previous mode
		if (previousInstrumentOption.isHardwareFault) {
			previous = InjectionType.HARDWARE;
		} else {
			if (previousInstrumentOption.includedInstruction.size() > 1) {
				previous = InjectionType.SOFTWARE_BATCH;
			} else {
				previous = InjectionType.SOFTWARE;
			}
		}
		
		if (current == previous) {
			return false;
		} else {
			return true;
		}
	}

	@FXML
	private void onClickInstructionInclude(ActionEvent event) {

		includeInstList = new ArrayList<>();
		if(instIncludeListView.getItems().size() > 0)
		{
			for(int i = 0; i < instIncludeListView.getItems().size();i++ )
			{
				includeInstList.add(instIncludeListView.getItems().get(i).toString());
			}

		}
		removeList = new ArrayList<>();
		if(instExcludeListView.getSelectionModel().getSelectedItems().size() > 0)
		{
			for(int i = 0; i < instExcludeListView.getSelectionModel().getSelectedItems().size();i++ )
			{
				removeList.add(instExcludeListView.getSelectionModel().getSelectedItems().get(i).toString());
				includeInstList.add(instExcludeListView.getSelectionModel().getSelectedItems().get(i).toString());
				//instExcludeListView.getItems().remove(instExcludeListView.getSelectionModel().getSelectedItems().get(i));
			}
		}
		items =FXCollections.observableArrayList (includeInstList);
		instIncludeListView.setItems(items);
		for(int i = 0; i < removeList.size();i++ )
		{
			//System.out.println("selected items = "+removeList.get(i));
			instExcludeListView.getItems().remove(removeList.get(i));
		}

	}
	@FXML
	private void onClickInstructionExclude(ActionEvent event) {


		excludeInstList = new ArrayList<>();
		if(instExcludeListView.getItems().size() > 0)
		{
			for(int i = 0; i < instExcludeListView.getItems().size();i++ )
			{
				excludeInstList.add(instExcludeListView.getItems().get(i).toString());
			}

		}
		removeList = new ArrayList<>();
		if(instIncludeListView.getSelectionModel().getSelectedItems().size() > 0)
		{
			for(int i = 0; i < instIncludeListView.getSelectionModel().getSelectedItems().size();i++ )
			{
				removeList.add(instIncludeListView.getSelectionModel().getSelectedItems().get(i).toString());
				excludeInstList.add(instIncludeListView.getSelectionModel().getSelectedItems().get(i).toString());
			}
		}
		items =FXCollections.observableArrayList (excludeInstList);
		instExcludeListView.setItems(items);
		for(int i = 0; i < removeList.size();i++ )
		{
			instIncludeListView.getItems().remove(removeList.get(i));
		}

	}


	@FXML
	private void enableIncludeMultipleSelection(javafx.scene.input.MouseEvent event){

		instIncludeListView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

	}
	@FXML
	private void enableExcludeMultipleSelection(javafx.scene.input.MouseEvent event){

		instExcludeListView.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

	}

	@FXML
	private void onSelectInstSelectRadio(ActionEvent event){
		if (customInstTypeRadio.isSelected()) {
			customInstCombo.setDisable(false);
			includeLabel.setDisable(true);

			instIncludeListView.setDisable(true);
			instExcludeListView.setDisable(true);
			instIncludeButton.setDisable(true);
			instExcludeButton.setDisable(true);
			
			allCheckBox.setDisable(true);
		} else {
			customInstCombo.setDisable(true);
			includeLabel.setDisable(false);
			
			instIncludeListView.setDisable(false);
			instExcludeListView.setDisable(false);
			instIncludeButton.setDisable(false);
			instExcludeButton.setDisable(false);
			
			allCheckBox.setDisable(false);
		}
	}

	@FXML
	private void onSelectRegSelectRadio(ActionEvent event) {
		if (customRegTypeRadio.isSelected() == true) {
			regCombo.setDisable(true);
			customRegCombo.setDisable(false);
		} else {
			regCombo.setDisable(false);
			customRegCombo.setDisable(true);
		}
	}

	@FXML
	private void onClickTraceOption(ActionEvent event) {
		traceCountText.clear();
		if (noTraceRadio.isSelected()) {
			forwardCheckbox.setDisable(true);
			backwardCheckbox.setDisable(true);
			traceCountText.setDisable(true);
			traceCountLabel.setDisable(true);
		} else if (limitTraceRadio.isSelected()) {
			forwardCheckbox.setDisable(false);
			backwardCheckbox.setDisable(false);
			traceCountText.setDisable(false);
			traceCountLabel.setDisable(false);
		} else { // full trace
			forwardCheckbox.setDisable(false);
			backwardCheckbox.setDisable(false);
			traceCountText.setDisable(true);
			traceCountLabel.setDisable(true);
		}
	}
	
	@FXML
	private void onClickSelectProfile(ActionEvent event){
		Stage stage = new Stage();
		
		FileChooser fileChooser = new FileChooser();
		fileChooser.setTitle("Open an input.yaml file");
		fileChooser.getExtensionFilters().addAll(new FileChooser.ExtensionFilter("YAML", "*.yaml"));
		
		File file = fileChooser.showOpenDialog(stage);
		if (file != null) {
			loadProfile(file);
		}
	}

	private void loadProfile(File file) {
		InputYaml parser = new InputYaml();
		parser.load(file);
		InstrumentOption option = parser.getInstrumentOption();
		
		// runtime option stays the same if
		// injection mode did not change
		previousInstrumentOption = option;
		previousRuntimeOption = parser.getRuntimeOptions();
		
		// set if hardware fault or not
		if (option.isHardwareFault) {
			Controller.isHardwareInjection = true;
		} else {
			Controller.isHardwareInjection = false;
		}
		
		// reset options to the correct ones
		resetAllOptions();
		
		if (option.isHardwareFault) {
			// set register
			if (option.customRegister) {
				regTypeRadio.setSelected(true);
				regCombo.setValue(option.regloc_OR_customRegSelector);
			} else {
				customRegTypeRadio.setSelected(true);
				customRegCombo.setValue(option.regloc_OR_customRegSelector);
			}
			onSelectRegSelectRadio(null);
		}
		
		// set selected instruction
		if (option.customInstruction) {
			// set state
			customInstTypeRadio.setSelected(true);
			
			// set value
			customInstCombo.setValue(option.includedInstruction.get(0));
		} else {
			// set state
			instTypeRadio.setSelected(true);
			
			// find what the new excluded list is
			List<String> newExcludedList;
			List<String> newIncludedList = new ArrayList<String>();
			if (Controller.isHardwareInjection) {
				newExcludedList = Controller.configReader.getInstruction();
			} else {
				newExcludedList = getApplicableSoftwareFailures();
			}
			for (String exclude: instExcludeListView.getItems()) {
				for (String include: option.includedInstruction) {
					if (include.equals(exclude.split("-")[0])) {
						newExcludedList.remove(exclude);
						newIncludedList.add(exclude);
						break;
					}
				}
			}
			
			// set excluded list
			instExcludeListView.setItems(FXCollections.observableArrayList(newExcludedList));
			// set included list
			instIncludeListView.setItems(FXCollections.observableArrayList(newIncludedList));
		}
		onSelectInstSelectRadio(null);
		
		// reset all checkbox #TODO does this run the allcheckbox function???
		allCheckBox.setSelected(false);

		// reset trace state
		if (option.maxTrace != null) {
			limitTraceRadio.setSelected(true);
		} else if (option.tracingEnabled) {
			fullTraceRadio.setSelected(true);
		} else {
			noTraceRadio.setSelected(true);
		}
		onClickTraceOption(null);
		
		// set trace count if exists
		if (option.maxTrace != null) {
			traceCountText.setText("" + option.maxTrace.intValue());
		}
	}

	/**
	 * Should be called 'reset profile' instead
	 * @param event
	 */
	@FXML
	private void onClickCreateNewProfile(ActionEvent event)
	{
		File yFile = new File(folderName+"/input.yaml");
		yFile.delete();
		resetAllOptions();
		Controller.cs.changeStateTo(State.COMPILE_COMPLETED);
	}

	@FXML
	public void onClickAll(ActionEvent e) {
		resetInstList(allCheckBox.isSelected());
	}

	/**
	 * Reset selection boxes to all software or hardware fault, depending on state of
	 * @param isSelectAll - this variable
	 */
	private void resetInstList(boolean isSelectAll) {
		List<String> allApplicableFaults;
		if (Controller.isHardwareInjection) {
			allApplicableFaults = Controller.configReader.getInstruction();
		} else {
			allApplicableFaults = getApplicableSoftwareFailures();
		}
		items = FXCollections.observableArrayList(allApplicableFaults);
		ObservableList<String> blankList = FXCollections
				.observableArrayList(new ArrayList<String>());

		if (isSelectAll) {
			instExcludeListView.setItems(blankList);
			instIncludeListView.setItems(items);
		} else {
			instIncludeListView.setItems(blankList);
			instExcludeListView.setItems(items);
		}
	}
	
	/**
	 * Reset the InstrumentOption to reflect hardware or software injection.
	 */
	private void resetAllOptions() {
		// RESETS / REREADS ALL FILES
		
		// reset register list
		registerList = Controller.configReader.getRegister();
		regCombo.setItems(FXCollections.observableArrayList(registerList));
		regCombo.setPromptText("-- Select --");
		
		// reset custom register list
		customRegList = Controller.configReader.getCustomRegister();
		customRegCombo.setItems(FXCollections.observableArrayList(customRegList));
		customRegCombo.setPromptText("-- Select --");
		
		// reset the included/excluded instruction list
		resetInstList(false);
		
		// reset custom instruction list
		if (Controller.isHardwareInjection) {
			customInstList = Controller.configReader.getCustomInstruction();
		} else {
			customInstList = Controller.configReader.getCustomSoftwareFault();
		}
		customInstCombo.setItems(FXCollections.observableArrayList(customInstList));
		customInstCombo.setPromptText("-- Select --");
		
		// RESET STATES
		
		// reset all checkbox
		allCheckBox.setSelected(false);
		
		// reset included / excluded inst
		instTypeRadio.setSelected(true);
		onSelectInstSelectRadio(null);
	
		// reset register selection state
		regTypeRadio.setSelected(true);
		onSelectRegSelectRadio(null);

		// reset trace state
		fullTraceRadio.setSelected(true);
		onClickTraceOption(null);
		
		// switch display between hardware/software injection
		changeInjectionDisplay(Controller.isHardwareInjection);
	}
	
	/**
	 * #SFIT opens llfi.applicable.software.failures.txt and read it into the list.
	 * If the file does not exist, it will generate one.
	 * @return - the list of applicable software failures
	 */
	private List<String> getApplicableSoftwareFailures() {
		FileReader applicableSoftwareFailure = null;
		String inputLocation = folderName + "/llfi.applicable.software.failures.txt";
		try {
			applicableSoftwareFailure = new FileReader(inputLocation);
		} catch (FileNotFoundException e) {
			// file not found, generate one
			Controller.softwareFailureAutoScan();
			try {
				applicableSoftwareFailure = new FileReader(inputLocation);
			} catch (FileNotFoundException e1) {
				System.err.println("ERROR: Unable to read " + inputLocation);
				e1.printStackTrace();
				return null;
			}
		}
		
		String line;
		BufferedReader bufferedReader = new BufferedReader(applicableSoftwareFailure);
		ArrayList<String> softwareFailure = new ArrayList<String>();
		
		try {
			// discard first line, as it is not a software failure
			bufferedReader.readLine();
			
			// read in all software failure, discarding everything before the dash
			while ((line = bufferedReader.readLine()) != null)   {
				softwareFailure.add(line.substring(line.indexOf("-") + 2));
			}
			bufferedReader.close();
		} catch (IOException e) {
			System.err.println("InstrumentController: Unable to read " + inputLocation);
			e.printStackTrace();
		} 
		
		return softwareFailure;
	}
	
	/**
	 * Change GUI state to Hardware Fault Injection
	 * @param e
	 */
	@FXML
	private void onClickChangeInjectionType(ActionEvent e) {
		if (hardware.isSelected()) {
			Controller.isHardwareInjection = true;
		} else {
			Controller.isHardwareInjection = false;
		}
		resetAllOptions();
	}
	
	private void changeInjectionDisplay(boolean isHardwareInjection) {
		if (!isHardwareInjection) {
			software.setSelected(true);
			
			// makes these boxes disappear
			customRegTypeRadio.setVisible(false);
			registerSelectionMethodLabel.setVisible(false);
			separator.setVisible(false);
			regTypeRadio.setVisible(false);
			regCombo.setVisible(false);
			customRegCombo.setVisible(false);
		} else {
			hardware.setSelected(true);
			
			// make these boxes appear
			customRegTypeRadio.setVisible(true);
			registerSelectionMethodLabel.setVisible(true);
			separator.setVisible(true);
			regTypeRadio.setVisible(true);
			regCombo.setVisible(true);
			customRegCombo.setVisible(true);
		}
	}
	
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		folderName = Controller.currentProgramFolder;
		
		// load profile if exist (user is re-instrumenting)
		File f = new File(Controller.currentProgramFolder + "/input.yaml");
		
		if(f.exists()) {
			createNewProfileButton.setDisable(false);
			fileContent = new ArrayList<>();

			loadProfile(f);
		} else {
			resetAllOptions();
		}
	} 
	
	/**
	 * fiResultDisplay from Controller.class needs to be passed to this controller
	 * after initialization. See http://stackoverflow.com/questions/14187963/passing-parameters-javafx-fxml
	 * @param fiResultDisplay
	 */
	public void initFiResultDisplay(ComboBox<String> fiResultDisplay) {
		this.fiResultDisplay = fiResultDisplay;
	}
}
