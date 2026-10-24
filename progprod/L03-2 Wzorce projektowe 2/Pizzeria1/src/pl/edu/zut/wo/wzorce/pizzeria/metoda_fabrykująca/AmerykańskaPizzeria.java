package pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.AmerykańskaOwoceMorzaPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.AmerykańskaPepperoniPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.AmerykańskaSerowaPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.AmerykańskaWegetariańskaPizza;

public class AmerykańskaPizzeria extends Pizzeria {

	Pizza utwórzPizza(String typ) {
		Pizza pizza = null;
		if (typ.equals("serowa")) {
			pizza = new AmerykańskaSerowaPizza();
		} else if (typ.equals("pepperoni")) {
			pizza = new AmerykańskaPepperoniPizza();
		} else if (typ.equals("owocemorza")) {
			pizza = new AmerykańskaOwoceMorzaPizza();
		} else if (typ.equals("wegetariańska")) {
			pizza = new AmerykańskaWegetariańskaPizza();
		}
		return pizza;
	}
}
