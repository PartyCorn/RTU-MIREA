import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IllegalTriangleException {
        Scanner sc = new Scanner(System.in);

        System.out.print("Введите 3 стороны треугольника, цвет и заливку (через пробел): ");
        double s1 = sc.nextDouble();
        double s2 = sc.nextDouble();
        double s3 = sc.nextDouble();
        String color = sc.next();
        boolean filled = sc.nextBoolean();

        Triangle t = new Triangle(s1, s2, s3, color, filled);
        System.out.println(t + "\nПлощадь: " + t.getArea() + "\nПериметр: " + t.getPerimeter());

        Circle c1 = new Circle(5);
        Circle c2 = new Circle(3);
        System.out.println("Больший круг (радиус): " + ((Circle) GeometricObject.max(c1, c2)).getRadius());

        Rectangle r1 = new Rectangle(4, 5);
        Rectangle r2 = new Rectangle(2, 8);
        System.out.println("Больший прямоугольник (площадь): " + GeometricObject.max(r1, r2).getArea());

        ComparableCircle cc1 = new ComparableCircle(4);
        ComparableCircle cc2 = new ComparableCircle(6);
        System.out.println("Больший ComparableCircle: " + ((ComparableCircle) GeometricObject.max(cc1, cc2)).getRadius());

        int res = c1.compareTo(r1);
        System.out.println(res > 0 ? "Круг больше" : res < 0 ? "Прямоугольник больше" : "Равны");
    }
}
