import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static int[] array = new int[40000000];
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));
        int n = in.nextInt();
        int k1 = in.nextInt();
        int k2 = in.nextInt();
        int A = in.nextInt();
        int B = in.nextInt();
        int C = in.nextInt();
        int a1 = in.nextInt();
        int a2 = in.nextInt();

        array[0] = a1;
        array[1] = a2;

        for (int i = 2; i < n; i++){
            array[i] = (A* array[i-2]+B* array[i-1]+C);
        }

        quickSort(0, n, k1, k2);

        for (int i = k1-1; i < k2; i++){
            out.write(String.valueOf(array[i]) + " ");
        }

        in.close();
        out.flush();
        out.close();

    }

    static void quickSort(int l, int r, int k1, int k2){
        if ((r-l < 2) || (r < k1) || (k2 < l)) return;

        int i = l;
        int j = r-1;
        int pivot = array[((l+r)/2)];

        do{
            while (array[i] < pivot){
                i++;
            }
            while (array[j] > pivot){
                j--;
            }
            if (i <= j){
                int tmp = array[i];
                array[i] = array[j];
                array[j] =  tmp;
                i++;
                j--;
            }
        } while (i <= j);
        quickSort(l,j+1, k1, k2);
        quickSort(i,r, k1, k2);

    }


}