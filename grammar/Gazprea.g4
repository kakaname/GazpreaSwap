grammar Gazprea;

// -- tokens for AST --
tokens {
}

// --- PARSER RULES ---
file: (global)* EOF;

global
    : identDecl
    | functionDeclr
    | functionDefinition
    | procedureDeclr
    | procedureDefinition;

stmt: simpleStmt | block; // Block should really be called compound statement.

simpleStmt
    : identDecl
    | assignment
    | conditional
    | loop
    | typeDef
    | output
    | input
    | BREAK
    | CONTINUE
    | return
    | functionDeclr
    | functionDefinition
    | procedureDeclr
    | procedureDefinition
    | procedureCall;

identDecl
    : (typeQualifier)? (type)? ID (EQ expr)? SC;

assignment
    : ID EQ (expr | procedureCall) SC;

conditional
    : IF expr stmt              # ifConditional
    | IF expr stmt ELSE stmt    # ifElseConditional;

loop
    : LOOP stmt                 # infiniteLoop
    | LOOP WHILE expr stmt      # whileLoop
    | LOOP iterDomain stmt      # domainLoop;

iterDomain
    : ID GET expr;

typeDef
    : TYPEDEF ID ID SC;

output
    : expr PUT STDOUT SC;

input
    : ID IN STDIN SC;

return
    : RETURN expr SC;

typeQualifier
    : VAR
    | CONST;

type
    : ID                                            #resolvedType
    | tupleTypeDecl                                 #tupleType
    | ID LSQRPAREN expressionOrWildcard RSQRPAREN   #vectorType
    | ID LSQRPAREN expressionOrWildcard COMMA
    expressionOrWildcard RSQRPAREN                  #matrixType
    ;

expressionOrWildcard:
    (MUL | expr);

tupleTypeDecl
    : TUPLE LPAREN typeOptionalIdentPair COMMA typeOptionalIdentPair
     (COMMA typeOptionalIdentPair)*;

typeOptionalIdentPair
    : type (ID)?;

typeIdentPair
    : type ID;

functionDeclr
    : FUNCTION funcName=ID LPAREN
      (typeOptionalIdentPair (COMMA typeOptionalIdentPair)*)?
      RPAREN RETURNS type SC;

functionDefinition
    : FUNCTION ID funcName=LPAREN
      (typeIdentPair (COMMA typeIdentPair)*)?
      RPAREN RETURNS type (block | EQ expr SC);

procedureDeclr
    : PROCEDURE procName=ID LPAREN
      (typeOptionalIdentPair (COMMA typeOptionalIdentPair)*)? RPAREN (RETURNS type)?;

procedureDefinition
    : PROCEDURE procName=ID LPAREN
    (typeIdentPair (COMMA typeIdentPair)*)? RPAREN (RETURNS type)? block;

functionCall // Should be an expression.
    : ID LPAREN (expr (COMMA expr)*)? RPAREN;

procedureCall
    : CALL ID LPAREN (expr (COMMA expr)*)? RPAREN;

block : LBRACE (stmt)* RBRACE ;

// TODO: Check precedence and add matrix literals, vector literals,
//  real literals, string literals, tuple literals.

// 1. promote bracketExpr to the highest priority
expr: LPAREN expr RPAREN                    # bracketExpr
    | expr PERIOD (ID | INTLITERAL)         # memberAccess
    | expr LSQRPAREN expr RSQRPAREN         # indexExpr
    | expr DD expr (BY expr)?               # rangeExpr
    | <assoc=right> op=(ADD | SUB | NOT) expr                 # notExpr
    | expr EXP expr                         # expExpr
    | expr ( MUL | DIV | MOD | SS)
      expr                                  # mulDivExpr // A better name perhaps
    | expr ( ADD | SUB ) expr               # addSubExpr
    | expr BY expr                          # byExpr
    | expr ( LT | GT | LTEQ | GTEQ )
      expr                                  # compExpr
    | expr ( EQEQ | NEQ ) expr              # equalExpr
    | expr AND expr                         # andExpr
    | expr (OR | XOR) expr                  # orExpr
    | expr APPENDOP expr                    # appendOp
    | AS LT type GT LPAREN expr RPAREN            # explicitCast
    | LSQRPAREN ID IN expr BAR expr RSQRPAREN       # generatorExpr
    | LSQRPAREN ID IN expr AND expr RSQRPAREN       # filterExpr
    | functionCall                          # funcCall
    | (TRUE | FALSE)                        # boolLiteral
    | NULL                                  # nullLiteral
    | IDENTITY                              # identityLiteral
    | ID                                    # identifier
    | INTLITERAL                            # intLiteral
    ;

realLiteral : fullRealLiteral | sciRealLiteral ;

sciRealLiteral
    : fullRealLiteral 'e' (ADD | SUB)? INT;

fullRealLiteral
    : INT PERIOD INT           # MainReal
    | INT PERIOD               # IntReal
    | PERIOD INT               # DotReal
    ;

char : QUOTE SChar QUOTE;

// --- LEXER RULES ---

// Characters ++
LPAREN : '(' ;
RPAREN : ')' ;
LSQRPAREN : '[' ;
RSQRPAREN : ']' ;
LBRACE : '{' ;
RBRACE : '}' ;
BAR : '|' ;
APPENDOP : '||' ;
SC : ';' ;
EQ : '=' ;
DD : '..' ;
PERIOD: '.' ;
AND : '&' ;
PUT : '->' ;
GET : '<-' ;
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
IN : 'in' ;
ANDATOM : 'and' ;
AS : 'as' ;
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
INTLITERAL : [0-9]+ ;
ID : [_a-zA-Z] [_a-zA-Z0-9]* ;

SChar:
//    :   EscapeSequence
//     TODO check if works
//    |   ~["\\\r\n]
    'scar'
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

