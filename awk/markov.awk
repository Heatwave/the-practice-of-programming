# markov.awk: markov chain algorithm for 2-word prefixes
BEGIN { MAXGEN = 10000; NOWWORD = "\n"; w1 = w2 = NOWWORD }
{
    for (i = 1; i <= NF; i++) { # read all words
        statetab[w1,w2,++nsuffix[w1,w2]] = $i
        w1 = w2
        w2 = $i
    }
}
END {
    statetab[w1,w2,++nsuffix[w1,w2]] = NOWWORD # add tail
    w1 = w2 = NOWWORD
    for (i = 0; i < MAXGEN; i++) {  # generate
        r = int(rand()*nsuffix[w1,w2]) + 1 # nsuffix >= 1
        p = statetab[w1,w2,r]
        if (p == NOWWORD)
            exit
        print p
        w1 = w2 # advance chain
        w2 = p
    }
}
