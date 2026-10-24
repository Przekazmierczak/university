package pl.edu.zut.wo.wzorce.pizzeria;

import pl.edu.zut.wo.wzorce.pizzeria.pizza.Pizza;

public class TestPizzerii2 {

	public static void main(String[] args) {
		Pizzeria pizzeria = new AmerykańskaPizzeria();
		Pizza pizza = pizzeria.zamówPizza("wegetariańska");
		System.out.println(pizza);
	}
}
