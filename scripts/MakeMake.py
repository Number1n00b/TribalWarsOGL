import subprocess # To run g++ commands to gather dependancies.
import sys # For command line args.
import os  # For file enumeration.

"""
@TODO: Modify this to use objects for rules and files, so that it's not just
       a bunch of string passing, and so that the objects can have extra
       rules attached to them. (Will help for tests, and CopyLibs).
"""

# ========== Self Defined Errors ============
class InvalidFileFormatError(Exception):
    def __init__(self, message):
        super().__init__(message)

# ===== Valid Configuration File Flags ======
VALID_CONFIG_FLAGS = {":ENVIRONMENT:" : ":END_ENVIRONMENT:", ":VARS:" : ":END_VARS:" , ":TESTS:" : ":END_TESTS:", ":ALLWAYS:" : ":END_ALLWAYS:"}

# ============= Main Program ================


# ======== Data structure for config ========

# Command line arguments: (Will override defaults, and everything in config file)
# --root-dir
# --src-dir
# --config-file
# --output-name

MAX_LINE_WIDTH = 80

def main():
    print("Running MakeMake...")

    # @TODO be more robust in parsing command line args, and parse the rest too.
    # (Right now we're just checking that the first arg is the config file name)
    if len(sys.argv) == 1 or sys.argv[1].startswith("-"):
        print("Using default configuration.")
        config_file_name = None
    else:
        config_file_name = sys.argv[1]
        print("Attempting to parse config file '{}'...".format(config_file_name))

    config, using_default = parse_config_file(config_file_name)

    if using_default:
        # Use all defaults.
        print("Creating default makefile...")
    else:
        # Use the config.
        print("Creating makefile based on config file...")

    discover_makefile_rules(config)

    create_makefile(config)

    return 0

# ======== Makefile Rule Creation  =========
def discover_makefile_rules(config):
    source_dir = config[":ENVIRONMENT:"]["PROJ_SOURCE_DIR"]

    abs_src_dir = os.path.abspath(source_dir)

    config["MAKE_RULES"] = {}
    if not os.path.exists(abs_src_dir):
        print("Error: The given source directory '{}' does not exist.".format(abs_src_dir))
        exit(-1)

    total_files = get_all_dependancies(config, abs_src_dir)
    make_rule_paths_relative(config)

    print("Generated {} rules.".format(total_files))


def get_all_dependancies(config, previous_dir_path, files_checked = 0):
    # Get all files in the current directory.
    for file in os.listdir(previous_dir_path):
        abs_file_path = previous_dir_path + '\\' + file

        # Recurse if the file is a directory, else analyze file for dependancies.
        if os.path.isdir(abs_file_path):
            #print("Entering {}".format(abs_file_path))
            files_checked = get_all_dependancies(config, abs_file_path, files_checked)
        else:
            # Skip non-c/cpp files.
            if (file.endswith('.c') or file.endswith('.cpp') or file.endswith('.cc')):
                files_checked += 1
                result, _ = run_command(["g++", "-std=c++11", "-MM", abs_file_path])
                result = replace_slashes(result)

                abs_root_path = os.path.abspath(config[":ENVIRONMENT:"]["PROJ_ROOT_DIR"])
                config["MAKE_RULES"][remove_proj_root_from_path(abs_file_path, abs_root_path)] = result

    return files_checked


def replace_slashes(string):
    result = list(string)
    for ii in range(0, len(result) - 1):
        if result[ii] == '\\' and not result[ii + 1] == '\n' and not result[ii + 2] == '\n':
            result[ii] = "/"

    return "".join(result)


def re_capitalize_path(rule):
    second_half = rule.split(":")[1]
    old_path = second_half.replace(" ", "")
    old_path = old_path.replace("\n", "")
    old_path = old_path.replace("\t", "")
    old_path = old_path.replace("\r", "")

    if old_path[0] == '\\':
        old_path = old_path.replace("\\", "", 1)

    # At this point the old path is a list of dependancies seperated by '\'
    dep_list = old_path.split('\\')
    for dep in dep_list:
        to_be_replaced, replaced_with = find_real_file_name(dep)
        rule = rule.replace(to_be_replaced, replaced_with)

    return rule


