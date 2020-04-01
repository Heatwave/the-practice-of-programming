package org.the.practice.of.programming.markovchain;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.StreamTokenizer;
import java.util.Hashtable;
import java.util.Random;
import java.util.Vector;

public class Chain {
    static final int NPREF = 2; // size of prefix
    static final String NOWWORD = "\n"; // "word" that can't appear
    Hashtable<Prefix, Vector<String>> statetab = new Hashtable<>();   // key = Prefix, value = suffix Vector;
    Prefix prefix = new Prefix(NPREF, NOWWORD); // initial prefix
    Random rand = new Random();

    // Chain build: build State table from input stream
    void build(FileInputStream in) throws IOException {
        StreamTokenizer st = new StreamTokenizer(in);

        st.resetSyntax();   // remove default rules
        st.wordChars(0, Character.MAX_VALUE);   // turn on all chars
        st.whitespaceChars(0, ' '); // except up to blank
        while (st.nextToken() != StreamTokenizer.TT_EOF)
            add(st.sval);
        add(NOWWORD);
    }

    // Chain add: add word to suffix list, update prefix
    void add(String word) {
        Vector<String> suf = statetab.get(prefix);
        if (suf == null) {
            suf = new Vector<>();
            statetab.put(new Prefix(prefix), suf);
        }
        suf.addElement(word);
        prefix.pref.removeElementAt(0);
        prefix.pref.addElement(word);
    }

    // Chain generate: generate output words
    void generate(int nwords) {
        prefix = new Prefix(NPREF, NOWWORD);
        for (int i = 0; i < nwords; i++) {
            Vector<String> s = statetab.get(prefix);
            String suf = s.elementAt(Math.abs(rand.nextInt()) % s.size());
            if (suf.equals(NOWWORD)) {
                break;
            }
            System.out.print(suf + " ");
            prefix.pref.removeElementAt(0);
            prefix.pref.addElement(suf);
        }
    }
}
