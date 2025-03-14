# -------------------------------- GENERATED BY C_BUILD --------------------------------
import os
import sys

def FIND_C_BUILD(current_dir):
    if os.path.isdir(os.path.join(current_dir, "c_build")):
        sys.path.insert(0, current_dir)
        return

    parent_dir = os.path.dirname(current_dir)
    if parent_dir != current_dir:
        FIND_C_BUILD(parent_dir)

FIND_C_BUILD(os.path.abspath(os.path.dirname(__file__)))
from c_build.source.UserUtilities import *
from c_build.source.Manager import *
# --------------------------------------------------------------------------------------s

pc: ProjectConfig = ProjectConfig(
    project_name = "ckg",
    project_dependencies = [],
    project_debug_with_visual_studio = True,
    project_rebuild_project_dependencies = False,
    project_executable_procedures  = ["test_ckg.exe"]
)

cc: CompilerConfig = CompilerConfig(
    compiler_name = C_BUILD_COMPILER_NAME() if C_BUILD_IS_DEPENDENCY() else "INVALID_COMPILER",
    compiler_std_version = "",
    compiler_warning_level = "",
    compiler_disable_specific_warnings = [""],
    compiler_treat_warnings_as_errors = True,
    compiler_disable_warnings  = False,
    compiler_disable_sanitizer = True
)

if IS_WINDOWS():
    cc.compiler_name = "cl"
if IS_DARWIN():
    cc.compiler_name = "clang"
elif IS_LINUX():
    cc.compiler_name = "gcc"

if cc.compiler_name == "cl":
    cc.compiler_warning_level = "4"
    cc.compiler_disable_specific_warnings = ["5105", "4668", "4820", "4996"]
else:
    cc.compiler_warning_level = "all"
    cc.compiler_disable_specific_warnings = ["deprecated-declarations"]

executable_procedure_libs = []
if IS_WINDOWS():
    windows_libs = ["User32.lib", "Gdi32.lib"] if cc.compiler_name == "cl" else ["-lUser32", "-lGdi32"]
    executable_procedure_libs += windows_libs


procedures_config = {
    "ckg_lib": ProcedureConfigElement(
        build_directory = f"./build_{cc.compiler_name}",
        output_name = GET_LIB_NAME(cc, 'ckg'),
        source_files = ["../ckg.c"],
        additional_libs = [],
        compile_time_defines = [],
        compiler_inject_into_args = [],
        include_paths = []
    ),

    "test_ckg": ProcedureConfigElement(
        build_directory = f"./example/{cc.compiler_name}",
        output_name = "test_ckg.exe",
        source_files = ["../*.c"],
        additional_libs = [f"../../build_{cc.compiler_name}/{GET_LIB_NAME(cc, 'ckg')}"],
        compile_time_defines = [""],
        compiler_inject_into_args = [],
        include_paths = [],
    ),
}

manager: Manager = Manager(cc, pc, procedures_config)
manager.build_project()
# -------------------------------------------------------------------------------------