package app;

import vehicles.Vehicle;
import vehicles.Car;
import vehicles.ElectricCar;

public class TestCar {
    public static void main(String[] args) {
        Vehicle ordinaryCar = new Car("Toyota Camry", "A123BC", "Black",
                2020, "Иван", 123456);
        Vehicle tesla = new ElectricCar("Tesla Model S", "E777EE", "White",
                2023, "Илон", 777777, 100);

        ordinaryCar.setOwnerName("Петр");
        ordinaryCar.setYear(2022);

        tesla.setOwnerName("Илон Маск");
        tesla.setYear(2025);

        ordinaryCar.setInsuranceNumber(654321);
        tesla.setInsuranceNumber(999999);

        ElectricCar electricTesla = (ElectricCar) tesla;

        int currentBattery = electricTesla.getBatteryCapacity();
        System.out.println("Текущая емкость батареи Теслы: " + currentBattery + " кВтч");

        electricTesla.setBatteryCapacity(120);

        System.out.println(ordinaryCar.toString());
        System.out.println(tesla.toString());
    }
}
