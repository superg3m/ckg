import sys
sys.path.append("./c-build/new_stuff")
from new_project import *

from enum import Enum
class Arg(Enum):
	COMPILER_ARG = 2

COMPILER = sys.argv[Arg.COMPILER_ARG.value] if len(sys.argv) > 1 else "cl"
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
#project.set_executables_to_run(["test_ckg.exe"])
project.build()

# JUST SO WE ARE CLEAR THIS IS A BREAKING CHANGE