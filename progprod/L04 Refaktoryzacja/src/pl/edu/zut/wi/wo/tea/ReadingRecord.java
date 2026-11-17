package pl.edu.zut.wi.wo.tea;

public class ReadingRecord {
	String customer;
	int quantity;
	int month;
	int year;
	
	double baseCharge;
	double taxableCharge;
	
	public ReadingRecord(String customer, int quantity, int month, int year) {
		this.customer = customer;
		this.quantity = quantity;
		this.month = month;
		this.year = year;
		
		calculateBaseCharge();
		calculatetaxableCharge();
	}
	
	public void calculateBaseCharge() {
		baseCharge =  baseRate() * quantity;
	}
	
	public void calculatetaxableCharge() {
		taxableCharge =  Math.max(0, baseCharge - taxThreshold());
	}

	public double taxThreshold() {
		return 100;
	}

	public double baseRate() {
		return 12.5;
	}
}
