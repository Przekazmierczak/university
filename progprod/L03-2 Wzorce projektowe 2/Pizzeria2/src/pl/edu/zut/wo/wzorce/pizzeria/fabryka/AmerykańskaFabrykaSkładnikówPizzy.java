package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.Bakłażany;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ciasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.GrubeChrupkieCiasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.CzarneOliwki;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Małże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Szpinak;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.PlastryPepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sery;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.SerMozzarella;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.SerParmezan;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sos;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.SosZPomidorówŚliwkowych;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Warzywa;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.MrożoneMałże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Przyprawy;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Oregano;

public class AmerykańskaFabrykaSkładnikówPizzy implements FabrykaSkładnikówPizzy {
	public Ciasto utwórzCiasto() {
		return new GrubeChrupkieCiasto();
	}

	public Sos utwórzSos() {
		return new SosZPomidorówŚliwkowych();
	}

	public Sery[] utwórzSery() {
		Sery sery[] = { new SerMozzarella(), new SerParmezan() };
		return sery;
	}

	public Warzywa[] utwórzWarzywa() {
		Warzywa warzywa[] = { new Bakłażany(), new Szpinak(), new CzarneOliwki() };
		return warzywa;
	}

	public Pepperoni utwórzPepperoni() {
		return new PlastryPepperoni();
	}

	public Małże utwórzMałże() {
		return new MrożoneMałże();
	}
	
	public Przyprawy[] utwórzPrzyprawy() {
		Przyprawy przyprawy[] = { new Oregano() };
		return przyprawy;
	}
}