def find_real_file_name(rel_path):
    file = rel_path.split("/")[-1]

    dir_path_list = rel_path.split("/")[0:-1]
    dir_path =  os.getcwd()
    for dir in dir_path_list:
        dir_path += "/" + dir

    for real_file in os.listdir(dir_path):
        if real_file.lower() == file.lower():
            return rel_path, rel_path.replace(file, real_file)

    raise FileNotFoundError("Could not find real file name for '{}'".format(file))

def remove_proj_root_from_path(path, abs_proj_root):
    path = path.replace(abs_proj_root + "\\", "")
    path = path.replace(abs_proj_root.lower() + "\\", "")
    return path


def make_rule_paths_relative(config):
    abs_root_path = os.path.abspath(config[":ENVIRONMENT:"]["PROJ_ROOT_DIR"])
    for rule in config["MAKE_RULES"].keys():
        config["MAKE_RULES"][rule] = config["MAKE_RULES"][rule].replace(abs_root_path + "\\", "")
        config["MAKE_RULES"][rule] = config["MAKE_RULES"][rule].replace(abs_root_path.lower() + "\\", "")


# ====== Makefile Creation Functions =======
def create_makefile(config):
    makefile_path = config[":ENVIRONMENT:"]["PROJ_ROOT_DIR"] + "/" + config[":ENVIRONMENT:"]["MAKEFILE_NAME"]

    # Now that we have all the rules, add a list of OBJ files to the vars.
    obj_file_list = []
    for rule in config["MAKE_RULES"].keys():
        obj_name = config["MAKE_RULES"][rule].split(":")
        obj_file_list.append(obj_name[0])

    config[":VARS:"]["OBJ_FILES"] = obj_file_list

    with open(makefile_path, "w") as makefile:
        makefile.write("# This file was auto-generated by MakeMake.py\n")

        write_makefile_vars(makefile, config[":VARS:"])

        write_makefile_rules(makefile, config)

        write_makefile_tests(makefile, config[":TESTS:"])

        # Write the rest of the makefile.
        makefile.write(config[":ALLWAYS:"] + "\n")


def write_makefile_vars(makefile, make_vars):
    makefile.write("CC=" + make_vars["CC"] + "\n")
    makefile.write("CFLAGS=" + make_vars["CFLAGS"] + "\n" + "\n")

    makefile.write("EXE_DIR=" + make_vars["EXE_DIR"] + "\n")
    makefile.write("TEST_DIR=" + make_vars["TEST_DIR"] + "\n")
    makefile.write("OBJ_DIR=" + make_vars["OBJ_DIR"] + "\n" + "\n")

    makefile.write("EXE_NAME=" + make_vars["EXE_NAME"] + "\n" + "\n")

    makefile.write("INCLUDE_DIRS=" + make_vars["INCLUDE_DIRS"] + "\n" + "\n")

    makefile.write("LIB_DIRS=" + make_vars["LIB_DIRS"] + "\n")
    makefile.write("LINK_COMMANDS=" + make_vars["LINK_COMMANDS"] + "\n" + "\n")

    makefile.write("COMPILE_WITH_CFLAGS=" + make_vars["COMPILE_WITH_CFLAGS"] + "\n")
    makefile.write("COMPILE_WITH_INCLUDES=" + make_vars["COMPILE_WITH_INCLUDES"] + "\n" + "\n")

    obj_files_str = obj_list_to_str(make_vars["OBJ_FILES"])
    makefile.write("OBJ_FILES=" + obj_files_str + "\n" + "\n")


def write_makefile_rules(makefile, config):
    abs_root_path = os.path.abspath(config[":ENVIRONMENT:"]["PROJ_ROOT_DIR"]).replace("\\", "/")

    make_rules = config["MAKE_RULES"]

    makefile.write("all: executable\n\n")

    makefile.write("executable: $(OBJ_FILES)\n")
    makefile.write("\t$(CC) $(OBJ_FILES) -o $(EXE_DIR)/$(EXE_NAME) $(LIB_DIRS) $(LINK_COMMANDS)\n\n")

    obj_prefix = "$(OBJ_DIR)/"

    for rule in make_rules:
        rel_source_name = rule.replace("\\", "/")
        deps = make_rules[rule].replace(abs_root_path + "/", "")
        deps = deps.replace(abs_root_path.lower() + "/", "")
        deps = fix_format(deps)

        obj_name = deps.split(":")[0]

        deps = re_capitalize_path(deps)

        makefile.write(obj_prefix + deps)
        command = "\t$(COMPILE_WITH_INCLUDES) " + rel_source_name + " -o " + obj_prefix + obj_name
        makefile.write(command + "\n" + "\n")


