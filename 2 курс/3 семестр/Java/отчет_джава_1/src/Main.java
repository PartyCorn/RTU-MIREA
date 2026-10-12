public class Main {
    public static void main(String[] args) {
        Car car1 = new Car();
        Car car2 = new Car("Toyota Camry", "А777АА777", "Черный", 2022);
        Car car3 = new Car("Lada Granta", 2023);

        car3.setLicense("Е123КХ99");

        System.out.println(car1.To_String());
        System.out.println("Возраст машины: " + car1.getAge());
        System.out.println(car2.To_String());
        System.out.println("Возраст машины: " + car2.getAge());
        System.out.println(car3.To_String());
    }
}
