package pl.edu.zut.wi.wo.order;

public class OrderCalculator {

	public static double price(Order order) {
		final double base = order.getQuantity() * order.getItemPrice();
		final double discount = Math.max(0, order.getQuantity() - 500) * order.getItemPrice() * 0.05;
		final double delivery = Math.min(order.getQuantity() * order.getItemPrice() * 0.1, 100);
		return base - discount + delivery;
	}
}
