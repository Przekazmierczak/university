package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class BitaŚmietana extends SkładnikDekorator {
	
	protected Napój napój;
	
	public BitaŚmietana(Napój napój) {
		this.napój = napój;
		opis = " + Bita śmietana";
	}

	public String pobierzOpis() {
		return napój.pobierzOpis() + opis;
	}
	
	public double koszt() {
		return napój.koszt() + 0.10;
	}
}
