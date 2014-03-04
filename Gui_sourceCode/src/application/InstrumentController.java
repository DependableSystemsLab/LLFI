package application;
import java.awt.Checkbox;
import java.awt.event.MouseEvent;
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
import java.lang.reflect.Array;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import com.sun.javafx.scene.control.skin.ListViewSkin;
import com.sun.javafx.sg.PGShape.Mode;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Cursor;
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
public class InstrumentController implements Initializable {
	
	@FXML
	private ListView instExcludeListView;
	@FXML
	private ListView instIncludeListView;
	@FXML
	private RadioButton instTypeRadio;
	@FXML
	private RadioButton customInstTypeRadio;
	@FXML
	private ComboBox regCombo;
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
	private ComboBox customInstCombo;
	@FXML
	private ComboBox customRegCombo;
	@FXML
	private Button createNewProfileButton;
	
	private List<String> fileContent;
	private String selectedInstSelectionMethod;
	private String selectedRegSelectionMethod;
	private String selectedTraceMethod;
	private ArrayList<String> includeInstList;
	private ArrayList<String> excludeInstList;
	private ArrayList<String> removeList;
	private ArrayList<String> includeRegList;
	private ArrayList<String> excludeRegList;
	private ArrayList<String> registerList;
	private ArrayList<String> customInstList;
	private ArrayList<String> customRegList;
	private ArrayList<String> instructionList;
	private String forward = "forward";
	private String backward = "backward";
	static public boolean selectProfileFlag = false;
	static public boolean existingInputFileFlag = false;
	@FXML
	ObservableList<String> items;
	private boolean errorFlag;
	public String folderName;
	public String fileName;
	 File theDirectory;
//	Controller controller = new Controller();
	//Model model = new Model();
	@FXML
	private void onClickGenerateYamlFile(ActionEvent event) {
		Parent root;
		try {
			Controller.console = new ArrayList<String>();
			folderName = Controller.currentProgramFolder;
			theDirectory = new File(folderName+"/llfi");
			String cmd1 = "rm -rf "+Controller.currentProgramFolder+"/llfi";
			ProcessBuilder p1 = new ProcessBuilder("/bin/tcsh","-c",cmd1);
		    
		    p1.redirectErrorStream(true);
		    Process pr1 = p1.start();
			BufferedReader in2 = new BufferedReader(new InputStreamReader(pr1.getInputStream()));
		    String line1;
		    Controller.errorString = new ArrayList<>();
		    while ((line1 = in2.readLine()) != null) {
		    	/*if(line1.contains("Sucess"))
		    		Controller.errorString = new ArrayList<>();
		    	else*/
		    		Controller.errorString.add(line1);
		       
		        if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
		        	errorFlag = true;
		        	
		    }
		    pr1.waitFor();
		    in2.close();
	        //delete(theDirectory);
		
		if(instTypeRadio.isSelected() ==true ){
			selectedInstSelectionMethod = "insttype";
		}else
			selectedInstSelectionMethod = "custominstselector";
			if(regTypeRadio.isSelected() == true)
			{
				selectedRegSelectionMethod = "regloc";
			}else
				selectedRegSelectionMethod = "customregselector";
			
				if(noTraceRadio.isSelected() == true)
					selectedTraceMethod = noTraceRadio.getText();
				else if(fullTraceRadio.isSelected() == true)
					selectedTraceMethod = fullTraceRadio.getText();
				else
					selectedTraceMethod = limitTraceRadio.getText();
				
					//What ever the yamlFile path is.
				           
				            
				            fileName = Controller.currentFileName;
					        File yamlFile = new File(folderName+"/input.yaml");
					        FileOutputStream is = new FileOutputStream(yamlFile);
					        OutputStreamWriter osw = new OutputStreamWriter(is);    
					        Writer w = new BufferedWriter(osw);
					        w.write("kernelOption:");
					        w.write("\n    - forceRun");

					        w.write("\n\ntimeOut: 1000");

					        w.write("\n\ncompileOption:");
					        w.write("\n    "+"instSelMethod: "+selectedInstSelectionMethod);
					        if(selectedInstSelectionMethod.equalsIgnoreCase("insttype"))
					        {
					        	w.write("\n    "+"include: ");
						        for(int i = 0; i< instIncludeListView.getItems().size(); i++)
						        {
						        	 w.write("\n        "+"- "+instIncludeListView.getItems().get(i).toString().split("-")[0]);
						        }
						        w.write("\n    "+"exclude: ");
						        for(int i = 0; i< instExcludeListView.getItems().size(); i++)
						        {
						        	 w.write("\n        "+"- "+instExcludeListView.getItems().get(i).toString().split("-")[0]);
						        }
					        }
					        else
					        {
					        	w.write("\n    customInstSelector: "+customInstCombo.getValue().toString().split("-")[0]);
					        }
					        
					        w.write("\n\n    "+"regSelMethod: "+selectedRegSelectionMethod);
					        if(selectedRegSelectionMethod.equalsIgnoreCase("regloc"))
					        {
					        	w.write("\n    "+selectedRegSelectionMethod+": "+regCombo.getValue().toString().split("-")[0]);
					        }
					        else
					        {
					        	w.write("\n    customRegSelector: "+customRegCombo.getValue().toString().split("-")[0]);
					        }
					        
					        
					       
					       /* for(int i = 0; i< regIncludeListView.getItems().size(traceCountText); i++)
					        {
					        	 w.write("\n\t\t"+"- "+regIncludeListView.getItems().get(i));
					        }*/
					        
					        //File+selectedTraceMethod);
					        if(fullTraceRadio.isSelected() == true || limitTraceRadio.isSelected() == true)
					        {
					        	w.write("\n\n    "+"includeInjectionTrace:");
					        	if(forwardCheckbox.isSelected() == true)
					        		
						        	 w.write("\n        "+"- "+forward);
					        	if(backwardCheckbox.isSelected() == true)
						        	 w.write("\n        "+"- "+backward);
					        	
					        	
					        }
					        if(limitTraceRadio.isSelected() == true)
					        {
					        	
					        	w.write("\n\n    "+"tracingPropagation:"+" True");
					        	w.write("\n\n    "+"tracingPropagationOption:");
					        	w.write("\n        "+"maxTrace: "+traceCountText.getText());
					        }
					        
					        if(selectProfileFlag == true || existingInputFileFlag ==true)
					        {
					        	for(int i = 0; i<fileContent.size();i++)
					        	{
					        		w.write(fileContent.get(i));
					        	}
					        }
					        	
					        w.close();
					        
						 String cmd = Controller.llfibuildPath+"bin/instrument -lpthread --readable "+folderName+"/"+folderName+".ll";
							ProcessBuilder p = new ProcessBuilder("/bin/tcsh","-c",cmd);
							Controller.console.add("$ "+cmd+"\n");
						    
						    p.redirectErrorStream(true);
						    Process pr = p.start();
							BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
						    
						    Controller.errorString = new ArrayList<>();
						    while ((line1 = in1.readLine()) != null) {
						    	/*if(line1.contains("Sucess"))
						    		Controller.errorString = new ArrayList<>();
						    	else*/
						    		Controller.console.add(line1+"\n");
						    		Controller.errorString.add(line1);
						       
						        if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
						        	errorFlag = true;
						        	
						    }
						    pr.waitFor();
						    in1.close();
					       
						  if(errorFlag == true)
						  {
							  errorFlag = false;
							  Node  source = (Node)  event.getSource(); 
							  Stage stage  = (Stage) source.getScene().getWindow();
							  stage.close();
							  
							  root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ErrorDisplay.fxml"));
						        stage = new Stage();
						        stage.setTitle("Error");
						        stage.setScene(new Scene(root, 450, 100));
						        stage.show();
						        
						  }
						  else
						  {
							  Controller.errorString = new ArrayList<>();
							  Node  source = (Node)  event.getSource(); 
							  Stage stage  = (Stage) source.getScene().getWindow();
							  stage.close();
						  }
						   
							   
						  
					       
					    
			
			
			
		
			
			//Files.createFile(C:\\Nithya\\sample_files\\input.txt, null)
	

		
			
		
		
	}catch (IOException e) {
        System.err.println("Problem writing to the file statsTest.txt");
    } catch (InterruptedException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	}
	
	public static void delete(File file)
	    	throws IOException{
	 
	    	if(file.isDirectory()){
	 
	    		//directory is empty, then delete it
	    		if(file.list().length==0){
	 
	    		   file.delete();
	    		   
	 
	    		}else{
	 
	    		   //list all the directory contents
	        	   String files[] = file.list();
	 
	        	   for (String temp : files) {
	        	      //construct the file structure
	        	      File fileDelete = new File(file, temp);
	 
	        	      //recursive delete
	        	     delete(fileDelete);
	        	   }
	 
	        	   //check the directory again, if empty then delete it
	        	   if(file.list().length==0){
	           	     file.delete();
	        	    
	        	   }
	    		}
	 
	    	}else{
	    		//if file, then delete it
	    		file.delete();
	    		
	    	}
	    }
	
	
	
	/*public static boolean deleteDirectory(File directory) {
		System.out.println("diret == "+directory.toString());
	    if(directory.exists()){
	        File[] files = directory.listFiles();
	        if(null!=files){
	            for(int i=0; i<files.length; i++) {
	                if(files[i].isDirectory()) {
	                    deleteDirectory(files[i]);
	                }
	                else {
	                    files[i].delete();
	                }
	            }
	        }
	    }
	    return(directory.delete());
	}*/
	
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
		FileReader inputFile;
		try{
			if(customInstTypeRadio.isSelected() == true){
				customInstCombo.setDisable(false);
				includeLabel.setDisable(true);
				
				instIncludeListView.setDisable(true);
				instExcludeListView.setDisable(true);
				instIncludeButton.setDisable(true);
				instExcludeButton.setDisable(true);
				inputFile = new FileReader("customInstruction_list.txt");
				BufferedReader bufferReader = new BufferedReader(inputFile);
		        
		        customInstList = new ArrayList<String>();
		        String line;
		        
		        while ((line = bufferReader.readLine()) != null)   {
		        	customInstList.add(line);
		        	
		        }
		        bufferReader.close();
		        items =FXCollections.observableArrayList (customInstList);
		        //regCombo.getItems().removeAll(true);
		        customInstCombo.setItems(items);
		        customInstCombo.setPromptText("-- Select --");
				
				
			}
			else{
				includeLabel.setDisable(false);
				customInstCombo.setDisable(true);
				instIncludeListView.setDisable(false);
				instExcludeListView.setDisable(false);
				instIncludeButton.setDisable(false);
				instExcludeButton.setDisable(false);
			}
		}
		
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();String line;
		}
        	
	
	}
	
	@FXML
	private void onSelectRegSelectRadio(ActionEvent event){
		FileReader inputFile;
		try
		{
			if(customRegTypeRadio.isSelected() == true){
				regCombo.setDisable(true);
				customRegCombo.setDisable(false);
				inputFile = new FileReader("customRegister_list.txt");
				BufferedReader bufferReader = new BufferedReader(inputFile);
		        
		        customRegList = new ArrayList<String>();
		        String line;
		        
		        while ((line = bufferReader.readLine()) != null)   {
		        	customRegList.add(line);
		        	
		        }
		        bufferReader.close();
		        items =FXCollections.observableArrayList (customRegList);
		        //regCombo.getItems().removeAll(true);
		        customRegCombo.setItems(items);
		        customRegCombo.setPromptText("-- Select --");
			
				}
			else{
				regCombo.setDisable(false);
				customRegCombo.setDisable(true);
				
			}
		}
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
			
	
	}
	
	@FXML
	private void onClickTraceOption(ActionEvent event){
		if(noTraceRadio.isSelected() == true)
		{
			forwardCheckbox.setDisable(true);
			backwardCheckbox.setDisable(true);
			
		}
		else if(limitTraceRadio.isSelected() == true){
			traceCountText.setDisable(false);
		}
		  
		else
		{
			forwardCheckbox.setDisable(false);
			backwardCheckbox.setDisable(false);
			traceCountText.setDisable(true);
		}
		
	}
	@FXML
	private void onClickSelectProfile(ActionEvent event){
		 Parent root;
	        //fileCount=0;
	    	Stage stage = new Stage();
	    	FileChooser fileChooser = new FileChooser();
	    	fileChooser.setTitle("Open Resource File");
	    	configureFileChooser(fileChooser); 
	    	List<File> list = fileChooser.showOpenMultipleDialog(stage);
	            if (list != null) {
	                for (File file : list) {
	                    openFile(file);
	                }
	            }
	}
	private static void configureFileChooser(
	        final FileChooser fileChooser) {      
	            
	            fileChooser.getExtensionFilters().addAll(
	               
	                new FileChooser.ExtensionFilter("YAML", "*.yaml")
	            );
	    }

