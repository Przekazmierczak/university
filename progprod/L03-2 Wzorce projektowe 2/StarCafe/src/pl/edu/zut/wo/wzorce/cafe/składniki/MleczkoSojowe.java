package pl.edu.zut.wo.wzorce.cafe.składniki;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;

public class MleczkoSojowe extends SkładnikDekorator {
	
	protected Napój napój;
	
	public MleczkoSojowe(Napój napój) {
		this.napój = napój;
		opis = " + Mleczko sojowe";
	}

	public String pobierzOpis() {
		return napój.pobierzOpis() + opis;
	}
	
	public double koszt() {
		return napój.koszt() + 0.15;
	}
}
