public class Base2toBase10 {
	
	public static void main(String[] args) 
	{
		String input = "101010";
		System.out.println("The binary number " + input + " is " + BinaryToNumber(input) + " in base 10.");
	}
	
	public static int BinaryToNumber(String num) 
	{
		int res = 0;
		for (int i = 0, pot = 1; i < num.length(); i++)
			res |= ((num.charAt(i) == '1') ? (pot << (num.length() - i - 1)) : 0);
	
		return res;
	}
}
