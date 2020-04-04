import os
import sys
import re

files=[
	"test-call-byref",
	"test-name-scope",
	"test-nested-expr",
	"test-program-dijkstra",
	"test-program-fibonacci-bottomup",
	"test-program-fibonacci-topdown",
	"test-program-gcd",
	"test-program-selection-sort",
	"test-program-simple",
	"test-simple-expr",
	"test-simple-if",
	"test-simple-return",
	"test-simple-while"
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

correct = 0
for file in files:
	os.system("./run.sh test/cases/{}.in test/out_test/{}.out".format(file, file))
	expected = ""
	out_file_path = "test/cases/{}.out".format(file)
	if os.path.exists(out_file_path):
		f = open(out_file_path, 'r')
		expected = f.read()
		f.close()
	actual = ""
	with open("test/out_test/{}.out".format(file)) as f:
		actual = f.read()

	if trim(actual) != trim(expected):
		print_red(file)
		print('---')
		f = open('test/cases/{}.in'.format(file))
		infile = f.read()
		print(infile)
		print('---')
		print_blue("Output")
		print(actual)
	else:
		print_green(file)
		correct += 1

print_green("\nPassing [{}/{}]".format(correct, len(files)))
