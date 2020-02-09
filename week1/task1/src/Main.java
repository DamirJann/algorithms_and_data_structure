import java.io.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        int a  = in.nextInt();
        int b  = in.nextInt();
        in.close();

        FileWriter out = new FileWriter(new File("output.txt"));
        out.write(String.valueOf(a+b));
        out.flush();
        out.close();

    }
}
