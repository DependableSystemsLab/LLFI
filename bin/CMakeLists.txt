cmake_minimum_required(VERSION 2.8)

include(../config/copy_utils.cmake)

project(bin)

copy(instrument.py instrument)
copy(injectfault.py injectfault)
copy(profile.py profile)
copy(Auto-discovery.py Auto-discovery)
copy(masterInstrument.py masterInstrument)
copy(masterProfile.py masterProfile)
copy(masterInjectfault.py masterInjectfault)
copy(batchInstrument.py batchInstrument)
copy(batchProfile.py batchProfile)
copy(batchInjectfault.py batchInjectfault)

genCopy()

