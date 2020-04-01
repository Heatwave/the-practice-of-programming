package main

import "fmt"
import "io"
import "os"
import "math/rand"

const (
	NPREF  int = 2     // number of prefix words
	MAXGEN int = 10000 // maximum words generated
)

var statetab map[string][]string

var NOWWORD = "\n"

func arrayToString(prefix []string) string {
	s := ""
	for i := 0; i < len(prefix); i++ {
		s += prefix[i]
	}
	return s
}

func add(prefix []string, suffix string) []string {
	key := arrayToString(prefix)
	statetab[key] = append(statetab[key], suffix)

	prefix = prefix[1:NPREF]
	prefix = append(prefix, suffix)
	return prefix
}

func build(prefix []string) {
	var suffix string
	for n, err := fmt.Scan(&suffix); n != 0 && err != io.EOF; n, err = fmt.Scan(&suffix) {
		if err != nil {
			fmt.Println("error: ", err)
			os.Exit(1)
		}
		prefix = add(prefix, suffix)
	}
	add(prefix[0:NPREF], NOWWORD)
}

func generate(prefix []string) {
	result := ""

	for i := 0; i < NPREF; i++ {
		prefix[i] = NOWWORD
	}

	for i := 0; i < MAXGEN; i++ {
		suffixArr := statetab[arrayToString(prefix)]
		word := suffixArr[rand.Intn(len(suffixArr))]
		if word == NOWWORD {
			break
		}
		result += word + " "

		prefix = prefix[1:NPREF]
		prefix = append(prefix, word)
	}

	fmt.Println(result)
}

func main() {
	statetab = make(map[string][]string)

	var prefix [NPREF]string

	for i := 0; i < NPREF; i++ {
		prefix[i] = NOWWORD
	}
	build(prefix[0:NPREF])
	generate(prefix[0:NPREF])
}