private void openFile(File file) {
    try{
    	selectProfileFlag = true;
    	String line;
    	String customInst;
    	String customReg;
    	fileContent = new ArrayList<>();
    	Path path = file.toPath();
        
        String fileInfo =path.toString();
        
        FileReader inputFile = new FileReader(fileInfo);
        BufferedReader bufferReader = new BufferedReader(inputFile);
        while ((line = bufferReader.readLine()) != null)   {
        	if(line.contains("instSelMethod"))
        	{
        		if(line.split(":")[1].trim().equalsIgnoreCase("custominstselector"))
        		{
        			customInstTypeRadio.setSelected(true);
        			customInstCombo.setDisable(false);
        			includeLabel.setDisable(true);    				
    				instIncludeListView.setDisable(true);
    				instExcludeListView.setDisable(true);
    				instIncludeButton.setDisable(true);
    				instExcludeButton.setDisable(true);
        			
        		}
        			
        	}
        	else if (line.contains("customInstSelector"))
        	{
        		customInst = line.split(":")[1].trim();
        		customInstCombo.setValue(customInst);

        	}
        	else if(line.contains("regSelMethod"))
        	{
        		if(line.split(":")[1].equalsIgnoreCase("customregselector"))
        		{
        			customRegTypeRadio.setSelected(true);
        			regCombo.setDisable(true);
        			customRegCombo.setDisable(false);
        		}
        			
        	}
        	else if (line.contains("customRegSelector"))
        	{
        		customReg = line.split(":")[1].trim();
        		customRegCombo.setValue(customReg);

        	}
        	else if(line.contains("includeInjectionTrace"))
        	{
        		fullTraceRadio.setSelected(true);
        	}
        	else if(line.contains("backward"))
        	{
        		backwardCheckbox.setSelected(true);
        	}
        	else if(line.contains("forward"))
        	{
        		forwardCheckbox.setSelected(true);
        	}
        	else if(line.contains("maxTrace"))
        	{
        		limitTraceRadio.setSelected(true);
        		traceCountText.setText(line.split(":")[1].trim());
        	}
        	if(line.contains("runOption"))
        	{
        		fileContent.add("\n\n"+line);
        		while ((line = bufferReader.readLine()) != null)   {
        			fileContent.add("\n"+line);
        		}
        	}
        	
        		
            
            
        }
    }catch(IOException e){
        System.out.println("Error while reading file line by line:" 
        + e.getMessage());                      
    } 
    }

