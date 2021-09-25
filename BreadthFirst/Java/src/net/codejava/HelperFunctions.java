package net.codejava;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class HelperFunctions {

    private static final int ROWS = 15;
    private static final int COLS = 19;
    static int count = 0;

    public static char[][] readTxtFile() throws IOException {

        //File path has to be the full path for the map file
        //eg. C:\Users\darpa\OneDrive\Desktop\Uni\Part 3\Semester 2\COMPSYS 301\Path finding algorithm\Breadth First\src\net\codejava\map.txt
        File file = new File("C:\\Users\\darpa\\OneDrive\\Desktop\\Uni\\Part 3\\Semester 2\\COMPSYS 301\\Path finding algorithm\\Breadth First\\src\\net\\codejava\\map.txt");

        char[][] map = new char[ROWS][COLS];
        BufferedReader br = new BufferedReader(new FileReader(file));

        String st;
        while ((st = br.readLine()) != null){
            char[] nums = st.toCharArray();
            map[count] = nums;
            count++;
        }
        return map;
    }


}

