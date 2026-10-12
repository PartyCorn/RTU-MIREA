package bikeproject;

public class Bike implements BikeParts {

	private String handleBars, frame, tyres, seatType;
	private int NumGears;
	private final String make;

	public Bike(){
		this.make = BikeParts.MAKE;
	}

	public Bike(String handleBars, String frame, String tyres, String seatType, int numGears) {
		this.handleBars = handleBars;
		this.frame = frame;
		this.tyres = tyres;
		this.seatType = seatType;
		NumGears = numGears;
		this.make = BikeParts.MAKE;
	}

	public String getMake() { return this.make; }
	public String getHandleBars() { return this.handleBars; }
	public String getFrame() { return this.frame; }
	public String getTyres() { return this.tyres; }
	public String getSeatType() { return this.seatType; }
	public int getNumGears() { return this.NumGears; }

	protected void printDescription()
	{
		System.out.println("\n" + this.make + "\n"
				          + "This bike has " + this.handleBars + " handlebars on a "
				          + this.frame + " frame with " + this.NumGears + " gears."
				          + "\nIt has a " + this.seatType + " seat with " + this.tyres + " tyres.");
	}
}
