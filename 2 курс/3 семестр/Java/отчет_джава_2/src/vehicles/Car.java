package vehicles;

public class Car extends Vehicle {
    public Car() {
        super();
    }

    public Car(String model, String license, String color, int year,
               String ownerName, int insuranceNumber, String engineType) {
        setModel(model);
        setLicense(license);
        setColor(color);
        setYear(year);
        setOwnerName(ownerName);
        setInsuranceNumber(insuranceNumber);
        setEngineType(engineType);
    }

    @Override
    public String vehicleType() {
        return "Car";
    }
}
