package vehicles;

public class Car extends Vehicle {
    public Car() {
        super();
        setEngineType("Combustion");
    }

    public Car(String model, String license, String color, int year,
               String ownerName, int insuranceNumber) {
        this(model, license, color, year, ownerName, insuranceNumber, "Combustion");
    }

    // для ElectricCar
    protected Car(String model, String license, String color, int year,
                  String ownerName, int insuranceNumber, String engineType) {
        setModel(model);
        setLicense(license);
        setColor(color);
        setYear(year);
        setOwnerName(ownerName);
        setInsuranceNumber(insuranceNumber);
        setEngineType(engineType); // Здесь запишется "Electric" для электрокара
    }

    @Override
    public String vehicleType() {
        return "Car";
    }
}
