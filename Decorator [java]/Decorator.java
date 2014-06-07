/********************************************
 *                                          *
 * @author Izabela Orlowska                 *
 *                                          *
 * A Decorator Design Pattern example.      *
 *                                          *
 ********************************************
 *                                          *
 * Wszystkie klasy w jednym pliku, zeby	    *
 * uniknac zamieszania.	                    *
 *                                          *
 ********************************************/

/**
 * Interfejs dla rowerkow.
 */
interface Bike {
	public abstract String getDescription();
}

/**
 * Podstawowey rowerek.
 */
class BasicBike implements Bike {
	@Override
	public String getDescription() {
		return "A bike";
	}
}
/**
 * Klasa abstrakcyjna dekoratora dla rowerow. Konstruktor bierze i zapamietuje
 * rowerek, ktory ma dekorowac.
 */
abstract class BikeDecorator implements Bike {
    protected Bike decoratedBike;
 
    public BikeDecorator (Bike decoratedBike) {
        this.decoratedBike = decoratedBike;
    }
    
    @Override
    public String getDescription() {
        return decoratedBike.getDescription();
    }
}
/**
 * Sportowy rowerek.
 */
class SportsBikeDecorator extends BikeDecorator {
    public SportsBikeDecorator (Bike decoratedBike) {
        super(decoratedBike);
    }
 
    @Override
    public String getDescription() {
        return super.getDescription() + ", sport edition";
    }
}
/**
 * Rowerek dla dzieci.
 */
class ChildrensBikeDecorator extends BikeDecorator {
    public ChildrensBikeDecorator (Bike decoratedBike) {
        super(decoratedBike);
    }
 
    @Override
    public String getDescription() {
        return super.getDescription() + " for children";
    }
}
	
public class Decorator {
	public static void main(String[] args) {
		//tworzymy rowerek sportowy dla dziecka
		Bike rowerekNaKomunie = new ChildrensBikeDecorator(
				new SportsBikeDecorator(new BasicBike()));
		
		//wypisujemy jego opis
		System.out.println(rowerekNaKomunie.getDescription());
	}

}
