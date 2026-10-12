package vehicles;

public abstract class Vehicle {
    private String model;
    private String license;
    private String color;
    private int year;
    private String ownerName;
    private int insuranceNumber;
    protected String engineType;

    public abstract String vehicleType();

    public String getModel() { return model; }
    public void setModel(String model) {
        this.model = model;
    }

    public String getLicense() { return license; }
    public void setLicense(String license) {
        this.license = license;
    }

    public String getColor() { return color; }
    public void setColor(String color) {
        this.color = color;
    }

    public int getYear() { return year; }
    public void setYear(int year) {
        this.year = year;
    }

    public String getOwnerName() { return ownerName; }
    public void setOwnerName(String ownerName) {
        this.ownerName = ownerName;
    }

    public int getInsuranceNumber() { return insuranceNumber; }
    public void setInsuranceNumber(int insuranceNumber) {
        this.insuranceNumber = insuranceNumber;
    }

    public String getEngineType() { return engineType; }
    public void setEngineType(String engineType) {
        this.engineType = engineType;
    }

    @Override
    public String toString() {
        return "Тип: " + vehicleType() +
                ", Модель: " + model +
                ", Номер: " + license +
                ", Цвет: " + color +
                ", Год: " + year +
                ", Владелец: " + ownerName +
                ", Страховка: " + insuranceNumber +
                ", Двигатель: " + engineType;
    }
}
