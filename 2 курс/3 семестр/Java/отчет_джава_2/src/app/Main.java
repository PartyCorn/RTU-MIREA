package app;

import vehicles.Vehicle;
import vehicles.Car;
import vehicles.ElectricCar;

public class Main {
    public static void main(String[] args) {
        // полиморфизм - тип Vehicle объект Car
        Vehicle ordinaryCar = new Car("Toyota Camry", "A123BC", "Black", 2020,
                "Иван", 123456, "Бензин");

        // так же для ElectricCar
        Vehicle tesla = new ElectricCar("Tesla Model S", "E777EE", "White", 2023,
                "Илон", 777777, 100);

        ordinaryCar.setOwnerName("Петр");
        ordinaryCar.setColor("Red");

        tesla.setOwnerName("Илон Маск");
        // у Vehicle нет этого метода, поэтому нужно привести тип к электрокару
        ElectricCar electricCar = (ElectricCar) tesla;
        electricCar.setBatteryCapacity(120);

        System.out.println(ordinaryCar.toString());
        System.out.println(tesla.toString());
    }
}
