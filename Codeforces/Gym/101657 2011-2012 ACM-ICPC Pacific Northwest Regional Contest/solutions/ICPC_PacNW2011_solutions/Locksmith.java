import java.awt.geom.AffineTransform;
import java.awt.geom.Area;
import java.awt.geom.Path2D;
import java.io.File;
import java.util.HashSet;
import java.util.Scanner;

public class Locksmith {
    static final long SENTINEL = (1 << 12) - 1;
    static final Area[] pieces = new Area[4];
    static final int[][] v = new int[4][32];
    static final int[][] h = new int[4][32];
    static final int[] c = new int[4];
    
    public static void main(String[] args) throws Exception {
        Scanner s = new Scanner(System.in);

        while (true) {
            int N = s.nextInt();
            if (N == 0) break;

            for (int i = 1; i <= N; i++) {
                c[i] = s.nextInt();
                int cv = 0, ch = 0;
                Path2D.Double path = new Path2D.Double();
                int sx = s.nextInt(), sy = s.nextInt();
                path.moveTo(sx, sy);
                int lx = sx, ly = sy;
                for (int j = 1; j < c[i]; j++) {
                    int cx = s.nextInt(), cy = s.nextInt();
                    if (cx == lx) v[i][cv++] = cx;
                    if (cy == ly) h[i][ch++] = cy;
                    lx = cx; ly = cy;
                    path.lineTo(cx, cy);
                }
                if (lx == sx) v[i][cv++] = sx;
                if (ly == sy) h[i][ch++] = sy;
                path.closePath();
                pieces[i] = new Area(path);
            }

            System.out.println(solve(N));
        }
    }
    
    static HashSet<Long> visited = new HashSet<Long>();
    static long[] queue = new long[1 << 24];
    static int start = 0;
    static int end = 0;
    static void enqueue(long num) {
        if (visited.contains(num)) return;
        visited.add(num);
        queue[end++] = num;
        if (end == queue.length) end = 0;
    }
    static long dequeue() {
        long answer = queue[start++];
        if (start == queue.length) start = 0;
        return answer;
    }
    static boolean queueIsEmpty() {return start == end;}
    static void clearQueue() {start = end = 0; visited.clear();}
    
    static final int LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3;
    static int getDelta(int a, int b, int cur, int shift, int dir) {
        int ans = (int) SENTINEL;
        for (int i = 0; i < c[a] / 2; i++) {
            for (int j = 0; j < c[b] / 2; j++) {
                int next = (dir == LEFT || dir == RIGHT ? shift + v[a][i] - v[b][j] : shift + h[a][i] - h[b][j]);
                if ((dir == LEFT || dir == DOWN) && next < cur) ans = Math.min(ans, cur - next);
                if ((dir == RIGHT || dir == UP) && next > cur) ans = Math.min(ans, next - cur);
            }
        }
        return ans;
    }

