package application;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.LinkedHashMap;

import org.yaml.snakeyaml.Yaml;

/**
 * Used for parsing and writing to the input.yaml file.
 * Also keep track of what the user has previously selected.
 */
public class InputYaml {	
	private Yaml yaml = new Yaml();
	
	// map to dump
	private Map<String, Object> input;
	
	// instrument option
	private Map<String, Object> compileOption;
	
	private List<Map<String, Map<String, List<String>>>> instSelMethod;
	private String regSelMethod;
	private String regloc_OR_customRegSelector;
	private List<String> includeInjectionTrace;
	private Map<String, Object> tracingPropagationOption;
	private Boolean tracingPropagation;
	
	/**
	 * Can be 'insttype' or 'customInstselector'
	 */
	private Map<String, List<String>> insttype;
	private List<String> includedInstruction;
	
	// runtime option
	private List<Map<String, Map<String, Object>>> runOption;
	private List<RuntimeOption> r = new ArrayList<RuntimeOption>();
	
	public InputYaml() {
		input = new LinkedHashMap<String, Object>();
		
		// keeping the old functionality of the GUI
		List<String> kernelOption = new ArrayList<String>();
		kernelOption.add("forceRun");
		input.put("kernelOption", kernelOption);
	}

	/**
	 * Load an input.yaml
	 * @param path - load the input.yaml from this path
	 */
	@SuppressWarnings("unchecked")
	public void load(File file) {
		try {
			input = (Map<String, Object>) yaml.load(new FileInputStream(file));
		} catch (FileNotFoundException e) {
			System.err.println("ERROR: selected input.yaml not found");
			e.printStackTrace();
		}
		
		// get compile option
		compileOption = (Map<String, Object>) input.get("compileOption");
		
		// get instSelMethod
		instSelMethod = (List<Map<String, Map<String, List<String>>>>) compileOption.get("instSelMethod");
		
		// check if we are doing custom instruction type
		insttype = instSelMethod.get(0).get("insttype");
		if (insttype == null) {
			insttype = instSelMethod.get(0).get("customInstselector");
		}
		
		// get included instruction
		includedInstruction = insttype.get("include");
		
		// get regSelMethod
		regSelMethod = (String) compileOption.get("regSelMethod");
		
		// get regloc_OR_customRegSelector depending on regSelMethod
		if (regSelMethod.equals("regloc")) {
			regloc_OR_customRegSelector = (String) compileOption.get("regloc");
		} else {
			regloc_OR_customRegSelector = (String) compileOption.get("customRegSelector");
		}
		
		// get tracing options
		tracingPropagation = (Boolean) compileOption.get("tracingPropagation");
		includeInjectionTrace = (List<String>) compileOption.get("includeInjectionTrace");
		tracingPropagationOption = (Map<String, Object>) compileOption.get("tracingPropagationOption");
		
		// get runOption
		runOption = (List<Map<String, Map<String, Object>>>) input.get("runOption");
		
		if (runOption != null) {
			for (int i = 0; i < runOption.size(); i++) {
				Map<String, Object> run = runOption.get(i).get("run");
				
				int numOfRuns = ((Integer) run.get("numOfRuns")).intValue();
				
				String fi_type = (String) run.get("fi_type");
				Integer fi_cycle = (Integer) run.get("fi_cycle");
				Integer fi_reg_index = (Integer) run.get("fi_reg_index");
				Integer fi_index = (Integer) run.get("fi_index");
				Integer fi_bit = (Integer) run.get("fi_bit");
				Integer timeOut = (Integer) run.get("timeOut");
				Integer randomSeed = (Integer) run.get("randomSeed");
				
				r.add(new RuntimeOption(numOfRuns, fi_type, fi_cycle,
						fi_reg_index, fi_index, fi_bit, timeOut, randomSeed));
			}
		}
	}
	
	/**
	 * Write the current mapping to a specified path.
	 * @param path
	 */
	public void writeChanges(String path) {
		writeChanges(path, input);	
	}
	
	private void writeChanges(String path, Object input) {
		String dump = yaml.dump(input);
		//System.out.println(dump);
		
		try {
			Writer w = new BufferedWriter(new FileWriter(path, false));
			w.write(dump);
			w.close();
		} catch (IOException e) {
			System.out.println("ERROR: unable to write .yaml file to " + path);
			e.printStackTrace();
		}	
	}
	
	/**
	 * Copy generated run options to all the sub-folders for batch software
	 * injection. #SFIT
	 * 
	 * @throws IOException
	 */
	public void copyRunOptionsToSubfolders() throws IOException {
		for (int i = 0; i < Controller.selectedSoftwareFailures.size(); i++) {
			String path = Controller.currentProgramFolder + "/llfi-"
					+ Controller.selectedSoftwareFailures.get(i)
					+ "/input.yaml";
			File yamlFile = new File(path);

			@SuppressWarnings("unchecked")
			Map<String, Object> input = (Map<String, Object>) yaml
					.load(new FileInputStream(yamlFile));
			input.put("runOption", runOption);
			writeChanges(path, input);
		}
	}
	
