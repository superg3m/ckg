# -------------------------------- GENERATED BY C_BUILD --------------------------------
import argparse
from c_build.new_stuff.globals import *
from c_build.new_stuff.new_project import *

parser = argparse.ArgumentParser(description='c_build_script')
parser.add_argument('--compiler', type=str, help='Compiler to use (e.g. gcc, clang)')
parser.add_argument('--build_type', type=str, required=True, help='Build type (e.g. debug, release)')
parser.add_argument('--level', type=int, help='level (e.g. 1, 2, 4)')
parser.add_argument('--is_dependency', type=bool, default=False, help='is_dependency (e.g. True, False)')
args = parser.parse_args()
build_type = args.build_type

if args.level:
	SET_LEVEL(args.level)
# --------------------------------------------------------------------------------------

COMPILER = args.compiler or "gcc"
project = Project("ckg", COMPILER, is_dependency = args.is_dependency)

# Do different things depending on the platform
if COMPILER == "cl":
	project.set_compiler_warning_level("2")
	project.disable_specific_warnings(["5105", "4668", "4820"])
elif COMPILER in ["gcc", "cc", "clang"]:
	project.set_compiler_warning_level("no-deprecated-declarations")

project.set_treat_warnings_as_errors(True)
project.set_debug_with_visual_studio(True)
project.set_rebuild_project_dependencies(True)
# If project.set_rebuild_project_dependencies is set to (False)
# then by default it will look at the source files and check if they have been modified since the cache

project.set_project_dependencies([""])
# -------------------------------------------------------------------------------------

procedures = {
    "ckit_lib": {
        "build_directory": f"./build_{COMPILER}",
        "output_name": "ckg.lib" if COMPILER == "cl" else "libckg.a",
        "source_files": ["../ckg.c"],
        "additional_libs": [],
        "compile_time_defines": [],
        "include_paths": [],
    },
	"test_ckg": {
        "build_directory": f"./example/{COMPILER}",
        "output_name": "test_ckg.exe",
        "source_files": ["../*.c"],
        "additional_libs": [f"../../build_{COMPILER}/ckg.lib" if COMPILER == "cl" else f"../../build_{COMPILER}/libckg.a"],
        "compile_time_defines": [],
        "include_paths": [],
    },
}

for procedure_name, procedure_data in procedures.items():
	procedure = project.add_procedure(procedure_data["build_directory"])
	procedure.set_output_name(procedure_data["output_name"])
	procedure.set_source_files(procedure_data["source_files"])
	procedure.set_include_paths(procedure_data["include_paths"])
	procedure.set_compile_time_defines(procedure_data["compile_time_defines"])
	procedure.set_additional_libs(procedure_data["additional_libs"])

# -------------------------------------------------------------------------------------
project.set_executables_to_run(["test_ckg.exe"])

project.build(build_type)