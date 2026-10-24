package pl.edu.zut.wo.wzorce.pizzeria.pizza;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;

public class PepperoniPizza extends Pizza {
	FabrykaSkładnikówPizzy fabrykaSkładników;

	public PepperoniPizza(FabrykaSkładnikówPizzy fabrykaSkładników) {
		this.fabrykaSkładników = fabrykaSkładników;
	}

	@Override
	public void przygotowanie() {
		ciasto = fabrykaSkładników.utwórzCiasto();
		sos = fabrykaSkładników.utwórzSos();
		sery = fabrykaSkładników.utwórzSery();
		warzywa = fabrykaSkładników.utwórzWarzywa();
		pepperoni = fabrykaSkładników.utwórzPepperoni();
	}

}
