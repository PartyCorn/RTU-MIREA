public class Triangle extends GeometricObject implements Colorable {
    private final double side1;
    private final double side2;
    private final double side3;

    public Triangle() {
        this.side1 = 1.0;
        this.side2 = 1.0;
        this.side3 = 1.0;
    }

    public Triangle(double side1, double side2, double side3) throws IllegalTriangleException {
        checkSides(side1, side2, side3);
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }

    public Triangle(double side1, double side2, double side3, String color, boolean filled) throws IllegalTriangleException {
        super(color, filled);
        checkSides(side1, side2, side3);
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
    }

    private void checkSides(double s1, double s2, double s3) throws  IllegalTriangleException {
        if (s1 + s2 <= s3 && s1 + s3 <= s2 && s2 + s3 <= s1) {
            throw new IllegalTriangleException("Некорректные стороны для треугольника.");
        }
    }

    public double getSide1() { return side1; }
    public double getSide2() { return side2; }
    public double getSide3() { return side3; }

    public double getArea() {
        double s = this.getPerimeter() / 2;
        return Math.sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    public double getPerimeter() {
        return side1 + side2 + side3;
    }

    @Override
    public String toString() {
        return "Треугольник: сторона1 = " + side1 + " сторона2 = " +
        side2 + " сторона3 = " + side3;
    }

    @Override
    public void howToColor() {
        System.out.println("Раскрасьте все три стороны.");
    }
}
