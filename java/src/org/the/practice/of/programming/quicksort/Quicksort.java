package org.the.practice.of.programming.quicksort;

import java.util.Arrays;
import java.util.Random;

public class Quicksort {
    static void sort(Object[] v, int left, int right, Cmp cmp) {
        int i, last;
        if (left >= right) // nothing to do
        {
            return;
        }
        swap(v, left, rand(left, right));
        last = left;
        for (i = left + 1; i <= right; i++) {
            if (cmp.cmp(v[i], v[left]) < 0) {
                swap(v, ++last, i);
            }
        }
        swap(v, left, last);
        sort(v, left, last - 1, cmp);
        sort(v, last + 1, right, cmp);
    }

    static Random rgen = new Random();

    private static int rand(int left, int right) {
        return left + Math.abs(rgen.nextInt()) % (right - left + 1);
    }

    static void swap(Object[] v, int i, int j) {
        Object temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    public static void main(String[] args) {
        Integer[] arr = {3, 1, 5, 8, 2, 4, 0};
        Quicksort.sort(arr, 0, arr.length - 1, new Icmp());
        System.out.println(Arrays.toString(arr));
    }
}
