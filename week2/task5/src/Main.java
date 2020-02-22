import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {



    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));
        ArrayList<Elem> array = new ArrayList<>();
        int n = in.nextInt();
        int k = in.nextInt();


        for (int i = 0; i < n; i++){
            array.add(new Elem(in.nextInt(), i));
        }

        quickSort(array, 0, n);

        boolean isPossible = true;



        for (int i = 0; i < n; i++){
            int j = i;
            boolean isMultiple = false;
            while ((j < n) && (array.get(i).value == array.get(j).value)){
                if (Math.abs(array.get(j).startInd-i) % k == 0){
                    isMultiple = true;
                    int tmp = array.get(j).startInd;
                    array.get(j).startInd = array.get(i).startInd;
                    array.get(i).startInd = tmp;
                    break;
                }
                j++;
            }
            if (isMultiple != true){
                isPossible = false;
                break;
            }
        }

        out.write(isPossible ? "YES" : "NO");


        in.close();
        out.flush();
        out.close();

    }

    static void quickSort(ArrayList<Elem> array, int l, int r){
        if (r-l < 2) return;

        int i = l;
        int j = r-1;
        int pivot = array.get(((l+r)/2)).value;

        do{
            while (array.get(i).value < pivot){
                i++;
            }
            while (array.get(j).value > pivot){
                j--;
            }
            if (i <= j){
                if (array.get(i).value != array.get(j).value) {
                    Elem tmp = array.get(i);
                    array.set(i, array.get(j));
                    array.set(j, tmp);
                }
                i++;
                j--;
            }
        } while (i <= j);
        quickSort(array, l,j+1);
        quickSort(array, i,r);

    }

}


class Elem{
    int value;
    int startInd;

    public Elem(int value, int startInd) {
        this.value = value;
        this.startInd = startInd;
    }
}