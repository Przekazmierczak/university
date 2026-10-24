package pl.edu.zut.wo.wzorce.symulator;

public class Kaczka {
	LatanieInterfejs latanieInt;
	KwakanieInterfejs kwakanieInt;
	
    void pływaj() {
    	System.out.println("Pływam jak kaczka.");
    }
    void wyświetl() {
    	System.out.println("Wyglądam jak kaczka.");
    }
    
    void wykonajKwacz() {
    	kwakanieInt.kwacz();
    }
    
    void wykonajLeć() {
    	latanieInt.leć();
    }
    
    void ustawKwaczInt(KwakanieInterfejs kwak) {
    	kwakanieInt = kwak;
    }
    
    void ustawLećInt(LatanieInterfejs lot) {
    	latanieInt = lot;
    }
}
