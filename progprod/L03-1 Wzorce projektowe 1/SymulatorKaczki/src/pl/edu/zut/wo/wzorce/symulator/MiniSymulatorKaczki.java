package pl.edu.zut.wo.wzorce.symulator;

public class MiniSymulatorKaczki {

	public static void main(String[] args) {
		Kaczka dzika = new DzikaKaczka();
		dzika.wyświetl();
		dzika.kwakanieInt.kwacz();
		dzika.latanieInt.leć();
		
		Kaczka gumowa = new GumowaKaczka();
		gumowa.wyświetl();
		gumowa.kwakanieInt.kwacz();
		gumowa.latanieInt.leć();
		
		Kaczka model = new ModelKaczki();
		model.wyświetl();
		model.kwakanieInt.kwacz();
		model.ustawKwaczInt(new Kwacz());
		model.kwakanieInt.kwacz();
		model.latanieInt.leć();
		model.ustawLećInt(new NieLatam());
		model.latanieInt.leć();
	}
}