    static int solve(int N) {
        if (N == 1) return 1;
        
        long start = align(N);
        clearQueue();
        enqueue(start);
        
        int left, right, down, up;
        while (!queueIsEmpty()) {
            long cur = dequeue();
            int v2shift = (int) ((cur & (SENTINEL << 36)) >> 36) - 2048;
            int v3shift = (int) ((cur & (SENTINEL << 24)) >> 24) - 2048;
            
            int h2shift = (int) ((cur & (SENTINEL << 12)) >> 12) - 2048;
            int h3shift = (int) ((cur & (SENTINEL << 0)) >> 0) - 2048;
            
            if (N == 2) {
                if (isSeparated(1, 2, v2shift, true)) return 2;
                if (isSeparated(1, 2, h2shift, false)) return 2;
                
                left = getDelta(1, 2, v2shift, 0, LEFT);
                right = getDelta(1, 2, v2shift, 0, RIGHT);
                if (left < SENTINEL && isDisjoint(1, 2, v2shift - left, h2shift)) enqueue(getState(v2shift - left, 0, h2shift, 0));
                if (right < SENTINEL && isDisjoint(1, 2, v2shift + right, h2shift)) enqueue(getState(v2shift + right, 0, h2shift, 0));
                
                down = getDelta(1, 2, h2shift, 0, DOWN);
                up = getDelta(1, 2, h2shift, 0, UP);
                if (down < SENTINEL && isDisjoint(1, 2, v2shift, h2shift - down)) enqueue(getState(v2shift, 0, h2shift - down, 0));
                if (up < SENTINEL && isDisjoint(1, 2, v2shift, h2shift + up)) enqueue(getState(v2shift, 0, h2shift + up, 0));
            } else { // N == 3
                if (isSeparated(1, 2, v2shift, true) && isSeparated(1, 3, v3shift, true)) {
                    swap(1, 3);
                    return 1 + solve(2);
                } else if (isSeparated(1, 2, v2shift, true) && isSeparated(2, 3, v3shift - v2shift, true)) {
                    swap(2, 3);
                    return 1 + solve(2);
                } else if (isSeparated(1, 3, v3shift, true) && isSeparated(2, 3, v3shift - v2shift, true)) {
                    return 1 + solve(2);
                }
                
                if (isSeparated(1, 2, h2shift, false) && isSeparated(1, 3, h3shift, false)) {
                    swap(1, 3);
                    return 1 + solve(2);
                } else if (isSeparated(1, 2, h2shift, false) && isSeparated(2, 3, h3shift - h2shift, false)) {
                    swap(2, 3);
                    return 1 + solve(2);
                } else if (isSeparated(1, 3, h3shift, false) && isSeparated(2, 3, h3shift - h2shift, false)) {
                    return 1 + solve(2);
                }
                
                // move piece 2
                left = Math.min(getDelta(1, 2, v2shift, 0, LEFT), getDelta(3, 2, v2shift, v3shift, LEFT));
                right = Math.min(getDelta(1, 2, v2shift, 0, RIGHT), getDelta(3, 2, v2shift, v3shift, RIGHT));
                if (isAligned(1, 3, v3shift, true)) {
                    if (left < SENTINEL && isDisjoint(1, 2, v2shift - left, h2shift) && isDisjoint(3, 2, v2shift - left - v3shift, h2shift - h3shift)) enqueue(getState(v2shift - left, v3shift, h2shift, h3shift));
                    if (right < SENTINEL && isDisjoint(1, 2, v2shift + right, h2shift) && isDisjoint(3, 2, v2shift + right - v3shift, h2shift - h3shift)) enqueue(getState(v2shift + right, v3shift, h2shift, h3shift));
                }
                
                down = Math.min(getDelta(1, 2, h2shift, 0, DOWN), getDelta(3, 2, h2shift, h3shift, DOWN));
                up = Math.min(getDelta(1, 2, h2shift, 0, UP), getDelta(3, 2, h2shift, h3shift, UP));
                if (isAligned(1, 3, h3shift, false)) {
                    if (down < SENTINEL && isDisjoint(1, 2, v2shift, h2shift - down) && isDisjoint(3, 2, v2shift - v3shift, h2shift - down - h3shift)) enqueue(getState(v2shift, v3shift, h2shift - down, h3shift));
                    if (up < SENTINEL && isDisjoint(1, 2, v2shift, h2shift + up) && isDisjoint(3, 2, v2shift - v3shift, h2shift + up - h3shift)) enqueue(getState(v2shift, v3shift, h2shift + up, h3shift));
                }

                // move piece 3
                left = Math.min(getDelta(1, 3, v3shift, 0, LEFT), getDelta(2, 3, v3shift, v2shift, LEFT));
                right = Math.min(getDelta(1, 3, v3shift, 0, RIGHT), getDelta(2, 3, v3shift, v2shift, RIGHT));
                if (isAligned(1, 2, v2shift, true)) {
                    if (left < SENTINEL && isDisjoint(1, 3, v3shift - left, h3shift) && isDisjoint(2, 3, v3shift - left - v2shift, h3shift - h2shift)) enqueue(getState(v2shift, v3shift - left, h2shift, h3shift));
                    if (right < SENTINEL && isDisjoint(1, 3, v3shift + right, h3shift) && isDisjoint(2, 3, v3shift + right - v2shift, h3shift - h2shift)) enqueue(getState(v2shift, v3shift + right, h2shift, h3shift));
                }
                
                down = Math.min(getDelta(1, 3, h3shift, 0, DOWN), getDelta(2, 3, h3shift, h2shift, DOWN));
                up = Math.min(getDelta(1, 3, h3shift, 0, UP), getDelta(2, 3, h3shift, h2shift, UP));
                if (isAligned(1, 2, h2shift, false)) {
                    if (down < SENTINEL && isDisjoint(1, 3, v3shift, h3shift - down) && isDisjoint(2, 3, v3shift - v2shift, h3shift - down - h2shift)) enqueue(getState(v2shift, v3shift, h2shift, h3shift - down));
                    if (up < SENTINEL && isDisjoint(1, 3, v3shift, h3shift + up) && isDisjoint(2, 3, v3shift - v2shift, h3shift + up - h2shift)) enqueue(getState(v2shift, v3shift, h2shift, h3shift + up));
                }
                
                // move piece 1
                left = Math.min(getDelta(1, 2, v2shift, 0, LEFT), getDelta(1, 3, v3shift, 0, LEFT));
                right = Math.min(getDelta(1, 2, v2shift, 0, RIGHT), getDelta(1, 3, v3shift, 0, RIGHT));
                if (isAligned(2, 3, v3shift - v2shift, true)) {
                    if (left < SENTINEL && isDisjoint(1, 2, v2shift - left, h2shift) && isDisjoint(1, 3, v3shift - left, h3shift)) enqueue(getState(v2shift - left, v3shift - left, h2shift, h3shift));
                    if (right < SENTINEL && isDisjoint(1, 2, v2shift + right, h2shift) && isDisjoint(1, 3, v3shift + right, h3shift)) enqueue(getState(v2shift + right, v3shift + right, h2shift, h3shift));
                }

                down = Math.min(getDelta(1, 2, h2shift, 0, DOWN), getDelta(1, 3, h3shift, 0, DOWN));
                up = Math.min(getDelta(1, 2, h2shift, 0, UP), getDelta(1, 3, h3shift, 0, UP));
                if (isAligned(2, 3, h3shift - h2shift, false)) {
                    if (down < SENTINEL && isDisjoint(1, 2, v2shift, h2shift - down) && isDisjoint(1, 3, v3shift, h3shift - down)) enqueue(getState(v2shift, v3shift, h2shift - down, h3shift - down));
                    if (up < SENTINEL && isDisjoint(1, 2, v2shift, h2shift + up) && isDisjoint(1, 3, v3shift, h3shift + up)) enqueue(getState(v2shift, v3shift, h2shift + up, h3shift + up));
                }
            }
        }
        
        return 0;
    }
    
