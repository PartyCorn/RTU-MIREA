package vehicles;

public class ElectricCar extends Car implements ElectricVehicle {
    private int batteryCapacity;

    public ElectricCar() {
        super();
    }

    public ElectricCar(String model, String license, String color, int year,
                       String ownerName, int insuranceNumber, int batteryCapacity) {
        super(model, license, color, year, ownerName, insuranceNumber, "Electric");
        setBatteryCapacity(batteryCapacity);
    }

    public int getBatteryCapacity() { return batteryCapacity; }
    public void setBatteryCapacity(int butteryCapacity) {
        this.batteryCapacity = butteryCapacity;
    }

    @Override
    public String vehicleType() {
        return "Electric Car";
    }

    @Override
    public String toString() {
        return super.toString() + ", Емкость батареи: " + batteryCapacity + " кВтч";
    }
}
