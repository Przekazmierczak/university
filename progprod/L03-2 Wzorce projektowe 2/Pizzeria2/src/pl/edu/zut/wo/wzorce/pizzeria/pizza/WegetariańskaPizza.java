package pl.edu.zut.wo.wzorce.pizzeria.pizza;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;

public class WegetariańskaPizza extends Pizza {
	FabrykaSkładnikówPizzy fabrykaSkładników;

	public WegetariańskaPizza(FabrykaSkładnikówPizzy fabrykaSkładników) {
		this.fabrykaSkładników = fabrykaSkładników;
	}

	@Override
	public void przygotowanie() {
		ciasto = fabrykaSkładników.utwórzCiasto();
		sos = fabrykaSkładników.utwórzSos();
		sery = fabrykaSkładników.utwórzSery();
		warzywa = fabrykaSkładników.utwórzWarzywa();
	}

}
