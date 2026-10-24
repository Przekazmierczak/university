package pl.edu.zut.wo.wzorce.symulator;

public class ModelKaczki extends Kaczka {
	
	public ModelKaczki() {
		latanieInt = new LotZNapędemRakietowym();
		kwakanieInt = new NieKwacz();
	}
	
	public void wyświetl(){
		System.out.println("Wygląda jak model kaczki.");
	}
	
}