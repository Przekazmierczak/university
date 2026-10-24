package pl.edu.zut.wo.wzorce.pizzeria.pizza;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ciasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Małże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sery;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sos;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Warzywa;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Przyprawy;

public abstract class Pizza {
	String nazwa;
	Ciasto ciasto;
	Sos sos;
	Warzywa warzywa[];
	Sery sery[];
	Pepperoni pepperoni;
	Małże małże;
	Przyprawy przyprawy[];

	public abstract void przygotowanie();

	public void pieczenie() {
		System.out.println("Pieczenie: 25 minut w temperaturze 180 stopni Celsjusza");
	}

	public void krojenie() {
		System.out.println("Krojenie pizzy na 8 kawałków");
	}

	public void pakowanie() {
		System.out.println("Pakowanie pizzy w oficjalne pudełko naszej sieci Pizzerii.");
	}

	public void ustawNazwa(String nazwa) {
		this.nazwa = nazwa;
	}

	public String pobierzNazwa() {
		return nazwa;
	}

	public String toString() {
		// kod wyświetlający informacje o pizzy
		String warz = (warzywa == null) ? null : "";
		String ser =  (sery == null) ? null : "";
		String przy = (przyprawy == null) ? null : "";
		if (warzywa != null) {
			int i = 0;
			for (Warzywa w : warzywa) {
				warz += (i++ == 0 ? "" : ", ") + w.getClass().getSimpleName();
			}
		}
		if (sery != null) {
			int i = 0;
			for (Sery s : sery) {
				ser += (i++ == 0 ? "" : ", ") + s.getClass().getSimpleName();
			}
		}
		if (przyprawy != null) {
			int i = 0;
			for (Przyprawy p : przyprawy) {
				przy += (i++ == 0 ? "" : ", ") + p.getClass().getSimpleName();
			}
		}
		String info = String.format("%s\n"
				+ "ciasto: %s\n"
				+ "sos: %s\n"
				+ "warzywa: %s\n"
				+ "sery: %s\n"
				+ "pepperoni: %s\n"
				+ "małże: %s\n"
				+ "przyprawy: %s",
				nazwa,
				ciasto == null ? "brak" : ciasto.getClass().getSimpleName(),
				sos == null ? "brak" : sos.getClass().getSimpleName(),
				warz == null ? "brak" : warz, 
				ser == null ? "brak" : ser,
				pepperoni == null ? "brak" : pepperoni.getClass().getSimpleName(),
				małże == null ? "brak" : małże.getClass().getSimpleName(),
				przy == null ? "brak" : przy); 
		return info;
	}
}