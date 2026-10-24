package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca.Pizzeria;
import pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca.WłoskaPizzeria;
import pl.edu.zut.wo.wzorce.pizzeria.metoda_fabrykująca.AmerykańskaPizzeria;
import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii {

	public static void main(String[] args) {
		System.out.println("WŁOSKA");
		Pizzeria pizzeria = new WłoskaPizzeria();
		Pizza pizza = pizzeria.zamówPizza("serowa");
		System.out.println(pizzeria.getClass().getSimpleName() + " wyprodukowała " + pizza.getClass().getSimpleName());
		
		System.out.println("AMERYKAŃSKA");
		Pizzeria pizzeria2 = new AmerykańskaPizzeria();
		Pizza pizza2 = pizzeria2.zamówPizza("serowa");
		System.out.println(pizzeria2.getClass().getSimpleName() + " wyprodukowała " + pizza2.getClass().getSimpleName());
	}
}
