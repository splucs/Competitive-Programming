/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem I. Intelligent Design                                  */
/*                                                                */
/* Original idea        Jury                                      */
/* Problem statement    Dmitry Shtukenberg                        */
/* Test set             Dmitry Shtukenberg                        */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Dmitry Shtukenberg                        */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    final int maxStringLen = 300000;
    final int maxVars = 12;
    final String [] ops = new String[] {"<=>", "->", "|", "&"};
    Random random = new Random(20121020);

    int testNo = 1;

    char randomVar (boolean with_const) {
        int v = random.nextInt (with_const ? maxVars+2 : maxVars);
        if (v >= maxVars) {
            return (char) (v - maxVars + (int)'0');
        }
        else {
            return (char) (v + (int)'A');
        }
    }

    int randomDiffVarScale (int scale) {
        int s;
        do {
            s = random.nextInt (1 << maxVars);
        } while (s == scale);
        return s;
    }

    String genLongSimple (String op, int n) {
        StringBuffer res = new StringBuffer (n);
        int var = 0;
        for (int i = 0;;) {
            i += op.length () + 1;
            if (i >= n-1) break;

            res.append((char) (var+(int)'A'));
            res.append(op);
            var = (var+1) % maxVars;
        }
        res.append((char) (var+(int)'A'));
        return res.toString();
    }

    String genLongNested (int n) {
        final int brackets = (n-3)/2;
        StringBuffer res = new StringBuffer (n);
        for (int i = 0; i < brackets; i++)
            res.append ("(");
        res.append ("E&F");
        for (int i = 0; i < brackets; i++)
            res.append (")");
        return res.toString();
    }

    String genLongHardExpandable (int n, boolean random_ops) {
        StringBuffer res = new StringBuffer (n);

        do {
            int len = res.length();

            if (len > 0) res.append (random_ops ? ops [random.nextInt (ops.length)] : "&");

            res.append ("(");
            for (int v = 0; v < maxVars/2; v++) {
                if (v != 0) res.append (random_ops ? ops [random.nextInt (ops.length)] : "|");

                if (random.nextBoolean()) res.append ('~');
                res.append (randomVar (false));
                res.append (random_ops ? ops [random.nextInt (ops.length)] : "&");
                if (random.nextBoolean()) res.append ('~');
                res.append (randomVar (false));
            }
            res.append (")");

            if (res.length () > n) {
                res.delete(len, res.length ());
                return res.toString ();
            }
        } while (true);
    }

    String genLongHardExpandable3 (int n, boolean random_ops) {
        int inner = (int) Math.sqrt (n);
        if (inner < maxVars*6+2) inner = maxVars*6+2;
        StringBuffer res = new StringBuffer (n);

        for (int i = 0; i < n/inner; i++) {
            if (i != 0) res.append (random_ops ? ops [random.nextInt (ops.length)] : "|");
            res.append ("(");
            res.append (genLongHardExpandable (inner-2, random_ops));
            res.append (")");
        }

        return res.toString ();
    }

    int tryGenRandomExpr (StringBuffer res, int n, int zero_at, int one_at) {
        int beg = res.length ();

        if (n <= 1)
            res.append ("????");

        else if (n <= 10) {
            int[] vars = new int [maxVars];

            for (int i = 0; i < maxVars; i++) {
                int one = ((one_at >> i) & 1);
                int zero = ((zero_at >> i) & 1);

                vars [i] = one-zero;
            }

            int variable = 0;
            do { variable = random.nextInt (maxVars); }
            while (vars [variable] == 0);

            if (vars [variable] > 0) {
                res.append ((char)(variable + (int)'A'));
            }
            else {
                res.append ("~");
                res.append ((char)(variable + (int)'A'));
            }
        }
        else
        {
            if (random.nextInt (4) < 1) {
                res.append ("~");
                n--;

                int t = zero_at;
                zero_at = one_at;
                one_at = t;
            }
            res.append ("("); n -= 2;

            int op_no = random.nextInt (4);
            String op = ops[op_no];

//            if (n - op.length() >= 4) {
                n -= op.length ();
                int random_vector;
                int left = random.nextInt (n-3)+2;

                switch (op_no) {
                    case 1:
                        if (random.nextBoolean ()) {
                            n -= tryGenRandomExpr (res, left, one_at, zero_at);
                            res.append (op);
                            tryGenRandomExpr (res, n, zero_at, randomDiffVarScale (zero_at));
                        }
                        else {
                            n -= tryGenRandomExpr (res, left, randomDiffVarScale (zero_at), zero_at);
                            res.append (op);
                            tryGenRandomExpr (res, n, zero_at, one_at);
                        }
                        break;

                    case 2:
                        if (random.nextBoolean ()) {
                            n -= tryGenRandomExpr (res, left, zero_at, randomDiffVarScale (zero_at));
                            res.append (op);
                            tryGenRandomExpr (res, n, zero_at, one_at);
                        }
                        else {
                            n -= tryGenRandomExpr (res, left, zero_at, one_at);
                            res.append (op);
                            tryGenRandomExpr (res, n, zero_at, randomDiffVarScale (zero_at));
                        }
                        break;

                    case 3:
                        if (random.nextBoolean ()) {
                            n -= tryGenRandomExpr (res, left, randomDiffVarScale (one_at), one_at);
                            res.append (op);
                            tryGenRandomExpr (res, n, zero_at, one_at);
                        }
                        else {
                            n -= tryGenRandomExpr (res, left, zero_at, one_at);
                            res.append (op);
                            tryGenRandomExpr (res, n, randomDiffVarScale (one_at), one_at);
                        }
                        break;

                    case 0: {
                        boolean is_zero = random.nextBoolean ();
                        if (random.nextBoolean ()) {
                            n -= tryGenRandomExpr (res, n-1, is_zero ? zero_at : one_at, is_zero ? one_at : zero_at);
                            res.append (op);
                            res.append (is_zero ? "0" : "1");
                        }
                        else {
                            res.append (is_zero ? "0" : "1");
                            res.append (op);
                            tryGenRandomExpr (res, n-1, is_zero ? zero_at : one_at, is_zero ? one_at : zero_at);
                        }
                    } break;
//                }
            }
            res.append (")");
        }

        return res.length () - beg;
    }

    String genLongRandom (int n) {
        StringBuffer res = new StringBuffer (n);
        int v = random.nextInt (1 << maxVars);
        tryGenRandomExpr (res, n, v, randomDiffVarScale (v));
        return res.toString ();
    }

    public void printTest(String line) {
        PrintWriter out = null;
        new File("tests").mkdir();
        try {
            out = new PrintWriter("tests/" + testNo / 10 + testNo % 10);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        out.println(line);

        out.close();
        testNo++;
    }

    public void run() throws IOException {
        final Scanner in = new Scanner(new File("tests.lst"));
        while (in.hasNextLine()) {
            String s = in.nextLine();
            if (s.length () > 0 && s.charAt(0) != '/')
                printTest(s);
        }

        printTest (genLongSimple ("&", 1024));
        printTest (genLongSimple ("|", 1024));
        printTest (genLongSimple ("<=>", 1024));
        printTest (genLongSimple ("->", 1024));
        printTest (genLongNested (1024));
        printTest (genLongHardExpandable (1024, false));
        printTest (genLongHardExpandable (1024, true));
        printTest (genLongHardExpandable3 (1024, false));
        printTest (genLongHardExpandable3 (1024, true));
        printTest (genLongRandom (1024));
        printTest (genLongRandom (1024));

        printTest (genLongSimple ("&", maxStringLen));
        printTest (genLongSimple ("|", maxStringLen));
        printTest (genLongSimple ("<=>", maxStringLen));
        printTest (genLongSimple ("->", maxStringLen));
        printTest (genLongNested (maxStringLen));
        printTest (genLongHardExpandable (maxStringLen, false));
        printTest (genLongHardExpandable (maxStringLen, true));
        printTest (genLongHardExpandable3 (maxStringLen, false));
        printTest (genLongHardExpandable3 (maxStringLen, true));
        printTest (genLongRandom (maxStringLen));
        printTest (genLongRandom (maxStringLen));
    }

    public static void main(String[] args) throws IOException {
        new Tests().run();
    }
}

