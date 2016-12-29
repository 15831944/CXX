
# Skip C-style commenting
#/<\!--/ , /-*>/b
#/\/\/\(.*\)/b

/<[^>]*$/{
:incompl_statement
N
/.*>/ {
   N
   t incompl_statement
   }
}

s/<\/[^>]*>/};\n/g
s/\/>/};\n/g

s/@element/@struct/g
s/@attr[ \t]*\([^ \t]*\)[ \t]*\(.*\)$/@var attribute \1\n@brief \2 -->\n<\!--- /g

s/<\!---/\/\*\! /g
s/<\!--/\/\* /g
s/-*->/ \*\//g

/<.*/ {
#  /<\!--/ , /.*>/b

  s/<\([^ \t\n]*\)[ \t\n]*/struct \1 {\n/g
  s/\([^ \t\n]*\)[ \t\n]*=[ \t\n]*"\([^"]*\)"/attribute \1;\n/g
# s/<*[^>]*>//g
  s/>//g
}

# /\/\*/ , /\*\//b
