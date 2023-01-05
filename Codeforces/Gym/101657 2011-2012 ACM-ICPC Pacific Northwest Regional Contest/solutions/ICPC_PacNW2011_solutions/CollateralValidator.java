// --------------------------------------------------------------------------
// Collateral Cleanup  [validator program for PC^2]
// 2011 Pacific Northwest Regional Programming Contest
//
// NOTE:    From the PC^2 External Validator instructions, run
//          {:validator} {:infile} {:outfile} {:ansfile} {:resfile} 
// ie.      java Validator collateral.in <run_output> collateral.out <result_file>
//
// Author:  Sonny Chan
// Date:    September 30, 2011
// --------------------------------------------------------------------------

import java.io.File;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.Vector;
import java.util.HashMap;
import java.util.Iterator;
import java.lang.Math;
import java.awt.geom.*;

public class CollateralValidator
{
    // what to return as output
    static final String ACCEPTED  = "yes";
    static final String INCORRECT = "Wrong Output";
    static final String INCOMPLETE= "Incomplete Output";
    static final String EXCESSIVE = "Excessive Output";
    static final String UNKNOWN   = "undetermined";
    
    // subclass of Line2D that implements hashCode and equals
    static class Line extends Line2D.Double
    {
        Line(Point2D p1, Point2D p2) {
            setLine(p1, p2);
        }
        public int hashCode() {
            return (int)((long)(getX1() + getY1() + getX2() + getY2()));
        }
        public boolean equals(Object other) {
            if (this == other) return true;
            if (!(other instanceof Line)) return false;
            Line l = (Line) other;
            if (getX1() != l.getX1()) return false;
            if (getY1() != l.getY1()) return false;
            if (getX2() != l.getX2()) return false;
            if (getY2() != l.getY2()) return false;
            return true;
        }
        public double deltaX() {
            return getX2() - getX1();
        }
    }
    
    public static void main(String[] args) throws Exception
    {
        // check arguments
        if (args.length < 4) {
            System.out.println("usage: java Validator collateral.in <run_output> collateral.out <result_file>");
            System.exit(1);
        }

        // stuff to report later
        String outcome  = ACCEPTED;
        String message  = "Everything OK";
        PrintStream res = new PrintStream(new File(args[3]));

        try
        {
            // PC^2 file argument order is judge input, program output,
            // judge answer file, and judgement result file
            Scanner infile  = new Scanner(new File(args[0]));
            Scanner outfile = new Scanner(new File(args[1]));
            
            int walls = infile.nextInt();
            for (int w = 0; w < walls; ++w)
            {
                //System.out.println("Reading test case " + (w+1));
            
                // hash to find coincident edges
                HashMap<Line2D, Integer> edges = new HashMap<Line2D, Integer>(4*walls);
            
                // adjacency lists
                int triangles = infile.nextInt();
                Vector<Vector<Integer>> adjacency = new Vector<Vector<Integer>>(triangles);
                //System.out.println("  Test case has " + triangles + " triangles");
                
                // read the triangles from the input file
                for (int t = 0; t < triangles; ++t)
                {
                    adjacency.add(new Vector<Integer>());
                
                    Point2D[] v = new Point2D[3];
                    for (int i = 0; i < 3; ++i) {
                        int x = infile.nextInt();
                        int y = infile.nextInt();
                        v[i] = new Point2D.Double(x, y);
                    }
                    
                    for (int i = 0; i < 3; ++i) {
                        Validator.Line e = new Validator.Line(v[i], v[(i+1)%3]);
                        Validator.Line f = new Validator.Line(v[(i+1)%3], v[i]);
                        Integer u = edges.get(f);
                        if (u != null) {
                            //System.out.println("Triangle " + t + " adjacent to " + u);
                            if (e.deltaX() > 0)         adjacency.get(t).add(u);
                            else if (e.deltaX() < 0)    adjacency.get(u).add(t);
                        }
                        else edges.put(e, t);
                    }
                }

                // array that holds indices to each triangle's position in the output
                int[] position = new int[triangles];
                for (int t = 0; t < triangles; ++t)
                    position[t] = -1;
                
                // read the ordering from the program's output
                try {
                    String line = outfile.nextLine();
                    Scanner in = new Scanner(line);
                    Vector<Integer> order = new Vector<Integer>(triangles);
                    for (int t = 0; t <= triangles && in.hasNextInt(); ++t)
                        order.add(in.nextInt());
                    
                    // check for correct number of integers on this line
                    if (order.size() < triangles) {
                        outcome = INCOMPLETE;
                        message = "Failed test case " + (w+1) +
                                  ": expecting " + triangles + " integers, found " + order.size();
                        break;
                    }
                    else if (order.size() > triangles) {
                        outcome = EXCESSIVE;
                        message = "Failed test case " + (w+1) +
                        ": expecting " + triangles + " integers, output contains more";
                        break;
                    }
                    
                    // index each triangle's position while checking bounds and uniqueness
                    boolean failed = false;
                    for (int p = 0; p < triangles; ++p) {
                        int t = order.get(p) - 1;
                        if (t < 0 || t >= triangles) {
                            outcome = INCORRECT;
                            message = "Failed test case " + (w+1) +
                                      ": " + (t+1) + " is not a valid triangle";
                            failed = true;
                            break;
                        }
                        else if (position[t] != -1) {
                            outcome = INCORRECT;
                            message = "Failed test case " + (w+1) +
                                      ": triangle " + (t+1) + " appears more than once";
                            failed = true;
                            break;
                        }
                        position[t] = p;
                    }
                    if (failed) break;  // catch failures inside above loop
                    
                }
                catch (Exception e) {
                    outcome = INCOMPLETE;
                    message = "Insufficient output at test case " + (w+1);
                    break;
                }
                                
                // iterate through and check each constraint on the order
                boolean failed = false;
                for (int i = 0; i < adjacency.size() && !failed; ++i)
                {
                    Vector<Integer> a = adjacency.get(i);
                    Iterator<Integer> j = a.iterator();
                    while (j.hasNext()) {
                        int t = j.next();
                        //System.out.println("    Testing " + i + " after " + t);
                        if (position[i] < position[t]) {
                            outcome = INCORRECT;
                            message = "Failed test case " + (w+1) +
                                      ": triangle " + (i+1) + " cannot appear before " + (t+1);
                            failed = true;
                            break;
                        }
                    }
                }
                if (failed) break;
            }
            
            // check for excessive output
            try {
                if (outcome == ACCEPTED) {
                    String line = outfile.nextLine();
                    if (line.length() != 0) {
                        outcome = EXCESSIVE;
                        message = "Run result contains excessive output";
                    }
                }
            }
            catch (Exception e) {}

        }
        catch (Exception e)
        {
            outcome = UNKNOWN;
            message = e.toString();
        }
        
        if (res != null)
        {
            // write the result to the result file
            res.println("<?xml version=\"1.0\"?>");
            res.println("<result outcome=\"" + outcome +
                        "\" security=\"" + args[3] +
                        "\"> " + message + " </result>");
            res.close();
        }
    }
}
