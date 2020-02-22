import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    static int counter = 0;


    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        FileWriter out = new FileWriter(new File("output.txt"));

        int n = in.nextInt();


        for (Integer elem: createTest(n)){
            out.write(String.valueOf(elem) + " ");
        }

        in.close();
        out.flush();
        out.close();

    }

    static ArrayList<Integer> createTest(int n){
        ArrayList<Integer> array = new ArrayList<>();
        array.add(1);
        if (n > 1) {
            array.add(2);
        }
        for (int i = 0; i < n-2; i++){
            int tmp = array.get(array.size()/2);
            array.set(array.size()/2, i+3);
            array.add(tmp);
        }
        return array;
    }
}