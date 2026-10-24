package pl.edu.zut.wo.wzorce.cafe;

import pl.edu.zut.wo.wzorce.cafe.napoje.Napój;
import pl.edu.zut.wo.wzorce.cafe.napoje.StarCafeSpecial;
import pl.edu.zut.wo.wzorce.cafe.napoje.MocnoPalona;
import pl.edu.zut.wo.wzorce.cafe.napoje.Bezkofeinowa;
import pl.edu.zut.wo.wzorce.cafe.napoje.Espresso;

import pl.edu.zut.wo.wzorce.cafe.składniki.Mleko;
import pl.edu.zut.wo.wzorce.cafe.składniki.Czekolada;
import pl.edu.zut.wo.wzorce.cafe.składniki.MleczkoSojowe;
import pl.edu.zut.wo.wzorce.cafe.składniki.BitaŚmietana;

public class StarCafe {
	public static void main(String... params) {
		Napój napój = new MocnoPalona();
		napój = new Czekolada(napój);
		napój = new BitaŚmietana(napój);
		System.out.println(napój.pobierzOpis() + " " + String.format("%.2f", napój.koszt()) + "zł");
		
		Napój napój2 = new StarCafeSpecial();
		napój2 = new Czekolada(napój2);
		napój2 = new MleczkoSojowe(napój2);
		System.out.println(napój2.pobierzOpis() + " " + String.format("%.2f", napój2.koszt()) + "zł");
		
		Napój napój3 = new Bezkofeinowa();
		napój3 = new Mleko(napój3);
		napój3 = new Mleko(napój3);
		napój3 = new Mleko(napój3);
		napój3 = new BitaŚmietana(napój3);
		System.out.println(napój3.pobierzOpis() + " " + String.format("%.2f", napój3.koszt()) + "zł");
	}
}