# markov.pl: markov chain algorithm for 2-word prefixes
$MAXGEN = 10000;
$NOWWORD = "\n";
$w1 = $w2 = $NOWWORD;   # initial state
while (<>) {    # read each line of input
    foreach (split) {
        push(@{$statetab{$w1}{$w2}}, $_);
        ($w1, $w2) = ($w2, $_); # multiple assignment
    }
}
push(@{$statetab{$w1}{$w2}}, $NOWWORD); # add tail
$w1 = $w2 = $NOWWORD;
for ($i = 0; $i < $MAXGEN; $i++) {
    $suf = $statetab{$w1}{$w2}; # array reference
    $r = int(rand @$suf);   # @$suf is number of elems
    exit if (($t = $suf->[$r]) eq $NOWWORD);
    print "$t\n";
    ($w1, $w2) = ($w2, $t); # advance chain
}
