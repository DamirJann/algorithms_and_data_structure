import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        int[] m = new int[1000];
        int n = in.nextInt();

        for (int i = 0; i < n; i++){
            m[i] = in.nextInt();
        }

        for (int i = 1; i < n; i++){
            int j = i;
            while ((j > 0) && (m[j-1] > m[j])){
                int tmp = m[j-1];
                m[j-1] = m[j];
                m[j] = tmp;
                out.write("Swap elements at indices " + i + " and " + j + "\n");
                j--;
            }
        }
        out.write("No more swaps needed\n");

        for (int i = 0; i < n; i++){
            out.write(m[i] + " ");
        }

        in.close();
        out.flush();
        out.close();

    }
}