	public void setInstrumentOption(InstrumentOption io) {
		// reset options
		compileOption = new LinkedHashMap<String, Object>();
		instSelMethod = new ArrayList<Map<String, Map<String, List<String>>>>();
		
		compileOption.put("instSelMethod", instSelMethod);
		insttype = new LinkedHashMap<String, List<String>>();
		
		// reset all trace options
		includeInjectionTrace = null;
		tracingPropagation = null;
		tracingPropagationOption = null;
		
		// set member variable
		includedInstruction = io.includedInstruction;
		regloc_OR_customRegSelector = io.regloc_OR_customRegSelector;
		
		// set actual data structure
		String name;
		if (io.customInstruction || !io.isHardwareFault) {
			name = "customInstselector";
		} else {
			name = "insttype";
		}
		// wrap "include" list 
		insttype.put("include", includedInstruction);
		
		// wrap "include" list inside the 'name' variable
		Map<String, Map<String, List<String>>> wrapper = new LinkedHashMap<String, Map<String, List<String>>>();
		wrapper.put(name, insttype);
		
		instSelMethod.add(wrapper);
		
		if (io.isHardwareFault) {
			if (io.customRegister) {
				compileOption.put("regSelMethod", "customregselector");
				compileOption.put("customRegSelector", regloc_OR_customRegSelector);
			} else {
				compileOption.put("regSelMethod", "regloc");
				compileOption.put("regloc", regloc_OR_customRegSelector);
			}
		} else {
			compileOption.put("regSelMethod", "customregselector");
			compileOption.put("customRegSelector", "Automatic");
		}
		
		// Do tracing
		
		// tracing is enabled and the user has selected either or both
		// backward and forward trace
		if (io.tracingEnabled && (io.backwardTrace || io.forwardTrace)) {
			// do tracing
			tracingPropagation = true;
			
			// backward or forward trace?
			includeInjectionTrace = new ArrayList<String>();
			if (io.forwardTrace) {
				includeInjectionTrace.add("forward");
			}
			if (io.backwardTrace) {
				includeInjectionTrace.add("backward");
			}
			
			// add tracing propagation option
			tracingPropagationOption = new LinkedHashMap<String, Object>();
			tracingPropagationOption.put("debugTrace", "True/False");
			tracingPropagationOption.put("generateCDFG", true);
			
			// sets maxTrace
			if (io.maxTrace != null) {
				tracingPropagationOption.put("maxTrace", io.maxTrace);
			}
		}
		setTraceOption();
		
		input.put("compileOption", compileOption);
		
		return;
	}
	
	private void setTraceOption() {
		if (includeInjectionTrace == null) {
			compileOption.remove("includeInjectionTrace");
		} else {
			compileOption.put("includeInjectionTrace", includeInjectionTrace);
		}
		
		if (tracingPropagation == null) {
			compileOption.remove("tracingPropagation");
		} else {
			compileOption.put("tracingPropagation", tracingPropagation);
		}
		
		if (tracingPropagationOption == null) {
			compileOption.remove("tracingPropagationOption");
		} else {
			compileOption.put("tracingPropagationOption", tracingPropagationOption);
		}
	}
	
	public InstrumentOption getInstrumentOption() {
		boolean tracingEnabled, backwardTrace = false, forwardTrace = false;
		Integer maxTrace;
		
		boolean isHardwareFault;
		boolean customRegister, customInstruction;
		
		// Check TraceOptions
		if (tracingPropagation != null) {
			tracingEnabled = true;
			
			// check for forward and backward trace options
			for (String s: includeInjectionTrace) {
				if (s.equals("forward")) {
					forwardTrace = true;
				} else if (s.equals("backward")) {
					backwardTrace = true;
				}
			}
			
			// check for maxTrace
			// will be null if not found
			maxTrace = (Integer) tracingPropagationOption.get("maxTrace");
		} else {
			tracingEnabled = false;
			maxTrace = null;
		}
		
		// Check InjectionModel
		if (regSelMethod.equals("regloc") || !regloc_OR_customRegSelector.equals("Automatic")) {
			isHardwareFault = true;
			customInstruction = false;
			
			// check for customInstruction
			if (includedInstruction.size() == 1) {
				// check for 'all' and 'excluded'
				if ("all".equals(includedInstruction.get(0))) {
					// get all possible hardware instructions
					List<String> includeList = Controller.configReader.getInstruction();
					
					// discard the '-' and everything after it
					List<String> newIncludeList = new ArrayList<String>();
					for (String s : includeList) {
						newIncludeList.add(s.split("-")[0]);
					}
					
					// get excluded instructions
					List<String> excludeList = insttype.get("exclude");
					
					// see if it's empty
					if (excludeList != null) {
						// compare the two list, get all the included instructions out
						for (String exclude: excludeList) {
							for (String include: includeList) {
								if (exclude.equals(include.split("-")[0])) {
									newIncludeList.remove(exclude);
									break;
								}
							}
						}
					}
					
					// make the 
					includedInstruction = newIncludeList;
				} else {
					List<String> customInstructionList = Controller.configReader.getCustomInstruction();
					for (int i = 0; i < customInstructionList.size(); i++) {
						if (customInstructionList.get(i).equals(includedInstruction.get(0))) {
							customInstruction = true;
							break;
						}
					}
				}
			}
			
			// check for customRegister
			if (regSelMethod.equals("regloc")) {
				customRegister = true;
			} else {
				customRegister = false;
			}
		} else {
			// always false for Software Injection
			customRegister = false;
			
			// may be false
			customInstruction = false;
			
			isHardwareFault = false;
			
			// check if we are doing a custom software injection
			if (includedInstruction.size() == 1) {
				List<String> customSoftwareFault = Controller.configReader.getCustomSoftwareFault();
				for (int i = 0; i < customSoftwareFault.size(); i++) {
					if (customSoftwareFault.get(i).equals(includedInstruction.get(0))) {
						customInstruction = true;
						break;
					}
				}
			}
		} 

		return new InstrumentOption(includedInstruction, isHardwareFault, customRegister,
				customInstruction, regloc_OR_customRegSelector, tracingEnabled,
				backwardTrace, forwardTrace, maxTrace);
	}

