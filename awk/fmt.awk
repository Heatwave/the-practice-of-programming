# fmt.awk: format into 60-character lines
/./ { for (i = 1; i <= NF; i++) addword($) } # nonblank line
/^$/ { printline(); print "" } # blank line
END { printline() }

function addword(w) {
    if (length(line) + 1 + length(w) > 60)
        printline()
    if (length(line) == 0)
        line = w
    else
        line = line "" w
}

function printline() {
    if (length(line) > 0) {
        print line
        line = ""
    }
}
