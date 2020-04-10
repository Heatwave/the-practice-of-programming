package org.the.practice.of.programming.csv;

import java.io.*;
import java.util.ArrayList;

public class Csv {
    private String line;
    BufferedReader reader;
    private ArrayList<String> field;
    private String fieldSeparator;

    public Csv(InputStream fin, String fieldSeparator) {
        this.fieldSeparator = fieldSeparator;
        reader = new BufferedReader(new InputStreamReader(fin));
        field = new ArrayList<>();
    }

    private void split() {
        for (int i = 0; i < line.length(); i++) {
            StringBuilder fld = new StringBuilder();
            if (line.charAt(i) == '"') {
                i += 1;
                for (int j = i; j < line.length(); j++) {
                    if (line.charAt(j) == '"' && j == line.length() - 1) {
                        i = j;
                        break;
                    }

                    if (line.charAt(j) == '"' && line.charAt(++j) != '"') {
                        int nextSeparator = line.indexOf(fieldSeparator, j);
                        if (nextSeparator == -1) {
                            fld.append(line, j, line.length());
                            i = line.length();
                        } else {
                            fld.append(line, j, nextSeparator);
                            i = nextSeparator;
                        }
                        break;
                    }
                    i = j;
                    fld.append(line.charAt(j));
                }
            } else {
                int nextSeparator = line.indexOf(fieldSeparator, i);
                if (nextSeparator != -1) {
                    fld.append(line, i, nextSeparator);
                    i = nextSeparator;
                } else {
                    fld.append(line.substring(i));
                    i = line.length();
                }
            }
            field.add(fld.toString());
        }
    }

    public int getNfield() {
        return field.size();
    }

    public boolean getline() throws IOException {
        field.clear();
        line = reader.readLine();
        if (line != null)
            split();
        return line != null && line.length() != 0;
    }

    public String getFieldContent(int n) {
        if (n < 0 || n > field.size())
            return "";
        return field.get(n);
    }

    public static void main(String[] args) throws IOException {
        File file = new File("csv-test-data");
        FileInputStream fileInputStream = new FileInputStream(file);

        Csv csv = new Csv(fileInputStream, ",");
        while (csv.getline()) {
            System.out.println(csv.line);
            for (int i = 0; i < csv.getNfield(); i++)
                System.out.println("field[" + i + "] = '" + csv.getFieldContent(i) + "'");
        }
    }
}
