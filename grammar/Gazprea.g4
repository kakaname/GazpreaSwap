grammar Gazprea;

// Parser rules
file: statement* EOF;

block: (statement | comment)*;

comment: INLINECOMMENT
         | BLOCKCOMMENT;

statement: declarStat
         | assignStat
         | ifStat
         | loopStat
         | printstat
         ;

declarStat: type ID ASSIGN_EQUAL expr SC;

assignStat: ID ASSIGN_EQUAL expr SC;

ifStat: IF L_PAREN expr R_PAREN block FI SC;

loopStat: LOOP L_PAREN expr R_PAREN block POOL SC;

printstat: PRINT L_PAREN expr R_PAREN SC;


type: INT
    | VECTOR
    ;

expr: L_PAREN expr R_PAREN                                    #paren
    | expr L_SQUARE_BRACKET expr R_SQUARE_BRACKET             #index
    | expr TWO_DOTS expr                                      #range
    | expr op=(MUL | DIV) expr            #mulDiv
    | expr op=(ADD | SUB) expr            #addSub
    | expr op=(LT | GT) expr              #lessGreater
    | expr op=(EQUAL | NOT_EQUAL) expr    #equalNotEqual
    | L_SQUARE_BRACKET ID IN expr VERTICAL_BAR expr R_SQUARE_BRACKET   #generator
    | L_SQUARE_BRACKET ID IN expr AMPERSAND expr R_SQUARE_BRACKET      #filter
    | INTEGER                             #literal
    | ID                                  #identifier
    ;

// Lexer rules
IF: 'if';
FI: 'fi';
LOOP: 'loop';
POOL: 'pool';
INT: 'int';
PRINT: 'print';
IN: 'in';
VECTOR: 'vector';

INLINECOMMENT: '//' .*? ('\r' | '\n') -> skip;
BLOCKCOMMENT: '/*' .*? '*/' -> skip;

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';
LT: '<';
GT: '>';
EQUAL: '==';
NOT_EQUAL: '!=';
TWO_DOTS: '..';
ASSIGN_EQUAL: '=';
L_PAREN: '(';
R_PAREN: ')';
L_SQUARE_BRACKET: '[';
R_SQUARE_BRACKET: ']';
SC: ';';
AMPERSAND: '&';
VERTICAL_BAR: '|';


INTEGER: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]*;

// Skip whitespace
WS : [ \t\r\n]+ -> skip ;