/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem K. Kingdom Subdivision                                 */
/*                                                                */
/* Original idea        Andrew Stankevich                         */
/* Problem statement    Maxim Buzdalov                            */
/* Test set             Maxim Buzdalov                            */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Maxim Buzdalov                            */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.*;

import com.vividsolutions.jts.geom.*;
import com.vividsolutions.jts.operation.polygonize.*;

public class Check implements Checker {
    private Polygon readPolygon(InStream str, Outcome.Type type, String name) {
        int n = str.nextInt();
        if (n < 0) {
            Outcome.quit(Outcome.Type.WA, name + " has negative size");
        }
        if (n > 20000) {
            Outcome.quit(Outcome.Type.WA, name + " is too large (" + n + ")");
        }
        Coordinate[] p = new Coordinate[n + 1];
        for (int i = 0; i < n; ++i) {
            p[i] = new Coordinate(str.nextDouble(), str.nextDouble());
        }
        p[n] = p[0];
        LineString ls = new GeometryFactory().createLineString(p);
        Polygonizer polyF = new Polygonizer();
        polyF.add(ls);
        if (!polyF.getCutEdges().isEmpty()) {
            Outcome.quit(type, name + " is not a polygon (JTS -> getCutEdges() not empty)");
        }
        if (!polyF.getDangles().isEmpty()) {
            Outcome.quit(type, name + " is not a polygon (JTS -> getDangles() not empty)");
        }
        if (!polyF.getInvalidRingLines().isEmpty()) {
            Outcome.quit(type, name + " is not a polygon (JTS -> getInvalidRingLines() not empty)");
        }
        Collection<Polygon> polys = polyF.getPolygons();
        if (polys.size() != 1) {
            Outcome.quit(type, name + " is not a polygon (JTS -> getPolygons().size() == " + polys.size() + ")");
        }
        return polys.iterator().next();
    }

    @Override
    public Outcome test(InStream inf, InStream ouf, @SuppressWarnings("unused") InStream ans) {
        Polygon input = readPolygon(inf, Outcome.Type.FAIL, "Input polygon");
        Polygon poly1 = readPolygon(ouf, Outcome.Type.WA, "First polygon");
        Polygon poly2 = readPolygon(ouf, Outcome.Type.WA, "Second polygon");

        if (!poly1.touches(poly2)) {
            Outcome.quit(Outcome.Type.WA, "Either the polygons do not touch or their interiors intersect");
        }
        Geometry union = poly1.union(poly2);
        if (input.difference(union).getArea() > 1e-3 * input.getArea()) {
            Outcome.quit(Outcome.Type.WA, "Union of the polygons does not form the input polygon");
        }
        double sq1 = poly1.getArea();
        double sq2 = poly2.getArea();
        if (Math.abs(sq1 - sq2) / Math.max(sq1, sq2) > 1e-3) {
            Outcome.quit(Outcome.Type.WA, "Squares are unequal: %.8f and %.8f", sq1, sq2);
        }
        return new Outcome(Outcome.Type.OK, String.format("OK (%.8f and %.8f)", sq1, sq2));
    }
}
