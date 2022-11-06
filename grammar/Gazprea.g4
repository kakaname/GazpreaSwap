grammar Gazprea;

// -- tokens for AST --
tokens {
}

// --- PARSER RULES ---
file: scope EOF;

stm : stmBody SC ;
block : OBRACE (stm)* CBRACE ;
blStm : block | stmBody ;

stmBody
    : (qualtype | qualifier | type)
      ID (EQ expr)?                 # Declaration
    | lvalue EQ expr                # Assignment
    | IF OPR expr CPR blStm
      (ELSE IF OPR expr CPR blStm)*
      (ELSE blStm)?                 # Conditional
    | LOOP (WHILE stmBody)? blStm   # Loop
    // TODO missing iterator loop for Part 1
    | TYPEDEF type ID               # Typedef
    | expr OUT STDOUT               # Output
    | lvalue IN STDIN               # Input
    | BREAK                         # Break
    | CONTINUE                      # Continue
    //| RETURN expr?                  # Return
    | funcDecl ( EQ expr | block)?  # FunctionDef
    | prodDecl block?               # ProcedureDef
    | prodCall                      # FunctionCall
    | CALL prodCall                 # ProcedureCall
    ;
prodCall : ID OPR (ID (COMMA ID)*)? CPR ;
funcDecl : FUNCTION ID OPR (type ID (COMMA type ID)*)? CPR ;
prodDecl : PROCEDURE ID OPR (qualtype ID (COMMA qualtype ID)*)? CPR ;

qualtype : qualifier type;

scope : stm* ;

expr
    : expr DOT ID                   # DotExpr
    | expr OBR expr CBR             # IndexExpr
    | expr DD expr                  # RangeExpr
    | OPR expr CPR                  # BracketExpr
    |<assoc=right> NOT expr         # NotExpr
    | expr EXP expr                 # ExpExpr
    | expr ( MUL | DIV | MOD | SS)
      expr                          # MulDivExpr
    | expr ( ADD | SUB ) expr       # AddSubExpr
    | expr BY expr                  # ByExpr
    | expr ( LT | GT | LTEQ | GTEQ )
      expr                          # CompExpr
    | expr ( EQEQ | NEQ ) expr      # EqualExpr
    | expr AND expr                 # AndExpr
    | expr (OR | XOR) expr          # OrExpr
    | expr BB expr                  # BBExpr
    | AS LT type GT OPR expr CPR    # AsExpr
    | OBR ID INATOM expr BAR expr CBR   # GeneratorExpr
    | OBR ID INATOM expr AND expr CBR   # FilterExpr
    | atom                         # AtomExpr
    ;

atom :
    | INT
    | ID
    | TRUE
    | FALSE
    | character
    | real
    | NULL
    | IDENTITY
    ;

real : fullReal | sciReal ;

sciReal
    : fullReal 'e' (ADD | SUB)? INT;

fullReal
    : INT DOT INT           # MainReal
    | INT DOT               # IntReal
    | DOT INT               # DotReal
    ;

character : QUOTE 'a' QUOTE;

lvalue : ID                         #ID

    ;

qualifier : CONST | VAR;

type
    : INATOM                            # InAtomType
    | VECTOR                            # VectorType
    | TUPLE OPR type (COMMA type)* CPR  # TupleType
    ;


// --- LEXER RULES ---

// Characters ++
OPR : '(' ;
CPR : ')' ;
OBR : '[' ;
CBR : ']' ;
OBRACE : '{' ;
CBRACE : '}' ;
BAR : '|' ;
BB : '||' ;
SC : ';' ;
EQ : '=' ;
DD : '..' ;
DOT: '.' ;
AND : '&' ;
OUT : '->' ;
IN : '<-' ;
QUOTE : '\'' ;
COMMA : ',' ;

// Ops
ADD : '+' ;
SUB : '-' ;
DIV : '/' ;
MUL : '*' ;
SS : '**' ;
LTEQ : '<=' ;
GTEQ : '>=' ;
LT : '<' ;
GT : '>' ;
EQEQ : '==';
NEQ : '!=' ;
EXP : '^' ;
MOD : '%' ;

// Reserved
IF : 'if' ;
LOOP : 'loop' ;
INATOM : 'in' ;
VECTOR : 'vector' ;
ANDATOM : 'and' ;
AS : 'as' ;
BOOLEANATOM : 'boolean' ;
ELSE : 'else' ;
BREAK : 'break' ;
CONTINUE : 'continue' ;
BY : 'by' ;
CALL : 'call' ;
CHARACTERATOM : 'character' ;
COLUMNS : 'columns' ;
CONST : 'const' ;
FALSE : 'false' ;
TRUE : 'true' ;
FUNCTION : 'function' ;
IDENTITY : 'identity' ;
INTEGERATOM : 'integer' ;
INTERVAL : 'interval' ;
LENGTH : 'length' ;
NOT : 'not' ;
NULL : 'null' ;
OR : 'or' ;
PROCEDURE : 'procedure' ;
REALATOM : 'real' ;
RETURN : 'return' ;
RETURNS : 'returns' ;
REVERSE : 'reverse' ;
STDIN : 'std_input' ;
STDOUT : 'std_output' ;
STRSTA : 'stream_state' ;
STRINGATOM : 'string' ;
TUPLE : 'tuple' ;
TYPEDEF : 'typedef' ;
VAR : 'var' ;
WHILE : 'while' ;
XOR : 'xor' ;


// Customs
INT : [0-9]+ ;
ID : [_a-zA-Z] [_a-zA-Z0-9]* ;

SChar
    :   EscapeSequence
    // TODO check if works
    |  ID
    ;

 fragment
 EscapeSequence
     :   '\\' ['"abtnrv\\]
     ;

// Skip whitespace
BlockComment
    :   '/*' .*? '*/'
        -> skip
    ;

LineComment
    :   '//' ~[\r\n]*
        -> skip
    ;
WS : [ \t\r\n]+ -> skip ;
