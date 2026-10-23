public class PrototypeDemo {
    public static void main(String[] args) {
        Circle circle = new Circle(5);
        Circle circleCopy = (Circle) circle.clone();
        circleCopy.setRadius(10);

        Rectangle rect = new Rectangle(4, 6);
        Rectangle rectCopy = (Rectangle) rect.clone();
        rectCopy.setSize(8, 12);

        System.out.println("Оригинал: " + circle);
        System.out.println("Копия:    " + circleCopy);
        System.out.println("Оригинал: " + rect);
        System.out.println("Копия:    " + rectCopy);
    }
}
