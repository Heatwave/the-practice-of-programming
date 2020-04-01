package org.the.practice.of.programming.quicksort;

public class Icmp implements Cmp {
    @Override
    public int cmp(Object x, Object y) {
        int i1 = (Integer) x;
        int i2 = (Integer) y;
        return Integer.compare(i1, i2);
    }
}