    static void swap(int a, int b) {
        int[] temparr = v[a]; v[a] = v[b]; v[b] = temparr;
        temparr = h[a]; h[a] = h[b]; h[b] = temparr;
        int temp = c[a]; c[a] = c[b]; c[b] = temp;
        Area tempArea = pieces[a]; pieces[a] = pieces[b]; pieces[b] = tempArea;
    }
    
    static boolean isAligned(int a, int b, int shift, boolean vert) {
        for (int i = 0; i < c[a] / 2; i++) {
            for (int j = 0; j < c[b] / 2; j++) {
                if (vert) {
                    if (v[a][i] == v[b][j] + shift) return true;
                } else {
                    if (h[a][i] == h[b][j] + shift) return true;
                }
            }
        }
        return false;
    }
    
    static boolean isSeparated(int a, int b, int shift, boolean vert) {
        int amax = Integer.MIN_VALUE, amin = Integer.MAX_VALUE;
        for (int i = 0; i < c[a] / 2; i++) {
            amax = Math.max(amax, vert ? v[a][i] : h[a][i]);
            amin = Math.min(amin, vert ? v[a][i] : h[a][i]);
        }
        int bmax = Integer.MIN_VALUE, bmin = Integer.MAX_VALUE;
        for (int i = 0; i < c[b] / 2; i++) {
            bmax = Math.max(bmax, vert ? v[b][i] : h[b][i]);
            bmin = Math.min(bmin, vert ? v[b][i] : h[b][i]);
        }
        return (amax <= bmin + shift || amin >= bmax + shift);
    }
    
    static boolean isDisjoint(int a, int b, int vshift, int hshift) {
        Area area = (Area) pieces[b].clone();
        area.transform(AffineTransform.getTranslateInstance(vshift, hshift));
        area.intersect(pieces[a]);
        return area.isEmpty();
    }
    
    static long align(int N) {
        if (N == 2) {
            // move 2 right as far as possible
            int vshift;
            for (vshift = 0; vshift < 1002; vshift++) {
                if (!isDisjoint(1, 2, vshift + 1, 0)) break;
            }
            
            // move 2 up as far as possible
            int hshift;
            for (hshift = 0; hshift < 1002; hshift++) {
                if (!isDisjoint(1, 2, vshift, hshift + 1)) break;
            }
            
            return getState(vshift, 0, hshift, 0);
        } else { // N == 3
            int v2shift, v3shift;
            // move 1 left as far as possible
            for (v2shift = 0, v3shift = 0; v2shift < 1002; v2shift++, v3shift++) {
                if (!isDisjoint(1, 2, v2shift + 1, 0)) break;
                if (!isDisjoint(1, 3, v3shift + 1, 0)) break;
            }
            // move 2 right as far as possible
            for (; v2shift < 1002; v2shift++) {
                if (!isDisjoint(1, 2, v2shift + 1, 0)) break;
                if (!isDisjoint(3, 2, v2shift + 1 - v3shift, 0)) break;
            }
            // move 3 right as far as possible
            for (; v3shift < 2004; v3shift++) {
                if (!isDisjoint(1, 3, v3shift + 1, 0)) break;
                if (!isDisjoint(2, 3, v3shift + 1 - v2shift, 0)) break;
            }
            
            int h2shift, h3shift;
            // move 1 down as far as possible
            for (h2shift = 0, h3shift = 0; h2shift < 1002; h2shift++, h3shift++) {
                if (!isDisjoint(1, 2, v2shift, h2shift + 1)) break;
                if (!isDisjoint(1, 3, v3shift, h3shift + 1)) break;
            }
            // move 2 up as far as possible
            for (; h2shift < 1002; h2shift++) {
                if (!isDisjoint(1, 2, v2shift, h2shift + 1)) break;
                if (!isDisjoint(3, 2, v2shift - v3shift, h2shift + 1 - h3shift)) break;
            }
            // move 3 up as far as possible
            for (; h3shift < 2004; h3shift++) {
                if (!isDisjoint(1, 3, v3shift, h3shift + 1)) break;
                if (!isDisjoint(2, 3, v3shift - v2shift, h3shift + 1 - h2shift)) break;
            }
            
            return getState(v2shift, v3shift, h2shift, h3shift);
        }
    }
    
    static long getState(long v2shift, long v3shift, long h2shift, long h3shift) {
        return ((v2shift + 2048) << 36L) + ((v3shift + 2048) << 24L) + ((h2shift + 2048) << 12L) + ((h3shift + 2048) << 0L);
    }
}
