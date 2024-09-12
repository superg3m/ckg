# -------------------------------- GENERATED BY C_BUILD --------------------------------
import argparse
from c_build.new_stuff.globals import *
from c_build.new_stuff.new_project import *

parser = argparse.ArgumentParser(description='c_build_script')
parser.add_argument('--compiler', type=str, help='Compiler to use (e.g. gcc, clang)')
parser.add_argument('--build_type', type=str, required=True, help='Build type (e.g. debug, release)')
parser.add_argument('--level', type=int, help='level (e.g. 1, 2, 4)')
args = parser.parse_args()
build_type = args.build_type

if args.level:
	SET_LEVEL(args.level)
# --------------------------------------------------------------------------------------

COMPILER = args.compiler or "cl"
project = Project("ckg", COMPILER)

# Do different things depending on the platform
if COMPILER == "cl":
	project.set_compiler_warning_level("2")
	project.disable_specific_warnings(["5105", "4668", "4820"])
elif COMPILER in ["gcc", "cc", "clang"]:
	project.set_compiler_warning_level("all")

project.set_treat_warnings_as_errors(True)
project.set_debug_with_visual_studio(True)
project.set_rebuild_project_dependencies(True)
# If project.set_rebuild_project_dependencies is set to (False)
# then by default it will look at the source files and check if they have been modified since the cache

project.set_project_dependencies([""])
# -------------------------------------------------------------------------------------
ckg_lib_procedure = project.add_procedure(f"./build_{COMPILER}")
ckg_lib_procedure.set_output_name("ckg.lib")
ckg_lib_procedure.set_compile_time_defines([""])
ckg_lib_procedure.set_include_paths([""])
ckg_lib_procedure.set_source_files(["../ckg.c"])
ckg_lib_procedure.set_additional_libs([""])
# -------------------------------------------------------------------------------------
ckg_test_procedure = project.add_procedure(f"./example/{COMPILER}")
ckg_test_procedure.set_output_name("test_ckg.exe")
ckg_test_procedure.set_compile_time_defines([""])
ckg_test_procedure.set_include_paths([""])
ckg_test_procedure.set_source_files(["../*.c"])
ckg_test_procedure.set_additional_libs([f"../../build_{COMPILER}/ckg.lib"])
# -------------------------------------------------------------------------------------
project.set_executables_to_run(["test_ckg.exe"])
project.build(build_type)