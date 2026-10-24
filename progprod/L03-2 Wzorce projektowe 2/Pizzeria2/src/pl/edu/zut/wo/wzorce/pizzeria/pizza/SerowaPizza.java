package pl.edu.zut.wo.wzorce.pizzeria.pizza;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;

public class SerowaPizza extends Pizza {
	FabrykaSkładnikówPizzy fabrykaSkładników;

	public SerowaPizza(FabrykaSkładnikówPizzy fabrykaSkładników) {
		this.fabrykaSkładników = fabrykaSkładników;
	}

	@Override
	public void przygotowanie() {
		ciasto = fabrykaSkładników.utwórzCiasto();
		sos = fabrykaSkładników.utwórzSos();
		sery = fabrykaSkładników.utwórzSery();
		przyprawy = fabrykaSkładników.utwórzPrzyprawy();
	}

}
