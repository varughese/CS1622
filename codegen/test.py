import os
import sys
import re

files=[
	# "test-call-byref",
	# "test-name-scope",
	# "test-nested-expr",
	# "test-program-dijkstra",
	# "test-program-fibonacci-bottomup",
	# "test-program-fibonacci-topdown",
	# "test-program-gcd",
	# "test-program-selection-sort",
	"test-program-simple",
	# "test-simple-expr",
	# "test-simple-if",
	# "test-simple-return",
	# "test-simple-while",
	"test-mingmat-var-decl"
]

RED='\033[0;31m'
GREEN='\033[0;32m'
OKBLUE = '\033[94m'
RESETCOLOR='\033[0m'
def print_green(txt):
	print(GREEN + txt + RESETCOLOR)

def print_red(txt):
	print(RED + txt + RESETCOLOR)

def print_blue(txt):
	print(OKBLUE + txt + RESETCOLOR)

os.system("./compile.sh")
os.makedirs("test/out_test/", exist_ok=True)

def trim(str):
	return re.sub('[\s+]', '', str)

def execute_mips(asm_path):
	# return 'f'
	spim_output = os.popen("spim -file {}".format(asm_path)).read()
	return '\n'.join(spim_output.splitlines()[5:])

correct = 0
for file in files:
	input_path = "test/cases/{}.in".format(file)
	asm_path = "test/out_test/{}.asm".format(file)
	os.system("./run.sh {} {}".format(input_path, asm_path))
	expected_stdout = ""
	stdout_path = "test/cases/{}.stdout".format(file)
	stdin_path = "test/cases/{}.stdin".format(file)
	if os.path.exists(stdout_path):
		f = open(stdout_path, 'r')
		expected_stdout = f.read()
		f.close()

	
	mips_output = execute_mips(asm_path)
	if trim(expected_stdout) != trim(mips_output):
		print_red(file)
		print_blue("Expected");
		print(expected_stdout)
		print_blue("Actual")
		print(mips_output)
	else:
		print_green(file)
		correct = correct + 1


print_green("\nPassing [{}/{}]".format(correct, len(files)))
