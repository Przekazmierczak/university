package pl.edu.zut.wi.wo.invoice.tests;

import static org.junit.Assert.assertEquals;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.time.LocalDate;
import java.util.Arrays;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import pl.edu.zut.wi.wo.invoice.Invoice;
import pl.edu.zut.wi.wo.invoice.InvoiceManager;
import pl.edu.zut.wi.wo.invoice.Order;

public class InvoiceMainTests {
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private final PrintStream originalOut = System.out;

	@Before
	public void setUpStreams() {
	    System.setOut(new PrintStream(outContent));
	}

	@After
	public void restoreStreams() {
	    System.setOut(originalOut);
	}
	@Test
	public void testMain() {
		Invoice invoice = new Invoice("Klient sp. z o.o.", Arrays.asList(new Order [] {
				new Order(10), 
				new Order(20), 
				new Order(30)}));
		InvoiceManager.printOwing(invoice);
		String separator = System.lineSeparator();
		LocalDate today = LocalDate.now();
		assertEquals("************************" + separator + 
				"* Rachunek dla klienta *" + separator + 
				"************************"+ separator + 
				"nazwa: Klient sp. z o.o."+ separator + 
				"kwota: 60.00" + separator + 
				"płatność do: " + today.plusDays(30) + separator,
				outContent.toString());
	}

}
