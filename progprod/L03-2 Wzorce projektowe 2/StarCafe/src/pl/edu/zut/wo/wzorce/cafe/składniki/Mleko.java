package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class Mleko extends SkładnikDekorator {
	
	protected Napój napój;
	
	public Mleko(Napój napój) {
		this.napój = napój;
		opis = " + Mleko";
	}

	public String pobierzOpis() {
		return napój.pobierzOpis() + opis;
	}
	
	public double koszt() {
		return napój.koszt() + 0.10;
	}
}
