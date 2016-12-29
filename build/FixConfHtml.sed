/TianShan.*/ {
s/::/\//g
}

s/Struct/Configuration Element/g
#s/struct\([ \t<]*\)/element\1/g
s/>struct \&nbsp;</>element \&nbsp;</g

s/>Classes</>Elements</g

s/Class[ \t\n]*List/Element List/g
s/Class\&nbsp;List/Element\&nbsp;List/g

s/Class[ \t\n]*Members/Element Attributes/g
s/Class\&nbsp;Members/Element\&nbsp;Attributes/g
s/>Variables</>Attributes</g


