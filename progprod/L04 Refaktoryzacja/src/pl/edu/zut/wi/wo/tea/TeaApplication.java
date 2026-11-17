package pl.edu.zut.wi.wo.tea;

public class TeaApplication {

	public static void main(String[] args) {
		System.out.println(String.format("firstMethod=%.2f", firstMethod()));
		System.out.println(String.format("secondMethod=%.2f", secondMethod()));
		System.out.println(String.format("thirdMethod=%.2f", thirdMethod()));
	}

	public static double firstMethod() {
		ReadingRecord aReading = new ReadingRecord("ivan", 10, 2, 2019);
		double baseCharge = aReading.baseRate() * aReading.quantity;
		return baseCharge;
	}

	public static double secondMethod() {
		ReadingRecord aReading = new ReadingRecord("ivan", 10, 2, 2019);
		double taxableCharge = aReading.taxableCharge;
		return taxableCharge;
	}
	
	public static double thirdMethod() {
		ReadingRecord aReading = new ReadingRecord("ivan", 10, 2, 2019);
		double basicChargeAmount = aReading.baseCharge;
		return basicChargeAmount;
	}
}
