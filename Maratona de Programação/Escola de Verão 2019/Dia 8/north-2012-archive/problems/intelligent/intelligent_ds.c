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
/* Solution                                                       */
/*                                                                */
/* Author               Dmitry Shtukenberg                        */
/******************************************************************/

//////////////////////////////////////////////////////////////////////////////
// NEERC'2012, Northern subregion.                                          //
// Problem I: Intelligent design                                            //
// Test solution                                                            //
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <process.h>
#include <stdarg.h>

void error (char* msg, ...) {
    va_list args;
    va_start (args, msg);
    vfprintf (stderr, msg, args);
    va_end (args);
    exit (1);
}

typedef __int64 int64;

#define ASSERT(expr) do { if (!(expr)) error ("Assertion failed: " #expr); } while (0)

#define MAXLEN (1 << 22)
#define MAXVARS 12
typedef enum { undef, stop_program, var, not, and, or, impl, xor, cont_equal, equal, bracket } oper_enum;

struct oper {
    oper_enum op:8;
    int val:8;
};

char buf [MAXLEN+1];

struct oper sm [MAXLEN+1];
int sm_length = 0;

//////////////////////////////////////////////////////////////////////////////
// Converting expression into stack machine format

oper_enum sm_stack [MAXLEN+1];
int sm_stack_depth = 0;

int pop_sm_stack () {
    ASSERT (sm_stack_depth > 0);
    return sm_stack [--sm_stack_depth];
}

void append_sm (oper_enum op, int val) {
    ASSERT (sm_length < MAXLEN);
    sm [sm_length].op = op;
    sm [sm_length++].val = val;
}

void push_sm_stack (oper_enum op, int left_associative) {
    int last_op = undef;

    while (sm_stack_depth > 0 &&
        (left_associative ?
            sm_stack [sm_stack_depth-1] <= op :
            sm_stack [sm_stack_depth-1] < op))
    {
        last_op = pop_sm_stack ();
        append_sm (last_op, 127);
    }

    ASSERT (sm_stack_depth < MAXLEN);
    if ((last_op == equal || last_op == cont_equal) && op == equal)
        sm_stack [sm_stack_depth++] = cont_equal;
    else
        sm_stack [sm_stack_depth++] = op;
}

void push_bracket () {
    ASSERT (sm_stack_depth < MAXLEN);
    sm_stack [sm_stack_depth++] = bracket;
}

void pop_bracket () {
    int op;
    while ((op = pop_sm_stack()) != bracket) {
        append_sm (op, 127);
    }
}

void build_sm () {
    char* p = buf;

    sm_stack_depth = 0;
    while (1) {
        switch (*p) {
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
                append_sm (var, *p - 'A');
                break;
            case '0': case '1':
                append_sm (var, *p - '0' + 24);
                break;

            case '&': push_sm_stack (and, 1); break;
            case '|': push_sm_stack (or, 1); break;
            case '-': ASSERT (p[1] == '>'); p++; push_sm_stack (impl, 0); break;
            case '<': ASSERT (p[1] == '=' && p[2] == '>'); p += 2; push_sm_stack (equal, 1); break;
//          case '^': push_sm_stack (xor, 1); break;
            case '~': push_sm_stack (not, 0); break;

            case '(': push_bracket (); break;
            case ')': pop_bracket (); break;

            case '\0': goto end_loop;

            default: error ("Unexpected symbol '%c'", *p);
        }

        p++;
    }

end_loop:
    while (sm_stack_depth > 0) {
        oper_enum op = pop_sm_stack ();
        if (op == bracket) error ("Unpaired bracket");

        append_sm (op, 127);
    }
    append_sm (stop_program, 127);
}

//////////////////////////////////////////////////////////////////////////////
// Evaluation

#if 1
typedef int64 eint;
#define EVALSIZE 64
#else
typedef int eint;
#define EVALSIZE 32
#endif

eint eval_stack [MAXLEN+1];
eint eval_flags [MAXLEN+1];
eint eval_stack_depth = 0;

int value_table [1 << MAXVARS];

#if 0
void eval_push (eint v) {
    ASSERT (eval_stack_depth < MAXLEN);
    eval_stack [eval_stack_depth++] = v;
}

eint eval_pop () {
    ASSERT (eval_stack_depth > 0);
    return eval_stack [--eval_stack_depth];
}
#else

#define eval_push(v) {eval_stack[eval_stack_depth]=(v); eval_stack_depth++;}
#define eval_pop() (eval_stack[--eval_stack_depth])

#endif

eint eval_sm (eint* vars_bitscale) {
    int i = -1;
    eval_stack_depth = 0;

eval_loop:
    switch (sm [++i].op) {
        case var:
            eval_push (vars_bitscale [sm [i].val]);
            goto eval_loop;

        case not: {
            eint a = ~eval_pop (); eval_push (a);
            goto eval_loop;
        }

        case and: {
            eint a = eval_pop(); eint b = eval_pop(); eval_push (a & b);
            goto eval_loop;
        }

        case or: {
            eint a = eval_pop(); eint b = eval_pop(); eval_push (a | b);
            goto eval_loop;
        }

        case xor: {
            eint a = eval_pop(); eint b = eval_pop(); eval_push (a ^ b);
            goto eval_loop;
        }

        case impl: {
            eint a = eval_pop(); eint b = eval_pop(); eval_push (~b|a);
            goto eval_loop;
        }

        case equal: {
            eint a = eval_pop();
            eint b = eval_pop();
            eint res = ~(a ^ b);
            eval_flags [eval_stack_depth] = a & res;
            eval_push (res);
            goto eval_loop;
        }

        case cont_equal: {
            eint b = eval_pop();
            eint a = eval_pop();
            eint flags = eval_flags [eval_stack_depth];
            eint res = a & (~(flags ^ b));
            eval_flags [eval_stack_depth] = b & res;
            eval_push (res);
            goto eval_loop;
        } break;

        case stop_program: {
            if (eval_stack_depth != 1)
                error ("Stack depth must equal to 1");
            return eval_pop ();
        }

        default: error ("Impossible eval operation");
    }
}

