import java.util.Date;

public abstract class GeometricObject implements Comparable<GeometricObject> {
    private String color;
    private boolean filled;
    private final Date dateCreated;

    public GeometricObject() {
        this.dateCreated = new Date();
    }

    public GeometricObject(String color, boolean filled) {
        this.dateCreated = new Date();
        this.color = color;
        this.filled = filled;
    }

    public String getColor() { return color; }
    public void setColor(String color) {
        this.color = color;
    }

    public boolean isFilled() { return filled; }
    public void setFilled(boolean filled) {
        this.filled = filled;
    }

    public Date getDateCreated() { return dateCreated; }

    public abstract double getArea();
    public abstract double getPerimeter();

    @Override
    public int compareTo(GeometricObject o) {
        return Double.compare(this.getArea(), o.getArea());
    }

    public static GeometricObject max(GeometricObject o1, GeometricObject o2) {
        return (o1.compareTo(o2) >= 0) ? o1 : o2;
    }

    @Override
    public String toString() {
        return "создан: " + dateCreated + "\nцвет: " + color + ", залит: " + filled;
    }
}
