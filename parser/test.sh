files=(
"test-call-bad-arg-expr1"
"test-call-bad-arg-expr2"
"test-call-empty-arg-expr"
"test-call-missing-lparen"
"test-call-missing-rparen"
"test-call-no-comma"
"test-call-simple"
"test-compstmt-noclose"
"test-compstmt-noopen"
"test-compstmt-simple"
"test-compstmt-stmt-after-vardecl"
"test-compstmt-stmt-only"
"test-compstmt-vardecl-after-stmt"
"test-compstmt-vardecl-only"
"test-compstmt-vardecl-stmt"
"test-decl-bad-lookahead"
"test-declist-bad-fun-in-many"
"test-declist-bad-var-in-many"
"test-declist-simple"
"test-empty"
"test-expr-addops-missing-rhs"
"test-expr-addops"
"test-expr-assign-assign-bad"
"test-expr-assign-assign"
"test-expr-assign-noassign"
"test-expr-assign-relop"
"test-expr-assign-simple"
"test-expr-assign-to-expr"
"test-expr-associativity"
"test-expr-mulops-missing-rhs"
"test-expr-mulops"
"test-expr-number-big1"
"test-expr-number"
"test-expr-parens-empty"
"test-expr-parens-missing"
"test-expr-parens"
"test-expr-precedence"
"test-expr-relop-3ops"
"test-expr-relop-compound"
"test-expr-relop-missing-rhs"
"test-expr-relops"
"test-expr-rhs-is-eof"
"test-expr-rhs-is-op"
"test-expr-subscript2"
"test-expr-unary"
"test-exprstmt-bad-expr"
"test-exprstmt-empty"
"test-exprstmt-no-semicolon"
"test-fundecl-close-paren-twice"
"test-fundecl-inside-fun"
"test-fundecl-no-closeparen"
"test-fundecl-no-compound-but-stmt"
"test-fundecl-no-compound-close"
"test-fundecl-no-compound-open"
"test-fundecl-no-compound"
"test-fundecl-no-id"
"test-fundecl-no-openparen"
"test-fundecl-no-params-at-all"
"test-fundecl-no-type-no-id"
"test-fundecl-no-type"
"test-fundecl-not-id"
"test-fundecl-not-id2"
"test-fundecl-not-type"
"test-fundecl-params-dangling-comma"
"test-fundecl-params-dangling-comma2"
"test-fundecl-params-empty-int"
"test-fundecl-params-empty"
"test-fundecl-params-many"
"test-fundecl-params-missing-next-and-close-paren"
"test-fundecl-params-missing-next"
"test-fundecl-params-no-comma-but-sym"
"test-fundecl-params-no-comma"
"test-fundecl-params-using-brackets"
"test-fundecl-params-using-brackets2"
"test-fundecl-params-void-and-comma"
"test-fundecl-params-void-and-more"
"test-fundecl-prototype"
"test-fundecl-retn"
"test-fundecl-simple"
"test-fundecl-simple2"
"test-iterationstmt-bad-expr1"
"test-iterationstmt-bad-stmt1"
"test-iterationstmt-complex"
"test-iterationstmt-nolparen"
"test-iterationstmt-noparen"
"test-iterationstmt-norparen"
"test-iterationstmt-simple"
"test-locdecl-after-stmts"
"test-locdecl-missing-semicolon"
"test-locdecl-simple"
"test-param-array"
"test-param-bracket-not-empty"
"test-param-many"
"test-param-no-nothing"
"test-param-noclosebracket"
"test-param-noid"
"test-param-noopenbracket"
"test-param-not-a-type"
"test-param-notype"
"test-param-simple"
"test-program-example"
"test-program-gcd"
"test-program-selection-sort"
"test-program-simple"
"test-program-sum"
"test-returnstmt-bad-expr"
"test-returnstmt-good-expr-no-semicolon"
"test-returnstmt-no-semicolon"
"test-returnstmt-simple"
"test-selectionstmt-bad-expr1"
"test-selectionstmt-bad-stmt1"
"test-selectionstmt-bad-stmt2"
"test-selectionstmt-complex"
"test-selectionstmt-dangling-else"
"test-selectionstmt-else-if"
"test-selectionstmt-nolparen"
"test-selectionstmt-noparen"
"test-selectionstmt-norparen"
"test-selectionstmt-simple"
"test-statement-bad-lookahead"
"test-stmtlist-before-locdecl"
"test-stmtlist-missing-semicolon"
"test-stmtlist-simple"
"test-var-expr"
"test-var-subscript-empty"
"test-var-subscript-noclose"
"test-var-subscript-noid"
"test-var-subscript-noopen"
"test-var-subscript"
"test-vardecl-array-negative"
"test-vardecl-array-positive"
"test-vardecl-array"
"test-vardecl-empty"
"test-vardecl-multiple-in-single-line"
"test-vardecl-noid"
"test-vardecl-nosemicolon"
"test-vardecl-notatype"
"test-vardecl-notype-but-decl"
"test-vardecl-notype"
"test-vardecl-simple"
"test-vardecl-size-isempty"
"test-vardecl-size-isexpr"
"test-vardecl-size-isid"
"test-vardecl-size-istrash"
"test-vardecl-size-noclose"
"test-vardecl-size-noopen"
"test-vardecl-size-nosemicolon"
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