def fix_format(deps):
    # Remove redundant newline stuff.
    deps = deps.replace("\n", "")
    deps = deps.replace("\r", "\n")

    # Prettify the padding.
    padding_length = len(deps.split(":")[0]) + 2 + len("$(OBJ_DIR)/")
    result = list(deps)

    prev_char = ''
    for ii in range(0, len(result)):
        if prev_char == '\\':
            result[ii + 1] = padding_length * " "

        prev_char = result[ii]

    return "".join(result)


def write_makefile_tests(makefile, make_tests):
    pass

# ======= Config Parsing Functions =========

# Returns: config, using_defaults
#            dict, bool
def parse_config_file(config_file_name):
    config = get_default_config()

    if not config_file_name:
        using_default = True
        return config, using_default

    using_default = False

    try:
        contents = []
        with open(config_file_name, "r") as f:
            for line in f:
                contents.append(line.strip("\n"))

        if len(contents) == 0:
            print("Warning: config file is empty.")
            using_default = True
            return config, using_default

        curr_line_number = 0
        flag_line_number = 0
        exit_flag_line_number = 0

        while(curr_line_number < len(contents)):
            # Ignore blank lines because they are not inside a flag block.
            curr_line_number = eat_empty_lines(contents, curr_line_number)
            curr_line = contents[curr_line_number]

            # Ignore all lines starting with a '#' outside of flag blocks.
            if curr_line.startswith('#'):
                curr_line_number += 1
                continue

            # Check if the flag is valid.
            if curr_line not in VALID_CONFIG_FLAGS.keys():
                msg = "Config file has incorrect format. Flag '{}' is invalid. (Or text outside of flag block).".format(curr_line)
                raise InvalidFileFormatError(msg)
            else:
                flag_line_number = curr_line_number
                exit_flag_line_number = find_exit_flag(contents, curr_line_number, VALID_CONFIG_FLAGS[curr_line])

                if not exit_flag_line_number:
                    msg = "Config file has incorrect format. Flag '{}' has no exit flag ('{}').".format(curr_line, VALID_CONFIG_FLAGS[curr_line])
                    raise InvalidFileFormatError(msg)

                parse_flag_contents(config, contents, flag_line_number, exit_flag_line_number)
                curr_line_number = exit_flag_line_number + 1

    except FileNotFoundError as e:
        print("\tConfig file '{}' not found.".format(config_file_name))
        using_default = True

    except IsADirectoryError as e:
        print("\tGiven config file '{}' is a directory!".format(config_file_name))
        using_default = True

    except InvalidFileFormatError as e:
        print("\t", e, sep="")
        using_default = True

        # Since the file didn't parse correctly, set the config back to defaults.
        config = get_default_config()

    return config, using_default


def eat_empty_lines(contents, curr_line_number):
    while(curr_line_number < len(contents) and len(contents[curr_line_number]) == 0):
        curr_line_number += 1

    return curr_line_number


def find_exit_flag(contents, curr_line_number, exit_flag):
    while curr_line_number < len(contents) - 1 and not contents[curr_line_number] == exit_flag:
        curr_line_number += 1

    if contents[curr_line_number] == exit_flag:
        return curr_line_number
    else:
        return None


