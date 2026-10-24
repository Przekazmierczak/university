package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.fabryka.FabrykaSkładnikówPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.fabryka.AmerykańskaFabrykaSkładnikówPizzy;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.OwoceMorzaPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.PepperoniPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.SerowaPizza;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.WegetariańskaPizza;

public class AmerykańskaPizzeria extends Pizzeria {
	protected Pizza utwórzPizza(String item) {
		Pizza pizza = null;
		FabrykaSkładnikówPizzy fabrykaSkładników = new AmerykańskaFabrykaSkładnikówPizzy();
		if (item.equals("serowa")) {
			pizza = new SerowaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Amerykańska Pizza Serowa");
		} else if (item.equals("wegetariańska")) {
			pizza = new WegetariańskaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Amerykańska Pizza Wegetariańska");
		} else if (item.equals("owoce morza")) {
			pizza = new OwoceMorzaPizza(fabrykaSkładników);
			pizza.ustawNazwa("Amerykańska Pizza Owoce Morza");
		} else if (item.equals("pepperoni")) {
			pizza = new PepperoniPizza(fabrykaSkładników);
			pizza.ustawNazwa("Amerykańska Pizza Pepperoni");
		}
		return pizza;
	}
}