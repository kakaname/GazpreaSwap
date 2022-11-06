grammar Gazprea;

file: .*? EOF;

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
