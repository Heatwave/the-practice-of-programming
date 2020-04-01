package org.the.practice.of.programming.markovchain;

import java.util.Objects;
import java.util.Vector;

public class Prefix {
    public Vector<String> pref; // NPREF adjacent words from input

    // Prefix constructor: duplicate existing prefix
    Prefix(Prefix p) {
        pref = (Vector<String>) p.pref.clone();
    }

    // Prefix constructor: n copies of str
    Prefix(int n, String str) {
        pref = new Vector<>();
        for (int i = 0; i < n; i++)
            pref.addElement(str);
    }

    static final int MULTIPLIER = 31;   // for hashCode()

    @Override
    public int hashCode() {
        int h = 0;

        for (int i = 0; i < pref.size(); i++) {
            h = MULTIPLIER * h + pref.elementAt(i).hashCode();
        }
        return h;
    }

    @Override
    public boolean equals(Object o) {
        Prefix p = (Prefix) o;
        for (int i = 0; i < pref.size(); i++) {
            if (!pref.elementAt(i).equals(pref.elementAt(i)))
                return false;
        }
        return true;
    }
}
