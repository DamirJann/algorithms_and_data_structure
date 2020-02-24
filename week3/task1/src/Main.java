import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {



    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        ArrayList<Integer> mArray = new ArrayList<>();
        ArrayList<Integer> nArray = new ArrayList<>();
        ArrayList<Integer> array = new ArrayList<>();

        int n = in.nextInt();
        int m = in.nextInt();

        for (int i = 0; i < n; i++){
            nArray.add(in.nextInt());
        }
        Collections.sort(nArray);

        for (int i = 0; i < m; i++){
            mArray.add(in.nextInt());
        }
        Collections.sort(mArray);





        for (Integer elem1: nArray){
            ArrayList<Integer> rightArray = new ArrayList<>();
            for (Integer elem2: mArray){
                rightArray.add(elem1*elem2);
            }
            array = merge(array, rightArray);
        }


        BigInteger sum = new BigInteger("0");

        for (int i = 0; i < array.size(); i+=10){
            sum = sum.add(BigInteger.valueOf(array.get(i)));
        }
        out.write(String.valueOf(sum));


        in.close();
        out.flush();
        out.close();

    }

    static ArrayList<Integer> merge(ArrayList<Integer> leftArray, ArrayList<Integer> rightArray) throws IOException {

        int i = 0;
        int j = 0;

        ArrayList<Integer> array = new ArrayList<>();

        while ((i < leftArray.size()) || (j < rightArray.size())) {
            if ((j == rightArray.size()) || ((i < leftArray.size()) && (leftArray.get(i) <= rightArray.get(j)))) {
                array.add(leftArray.get(i));
                i++;
            } else {
                array.add(rightArray.get(j));
                j++;
            }
        }
        return array;
    }
}