def get_default_config():
    config = {}

    # Set up environment variables.
    env_vars = {}

    env_vars["PROJ_ROOT_DIR"] = "."
    env_vars["PROJ_SOURCE_DIR"]  = env_vars["PROJ_ROOT_DIR"] + "/src"

    env_vars["MAKEFILE_NAME"] = "Makefile"

    config[":ENVIRONMENT:"] = env_vars

    # Set up makefile variables.
    makefile_vars = {}
    makefile_vars["CC"] = "g++"
    makefile_vars["CFLAGS"] = "-std=c++11 -Wall -pedantic -g -ggdb -c"

    makefile_vars["EXE_DIR"] = "bin"
    makefile_vars["TEST_DIR"] = "bin/tests"
    makefile_vars["OBJ_DIR"] = "bin/obj"

    makefile_vars["EXE_NAME"] = "program"

    makefile_vars["INCLUDE_DIRS"] = " # Empty"   # Empty until we look through the files.

    makefile_vars["LIB_DIRS"] = " # Empty"       # Empty until we look through the files.
    makefile_vars["LINK_COMMANDS"] = " # Empty"  # Empty until we look through the files.

    makefile_vars["COMPILE_WITH_CFLAGS"] = "$(CC) $(CFLAGS)"
    makefile_vars["COMPILE_WITH_INCLUDES"] = "$(CC) $(CFLAGS) $(INCLUDE_DIRS)"

    makefile_vars["OBJ_FILES"] = " # Empty"      # Empty until we look through the files.

    config[":VARS:"] = makefile_vars

    # Set up test cases. (Empty unless user specifies).
    tests = {}

    config[":TESTS:"] = tests

    # Set up rules. (Empty until we look through the files).
    rules = {}

    config[":RULES:"] = rules

    # Set up 'allways' makefile code.
    allways = """
# Run stuff
.PHONY: run
run:
	./$(EXE_DIR)/$(EXE_NAME)

.PHONY: runVal
runVal:
	valgrind ./$(EXE_DIR)/$(EXE_NAME)


# Clean
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXE_DIR)/$(EXE_NAME) $(EXE_DIR)/*.dll $(TEST_DIR)/* *~*


# Memes
.PHONY: urn
urn:
	@echo "You don't know how to make an urn."


.PHONY: rum
rum:
	@echo "Why is the rum gone?!"


.PHONY: ruin
ruin:
	@echo "You ruined it! :("


.PHONY: riun
riun:
	@echo "Dam dude... can't even ruin it right. :\\"
    """

    config[":ALLWAYS:"] = allways

    return config


def parse_flag_contents(config, contents, start_line, end_line):
    # At this point the tag should be valid, so we don't worry about keyerror here.
    tag = contents[start_line]

    curr_line_number = start_line + 1

    if tag == ":ENVIRONMENT:" or tag == ":VARS:":
        while curr_line_number != end_line:
            curr_line = contents[curr_line_number]

            # Skip comments and empty lines.
            if len(curr_line) == 0 or curr_line.startswith("#"):
                curr_line_number += 1
                continue

            split_line = curr_line.split("=", 1)

            var = split_line[0]
            value = split_line[1]

            if var not in config[tag].keys():
                raise InvalidFileFormatError("Unknown variable '{}' in '{}'.".format(var, tag))

            config[tag][var] = value
            curr_line_number += 1

        return

    if tag == ":ALLWAYS:":
        allways_str = ""
        for ii in range(start_line + 1, end_line):
            allways_str += contents[ii] + "\n"

        config[tag] = allways_str
        return

    print("\tUnprocessed tag:", tag)

# =========== Util ===========
def run_command(command):
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return str(result.stdout.decode("utf-8"))[0:-1], result


def obj_list_to_str(obj_list):
    obj_str = "\\\n"

    obj_prefix = "\t$(OBJ_DIR)/"

    for obj in obj_list:
        # If the total length is too long, go to a new line.
        obj_str += obj_prefix + obj + "\\\n"

    # Remove the last trailing '\' and '\n'
    obj_str = obj_str[0:-2]

    return obj_str


# @ Depracted, use if you want obj file list to be more compact.
def old_obj_list_to_str(obj_list):
    obj_str = "\\\n"

    obj_prefix = "$(OBJ_DIR)/"

    curr_line = "\t"
    for obj in obj_list:
        if len(curr_line + obj_prefix + obj) > MAX_LINE_WIDTH:
            if len(obj_prefix + obj) >= MAX_LINE_WIDTH:
                # If the filename is just really long, give it its own line.
                obj_str += "\t" + obj_prefix + obj + "\\\n"
            else:
                # If the total length is too long, go to a new line.
                obj_str += curr_line + "\\\n"

                # Reset the current line.
                curr_line = "\t"

        else: # The length is still fine, so just add the obj.
            curr_line += obj_prefix + obj + " "

    # Add the final line if it's not empty.
    if not curr_line == "\t":
        obj_str += curr_line

    return obj_str

# ======= Entry Point ========
if __name__ == "__main__":
    main()
