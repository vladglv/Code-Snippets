import java.util.Scanner;

public class Base2toBase10 {
	
	public static void main(String[] args) {

        String input = "101010";
		System.out.println("The binary number " + input + " is " + BinaryToNumber(input) + " in base 10.");

	}
	
	public static int BinaryToNumber(String num) {

		int res = 0;
		for (int i = num.length() - 1, pot = 1; i >=0; i--)
			res |= ((num.charAt(i) == '1') ? (pot << i) : 0);
	
		return res;
	}
}