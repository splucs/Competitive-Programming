/* ICPC PacNW 2011 Contest
	Gimme problem -- designed for all teams to solve
*/
import java.util.*;//Scanner

public class GoodOrBad
{

	public static void main(String [] args)
	{
		Scanner kb = new Scanner(System.in);
		int nameCount, bCount, gCount;
		String name;
		char ch;
		
		nameCount = kb.nextInt();
		kb.nextLine(); //flush leftover \n
		
		for (int i = 0; i < nameCount; i++)
		{
			bCount = 0;
			gCount = 0;
			name = kb.nextLine();
			for (int j = 0; j < name.length(); j++)
			{
				ch = name.charAt(j);
				if (ch == 'b' || ch == 'B')
					bCount++;
				else if (ch == 'g' || ch == 'G')
					gCount++;
							
			}//end j loop
			System.out.print(name + " is ");
			if (gCount > bCount)
				System.out.println("GOOD");
			else if (bCount > gCount)
				System.out.println("A BADDY");
			else
				System.out.println("NEUTRAL");
		
		}//end i loop
		
	}//end main

}//end class
