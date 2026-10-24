package pl.edu.zut.wo.wzorce.pizzeria.fabryka;

import pl.edu.zut.wo.wzorce.pizzeria.składniki.Ciasto;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Małże;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Pepperoni;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Przyprawy;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sery;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Sos;
import pl.edu.zut.wo.wzorce.pizzeria.składniki.Warzywa;

public interface FabrykaSkładnikówPizzy {
	public Ciasto utwórzCiasto();

	public Sos utwórzSos();

	public Sery[] utwórzSery();

	public Warzywa[] utwórzWarzywa();

	public Pepperoni utwórzPepperoni();

	public Małże utwórzMałże();
	
	public Przyprawy[] utwórzPrzyprawy();
}