@FXML
private void onClickCreateNewProfile(ActionEvent event)
{
	
	
		File yFile= new File(folderName+"/input.yaml");
		yFile.delete();
		resetAllOptions();
		existingInputFileFlag = false;
	
}

private void resetAllOptions()
{
	FileReader inputFile;
	FileReader inputFile1;
	try{
	inputFile = new FileReader("register_list.txt");
	BufferedReader bufferReader = new BufferedReader(inputFile);
    
    registerList = new ArrayList<String>();
    String line;
    
    while ((line = bufferReader.readLine()) != null)   {
   	 registerList.add(line);
    	
    }
    bufferReader.close();
    items =FXCollections.observableArrayList (registerList);
    //regCombo.getItems().removeAll(true);
    regCombo.setItems(items);
    regCombo.setPromptText("-- Select --");
    
    inputFile1 = new FileReader("instruction_list.txt");
	BufferedReader bufferReader1 = new BufferedReader(inputFile1);
    
	instructionList = new ArrayList<String>();
       
    while ((line = bufferReader1.readLine()) != null)   {
    	instructionList.add(line);
    	
    }
    bufferReader1.close();
    items =FXCollections.observableArrayList (instructionList);
    
    instExcludeListView.setItems(items);
    
    if(customInstTypeRadio.isSelected() == true){
		customInstCombo.setDisable(false);
		includeLabel.setDisable(true);
		
		instIncludeListView.setDisable(true);
		instExcludeListView.setDisable(true);
		instIncludeButton.setDisable(true);
		instExcludeButton.setDisable(true);
		inputFile = new FileReader("customInstruction_list.txt");
		bufferReader = new BufferedReader(inputFile);
        
        customInstList = new ArrayList<String>();
        
        
        while ((line = bufferReader.readLine()) != null)   {
        	customInstList.add(line);
        	
        }
        bufferReader.close();
        items =FXCollections.observableArrayList (customInstList);
        //regCombo.getItems().removeAll(true);
        customInstCombo.setItems(items);
        customInstCombo.setPromptText("-- Select --");
		
		
	}
	else{
		includeLabel.setDisable(false);
		customInstCombo.setDisable(true);
		instIncludeListView.setDisable(false);
		instExcludeListView.setDisable(false);
		instIncludeButton.setDisable(false);
		instExcludeButton.setDisable(false);
	}
    if(customRegTypeRadio.isSelected() == true){
		regCombo.setDisable(true);
		customRegCombo.setDisable(false);
		inputFile = new FileReader("customRegister_list.txt");
		bufferReader = new BufferedReader(inputFile);
        
        customRegList = new ArrayList<String>();
        
        
        while ((line = bufferReader.readLine()) != null)   {
        	customRegList.add(line);
        	
        }
        bufferReader.close();
        items =FXCollections.observableArrayList (customRegList);
        //regCombo.getItems().removeAll(true);
        customRegCombo.setItems(items);
        customRegCombo.setPromptText("-- Select --");
	
		}
	else{
		regCombo.setDisable(false);
		customRegCombo.setDisable(true);
		
	}
    if(limitTraceRadio.isSelected() == true)
    {
    	traceCountText.setDisable(false);
    }
    else if(fullTraceRadio.isSelected() == true)
    {
    	traceCountText.setDisable(true);
    }
    else if(noTraceRadio.isSelected() == true)
    {
    	traceCountText.setDisable(true);
    	forwardCheckbox.setDisable(true);
    	backwardCheckbox.setDisable(true);
    }
	}catch (IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		FileReader inputFile;
		FileReader inputFile1;
		try {
			selectProfileFlag = false;
			existingInputFileFlag = false;
			folderName = Controller.currentProgramFolder;
			
			String line;
			resetAllOptions();
	        String customInst;
	    	String customReg;
	        File f = new File(Controller.currentProgramFolder+"/input.yaml");
	       
	        if(f.exists()) {
	        	createNewProfileButton.setDisable(false);
	        	existingInputFileFlag = true;
	        	fileContent = new ArrayList<>();
	        	
	        	 FileReader iFile = new FileReader(Controller.currentProgramFolder+"/input.yaml");
	             BufferedReader bufferReader2 = new BufferedReader(iFile);
	             while ((line = bufferReader2.readLine()) != null)   {
	             	if(line.contains("instSelMethod"))
	             	{
	             		if(line.split(":")[1].equalsIgnoreCase("custominstselector"))
	             		{
	             			customInstTypeRadio.setSelected(true);
	             			customInstCombo.setDisable(false);
	             			includeLabel.setDisable(true);    				
	         				instIncludeListView.setDisable(true);
	         				instExcludeListView.setDisable(true);
	         				instIncludeButton.setDisable(true);
	         				instExcludeButton.setDisable(true);
	             			
	             		}
	             			
	             	}
	             	else if (line.contains("customInstSelector"))
	             	{
	             		customInst = line.split(":")[1].trim();
	             		customInstCombo.setValue(customInst);

	             	}
	             	else if(line.contains("regSelMethod"))
	             	{
	             		if(line.split(":")[1].equalsIgnoreCase("customregselector"))
	             		{
	             			customRegTypeRadio.setSelected(true);
	             			regCombo.setDisable(true);
	             			customRegCombo.setDisable(false);
	             		}
	             			
	             	}
	             	else if (line.contains("customRegSelector"))
	             	{
	             		customReg = line.split(":")[1].trim();
	             		customRegCombo.setValue(customReg);

	             	}
	             	else if(line.contains("includeInjectionTrace"))
	             	{
	             		fullTraceRadio.setSelected(true);
	             	}
	             	else if(line.contains("backward"))
	             	{
	             		backwardCheckbox.setSelected(true);
	             	}
	             	else if(line.contains("forward"))
	             	{
	             		forwardCheckbox.setSelected(true);
	             	}
	             	else if(line.contains("maxTrace"))
	             	{
	             		limitTraceRadio.setSelected(true);
	             		traceCountText.setText(line.split(":")[1].trim());
	             	}
	             	if(line.contains("runOption"))
	             	{
	             		fileContent.add("\n\n"+line);
	             		while ((line = bufferReader2.readLine()) != null)   {
	             			fileContent.add("\n"+line);
	             		}
	             	}
	        }
	        }
	        
	     
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
	    // TODO
	} 
}
