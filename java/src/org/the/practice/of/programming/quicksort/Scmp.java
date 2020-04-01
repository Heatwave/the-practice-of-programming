package org.the.practice.of.programming.quicksort;

public class Scmp implements Cmp {
    @Override
    public int cmp(Object x, Object y) {
        String s1 = (String) x;
        String s2 = (String) y;
        return s1.compareTo(s2);
    }
}