void fill_value_table () {
    int i;
    for (i = 0; i < (1 << MAXVARS); i += EVALSIZE) {
        eint vars [32];
        eint res;
        int v,j;

        vars [24] = 0;
        vars [25] = ~((eint)0);

        for (v = 0; v < MAXVARS; v++) {
            vars [v] = 0;
            for (j = 0; j < EVALSIZE; j++) {
                eint bit = ((i+j) >> v) & 1;
                vars [v] |= bit << j;
            }
        }

        res = eval_sm (vars);

        for (j = 0; j < EVALSIZE; j++) {
            value_table [i+j] = (res >> j) & 1;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// Neural network designing

int used_vars;
int used_vars_num;

void find_used_vars () {
    int v = 0;

    used_vars = 0;
    used_vars_num = 0;
    for (v = 0; v < MAXVARS; v++) {
        int set;
        int varmask = 1 << v;
        for (set = 0; set < (1<<MAXVARS); set++) {
            if ((set & varmask) != 0) continue;

            if (value_table [set] != value_table [set | varmask]) {
                if ((used_vars & varmask) == 0) {
                    used_vars |= varmask;
                    used_vars_num ++;
                }
            }
        }
    }
}

int count_nonzero_lines () {
    int lines = 0;
    int v;

    if (used_vars == 0) return 0;

    for (v = 0; v < (1 << MAXVARS); v++) {
        if ((v & ~used_vars) != 0) continue;
        lines += value_table [v];
    }

    return lines;
}

void write_network (const char* fn) {
    int i;
    int nonzero = count_nonzero_lines ();
    int curr_nonzero = 0;
    FILE* f = fopen (fn, "wt");
    ASSERT (f != NULL);

    fprintf (f, "%d\n", nonzero + 1 + 1);

    for (i = 0; i < nonzero; i++) {
        int inp;

        ASSERT (curr_nonzero < 1<<MAXVARS);
        while (value_table [curr_nonzero] == 0 || (curr_nonzero & ~used_vars) != 0)
        {
            curr_nonzero++;
            ASSERT (curr_nonzero < 1<<MAXVARS);
        }

        fprintf (f, "%d", used_vars_num*2-1);

        for (inp = 0; inp < MAXVARS; inp++) {
            if (((used_vars >> inp) & 1) == 0) continue;
            fprintf (f, " %s%c", (curr_nonzero & (1 << inp)) ? "" : "~", inp+'A');
        }

        for (inp = 0; inp < used_vars_num-1; inp++) {
            fprintf (f, " 0");
        }

        fprintf (f, "\n");
        curr_nonzero++;
    }

    // nonzero+1 -- last (auxiliary) 1st layer node
    // 1 when the expression is tautology; otherwise 0
    fprintf (f, "1 %s0\n", (used_vars == 0) && (value_table[0] != 0) ? "~" : "");

    fprintf (f, "%d", nonzero*2+1); // 2nd layer node
    for (i = 1; i <= nonzero+1; i++) {
        fprintf (f, " %d", i);
    }

    for (i = 0; i < nonzero; i++) {
        fprintf (f, " ~0");
    }
    fprintf (f, "\n");

    fclose (f);
}

//////////////////////////////////////////////////////////////////////////////
// Main

void read_line (const char* fn) {
    FILE* inp = fopen (fn, "rt");
    int pos = 0;
    ASSERT (inp != NULL);

    while(1) {
        int c = fgetc (inp);
        int expect_eof = 0;
        switch (c) {
            case -1: buf [pos] = '\0'; return;

            case '\n': expect_eof = 1; break;

            default:
                if ((c < 'A' || c > 'L') && c != '&' && c != '-' &&
                    c != '>' && c != '|' && c != '=' && c != '~' &&
                    c != '0' && c != '1' && c != '(' && c != ')' && c != '<')
                    error ("Unexpected symbol '%c'", c);
                else if (pos > MAXLEN)
                    error ("Length > MAXLEN");
                else if (expect_eof)
                    error ("Symbols after EOF");
                else
                    buf [pos++] = c;
        }
    }

    fclose (inp);
}

int main () {
    int i;

    read_line ("intelligent.in");
    build_sm ();

#if 0
    printf ("Program:\n");
    for (i = 0; i < sm_length; i++) {
        printf ("%d.%d ", sm [i].op, sm[i].val);
    }
    printf ("\n");
#endif

    fill_value_table ();
    find_used_vars ();

#if 0
    printf ("Used vars: %x\n", used_vars);

    for (i = 0; i < 128; i++)
        printf ("%d",value_table [i]);

#endif

    write_network ("intelligent.out");

    return 0;
}

