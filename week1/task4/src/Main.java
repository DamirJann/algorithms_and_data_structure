import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        double[] m = new double[1000];
        int[] no = new int[1000];
        int n = in.nextInt();

        for (int i = 0; i < n; i++){
            m[i] = Double.valueOf(in.next());
            no[i] = i;
        }

        for (int i = 0; i < n; i++){
            int j = i;
            while ((j > 0) && (m[j-1] > m[j])){
                double tmp = m[j];
                m[j] = m[j-1];
                m[j-1] = tmp;

                int tmp1 = no[j];
                no[j] = no[j-1];
                no[j-1] = tmp1;
                j--;
            }
        }

        out.write((no[0]+1) + " " + (no[(n-1)/2]+1) + " " + (no[n-1]+1));


        in.close();
        out.flush();
        out.close();

    }
}
