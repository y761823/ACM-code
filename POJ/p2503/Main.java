import java.util.*;
import java.lang.*;
import java.math.*;

public class Main {
    static Map<String, String> mymap = new HashMap<String, String>();
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        String Line = cin.nextLine();
        while(Line.length() > 0) {
            String s[] = Line.split(" ");
            mymap.put(s[1], s[0]);
            Line = cin.nextLine();
        }
        while(cin.hasNext()) {
            String s = cin.next();
            String ans = mymap.get(s);
            System.out.println(ans == null ? "eh" : ans);
        }
    }
}
