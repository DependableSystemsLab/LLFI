cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(bin)

copy(instrument.py instrument)
copy(injectfault.py injectfault)
copy(profile.py profile)
copy(SoftwareFailureAutoScan.py SoftwareFailureAutoScan)
copy(batchInstrument.py batchInstrument)
copy(batchProfile.py batchProfile)
copy(batchInjectfault.py batchInjectfault)
copy(llfi-gui.py llfi-gui)
copy(HardwareFailureAutoScan.py HardwareFailureAutoScan)
copy(InjectorAutoScan.py InjectorAutoScan)

genCopy()

