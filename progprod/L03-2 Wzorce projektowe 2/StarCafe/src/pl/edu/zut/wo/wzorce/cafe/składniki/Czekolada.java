package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class Czekolada extends SkładnikDekorator {
	
	protected Napój napój;
	
	public Czekolada(Napój napój) {
		this.napój = napój;
		opis = " + Czekolada";
	}

	public String pobierzOpis() {
		return napój.pobierzOpis() + opis;
	}
	
	public double koszt() {
		return napój.koszt() + 0.20;
	}
}
