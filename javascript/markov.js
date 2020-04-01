'use strict';

const fs = require('fs');

const NPREF = 2;
const MAXGEN = 10000;
const NOWWORD = '\n';

const statetab = {};
const prefix = [];

let result = '';

function add(prefix, suffix) {
    if (!statetab[prefix]) {
        statetab[prefix] = [suffix];
    } else {
        statetab[prefix].push(suffix);
    }
    prefix.shift();
    prefix.push(suffix);
}

function build(prefix, text) {
    text.forEach(word => {
        add(prefix, word);
    });
}

function generate() {
    for (let i = 0; i < NPREF; i++) {
        prefix[i] = NOWWORD;
    }

    for (let i = 0; i < MAXGEN; i++) {
        const suffix = statetab[prefix];
        const word = suffix[Math.floor(Math.random() * suffix.length)];
        if (word === NOWWORD)
            break;
        result += word + ' ';
        prefix.shift();
        prefix.push(word);
    }
}

fs.readFile('markov-chain-test-text.txt', (err, data) => {
    if (err) throw err;

    const text = data.toString().split(/[\s\n]/g).filter((word) => {
        return word.length > 0;
    });

    for (let i = 0; i < NPREF; i++) {
        prefix[i] = NOWWORD;
    }
    build(prefix, text);
    add(prefix, NOWWORD);
    generate();
    console.log(result);
});
