cmake_minimum_required(VERSION 2.8)

include(../config/llfigui.cmake)
include(../config/copy_utils.cmake)

project(gui)

MESSAGE("INCLUDED JAVA CLASSPATH: ${CMAKE_JAVA_INCLUDE_PATH}")

add_java_src(application/ClosePopupController.java)
add_java_src(application/CompileToIrController.java)
add_java_src(application/Controller.java)
add_java_src(application/FaultInjectionController.java)
add_java_src(application/InstrumentController.java)
add_java_src(application/Main.java)
add_java_src(application/MyThread.java)
add_java_src(application/ProfilingController.java)
add_java_src(application/ProgressBarController.java)
add_java_src(application/ResultTable.java)
add_java_src(application/SaveProfileController.java)
add_java_src(application/Table.java)
add_java_src(application/TraceController.java)
add_java_src(application/InputYaml.java)
add_java_src(application/ConfigReader.java)

copy(application/TraceOpenError.fxml application/TraceOpenError.fxml)
copy(application/TracingErrorDisplay.fxml application/TracingErrorDisplay.fxml)
copy(application/compileToIR.fxml application/compileToIR.fxml)
copy(application/Config.fxml application/Config.fxml)
copy(application/ErrorDisplay.fxml application/ErrorDisplay.fxml)
copy(application/InjectFaultResult.fxml application/InjectFaultResult.fxml)
copy(application/Instrument.fxml application/Instrument.fxml)
copy(application/NextRunOptionPopup.fxml application/NextRunOptionPopup.fxml)
copy(application/Profile.fxml application/Profile.fxml)
copy(application/ProfileName.fxml application/ProfileName.fxml)
copy(application/ProfileWithInput.fxml application/ProfileWithInput.fxml)
copy(application/Profiling.fxml application/Profiling.fxml)
copy(application/ProgressWindow.fxml application/ProgressWindow.fxml)
copy(application/Sample.fxml application/Sample.fxml)

copy(gui_config.yaml gui_config.yaml)

copy(application/lib/snakeyaml-1.15.jar application/lib/snakeyaml-1.15.jar)

compileGUI()

