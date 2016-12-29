# Skip C-style commenting
/\/\*/ , /\*\//b
/\/\/\(.*\)/b

s/module/namespace/
s/local//
s/idempotent//
s/dictionary/typedef map/
s/sequence/typedef vector/

/exception/ , /{/    {
#change extends
    s/extends/: public/
}

#parse local class
/class/ , /{/    {
#change extends
    s/extends/: public/

#add public before every keyword, but not {
    /{/!s/,\(.*\)/, public \1/g
    s/{/{public:/
}

#parse local interface
/interface/ , /{/    {
    /interface/ {
        #change interface to class
        s/interface\(.*\)/class \1/
    }
#change extends
    s/extends/: public/

#add public before every keyword, but not {
    /{/!s/,\(.*\)/, public \1/g
    s/{/{public:/
}

s/nonmutating\(.*)\)/\1 const/

/throws/,/;/ {
    s/throws/throw(/
    s/;/);/
}

