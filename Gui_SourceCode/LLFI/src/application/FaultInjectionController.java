package application;


import java.awt.Dialog;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.URL;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.ResourceBundle;

import javax.swing.GroupLayout.Alignment;
import javax.swing.plaf.basic.BasicSplitPaneUI.KeyboardEndHandler;

import com.sun.javafx.collections.MappingChange.Map;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.DragEvent;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import application.Controller;
import javafx.scene.control.Button;

public class FaultInjectionController implements Initializable{
	
	@FXML
	private TextField noOfRunsText;
	@FXML
	private TextField fiRegIndex;
	@FXML
	private TextField fiBitText;
	@FXML
	private TextField randomSeed;
	@FXML
	private Label fiIndexLabel;
	@FXML
	private Slider fiIndexSlider;
	@FXML
	private Label fiCycleLabel;
	@FXML
	private Slider fiCycleSlider;
	@FXML
	private ComboBox faulInjectionTypeCombo;
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
	private String buildPath;
	private String runCountString;
	private String noOfRuns;
	private String fiType;
	private String fiCycle;
	private String fiIndex;
	private ArrayList<String> faultTypeList;
	private ArrayList<String> fileNameLists;
	private ArrayList<String> resultList;
	private String fiBit;
	private boolean errorFlag;
	private String indexBound;
	private  boolean profileLoadFlag = false;
	FileReader inputFile;
	String str;
	String line;
	String subStr[];
	String fiTypefault;
	int index;
	int cycle;
	int regIndex;
	int bit;
	String status;
	String result;
	public String currentFolderName = null;
	private List<String> runContent = new ArrayList<String>();
	public int runCount = 0;
	String profName = null;
	public ArrayList<String> singleRunOption = new ArrayList<String>();
	public ArrayList<HashMap<String, ArrayList<String>>> profileListRunOption =  new ArrayList<HashMap<String, ArrayList<String>>>();
	public HashMap<String, ArrayList<String>> runOptionMap = new HashMap<>();
	int runNumber = 1;
	int profileCount = 0;
	@FXML
	ObservableList<String> items;
	@FXML
	private void onClickDeleteRun(ActionEvent event)
	{
		boolean delFlag = false;
		Iterator it = runOptionMap.entrySet().iterator();
		String key;
		
		String currentKey;
		ArrayList<String> tempList = new ArrayList<String>();
		runOptionMap.remove(runNumberLabel.getText());
		currentKey = runNumberLabel.getText().substring(3);
		 it = runOptionMap.entrySet().iterator();
		 while (it.hasNext()) {
			java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
	    	tempList = new ArrayList<String>();
	    	tempList = (ArrayList<String>)pairs.getValue();
	    	key = (String)pairs.getKey();
	    	if(Integer.parseInt(key.substring(3)) == Integer.parseInt(currentKey)+1)
	    	{
	    		runOptionMap.remove(key);
	    		delFlag = true;
	    		runOptionMap.put("run"+currentKey, tempList);
	    		noOfRunsText.setText(tempList.get(0));
				if(!tempList.get(1).equalsIgnoreCase(""))
					faulInjectionTypeCombo.setValue(tempList.get(1));;
				
				fiRegIndex.setText(tempList.get(2));
				if(!tempList.get(3).equalsIgnoreCase(""))
				fiCycleLabel.setText(tempList.get(3));
				else
					fiCycleLabel.setText("0");
				fiBitText.setText(tempList.get(4));
				if(!tempList.get(5).equalsIgnoreCase(""))
				fiIndexLabel.setText(tempList.get(5));
				else
					fiIndexLabel.setText("0");
				randomSeed.setText(tempList.get(6));
				if(!tempList.get(3).equalsIgnoreCase(""))
				fiCycleSlider.setValue(Integer.parseInt(tempList.get(3)));
				if(!tempList.get(5).equalsIgnoreCase(""))
				fiIndexSlider.setValue(Integer.parseInt(tempList.get(5)));
				runNumberLabel.setText("run"+runNumber);
	    	}
	    	
	    	
	    	
	    }
		 it = runOptionMap.entrySet().iterator();
		 while (it.hasNext()) {
				java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
		    	tempList = new ArrayList<String>();
		    	tempList = (ArrayList<String>)pairs.getValue();
		    	key = (String)pairs.getKey();
		    	if(Integer.parseInt(key.substring(3)) > Integer.parseInt(currentKey))
		    	{
		    		runOptionMap.remove(key);
		    		runOptionMap.put("run"+(Integer.parseInt(key.substring(3))-1), tempList);
		    	}
		 }
		 if(!delFlag)
		 {
			 noOfRunsText.setText("");
			 faulInjectionTypeCombo.setValue("-- Select --");
			 fiRegIndex.setPromptText("null");
			 fiCycleLabel.setText("0");
			 fiCycleSlider.setValue(0);
			 fiBitText.setPromptText("null");
			 fiIndexLabel.setText("0");
			 fiIndexSlider.setValue(0);
			 randomSeed.setPromptText("null");
		 }
		
	}
	@FXML
	private void onClickAddRunOption(ActionEvent event){
		currentFolderName = Controller.currentProgramFolder;
		FileReader inputFile;
		String line;
		String fileContent = "";
		boolean runFlag = false;
		String runNumberContent;
		HashMap<String, ArrayList<String>> tempMap;
		ArrayList<String> tempList = new ArrayList<String>();
		ArrayList<String> newList = new ArrayList<String>();
		boolean nextElementChkFlag = false;
		Parent root;
		try{
			Iterator it = runOptionMap.entrySet().iterator();
		    while (it.hasNext()) {
		    	java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
		       
		        //it.remove(); // avoids a ConcurrentModificationException
		    }
		   // it = runOptionMap.entrySet().iterator();
		    if(!noOfRunsText.getText().contentEquals(""))
			{
		    	
				runNumberContent = runNumberLabel.getText();
				
				// while (it.hasNext()) {
				    	//java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
					
					
						//nextElementChkFlag = true;
						//tempList = (ArrayList<String>)pairs.getValue();
						newList = new ArrayList<String>();
							newList.add(noOfRunsText.getText());
							newList.add(faulInjectionTypeCombo.getValue().toString());
							newList.add(fiRegIndex.getText());
							newList.add(fiCycleLabel.getText());
							newList.add(fiBitText.getText());
							newList.add(fiIndexLabel.getText());
							newList.add(randomSeed.getText());
						runOptionMap.put(runNumberContent,newList);
						
						
						
					
					
				// }
				
			}
			 it = runOptionMap.entrySet().iterator();
			 while (it.hasNext()) {
				
				 
				 java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
		    	tempList = new ArrayList<String>();
		    	tempList = (ArrayList<String>)pairs.getValue();
		    	
		    }
			inputFile = new FileReader(currentFolderName+"/input.yaml");
			
			
			//if(runCount == 0)
			//{
				BufferedReader bufferReader = new BufferedReader(inputFile);
			    while ((line = bufferReader.readLine()) != null)   {
		      	if(line.contains("runOption:"))
		      	{	runFlag = true;
			        break;
		      	}
		      	else
		      	{
		      		fileContent+=line+"\n";
		      	}
		      	
		        }
			    
			    File yamlFile = new File(currentFolderName+"/input.yaml");
		        FileOutputStream is = new FileOutputStream(yamlFile);
		        OutputStreamWriter osw = new OutputStreamWriter(is);    
		        Writer w = new BufferedWriter(osw);
		        w.write(fileContent);
			    if(runFlag)
			    {
			    	w.write("runOption:");
			    	runFlag = false;
			    }
			    	
			    else
			    	w.write("\nrunOption:");
			    it = runOptionMap.entrySet().iterator();
				 while (it.hasNext()) {
					
					 
					 java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
			    	tempList = new ArrayList<String>();
			    	tempList = (ArrayList<String>)pairs.getValue();
			    	w.write("\n    - run:");
			    	w.write("\n        numOfRuns: "+tempList.get(0));
			    	w.write("\n        fi_type: "+tempList.get(1).toString().split("-")[0]);
			    	if(!tempList.get(2).equalsIgnoreCase(""))
						w.write("\n        fi_reg_index: "+tempList.get(2));
			    	if(!tempList.get(3).equalsIgnoreCase("0") && !tempList.get(3).equalsIgnoreCase(""))
						w.write("\n        fi_cycle: "+tempList.get(3));
			    	if(!tempList.get(4).equalsIgnoreCase(""))
					{
						w.write("\n        fi_bit: "+tempList.get(4));
						if(tempList.get(2).equalsIgnoreCase(""))
							w.write("\n        fi_reg_index: "+"0");
						if(tempList.get(3).equalsIgnoreCase("0"))
							w.write("\n        fi_cycle: "+tempList.get(3));
						if(tempList.get(5).equalsIgnoreCase("0"))
							w.write("\n        fi_index: "+tempList.get(5));
						
					
					}
			    	if(!tempList.get(5).equalsIgnoreCase("0") && !tempList.get(5).equalsIgnoreCase(""))
						w.write("\n        fi_index: "+tempList.get(5));
						if(!tempList.get(6).equalsIgnoreCase(""))
						w.write("\n        fi_random_seed: "+tempList.get(6));
						
			    	
				 }
				 w.close();
				 
						/*w.write("\n    - run:");
						w.write("\n        numOfRuns: "+noOfRunsText.getText());
						w.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
						
						if(!fiRegIndex.getText().equalsIgnoreCase(""))
						w.write("\n        fi_reg_index: "+fiRegIndex.getText());
					
						if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
						w.write("\n        fi_cycle: "+fiCycleLabel.getText());
						
						if(!fiBitText.getText().equalsIgnoreCase(""))
						{
							w.write("\n        fi_bit: "+fiBitText.getText());
							if(fiRegIndex.getText().equalsIgnoreCase(""))
								w.write("\n        fi_reg_index: "+"0");
							if(fiCycleLabel.getText().equalsIgnoreCase("0"))
								w.write("\n        fi_cycle: "+fiCycleLabel.getText());
							if(fiIndexLabel.geParent root;tText().equalsIgnoreCase("0"))
								w.write("\n        fi_index: "+fiIndexLabel.getText());
						
						}
					
						if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
						w.write("\n        fi_index: "+fiIndexLabel.getText());
						if(!randomSeed.getText().equalsIgnoreCase(""))
						w.write("\n        fi_random_seed: "+randomSeed.getText());
						w.close();
				    
				    
				    
				    
				    
				}*/
				/*else
				{

			    	FileWriter injectWrite = new FileWriter(currentFolderName+"/input.yaml",true);
			    	//injectWrite.write("\n\nrunOption:");
					injectWrite.write("\n\n    - run:");
					injectWrite.write("\n        numOfRuns: "+noOfRunsText.getText());
					injectWrite.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
					
					if(!fiRegIndex.getText().equalsIgnoreCase(""))
					injectWrite.write("\n        fi_reg_index: "+fiRegIndex.getText());
				
					if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
					injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
					
					if(!fiBitText.getTextline.contains("fi_type")().equalsIgnoreCase(""))
					{
						injectWrite.write("\n        fi_bit: "+fiBitText.getText());
						if(fiRegIndex.getText().equalsIgnoreCase(""))
							injectWrite.write("\n        fi_reg_index: "+"0");
						if(fiCycleLabel.getText().equalsIgnoreCase("0"))
							injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
						if(fiIndexLabel.getText().equalsIgnoreCase("0"))
							injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
					
					}
				
					if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
					injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
					if(!randomSeed.getText().equalsIgnoreCase(""))
					injectWrite.write("\n        fi_random_seed: "+randomSeed.getText());
					injectWrite.close();
				}*/
				
				//runCount++;
				//runCountLabel.setText(runCount+" Run Option Added");
				 
				/*noOfRunsText.setText("");
				faulInjectionTypeCombo.setValue("--Select--");
				fiRegIndex.setText("");
				fiRegIndex.setPromptText("null");
				fiBitText.setText("");
				fiBitText.setPromptText("null");
				randomSeed.setText("");
				randomSeed.setPromptText("null");
				fiCycleLabel.setText("0");
				fiIndexLabel.setText("0");
				fiIndexSlider.setValue(0);
				fiCycleSlider.setValue(0);
				
					w.write("\n    - run:");
					w.write("\n        numOfRuns: "+noOfRunsText.getText());
					w.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
					
					if(!fiRegIndex.getText().equalsIgnoreCase(""))
					w.write("\n        fi_reg_index: "+fiRegIndex.getText());
				
					if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
					w.write("\n        fi_cycle: "+fiCycleLabel.getText());
					
					if(!fiBitText.getText().equalsIgnoreCase(""))
					{
						w.write("\n        fi_bit: "+fiBitText.getText());
						if(fiRegIndex.getText().equalsIgnoreCase(""))
							w.write("\n        fi_reg_index: "+"0");
						if(fiCycleLabel.getText().equalsIgnoreCase("0"))
							w.write("\n        fi_cycle: "+fiCycleLabel.getText());
						if(fiIndexLabel.getText().equalsIgnoreCase("0"))
							w.write("\n        fi_index: "+fiIndexLabel.getText());
					
					}
				
					if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
					w.write("\n        fi_index: "+fiIndexLabel.getText());
					if(!randomSeed.getText().equalsIgnoreCase(""))
					w.write("\n        fi_random_seed: "+randomSeed.getText());
					w.close();
			    
			    
			    
			    
			    
			}*/
			/*else
			{

		    	FileWriter injectWrite = new FileWriter(currentFolderName+"/input.yaml",true);
		    	//injectWrite.write("\n\nrunOption:");
				injectWrite.write("\n\n    - run:");
				injectWrite.write("\n        numOfRuns: "+noOfRunsText.getText());
				injectWrite.write("\n        fi_type: "+faulInjectionTypeCombo.getValue().toString().split("-")[0]);
				
				if(!fiRegIndex.getText().equalsIgnoreCase(""))
				injectWrite.write("\n        fi_reg_index: "+fiRegIndex.getText());
			
				if(!fiCycleLabel.getText().equalsIgnoreCase("0"))
				injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
				
				if(!fiBitText.getText().equalsIgnoreCase(""))
				{
					injectWrite.write("\n        fi_bit: "+fiBitText.getText());
					if(fiRegIndex.getText().equalsIgnoreCase(""))
						injectWrite.write("\n        fi_reg_index: "+"0");
					if(fiCycleLabel.getText().equalsIgnoreCase("0"))
						injectWrite.write("\n        fi_cycle: "+fiCycleLabel.getText());
					if(fiIndexLabel.getText().equalsIgnoreCase("0"))
						injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
				
				}
			
				if(!fiIndexLabel.getText().equalsIgnoreCase("0"))
				injectWrite.write("\n        fi_index: "+fiIndexLabel.getText());
				if(!randomSeed.getText().equalsIgnoreCase(""))
				injectWrite.write("\n        fi_random_seed: "+randomSeed.getText());
				injectWrite.close();
			}*/
			
			//runCount++;@FXML
					
			//runCountLabel.setText(runCount+" Run Option Added");
			
			
			/*noOfRunsText.setText("");
			faulInjectionTypeCombo.setValue("--Select--");
			fiRegIndex.setText("");
			fiRegIndex.setPromptText("null");
			fiBitText.setText("");
			fiBitText.setPromptText("null");
			randomSeed.setText("");
			randomSeed.setPromptText("null");
			fiCycleLabel.setText("0");
			fiIndexLabel.setText("0");
			fiIndexSlider.setValue(0);
			fiCycleSlider.setValue(0);*/
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
				  if(saveProfileCheckBox.isSelected())
						 
					 {
					  
					  FileChooser fileChooser = new FileChooser();
					  
		              //Set extension filter
		              FileChooser.ExtensionFilter extFilter = new FileChooser.ExtensionFilter("(*.yaml)", "*.yaml");
		              fileChooser.getExtensionFilters().add(extFilter);
		              
		              //Show save file dialog
		              File file = fileChooser.showSaveDialog(stage);
		             
		              if(file != null){
		            	 String profileName;
		         		 String fileContent1 = "";
		         		 FileReader actualFile;
		         		 String line1;
		         		
		         			actualFile = new FileReader(Controller.currentProgramFolder+"/input.yaml");
		         		
		         		 BufferedReader bufferReader1 = new BufferedReader(actualFile);
		         		 //profileName = checkFileName(profileCount);
		         		// profileName = profileNameText.getText();
		         	    	

		         		    File profileFile = new File(file+".yaml");
		         	        FileOutputStream is1 = new FileOutputStream(profileFile);
		         	        OutputStreamWriter osw1 = new OutputStreamWriter(is1); 
		         	        Writer w1 = new BufferedWriter(osw1);
		         		    
		         				while ((line1 = bufferReader1.readLine()) != null)   {
		         					fileContent1 = line1+"\n";		        
		         				    w1.write(fileContent1);
		         				
		         				}
		         			 
		         		    w1.close();
		         		
		                  //SaveFile(Santa_Claus_Is_Coming_To_Town, file);
		              }
						/*root = FXMLLoader.load(getClass().getClassLoader().getResource("application/ProfileName.fxml"));
					     stage = new Stage();
					        stage.setTitle("Profile Name");
					        stage.setScene(new Scene(root, 400, 100));
					        stage.show();*/
						
						 
					 }
			  }
		}
		catch (IOException e) {
	        System.err.println("Exception Occured in writing to the input.yaml file");
	    }
		
	}
	
	public String checkFileName(int profCount)
	{
		
		
		File f = new File(currentFolderName+"/profile_"+profCount+".yaml");
    	if(f.exists()) {
    		profCount++;
    		profName = checkFileName(profCount);
    	}
    	else
    	{
    		profName = "profile_"+profCount;
    		
    	}
    	return profName;
	}
	@FXML
	private void onClickFaultInjection(ActionEvent event) {
		Parent root;
		try{
			 ObservableList<ResultTable> data;
			 final File folder = new File(Controller.currentProgramFolder+"/llfi/llfi_stat_output");
			 if(folder.exists())
			  deleteFilesInFolder(folder);
			  final File errorFolder = new File(Controller.currentProgramFolder+"/llfi/error_output");
			  if(errorFolder.exists())
			  deleteFilesInFolder(errorFolder);
			//runCount++;
			//faultCount.setVisible(true);
			//faultCount.setText("No.Of Fault Injections Added: "+runCount);
			
		    ProcessBuilder p = new ProcessBuilder("/bin/tcsh","-c",Controller.llfibuildPath+"bin/injectfault "+Controller.currentProgramFolder+"/llfi/"+Controller.currentProgramFolder+"-faultinjection.exe "+Controller.inputString);
		    
		    p.redirectErrorStream(true);
		    Process pr = p.start();
			BufferedReader in1 = new BufferedReader(new InputStreamReader(pr.getInputStream()));
		    String line1;
		    while ((line1 = in1.readLine()) != null) {
		    	Controller.errorString.add(line1+"\n");
		    	if(line1.contains("error")||line1.contains("Error")||line1.contains("ERROR"))
		    		errorFlag= true;
		    	
		        
		    }
		    pr.waitFor();
		   in1.close();
		   
		   
		   /*
		   root = FXMLLoader.load(getClass().getClassLoader().getResource("application/InjectFaultResult.fxml"));
	        Stage stage = new Stage();
	        stage.setTitle("Profiling");
	        stage.setScene(new Scene(root, 400, 100));
	        stage.show();*/
	        
		   //controller.flag =1;
		  // controller.onGeneratingResultTable();
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
		  
	     
	      
			
		    
			
		}
		catch (IOException e) {
	        System.err.println("Problem writing to the file statsTest.txt");
	    } catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public void deleteFilesInFolder(final File folder) {
		//resultFileNameLists = new ArrayList<String>();
	    for (final File fileEntry : folder.listFiles()) {
	    	
	        if (fileEntry.isDirectory()) {
	        	deleteFilesInFolder(fileEntry);
	        } else {
	        	fileEntry.delete();
	        }
	    }
	}
	
	
	
	
	@FXML
	private void onChangeIndexSlider(MouseEvent e){
		
		int slideValue = (int)Math.round(fiIndexSlider.getValue());
		
		fiIndexLabel.setText(String.valueOf(slideValue));
	}
	
	@FXML
	private void onChangeRegIndexSlider(MouseEvent e){
		
		int slideValue1 = (int)Math.round(fiCycleSlider.getValue());
		
		fiCycleLabel.setText(String.valueOf(slideValue1));
	}
	
	@FXML
	private void checkForNumberRuns(KeyEvent event){
		String regex = "\\d+";
		if(noOfRunsText.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			noOfRunsText.setText("");
		}
	}
	
	@FXML
	private void checkForNumberRegister(KeyEvent event){
		String regex = "\\d+";
		if(fiRegIndex.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			fiRegIndex.setText("");
		}
	}
	@FXML
	private void checkForNumberBit(KeyEvent event){
		String regex = "\\d+";
		if(fiBitText.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			fiBitText.setText("");
		}
	}
	@FXML
	private void checkForNumberSeed(KeyEvent event){
		String regex = "\\d+";
		if(randomSeed.getText().matches(regex))
		{
			//noOfRunsText.setText(noOfRunsText.getText());
		}
		else
		{
			randomSeed.setText("");
		}
	}
	@FXML
	private void onClickNextRunOption(ActionEvent event){
		boolean nextElementChkFlag = false;
		HashMap<String, ArrayList<String>> tempMap;
		ArrayList<String> tempList = new ArrayList<String>();
		//System.out.println("content ="+noOfRunsText.getText());
		if(noOfRunsText.getText().contentEquals(""))		{
			Parent root;
			try {
				root = FXMLLoader.load(getClass().getClassLoader().getResource("application/NextRunOptionPopup.fxml"));
				Stage stage = new Stage();
		        stage.setTitle("Error");
		        stage.setScene(new Scene(root, 400, 100));
		        stage.show();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	        
		}
		else
		{
			//runNumber++;
			runCountString= "run"+Integer.toString(runNumber);
			runNumberLabel.setText(runCountString);
			singleRunOption = new ArrayList<>();
			singleRunOption.add(noOfRunsText.getText());
			singleRunOption.add(faulInjectionTypeCombo.getValue().toString());
			singleRunOption.add(fiRegIndex.getText());
			singleRunOption.add(fiCycleLabel.getText());
			singleRunOption.add(fiBitText.getText());
			singleRunOption.add(fiIndexLabel.getText());
			singleRunOption.add(randomSeed.getText());
			runOptionMap.put(runNumberLabel.getText(), singleRunOption);
			//profileListRunOption.add(runOptionMap);
			prevRunOption.setDisable(false);
			runNumber++;
			Iterator it = runOptionMap.entrySet().iterator();
			while (it.hasNext()) {
			    java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
				
				if(pairs.getKey().toString().contentEquals("run"+runNumber))
				{
					nextElementChkFlag = true;
					tempList =(ArrayList<String>) pairs.getValue();
					noOfRunsText.setText(tempList.get(0));
					if(!tempList.get(1).equalsIgnoreCase(""))
						faulInjectionTypeCombo.setValue(tempList.get(1));;
					
					fiRegIndex.setText(tempList.get(2));
					if(!tempList.get(3).equalsIgnoreCase(""))
					fiCycleLabel.setText(tempList.get(3));
					else
						fiCycleLabel.setText("0");
					fiBitText.setText(tempList.get(4));
					if(!tempList.get(5).equalsIgnoreCase(""))
					fiIndexLabel.setText(tempList.get(5));
					else
						fiIndexLabel.setText("0");
					randomSeed.setText(tempList.get(6));
					if(!tempList.get(3).equalsIgnoreCase(""))
					fiCycleSlider.setValue(Integer.parseInt(tempList.get(3)));
					if(!tempList.get(5).equalsIgnoreCase(""))
					fiIndexSlider.setValue(Integer.parseInt(tempList.get(5)));
					runNumberLabel.setText("run"+runNumber);
				}
			}
			
			if(nextElementChkFlag == false)
			{
				noOfRunsText.setText("");
				faulInjectionTypeCombo.setValue("--Select--");
				fiRegIndex.setText("");
				fiRegIndex.setPromptText("null");
				fiBitText.setText("");
				fiBitText.setPromptText("null");
				randomSeed.setText("");
				randomSeed.setPromptText("null");
				fiCycleLabel.setText("0");
				fiIndexLabel.setText("0");
				fiIndexSlider.setValue(0);
				fiCycleSlider.setValue(0);
				
				runNumberLabel.setText("run"+runNumber);
			}
			
			
		}
	}
	@FXML
	private void onClickPrevRunOption(ActionEvent event){
		if(!noOfRunsText.getText().contentEquals("") && (faulInjectionTypeCombo.getSelectionModel().getSelectedIndex() == 0))		{
			//runCountString= "run"+Integer.toString(runNumber);
			runCountString = runNumberLabel.getText();
			singleRunOption = new ArrayList<>();
			singleRunOption.add(noOfRunsText.getText());
			singleRunOption.add(faulInjectionTypeCombo.getValue().toString());
			singleRunOption.add(fiRegIndex.getText());
			singleRunOption.add(fiCycleLabel.getText());
			singleRunOption.add(fiBitText.getText());
			singleRunOption.add(fiIndexLabel.getText());
			singleRunOption.add(randomSeed.getText());
			runOptionMap.put(runNumberLabel.getText(), singleRunOption);
			profileListRunOption.add(runOptionMap);
		}
		
		HashMap<String, ArrayList<String>> tempMap;
		ArrayList<String> tempList = new ArrayList<String>();
		runNumber--;
		String prevRun = "run"+runNumber;
		//if(runCountLabel.getText().contentEquals(""))
		//{
		Iterator it = runOptionMap.entrySet().iterator();
		while (it.hasNext()) {
		    java.util.Map.Entry pairs = (java.util.Map.Entry)it.next();
			
			if(pairs.getKey().toString().contentEquals("run"+runNumber))
			{
			
					tempList = (ArrayList<String>) pairs.getValue();
					noOfRunsText.setText(tempList.get(0));
					faulInjectionTypeCombo.setValue(tempList.get(1));
					fiRegIndex.setText(tempList.get(2));
					fiCycleLabel.setText(tempList.get(3));
					fiBitText.setText(tempList.get(4));
					fiIndexLabel.setText(tempList.get(5));
					randomSeed.setText(tempList.get(6));
					fiCycleSlider.setValue(Integer.parseInt(tempList.get(3)));
					fiIndexSlider.setValue(Integer.parseInt(tempList.get(5)));
					runNumberLabel.setText(prevRun);
				}
			}
		//}
		if(runNumber == 1)
			prevRunOption.setDisable(true);
	}
	@Override
	public void initialize(URL url, ResourceBundle rb) {
		FileReader inputFile;
		try{
			buildPath=Controller.llfibuildPath+"LLFI-GUI/";
			currentFolderName = Controller.currentProgramFolder;
			runNumberLabel.setText("run1");
		inputFile = new FileReader("llfi.stat.totalindex.txt");
		BufferedReader bufferReader = new BufferedReader(inputFile);
        
       
        String line;
        
        while ((line = bufferReader.readLine()) != null)   {
        	indexBound = line.split("=")[1];
        	
        }
        bufferReader.close();
        fiIndexSlider.setMax(Double.parseDouble(indexBound));
        fiIndexSlider.setMajorTickUnit(Double.parseDouble(indexBound));
        //regCombo.getItems().removeAll(true);
        
        inputFile = new FileReader("llfi.stat.prof.txt");
		bufferReader = new BufferedReader(inputFile);
        
       
        while ((line = bufferReader.readLine()) != null)   {
        	if(line.contains("="))
        	indexBound = line.split("=")[1];
        	
        }
        bufferReader.close();
        if(indexBound.equalsIgnoreCase("0"))
        {
        	indexBound="-1";
        	fiCycleSlider.setDisable(true);
        }
        	
        
        fiCycleSlider.setMax(Double.parseDouble(indexBound));
        fiCycleSlider.setMajorTickUnit(Double.parseDouble(indexBound));
        
        inputFile = new FileReader(buildPath+"fault_type.txt");
		bufferReader = new BufferedReader(inputFile);
        
		faultTypeList = new ArrayList<String>();
       // String line;
        
        while ((line = bufferReader.readLine()) != null)   {
        	faultTypeList.add(line);
        	
        }
        bufferReader.close();
        items =FXCollections.observableArrayList (faultTypeList);
        //regCombo.getItems().removeAll(true);
        faulInjectionTypeCombo.setItems(items);
        faulInjectionTypeCombo.setPromptText("-- Select --");
        FileReader existingFile = new FileReader(currentFolderName+"/input.yaml");
        BufferedReader bufferReader1 = new BufferedReader(existingFile);
        ArrayList<String> runOptionList = new ArrayList<String>();
        runOptionList.add("numOfRuns");
        runOptionList.add("fi_type");
        runOptionList.add("fi_reg_index");
        runOptionList.add("fi_cycle");
        runOptionList.add("fi_bit");
        runOptionList.add("fi_index");
        runOptionList.add("fi_random_seed");
       
        boolean runOptionChkFlag = false;
        boolean firstItemChk = false;
        int runCountfromProfile = 1;
	    while ((line = bufferReader1.readLine()) != null)   {
      	if(line.contains("runOption:"))
      	{
      		 
      			profileLoadFlag = true;
      			 
      				
      				//runContent = new ArrayList<>();
      				singleRunOption = new ArrayList<String>();
      				
      				while ((line = bufferReader1.readLine()) != null)
      				{
      					
      					/*if(line.contains("run") && )
      							runCountfromProfile++;	*/	
      							
      					if((line.contains("run") && firstItemChk == true) )
      					{
      						singleRunOption = new ArrayList<String>();
      						for(int i = 0;i<runOptionList.size();i++)
      	      				{
      							runOptionChkFlag = false;
      	      					for(int k = 0;k <runContent.size();k++)
      	          				{
      	      					
      	      						
      	          					if(runContent.get(k).contains(runOptionList.get(i)))
      	          					{
      	          						
      	          						singleRunOption.add(runContent.get(k).split(":")[1].trim());
      	          						runOptionChkFlag = true;
      	          						break;
      	          					}						
      	          				}
      	          				if(runOptionChkFlag == false)
      	          				{
      	          				
      	          				//if(runOptionList.get(i).equalsIgnoreCase("fi_cycle"))
      	          				
      	          					runOptionChkFlag = false;
      	          					singleRunOption.add("");
      	          				}
      	          				
      	      				}
      	      				runOptionMap.put("run"+runCountfromProfile, singleRunOption);
      	      				runCountfromProfile++;
      						
      						
      				//bufferReader1.mark(1);
      						//break;
      						runContent = new ArrayList<>();
      					}
      					
      					else
      					{
      						firstItemChk = true;
      						runContent.add(line);
      					}
      											
      						
      				}
      				singleRunOption = new ArrayList<String>();
						for(int i = 0;i<runOptionList.size();i++)
	      				{
							runOptionChkFlag = false;
	      					for(int k = 0;k <runContent.size();k++)
	          				{
	      						
	          					if(runContent.get(k).contains(runOptionList.get(i)))
	          					{
	          						singleRunOption.add(runContent.get(k).split(":")[1].trim());
	          						runOptionChkFlag = true;
	          						break;
	          					}						
	          				}
	          				if(runOptionChkFlag == false)
	          				{
	          				
	          					runOptionChkFlag = false;
	          					singleRunOption.add("");
	          				}
	          				
	      				}
	      				runOptionMap.put("run"+runCountfromProfile, singleRunOption);
	      				runCountfromProfile++;
      				
      				
      				
      				
      				
      			 
      		 
      		
      	}
	    }
	    if(profileLoadFlag == true)
	    {
	    	ArrayList<String> tempList = new ArrayList<String>();
	    	tempList = runOptionMap.get("run1");
	    	runNumberLabel.setText("run1");
	    	noOfRunsText.setText(tempList.get(0));
	    	if(!tempList.get(1).equalsIgnoreCase(""))
	    	faulInjectionTypeCombo.setValue(tempList.get(1));;
	    	if(!tempList.get(2).equalsIgnoreCase(""))
	    	fiRegIndex.setText(tempList.get(2));	    		
	    	if(!tempList.get(3).equalsIgnoreCase(""))
	    	{
	    		fiCycleLabel.setText(tempList.get(3));
	    		fiCycleSlider.setValue(Integer.parseInt(tempList.get(3)));
	    	}
	    	else
	    	{
	    		fiCycleSlider.setValue(0);
	    		fiCycleLabel.setText("0");
	    	}
	    	if(!tempList.get(4).equalsIgnoreCase(""))
		    	fiBitText.setText(tempList.get(4));	
	    	if(!tempList.get(5).equalsIgnoreCase(""))
	    	{
	    		fiIndexLabel.setText(tempList.get(5));
	    		fiIndexSlider.setValue(Integer.parseInt(tempList.get(5)));
	    	}
	    	else
	    	{
	    		fiIndexSlider.setValue(0);
	    		fiIndexLabel.setText("0");
	    	}
	    	if(!tempList.get(6).equalsIgnoreCase(""))
		    	randomSeed.setText(tempList.get(6));	
	    		
	    	
	    	
	    }
	    
		}catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    // TODO
	}

}
