import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File("input.txt"));
        long a  = in.nextInt();
        long b  = in.nextInt();
        in.close();

        FileWriter out = new FileWriter(new File("output.txt"));
        out.write(String.valueOf(a+b*b));
        out.flush();
        out.close();

    }
}
