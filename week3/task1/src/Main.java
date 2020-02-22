import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.Array;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;

public class Main {



    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        ArrayList<Integer> mArray = new ArrayList<>();
        ArrayList<Integer> nArray = new ArrayList<>();
        byte[] cArray = new byte[1600000000];
        int n = in.nextInt();
        int m = in.nextInt();


        for (int i = 0; i <= 1600000000; i++){
            cArray[i] = 0;
        }
        for (int i = 0; i < n; i++){
            nArray.add(in.nextInt());
        }

        for (int i = 0; i < m; i++){
            mArray.add(in.nextInt());
        }


        for (Integer elem1: nArray){
            for (Integer elem2: mArray){
                cArray[elem1*elem2]++;
            }
        }

        for (int i = 1; i <= 40000; i++){
            cArray[i] += cArray[i-1];
        }


        BigInteger sum = new BigInteger("0");

        for (Integer elem1: nArray){
            for (Integer elem2: mArray){
                if ((cArray[elem1*elem2])%10==1){
                    sum = sum.add(BigInteger.valueOf(elem1*elem2));
                }
                cArray[elem1*elem2]--;
            }
        }


        out.write(String.valueOf(sum));

        in.close();
        out.flush();
        out.close();

    }


}

