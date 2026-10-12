public class ColorableTestMain {
    public static void main(String[] args) {
        try {
            GeometricObject[] objects = {
                    new Square(4.5),
                    new Circle(3.0),
                    new ComparableCircle(4.0),
                    new Rectangle(2.0, 5.0),
                    new Triangle(3.0, 4.0, 5.0)
            };

            for (GeometricObject obj : objects) {
                System.out.println("\nФигура: " + obj.getClass().getSimpleName());
                System.out.printf("Площадь: %.2f\n", obj.getArea());
                ((Colorable) obj).howToColor();
            }

        } catch (IllegalTriangleException e) {
            System.err.println("Ошибка инициализации данных: " + e.getMessage());
        }
    }
}