	public List<RuntimeOption> getRuntimeOptions() {
		return r;
	}
	
	public void setRuntimeOption(List<RuntimeOption> r) {
		// reset 
		runOption = new ArrayList<Map<String, Map<String, Object>>>();
		this.r = r;
		
		for (int i = 0; i < r.size(); i++) {
			RuntimeOption currentRun = r.get(i);
			
			Map<String, Map<String, Object>> wrapper = new LinkedHashMap<String, Map<String, Object>>();
			Map<String, Object> run = new LinkedHashMap<String, Object>();
			wrapper.put("run", run);
			runOption.add(wrapper);
			
			run.put("numOfRuns", currentRun.numOfRuns);

			if (currentRun.fi_type != null) {
				run.put("fi_type", currentRun.fi_type);
			}
			if (currentRun.fi_cycle != null) {
				run.put("fi_cycle", currentRun.fi_cycle);
			}
			if (currentRun.fi_reg_index != null) {
				run.put("fi_reg_index", currentRun.fi_reg_index);
			}
			if (currentRun.fi_index != null) {
				run.put("fi_index", currentRun.fi_index);
			}
			if (currentRun.fi_bit != null) {
				run.put("fi_bit", currentRun.fi_bit);
			}
			if (currentRun.timeOut != null) {
				run.put("timeOut", currentRun.timeOut);
			}
			if (currentRun.randomSeed != null) {
				run.put("randomSeed", currentRun.randomSeed);
			}
		}
		
		input.put("runOption", runOption);
	}
	
	public static class InstrumentOption {
		// included instructions
		public List<String> includedInstruction;
		
		// injection model
		public boolean isHardwareFault;
		public boolean customRegister;
		public boolean customInstruction;
		
		public String regloc_OR_customRegSelector;

		// tracing options
		public boolean tracingEnabled;
		public boolean backwardTrace;
		public boolean forwardTrace;

		public Integer maxTrace = null;
		
		public InstrumentOption() {};
		
		public InstrumentOption(List<String> includedInstruction,
				boolean isHardwareFault, boolean customRegister,
				boolean customInstruction, String regloc_OR_customRegSelector,
				boolean tracingEnabled, boolean backwardTrace,
				boolean forwardTrace, Integer maxTrace) {
			
			this.includedInstruction = includedInstruction;

			this.isHardwareFault = isHardwareFault;
			this.customRegister = customRegister;
			this.customInstruction = customInstruction;

			this.regloc_OR_customRegSelector = regloc_OR_customRegSelector;

			this.tracingEnabled = tracingEnabled;
			this.backwardTrace = backwardTrace;
			this.forwardTrace = forwardTrace;

			this.maxTrace = maxTrace;
		}
	}
	
	public static class RuntimeOption {
		public int numOfRuns;
		
		public String fi_type = null;
		public Integer fi_cycle = null;
		public Integer fi_reg_index = null;
		public Integer fi_index = null;
		public Integer fi_bit = null;
		public Integer timeOut = null;
		
		public Integer randomSeed = null;
		
		public RuntimeOption() {};
		
		public RuntimeOption(int numOfRuns, String fi_type, Integer fi_cycle,
				Integer fi_reg_index, Integer fi_index, Integer fi_bit, Integer timeOut, Integer randomSeed) {
			
			this.numOfRuns = numOfRuns;
			
			this.fi_type = fi_type;
			this.fi_cycle = fi_cycle;
			this.fi_reg_index = fi_reg_index;
			this.fi_index = fi_index;
			this.fi_bit = fi_bit;
			this.timeOut = timeOut;
			
			this.randomSeed = randomSeed;
		}
	}
}
