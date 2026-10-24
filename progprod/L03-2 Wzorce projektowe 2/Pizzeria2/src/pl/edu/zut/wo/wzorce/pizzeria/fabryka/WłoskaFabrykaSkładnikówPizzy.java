package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.Cebula;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ciasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.CienkieChrupkieCiasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.CzerwonaPapryka;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Czosnek;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Małże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pieczarki;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.PlastryPepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Przyprawy;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sery;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.SerReggiano;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sos;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.SosMarinara;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Warzywa;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.ŚwieżeMałże;

public class WłoskaFabrykaSkładnikówPizzy implements FabrykaSkładnikówPizzy {
	public Ciasto utwórzCiasto() {
		return new CienkieChrupkieCiasto();
	}

	public Sos utwórzSos() {
		return new SosMarinara();
	}

	public Sery[] utwórzSery() {
		Sery sery[] = { new SerReggiano() };
		return sery;
	}

	public Warzywa[] utwórzWarzywa() {
		Warzywa warzywa[] = { new Czosnek(), new Cebula(), new Pieczarki(), new CzerwonaPapryka() };
		return warzywa;
	}

	public Pepperoni utwórzPepperoni() {
		return new PlastryPepperoni();
	}

	public Małże utwórzMałże() {
		return new ŚwieżeMałże();
	}
	
	public Przyprawy[] utwórzPrzyprawy() {
		Przyprawy przyprawy[] = {};
		return przyprawy;
	}
}