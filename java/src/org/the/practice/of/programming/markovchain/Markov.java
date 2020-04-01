package org.the.practice.of.programming.markovchain;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class Markov {
    static final int MAXGEN = 10000;    // maximum words generated

    public static void main(String[] args) throws IOException {
        Chain chain = new Chain();
        File file = new File("markov-chain-test-text.txt");
        FileInputStream fileInputStream = new FileInputStream(file);

        chain.build(fileInputStream);
        chain.generate(MAXGEN);
    }
}
