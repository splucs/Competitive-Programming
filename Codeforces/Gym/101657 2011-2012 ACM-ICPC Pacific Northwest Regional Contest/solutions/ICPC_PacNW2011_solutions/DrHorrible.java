/*
Solution for DrHorrible from ICPC-PACNW-2011 problem set
Author: Kyle Parker-Robinson
Date: 9/12/11
*/

import java.util.*;
import java.io.*;

public class DrHorrible {
	int width, height;
	Map<Integer, Map<String, String>> squares;
	
	public DrHorrible() throws Exception
	{
		Scanner in = new Scanner(System.in);

		int boardCount = 0;
		
		height = in.nextInt();
		width = in.nextInt();
		in.nextLine();
		while(height != 0)
		{
			boardCount++;
			System.out.println("Board " + boardCount + ":");
			
			this.squares = new HashMap<Integer, Map<String, String>>(width * height);
			String line = in.nextLine();
			while(!line.equals("0"))
			{
				String[] tokens = line.split(" ");
				int num = Integer.parseInt(tokens[0]);
				
				Map<String, String> square = new HashMap<String, String>(num);
				for(int i=1; i<tokens.length; i++)
				{
					String a = Character.toString(tokens[i].charAt(0));
					String b = Character.toString(tokens[i].charAt(1));
					square.put(a, b);
					square.put(b, a);
				}
				
				this.squares.put(num, square);
				line = in.nextLine();
			}
			
			line = in.nextLine();
			String[] tokens = line.split(" ");
			for(int i=0; i<tokens.length; i++)
			{
				String token = tokens[i];
				int startSquare = Integer.parseInt(token.substring(0, token.length()-1));
				String startPoint = Character.toString(token.charAt(token.length()-1));
				System.out.print(startSquare + startPoint + " is connected to ");
				Process(startSquare, startPoint);
			}
			
			in.nextLine();
			height = in.nextInt();
			width = in.nextInt();
			if(height != 0)
			{
				System.out.println();
				in.nextLine();
			}
		}
	}
	
	private void Process(int curSquare, String point)
	{
		String endPoint = squares.get(curSquare).get(point);
		
		int nextSquare = 0;
		String nextPoint = null;
		boolean solved = false;
		switch(endPoint.charAt(0))
		{
			case 'A':
				if(curSquare <= width)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare-width;
					nextPoint = "F";	
				}
				break;
			case 'B':
				if(curSquare <= width)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare-width;
					nextPoint = "E";	
				}
				break;
			case 'C':
				if(curSquare % width == 0)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare+1;
					nextPoint = "H";	
				}
				break;
			case 'D':
				if(curSquare % width == 0)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare+1;
					nextPoint = "G";	
				}
				break;
			case 'E':
				if(curSquare > (width * height) - width)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare+width;
					nextPoint = "B";	
				}
				break;
			case 'F':
				if(curSquare > (width * height) - width)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare+width;
					nextPoint = "A";	
				}
				break;
			case 'G':
				if((curSquare - 1) % width == 0)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare-1;
					nextPoint = "D";	
				}
				break;
			case 'H':
				if((curSquare - 1) % width == 0)
				{
					solved = true;
				}
				else
				{
					nextSquare = curSquare-1;
					nextPoint = "C";	
				}
				break;
		}
		
		if(solved)
		{
			System.out.println(curSquare + endPoint);
		}
		else
		{
			Process(nextSquare, nextPoint);
		}
	}
	
	public static void main(String[] args) throws Exception
	{
		new DrHorrible();
	}
}
