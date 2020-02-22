import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        ArrayList<Integer> array = new ArrayList<>();
        int n = in.nextInt();

        for (int i = 0; i < n; i++){
            array.add(in.nextInt());
        }
        out.write(String.valueOf(getInversionCount(array,0, n)));
        in.close();
        out.flush();
        out.close();

    }

    // sort array from l-index to r-1 index
    static BigInteger getInversionCount(ArrayList<Integer> array, int l, int r) {
        BigInteger inversionCount = new BigInteger("0");
        if (r - l == 1) return inversionCount;


        inversionCount = getInversionCount(array, l, (l + r + 1) / 2).add(getInversionCount(array, (l + r + 1) / 2, r));

        ArrayList<Integer> mergedArray = new ArrayList<>();

        int i = l;
        int j = (l + r + 1) / 2;

        while ((i < (l + r + 1) / 2) || (j < r)) {
            if ((j == r) || ((i < (l + r + 1) / 2) && (array.get(i) <= array.get(j)))) {
                mergedArray.add(array.get(i));
                i++;
            } else {
                inversionCount = inversionCount.add(BigInteger.valueOf((l+r+1)/2-i));
                mergedArray.add(array.get(j));
                j++;
            }
        }
        for (i = l; i < r; i++) {
            array.set(i, mergedArray.get(i - l));
        }
        return inversionCount;
    }
}