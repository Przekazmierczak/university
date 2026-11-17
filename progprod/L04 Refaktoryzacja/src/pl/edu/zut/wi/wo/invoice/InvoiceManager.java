package pl.edu.zut.wi.wo.invoice;

import java.time.LocalDate;

public class InvoiceManager {

	public static void printOwing(Invoice invoice) {
		printTitle();
		double outstanding = calculateDue(invoice);
		setDate(invoice);
		printDetails(invoice, outstanding);
	}

	static void printTitle() {
		System.out.println("************************");
		System.out.println("* Rachunek dla klienta *");
		System.out.println("************************");
	}

	static double calculateDue(Invoice invoice) {
		double outstanding = 0;
		for (Order o : invoice.getOrders()) {
			outstanding += o.getAmount();
		}
		return outstanding;
	}

	static void setDate(Invoice invoice) {
		LocalDate today = LocalDate.now();
		invoice.setDueDate(today.plusDays(30));
	}

	static void printDetails(Invoice invoice, Double outstanding) {
		System.out.println(String.format("nazwa: %s", invoice.getCustomer()));
		System.out.println(String.format("kwota: %.2f", outstanding));
		System.out.println(String.format("płatność do: %s", invoice.getDueDate()));
	}

}
