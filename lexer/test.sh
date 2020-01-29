files=(
# "test-comment-fun"
# "test-comment-multi-line"
# "test-comment-nesting"
# "test-comment-single-line"
# "test-comment-unclosed-2"
# "test-comment-unclosed"
# "test-comment-unopened"
# "test-empty"
# "test-id"
# "test-invalid-char-not"
# "test-invalid-char-underscore"
# "test-invalid-div-equal"
# "test-invalid-less-equal"
# "test-invalid-mult-equal"
# "test-invalid-plus-equal"
# "test-keywords"
# "test-number-2"
# "test-number"
# "test-program-gcd"
# "test-program-selection-sort"
"test-program-simple"
"test-program-sum"
"test-stop-on-first-error-2"
"test-stop-on-first-error"
"test-symbols"
"test-whitespace-2"
# "test-whitespace"
)

RED='\033[0;31m'
GREEN='\033[0;32m'
RESETCOLOR='\033[0m' # No Color

/bin/bash ./compile.sh
for f in "${files[@]}"
do
	/bin/bash ./run.sh test/cases/$f.in test/out_test/$f.out

	diff_output="$(diff "test/cases/$f.out" "test/out_test/$f.out")"  
	if [[ $diff_output == "" ]]; then
    	echo -e "${GREEN}${f}${RESETCOLOR}"
	else
		echo -e "${RED}${f}${RESETCOLOR}"
		echo "----"
		cat test/cases/$f.in
		echo "----"
		sdiff test/cases/$f.out test/out_test/$f.out
	fi
	echo
done