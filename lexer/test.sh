files=(
"test-comment-fun"
"test-comment-multi-line"
"test-comment-nesting"
"test-comment-single-line"
"test-comment-unclosed-2"
"test-comment-unclosed"
"test-comment-unopened"
"test-empty"
"test-id"
"test-invalid-char-not"
"test-invalid-char-underscore"
"test-invalid-div-equal"
"test-invalid-less-equal"
"test-invalid-mult-equal"
"test-invalid-plus-equal"
"test-keywords"
"test-number-2"
"test-number"
"test-program-gcd"
"test-program-selection-sort"
"test-program-simple"
"test-program-sum"
"test-stop-on-first-error-2"
"test-stop-on-first-error"
"test-symbols"
"test-whitespace-2"
"test-whitespace"
)

/bin/bash ./compile.sh
for f in "${files[@]}"
do
	/bin/bash ./run.sh test/cases/$f.in test/out_test/$f.out
	echo
	echo
	echo $f
	diff test/cases/$f.out test/out_test/$f.out
done