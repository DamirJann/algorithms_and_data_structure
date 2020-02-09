import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        int[] array = new int[1000];
        int n = in.nextInt();

        for (int i = 0; i < n; i++){
            array[i] = in.nextInt();
        }

        for (int i = 0; i < n; i++){
            int j = i;
            while ((j > 0) && (array[j-1] > array[j])){
                int tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
                j--;
            }
            out.write((j+1) + " ");
        }
        out.write("\n");

        for (int i = 0; i < n; i++){
            out.write(array[i] + " ");
        }


        in.close();
        out.flush();
        out.close();

    }
}
