cmake_minimum_required(VERSION 2.8)

include(../../config/copy_utils.cmake)

project(test_suite-SCRIPTS)

copy(build_prog.py build_prog.py)
copy(check_injection.py check_injection.py)
copy(clean_prog.py clean_prog.py)
copy(clear_all.py clear_all.py)
copy(clear_llfi.py clear_llfi.py)
copy(deploy_prog.py deploy_prog.py)
copy(inject_prog.py inject_prog.py)
copy(test_trace_tools.py test_trace_tools.py)
copy(llfi_test.py llfi_test)

genCopy()
