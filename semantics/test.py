import os
import sys
import re
from difflib import context_diff as diff

files=[
	"test-call-missing-paren",
	"test-expr-number-big2",
	"test-fundecl-params-void-and-stuff",
	"test-fundecl-retn",
	"test-keyword-as-id",
	"test-locdecl-void",
	"test-program-simple",
	"test-sema-array-out-of-bounds-lower",
	"test-sema-array-out-of-bounds-upper",
	"test-sema-array-subscript-non-array",
	"test-sema-builtin-bad-array-param",
	"test-sema-builtin-bad-param-count",
	"test-sema-builtin-bad-return-type",
	"test-sema-builtin",
	"test-sema-call-argcount-match",
	"test-sema-call-argcount-too-few",
	"test-sema-call-argcount-too-many",
	"test-sema-call-missing-paren",
	"test-sema-fun-in-assignment",
	"test-sema-fun-in-boolean-test",
	"test-sema-fun-redecl-as-local",
	"test-sema-fun-redecl-as-param",
	"test-sema-fun-redecl-as-var",
	"test-sema-fun-redecl-but-overload",
	"test-sema-fun-redecl",
	"test-sema-fun-use-before-decl",
	"test-sema-local-redecl-as-inner-local",
	"test-sema-local-redecl-as-local",
	"test-sema-main-last-decl-has-param",
	"test-sema-main-last-decl-name-main",
	"test-sema-main-last-decl-no-void",
	"test-sema-main-last-decl-ok",
	"test-sema-main-last-decl-var-decl",
	"test-sema-no-decl",
	"test-sema-param-array-in-expr",
	"test-sema-param-array-test1",
	"test-sema-param-array-test2",
	"test-sema-param-redecl-as-inner-local",
	"test-sema-param-redecl-as-local",
	"test-sema-param-redecl-as-param",
	"test-sema-recursive-fun",
	"test-sema-stmt-array",
	"test-sema-typecheck-assign-array-to-array",
	"test-sema-typecheck-assign-array-to-int",
	"test-sema-typecheck-assign-array-to-void",
	"test-sema-typecheck-assign-int-call-to-int",
	"test-sema-typecheck-assign-int-fun-to-int",
	"test-sema-typecheck-assign-int-to-array",
	"test-sema-typecheck-assign-int-to-int",
	"test-sema-typecheck-assign-int-to-void",
	"test-sema-typecheck-assign-void-to-array",
	"test-sema-typecheck-assign-void-to-int",
	"test-sema-typecheck-assign-void-to-void",
	"test-sema-typecheck-binary-expr-array-to-array",
	"test-sema-typecheck-binary-expr-array-to-int",
	"test-sema-typecheck-binary-expr-array-to-void",
	"test-sema-typecheck-binary-expr-fun-to-int",
	"test-sema-typecheck-binary-expr-int-to-array",
	"test-sema-typecheck-binary-expr-int-to-int",
	"test-sema-typecheck-binary-expr-int-to-void",
	"test-sema-typecheck-binary-expr-void-to-array",
	"test-sema-typecheck-binary-expr-void-to-int",
	"test-sema-typecheck-binary-expr-void-to-void",
	"test-sema-typecheck-call-void-arg",
	"test-sema-typecheck-iterationstmt-expr-array",
	"test-sema-typecheck-iterationstmt-expr-fun-call",
	"test-sema-typecheck-iterationstmt-expr-int",
	"test-sema-typecheck-iterationstmt-expr-void",
	"test-sema-typecheck-param-array-to-array-subscript",
	"test-sema-typecheck-param-array-to-array",
	"test-sema-typecheck-param-array-to-int",
	"test-sema-typecheck-param-array-to-void",
	"test-sema-typecheck-param-int-to-array-subscript",
	"test-sema-typecheck-param-int-to-array",
	"test-sema-typecheck-param-int-to-int",
	"test-sema-typecheck-param-int-to-void",
	"test-sema-typecheck-returnstmt-array-in-int",
	"test-sema-typecheck-returnstmt-array-in-void",
	"test-sema-typecheck-returnstmt-empty-in-int",
	"test-sema-typecheck-returnstmt-empty-in-void",
	"test-sema-typecheck-returnstmt-int-in-int",
	"test-sema-typecheck-returnstmt-int-in-void",
	"test-sema-typecheck-returnstmt-void-in-int",
	"test-sema-typecheck-returnstmt-void-in-void",
	"test-sema-typecheck-selectionstmt-expr-array",
	"test-sema-typecheck-selectionstmt-expr-int",
	"test-sema-typecheck-selectionstmt-expr-void",
	"test-sema-typecheck-var-index-array",
	"test-sema-typecheck-var-index-int",
	"test-sema-typecheck-var-index-void",
	"test-sema-var-in-call",
	"test-sema-var-redecl-as-fun",
	"test-sema-var-redecl-as-local",
	"test-sema-var-redecl-as-param",
	"test-sema-var-redecl-as-var",
	"test-sema-var-use-before-decl",
	"test-sema-var-use-outside-of-fun-body",
	"test-sema-var-use-outside-of-inner-scope",
	"test-sema-var-use-outside-of-scope",
	"test-sema-void-param-type",
	"test-sema-void-var-type",
	"test-var-simple",
	"test-var-subscript-2d",
	"test-vardecl-array-2d"
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
		# print_green(file)
		correct += 1

print_green("\nPassing [{}/{}]".format(correct, len(files)))
