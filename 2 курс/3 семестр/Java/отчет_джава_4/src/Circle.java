public class Circle extends GeometricObject implements Colorable {
    private double radius;

    public Circle() { }

    public Circle(double radius) {
        this.radius = radius;
    }

    public Circle(double radius, String color, boolean filled) {
        super(color, filled);
        this.radius = (radius >= 0) ? radius : 0;
    }

    public double getRadius() { return radius; }
    public void setRadius(double radius) {
        this.radius = (radius >= 0) ? radius : 0;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }

    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }

    public double getDiameter() {
        return 2 * radius;
    }

    public void printCircle() {
        System.out.println("Круг создан " + getDateCreated() + ", радиус: " + radius);
    }

    @Override
    public void howToColor() {
        System.out.println("Раскрасьте по всей площади круга.");
    }
}
